// High Score
// UVa ID: 12261
// Verdict: Accepted
// Submission Date: 2026-01-21
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int calculateMinMoves(const string& name) {
    int n = name.size();
    // 1. 计算垂直移动总次数
    int verticalMoves = 0;
    for (char c : name) {
        int diff = c - 'A';
        verticalMoves += min(diff, 26 - diff);
    }
    // 2. 计算最小横向移动
    // 基本移动：从第一个走到最后一个非'A'
    int firstNonA = n, lastNonA = -1;
    for (int i = 0; i < n; ++i)
        if (name[i] != 'A') {
            firstNonA = min(firstNonA, i);
            lastNonA = max(lastNonA, i);
        }
    // 如果全是'A'，返回0
    if (firstNonA == n) return 0;
    // 初始最小移动次数
    int minMove = min(lastNonA, n - firstNonA);
    // 3. 枚举所有可能的折返策略
    // 关键思想：对于每个位置i，考虑以它为转折点
    for (int i = 0; i < n; ++i) {
        // 找到i之后第一个非'A'
        int j = i + 1;
        while (j < n && name[j] == 'A') j++;
        // 方案1: 先向右走到i，再向左走到j
        if (j < n) minMove = min(minMove, i * 2 + (n - j));
        // 方案2: 先向左走到i，再向右走到j
        // 注意：向左走到i相当于走到n-i位置（因为循环）
        if (j < n) minMove = min(minMove, (n - j) * 2 + i);
    }
    // 4. 特殊处理：连续A段在开头或结尾的情况
    // 计算开头连续A的长度
    int startA = 0;
    while (startA < n && name[startA] == 'A') startA++;
    // 如果开头有A，可以直接从结尾开始向左走
    if (startA > 0) minMove = min(minMove, n - startA);
    // 计算结尾连续A的长度
    int endA = 0;
    while (endA < n && name[n - 1 - endA] == 'A') endA++;
    // 如果结尾有A，可以少走到最后
    if (endA > 0) minMove = min(minMove, lastNonA);
    return verticalMoves + minMove;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        string name;
        cin >> name;
        cout << calculateMinMoves(name) << "\n";
    }
    return 0;
}
