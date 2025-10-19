// Egyptian Fractions (HARD version)
// UVa ID: 12558
// Verdict: Accepted
// Submission Date: 2025-10-19
// UVa Run Time: 1.840s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <algorithm>
#include <cstring>
#include <set>
using namespace std;

typedef long long LL;

LL finalAns[1002], currentPath[1002];  // 最终答案和当前搜索路径
set<LL> bannedDenominators;            // 禁止使用的分母集合
int currentMaxDepth;                   // 当前迭代加深的最大深度

// 计算最大公约数
LL gcd(LL a, LL b) {
    return b ? gcd(b, a % b) : a;
}

// 计算第一个可能的分母下界
LL getFirstDenominator(LL numerator, LL denominator) {
    return denominator / numerator + 1;
}

// 判断当前解是否比已知最优解更好
bool isBetterSolution(int depth) {
    for (int i = depth; i >= 0; i--) {
        if (currentPath[i] != finalAns[i])
            return finalAns[0] == -1 || currentPath[i] < finalAns[i];
    }
    return false;
}

// 深度优先搜索函数
bool depthFirstSearch(int currentDepth, LL nextDenominator, LL remainingNumerator, LL remainingDenominator) {
    // 到达最大深度，检查是否找到解
    if (currentDepth == currentMaxDepth) {
        // 检查剩余分数是否能表示为单个单位分数
        if (remainingDenominator % remainingNumerator) return false;
        LL finalDenom = remainingDenominator / remainingNumerator;
        currentPath[currentDepth] = finalDenom;
        
        // 检查最终分母是否被禁止
        if (bannedDenominators.count(finalDenom)) return false;
        
        // 更新最优解
        if (isBetterSolution(currentDepth)) {
            memcpy(finalAns, currentPath, sizeof(LL) * (currentDepth + 1));
        }
        return true;
    }
    
    bool solutionFound = false;
    LL startDenom = max(nextDenominator, getFirstDenominator(remainingNumerator, remainingDenominator));
    
    // 遍历所有可能的分母
    for (LL denom = startDenom; ; denom++) {
        // 重要剪枝：检查剩余深度是否足够完成分解
        if (remainingDenominator * (currentMaxDepth + 1 - currentDepth) <= denom * remainingNumerator) break;
        
        // 跳过被禁止的分母
        if (bannedDenominators.count(denom)) continue;
        
        currentPath[currentDepth] = denom;
        
        // 计算新的剩余分数：remainingNumerator/remainingDenominator - 1/denom
        LL newDenominator = remainingDenominator * denom;
        LL newNumerator = remainingNumerator * denom - remainingDenominator;
        
        if (newNumerator < 0) continue;
        
        // 约分新分数
        LL commonDivisor = gcd(newNumerator, newDenominator);
        newNumerator /= commonDivisor;
        newDenominator /= commonDivisor;
        
        // 递归搜索
        if (depthFirstSearch(currentDepth + 1, denom + 1, newNumerator, newDenominator)) {
            solutionFound = true;
        }
    }
    
    return solutionFound;
}

int main() {
    int testCaseCount;
    cin >> testCaseCount;
    
    for (int caseIndex = 1; caseIndex <= testCaseCount; caseIndex++) {
        LL numerator, denominator, bannedCount;
        cin >> numerator >> denominator >> bannedCount;
        
        bannedDenominators.clear();
        for (int i = 0; i < bannedCount; i++) {
            LL bannedNum;
            cin >> bannedNum;
            bannedDenominators.insert(bannedNum);
        }
        
        // 迭代加深搜索：从深度1开始逐渐增加
        bool solutionFound = false;
        for (currentMaxDepth = 1; ; currentMaxDepth++) {
            memset(finalAns, -1, sizeof(finalAns));
            if (depthFirstSearch(0, getFirstDenominator(numerator, denominator), numerator, denominator)) {
                solutionFound = true;
                break;
            }
        }
        
        // 输出结果
        cout << "Case " << caseIndex << ": " << numerator << "/" << denominator << "=";
        for (int i = 0; i <= currentMaxDepth; i++) {
            if (i > 0) cout << "+";
            cout << "1/" << finalAns[i];
        }
        cout << endl;
    }
    
    return 0;
}
