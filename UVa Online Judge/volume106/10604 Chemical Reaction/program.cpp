// Chemical Reaction
// UVa ID: 10604
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f;

int dp[10][10][7], cr[10][10][2], marker[10][10];
int m, n, tubes[10];

void dfs(int l, int r)
{
    if (l == r) return 0;
    if (marked[l][r]) return;
    marked[l][r] = 1;
    for (int k = l; k <= r; k++)
    {
        dfs(l, k);
        dfs(k + 1, r);
        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= m;j++)
            {
                if (dp[l][k][i] != INF && dp[k][r][j] != INF)
                {
                    int combined = cr[i][j][0];
                    int hear = cr[i][j][1];
                    dp[l][r][combined] = min(dp[l][r][combined], dp[l][k][i] + dp[k][r][j] + heat);
                }
            }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> m;
        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= m; j++)
            {
                cin >> cr[i][j][0];
                cin >> cr[i][j][1];
            }
        cin >> n;
        for (int i = 0; i < n; i++)
            cin >> tubes[i];
        memset(marked, 0, sizeof(marked));
        memset(dp, 0x3f, sizeof(dp));
        int minimal = INF;
        for (int i = 1; i <= m; i++)
            minimal = min(minimal, dp[0][n - 1][i]);
        cout << minimal << '\n';
    }

    return 0;
}
