// Extreme Discrete Summation
// UVa ID: 11485
// Verdict: Accepted
// Submission Date: 2023-05-10
// UVa Run Time: 0.000s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include<bits/stdc++.h>
using namespace std;
int main(int argc, char *argv []) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int n, f[110];
    long long dp[16][128];
    while (cin >> n, n) {
        string d;
        for (int i = 0; i < n; i++) {
            cin >> d;
            f[i] = stoi(d.substr(d.find('.') + 1));
        }
        memset(dp, 0, sizeof dp);
        dp[0][0] = 1;
        for (int i = 1; i <= 8; i++)
            for (int j = 0; j < n; j++)
                for (int k = 80; k >= f[j]; k--)
                    dp[i][k] += dp[i - 1][k - f[j]];
        long long r = 0;
        for (int i = 0; i <= 72; i++)
            r += dp[8][i] * (i / 10);
        cout << r << '\n';
    }
    return 0;
}
