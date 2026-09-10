// Vogons
// UVa ID: 13106
// Verdict: Accepted
// Submission Date: 2026-07-30
// UVa Run Time: 0.140s

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    while (cin >> n >> m) {
        vector<vector<int>> grid(n, vector<int>(m));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                cin >> grid[i][j];

        vector<long long> colVal(m, 0);
        for (int j = 0; j < m; ++j) {
            vector<long long> dpRow(n, 0);
            for (int i = 0; i < n; ++i) {
                if (i == 0) dpRow[i] = grid[i][j];
                else if (i == 1) dpRow[i] = max((long long)grid[0][j], (long long)grid[1][j]);
                else dpRow[i] = max(dpRow[i - 1], dpRow[i - 2] + (long long)grid[i][j]);
            }
            colVal[j] = dpRow[n - 1];
        }

        long long ans;
        if (m == 1) {
            ans = colVal[0];
        } else {
            const long long NEG = -4e18;
            long long dp[2][2];
            for (int a = 0; a < 2; ++a)
                for (int b = 0; b < 2; ++b)
                    dp[a][b] = NEG;
            for (int a = 0; a < 2; ++a)
                for (int b = 0; b < 2; ++b)
                    if (a + b == 1)
                        dp[a][b] = a * colVal[0] + b * colVal[1];

            for (int i = 2; i < m; ++i) {
                long long ndp[2][2];
                for (int a = 0; a < 2; ++a)
                    for (int b = 0; b < 2; ++b)
                        ndp[a][b] = NEG;
                for (int a = 0; a < 2; ++a)
                    for (int b = 0; b < 2; ++b) {
                        if (dp[a][b] == NEG) continue;
                        for (int c = 0; c < 2; ++c) {
                            if (b + c > 1) continue;
                            if (a + b + c < 1) continue;
                            ndp[b][c] = max(ndp[b][c], dp[a][b] + c * colVal[i]);
                        }
                    }
                for (int a = 0; a < 2; ++a)
                    for (int b = 0; b < 2; ++b)
                        dp[a][b] = ndp[a][b];
            }

            ans = NEG;
            for (int a = 0; a < 2; ++a)
                for (int b = 0; b < 2; ++b)
                    if (a + b >= 1)
                        ans = max(ans, dp[a][b]);
        }
        cout << ans << '\n';
    }
    return 0;
}
