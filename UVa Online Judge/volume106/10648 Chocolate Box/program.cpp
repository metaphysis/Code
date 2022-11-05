// Chocolate Box
// UVa ID: 10648
// Verdict: Accepted
// Submission Date: 2022-11-05
// UVa Run Time: 0.000s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    double dp[110][110];
    int n, m, cases = 1;
    while (cin >> n >> m)
    {
        if (n == -1) break;
        cout << "Case " << cases++ << ": ";
        dp[1][1] = 1.0, dp[1][0] = 0.0;
        for (int i = 2; i <= n; i++)
            for (int j = 1; j <= i; j++)
                dp[i][j] = dp[i - 1][j] * j / m + dp[i - 1][j - 1] * (m - j + 1) / m;
        double r = 0.0;
        for (int i = 1; i < m; i++) r += dp[n][i];
        cout << fixed << setprecision(7) << r << '\n';
    }

    return 0;
}
