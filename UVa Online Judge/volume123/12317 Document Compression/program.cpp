// Document Compression
// UVa ID: 12317
// Verdict: Accepted
// Submission Date: 2025-12-26
// UVa Run Time: 0.080s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int main() {
    int m, n;
    while (cin >> m >> n and (m or n)) {
        // 读取基础文档
        vector<int> basisMasks(m);
        for (int i = 0; i < m; ++i) {
            int k, term;
            cin >> k;
            int mask = 0;
            while (k--) {
                cin >> term;
                mask |= (1 << (term - 1)); // 术语从 1 开始，映射到 0-15 位
            }
            basisMasks[i] = mask;
        }
        // DP数组，初始化为无穷大
        vector<int> dp(1 << 16, INF);
        dp[0] = 0;
        // 遍历所有状态
        for (int mask = 0; mask < (1 << 16); ++mask) {
            if (dp[mask] == INF) continue; // 无法达到的状态
            // 尝试添加每个基础文档
            for (int basis : basisMasks) {
                int newMask = mask | basis;
                if (dp[newMask] > dp[mask] + 1) {
                    dp[newMask] = dp[mask] + 1;
                }
            }
        }
        // 处理每个目标文档
        vector<int> results;
        for (int docIdx = 0; docIdx < n; ++docIdx) {
            int k, term;
            cin >> k;
            int targetMask = 0;
            while (k--) {
                cin >> term;
                targetMask |= (1 << (term - 1));
            }
            // 获取结果
            if (dp[targetMask] == INF) results.push_back(0);
            else results.push_back(dp[targetMask]);
        }
        // 输出结果
        for (size_t i = 0; i < results.size(); ++i) {
            if (i) cout << ' ';
            cout << results[i];
        }
        cout << '\n';
    }
    return 0;
}
