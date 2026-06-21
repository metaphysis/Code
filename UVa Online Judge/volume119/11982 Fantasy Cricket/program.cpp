// Fantasy Cricket
// UVa ID: 11982
// Verdict: Accepted
// Submission Date: 2026-06-21
// UVa Run Time: 0.090s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    for (int tc = 1; tc <= T; ++tc) {
        string s;
        cin >> s;
        int n = (int)s.size();

        vector<long long> dp(n + 1, 0), ndp(n + 1, 0);
        dp[0] = 1; // 初始无挂起

        for (char ch : s) {
            fill(ndp.begin(), ndp.end(), 0);

            if (ch == 'E') {
                for (int j = 0; j <= n; ++j)
                    ndp[j] = (ndp[j] + dp[j]) % MOD;
            }
            else if (ch == 'U') {
                for (int j = 0; j <= n; ++j) {
                    if (dp[j] == 0) continue;
                    // 不匹配，挂起数 +1
                    if (j + 1 <= n)
                        ndp[j + 1] = (ndp[j + 1] + dp[j]) % MOD;
                    // 匹配一个旧 U
                    if (j > 0)
                        ndp[j] = (ndp[j] + dp[j] * j) % MOD;
                }
            }
            else { // 'D'
                for (int j = 1; j <= n; ++j) {
                    if (dp[j] == 0) continue;
                    // 数字 i 进入池子，挂起数不变
                    ndp[j] = (ndp[j] + dp[j] * j) % MOD;
                    // 数字 i 匹配一个旧 U，挂起数 -1
                    ndp[j - 1] = (ndp[j - 1] + dp[j] * j % MOD * j) % MOD;
                }
            }

            dp.swap(ndp);
        }

        cout << "Case " << tc << ": " << dp[0] % MOD << "\n";
    }

    return 0;
}
