// Martian Mining
// UVa ID: 1366
// Verdict: Accepted
// Submission Date: 2025-11-03
// UVa Run Time: 0.070s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int n, m;
    while (cin >> n >> m && (n || m)) {
        vector<vector<int>> yey(n + 1, vector<int>(m + 1, 0));
        vector<vector<int>> blog(n + 1, vector<int>(m + 1, 0));
        // 输入 yeyenum
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j)
                cin >> yey[i][j];
        // 输入 bloggium
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j)
                cin >> blog[i][j];
        // 预处理 Y[i][j]：第 i 行前 j 列的 yeyenum 和
        vector<vector<int>> Y(n + 1, vector<int>(m + 1, 0));
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j)
                Y[i][j] = Y[i][j - 1] + yey[i][j];
        // 预处理 B[i][j]：第 j 列前 i 行的 bloggium 和
        vector<vector<int>> B(n + 1, vector<int>(m + 1, 0));
        for (int j = 1; j <= m; ++j)
            for (int i = 1; i <= n; ++i)
                B[i][j] = B[i - 1][j] + blog[i][j];
        // DP
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j)
                dp[i][j] = max(dp[i - 1][j] + Y[i][j], dp[i][j - 1] + B[i][j]);
        cout << dp[n][m] << "\n";
    }
    return 0;
}
