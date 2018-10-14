// Busy Programmer
// UVa ID: 11432
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int D, G;
int dp[34][34][34][34][2];

int dfs(int d1, int d2, int g1, int g2, int k)
{
    if (d1 == D || d2 == D)
    {
        if (k == 0 && d1 == D && d2 < D)
            return dp[d1][d2][g1][g2][k] = 1;
        if (k == 1 && d2 == D && d1 < D)
            return dp[d1][d2][g1][g2][k] = 1;
        return 0;
    }
    if (~dp[d1][d2][g1][g2][k]) return dp[d1][d2][g1][g2][k];
    if (g1 == G) return dp[d1][d2][g1][g2][k] = dfs(d1, d2 + 1, 0, 1, k);
    if (g2 == G) return dp[d1][d2][g1][g2][k] = dfs(d1 + 1, d2, 1, 0, k);
    int r = dfs(d1 + 1, d2, g1 + 1, g2, k) + dfs(d1, d2 + 1, g1, g2 + 1, k);
    return dp[d1][d2][g1][g2][k] = r;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0;
    while (cin >> D >> G)
    {
        if (D == -1) break;
        cout << "Case " << ++cases << ": ";
        memset(dp, -1, sizeof(dp));
        int r = dfs(1, 0, 1, 0, 0);
        memset(dp, -1, sizeof(dp));
        r += dfs(0, 1, 0, 1, 1);
        cout << r << '\n';
    }

    return 0;
}
