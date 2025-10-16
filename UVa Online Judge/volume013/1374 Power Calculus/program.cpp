// Power Calculus
// UVa ID: 1374
// Verdict: Accepted
// Submission Date: 2025-10-16
// UVa Run Time: 0.130s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <algorithm>
using namespace std;

int target;        // 目标指数 n
int maxDepth;      // 当前迭代加深的最大深度
int currentChain[20]; // 存储当前的幂次链，currentChain[i] 表示第 i 步得到的指数

/**
 * 迭代加深搜索函数
 * @param currentStep 当前搜索的步数
 * @return 是否在当前深度限制下找到解
 */
bool idaStar(int currentStep) {
    // 如果当前步数已经达到目标，检查是否找到解
    if (currentStep == maxDepth) {
        return currentChain[currentStep] == target;
    }
    
    // 剪枝：如果当前最大值在剩余步数内即使每一步都翻倍也达不到目标，则剪枝
    // 剩余步数 = maxDepth - currentStep
    int currentMax = currentChain[currentStep];
    if ((currentMax << (maxDepth - currentStep)) < target) {
        return false;
    }
    
    // 尝试所有可能的组合：当前最大值与链中已有的每个值进行运算
    for (int i = currentStep; i >= 0; i--) {
        // 加法运算（乘法）：currentChain[currentStep] + currentChain[i]
        int nextValue = currentChain[currentStep] + currentChain[i];
        if (nextValue <= 10000) {  // 防止数值过大
            currentChain[currentStep + 1] = nextValue;
            if (idaStar(currentStep + 1)) {
                return true;
            }
        }
        
        // 减法运算（除法）：currentChain[currentStep] - currentChain[i]
        nextValue = currentChain[currentStep] - currentChain[i];
        if (nextValue > 0) {  // 结果必须为正指数
            currentChain[currentStep + 1] = nextValue;
            if (idaStar(currentStep + 1)) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    while (cin >> target && target != 0) {
        // 特殊情况：x^1 不需要任何运算
        if (target == 1) {
            cout << 0 << endl;
            continue;
        }
        
        // 初始化幂次链，起始状态为 x^1
        currentChain[0] = 1;
        maxDepth = 1;
        
        // 迭代加深搜索：从深度1开始逐步增加深度限制
        while (true) {
            if (idaStar(0)) {
                cout << maxDepth << endl;
                break;
            }
            maxDepth++;
        }
    }
    return 0;
}
