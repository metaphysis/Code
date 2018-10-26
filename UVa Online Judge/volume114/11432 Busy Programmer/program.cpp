// Busy Programmer
// UVa ID: 11432
// Verdict: Accepted
// Submission Date: 2018-10-26
// UVa Run Time: 0.350s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int D, G;
long long dp[34][34][34][34];

long long dfs(int d1, int d2, int g1, int g2)
{
    if (d1 == D || d2 == D)
    {
        if (d2 < D) return dp[d1][d2][g1][g2] = 1LL;
        return 0;
    }
    if (~dp[d1][d2][g1][g2]) return dp[d1][d2][g1][g2];
    if (g1 == G) return dp[d1][d2][g1][g2] = dfs(d1, d2 + 1, 0, 1);
    if (g2 == G) return dp[d1][d2][g1][g2] = dfs(d1 + 1, d2, 1, 0);
    long long r = 0;
    if (g1)
        r = dfs(d1 + 1, d2, g1 + 1, g2) + dfs(d1, d2 + 1, 0, 1);
    else
        r = dfs(d1, d2 + 1, g1, g2 + 1) + dfs(d1 + 1, d2, 1, 0);
    return dp[d1][d2][g1][g2] = r;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0;
    while (cin >> D >> G)
    {
        if (D == -1) break;
        cout << "Case " << ++cases << ": ";
        if (D == 0 || G == 0)
        {
            cout << "0\n";
            continue;
        }
        for (int i = 0; i <= D; i++)
            for (int j = 0; j <= D; j++)
                for (int k = 0; k <= G; k++)
                    for (int l = 0; l <= G; l++)
                        dp[i][j][k][l] = -1LL;
        cout << (dfs(1, 0, 1, 0) * 2) << '\n';
    }

    return 0;
}
