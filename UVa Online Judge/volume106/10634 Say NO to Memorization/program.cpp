// Say NO to Memorization
// UVa ID: 10634
// Verdict: Accepted
// Submission Date: 2025-11-03
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
const int MAX = 2005; // 最大可能用到的组合数下标
long long combTable[MAX][MAX]; // 组合数表
// 预计算组合数表
void precomputeCombinations() {
    for (int i = 0; i < MAX; i++) {
        combTable[i][0] = combTable[i][i] = 1; // 边界条件
        for (int j = 1; j < i; j++) {
            // 使用组合数递推公式
            combTable[i][j] = combTable[i - 1][j] + combTable[i - 1][j - 1];
        }
    }
}
int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    cin.tie(NULL);
    precomputeCombinations(); // 预计算组合数
    int degree, varCount;
    while (cin >> degree >> varCount) {
        if (degree == 0 && varCount == 0) break;
        long long totalTerms = 0;
        int parity = degree % 2; // 奇偶性
        for (int k = parity; k <= varCount; k += 2) {
            int m = (degree - k) / 2; // 计算中间变量
            if (m < 0) continue; // 负值跳过
            // 累加满足条件的项数
            totalTerms += combTable[varCount][k] * combTable[m + varCount][varCount];
        }
        cout << totalTerms << "\n";
    }
    return 0;
}
