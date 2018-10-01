// Palindromic Paths
// UVa ID: 1244
// Verdict: Accepted
// Submission Date: 2018-10-01
// UVa Run Time: 0.070s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int cases, n;
char g[64][64];
string dp[64][64];

string dfs(int i, int j)
{
    if (i == j) return "";
    if (i > j) return "*";
    if (dp[i][j] != "$") return dp[i][j];
    string r = string(1, g[i][j]);
    for (int u = i + 1; u <= n; u++)
        for (int v = j - 1; v >= 1; v--)
            if (g[i][u] == g[v][j] && g[i][u] != '*')
            {
                string inner = dfs(u, v);
                if (inner == "*") continue;
                string outer = g[i][u] + inner + g[v][j];
                if (outer.length() > r.length() || (outer.length() == r.length() && outer < r))
                    r = outer;
            }
    return dp[i][j] = r;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> n;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
            {
                cin >> g[i][j];
                dp[i][j] = "$";
            }
        dfs(1, n);
        if (dp[1][n].length() > 0)
            cout << dp[1][n] << '\n';
        else
            cout << "NO PALINDROMIC PATH\n";
    }

    return 0;
}
