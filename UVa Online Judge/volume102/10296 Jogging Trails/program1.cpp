// Jogging Trails
// UVa ID: 10296
// Verdict: Accepted
// Submission Date: 2018-04-04
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 24, INF = 0x3f3f3f3f;

int dist[MAXN][MAXN], deg[MAXN], dp[1 << 16], n, m;
vector<int> odd;

// DP + Memoization.
int dfs(int state)
{
    if (!state) return 0;
    if (dp[state]) return dp[state];
    int cost = INF;
    for (int i = 0; i < odd.size(); i++)
        if ((state >> i) & 1)
        {
            for (int j = i + 1; j < odd.size(); j++)
                if ((state >> j) & 1)
                    cost = min(cost, dfs(state - (1 << i) - (1 << j)) + dist[odd[i]][odd[j]]);
            break;
        }
    return dp[state] = cost;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int u, v, w;

    while (cin >> n, n > 0)
    {
        cin >> m;

        memset(dist, 0x3f, sizeof(dist));
        for (int i = 1; i <= n; i++)
            dist[i][i] = 0;
        memset(deg, 0, sizeof(deg));

        int cost = 0;
        for (int i = 1; i <= m; i++)
        {
            cin >> u >> v >> w;
            dist[u][v] = min(dist[u][v], w);
            dist[v][u] = min(dist[v][u], w);
            deg[u]++, deg[v]++;
            cost += w;
        }

        odd.clear();
        for (int i = 1; i <= n; i++)
            if (deg[i] & 1)
                odd.push_back(i);

        // Floyd-Warshall.
        for (int k = 1; k <= n; k++)
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);        
        
        memset(dp, 0, sizeof(dp));
        cout << (cost + dfs((1 << odd.size()) - 1)) << '\n';
    }

    return 0;
}
