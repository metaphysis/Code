// Expect the Expected
// UVa ID: 11427
// Verdict: Accepted
// Submission Date: 2019-02-15
// UVa Run Time: 0.010s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        int nume, deno, n;
        char slash;
        cin >> nume >> slash >> deno >> n;
        double dp[110][110] = {}, p = 1.0 * nume / deno;
        dp[0][0] = 1, dp[0][1] = 0;
        for (int i = 1; i <= n; i++)
            for (int j = 0; j * deno <= i * nume; j++)
            {
                dp[i][j] = dp[i - 1][j] * (1 - p);
                if (j) dp[i][j] += dp[i - 1][j - 1] * p;
            }
        double pa = 0;
        for (int i = 0; i * deno <= n * nume; i++)
            pa += dp[n][i];
        cout << "Case #" << cs << ": " << (int)(1 / pa) << '\n';
    }

    return 0;
}
