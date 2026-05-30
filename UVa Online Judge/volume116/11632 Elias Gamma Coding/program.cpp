// Elias Gamma Coding
// UVa ID: 11632
// Verdict: Accepted
// Submission Date: 2026-05-30
// UVa Run Time: 0.010s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9;

int main() {
    int n;
    while (cin >> n, n) {
        vector<int> c(n + 1);
        for (int i = 1; i <= n; ++i) cin >> c[i];
        
        // 提取实际出现的二进制长度
        vector<int> L, cnt;
        for (int i = 1; i <= n; ++i) if (c[i] > 0) {
            L.push_back(i);
            cnt.push_back(c[i]);
        }
        
        int m = L.size();
        // 前缀和，便于快速计算区间整数个数
        vector<int> pre(m + 1, 0);
        for (int i = 1; i <= m; ++i) pre[i] = pre[i - 1] + cnt[i - 1];
        
        // dp[i][j]: 用了 i 个前缀，最后一个前缀对应第 j 种长度
        vector<vector<int>> dp(m + 2, vector<int>(m + 2, INF));
        dp[0][0] = 0;
        
        for (int i = 1; i <= m; ++i) {
            for (int j = i; j <= m; ++j) {
                // k 是前一个前缀对应的种类，至少为 i-1（保证有 i-1 个不同长度）
                int startK = (i == 1) ? 0 : i - 1;
                for (int k = startK; k < j; ++k) {
                    if (dp[i - 1][k] == INF) continue;
                    int sum = pre[j] - pre[k];  // 区间 [k+1, j] 的整数个数
                    dp[i][j] = min(dp[i][j], dp[i - 1][k] + (i + L[j - 1]) * sum);
                }
            }
        }
        
        int ans = INF;
        for (int i = 1; i <= m; ++i) ans = min(ans, dp[i][m]);
        cout << ans << endl;
    }
    return 0;
}
