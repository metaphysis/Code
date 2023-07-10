// Strings
// UVa ID: 11081
// Verdict: Accepted
// Submission Date: 2023-07-09
// UVa Run Time: 0.330s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include<bits/stdc++.h>
using namespace std;
int n1, n2, n3, MOD = 10007;
string s1, s2, s3;
int dp[64][64][64], dp1[64][64][64], dp2[64][64][64];
int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int T; cin >> T;
    while (T--) {
        cin >> s1 >> s2 >> s3;
        memset(dp, 0, sizeof dp);
        memset(dp1, 0, sizeof dp1);
        memset(dp2, 0, sizeof dp2);
        n1 = (int)s1.length(), n2 = (int)s2.length(), n3 = (int)s3.length();
        for (int i = 0; i <= n1; i++)
            for (int j = 0; j <= n2; j++)
                dp[i][j][0] = dp1[i][j][0] = dp2[i][j][0] = 1;
        for (int k = 1; k <= n3; k++)
            for (int i = 0; i <= n1; i++)
                for (int j = 0; j <= n2; j++) {
                    if (i) {
                        dp1[i][j][k] = dp1[i - 1][j][k];
                        if (s1[i - 1] == s3[k - 1]) dp1[i][j][k] += dp[i - 1][j][k - 1];
                        dp1[i][j][k] %= MOD;
                    }
                    if (j) {
                        dp2[i][j][k] = dp2[i][j - 1][k];
                        if (s2[j - 1] == s3[k - 1]) dp2[i][j][k] += dp[i][j - 1][k - 1];
                        dp2[i][j][k] %= MOD;
                    }
                    dp[i][j][k] = (dp1[i][j][k] + dp2[i][j][k]) % MOD;
                }
        cout << dp[n1][n2][n3] << '\n';
    }
    return 0;
}

