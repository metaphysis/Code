// Number String
// UVa ID: 1650
// Verdict: Accepted
// Submission Date: 2025-11-18
// UVa Run Time: 0.140s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;

int countPermutations(string s) {
    int n = s.length();
    vector<vector<int>> dp(n + 1, vector<int>(n + 2, 0));
    dp[0][1] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i + 1; j++) {
            if (s[i - 1] == 'I' || s[i - 1] == '?') {
                dp[i][j] = (dp[i][j] + dp[i - 1][j - 1]) % MOD;
            }
            if (s[i - 1] == 'D' || s[i - 1] == '?') {
                dp[i][j] = (dp[i][j] + (dp[i - 1][i] - dp[i - 1][j - 1] + MOD) % MOD) % MOD;
            }
        }
        for (int j = 1; j <= i + 1; j++)
            dp[i][j] = (dp[i][j] + dp[i][j - 1]) % MOD;
    }
    return dp[n][n + 1];
}

int main() {
    string s;
    while (cin >> s)
        cout << countPermutations(s) << endl;
    return 0;
}
