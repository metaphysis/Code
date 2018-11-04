// Placing Lampposts
// UVa ID: 10859
// Verdict: Accepted
// Submission Date: 2018-11-04
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 1024;

int n, m, visited[MAXV], dp[MAXV][2], lighted[MAXV][2];
list<int> edges[MAXV];

void dfs(int u)
{
    dp[u][0] = 0;
    dp[u][1] = 1;
    lighted[u][0] = lighted[u][1] = 0;
    visited[u] = 1;

    for (auto v : edges[u])
    {
        if (!visited[v])
        {
            dfs(v);
            dp[u][0] += dp[v][1];
            lighted[u][0] += lighted[v][1];

            if (dp[v][0] == dp[v][1])
            {
                dp[u][1] += dp[v][1];
                lighted[u][1] += max(lighted[v][0], 1 + lighted[v][1]);
            }
            else
            {
                if (dp[v][0] < dp[v][1])
                {
                    dp[u][1] += dp[v][0];
                    lighted[u][1] += lighted[v][0];
                }
                else
                {
                    dp[u][1] += dp[v][1];
                    lighted[u][1] += 1 + lighted[v][1];
                }
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
        cin >> n >> m;
        for (int i = 0; i < n; i++) edges[i].clear();
        for (int i = 1, u, v; i <= m; i++)
        {
            cin >> u >> v;
            edges[u].push_back(v);
            edges[v].push_back(u);
        }
        
        int r1 = 0, r2 = 0;
        memset(visited, 0, sizeof(visited));
        for (int i = 0; i < n; i++)
            if (!visited[i])
            {
                dfs(i);
                r1 += min(dp[i][0], dp[i][1]);
                if (dp[i][0] == dp[i][1]) r2 += max(lighted[i][0], lighted[i][1]);
                else
                {
                    if (dp[i][0] < dp[i][1]) r2 += lighted[i][0];
                    else r2 += lighted[i][1];
                }
            }
        cout << r1 << ' ' << r2 << ' ' << (m - r2) << '\n';
    }

    return 0;
}
