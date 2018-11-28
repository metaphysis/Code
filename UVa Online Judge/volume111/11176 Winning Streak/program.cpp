// Winning Streak
// UVa ID: 11176
// Verdict: Accepted
// Submission Date: 2018-11-28
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n;
    double p, dp[501][501], pp[501];
    while (cin >> n >> p)
    {
        if (n == 0) break;
        pp[0] = 1;
        for (int i = 1; i <= n; i++) pp[i] = pp[i - 1] * p;
        for (int j = 0; j <= n; j++) dp[0][j] = 1;
        for (int i = 1; i <= n; i++)
            for (int j = 0; j <= n; j++)
            {
                dp[i][j] = dp[i - 1][j];
                if (j + 1 == i) dp[i][j] -= pp[j + 1];
                else
                {
                    if (j + 1 < i)
                        dp[i][j] -= dp[i - (j + 1) - 1][j] * (1 - p) * pp[j + 1];
                }
            }
        double r = 0;
        for (int j = 1; j <= n; j++) r += (dp[n][j] - dp[n][j - 1]) * j;
        cout << fixed << setprecision(10) << r << '\n';
    }

    return 0;
}
