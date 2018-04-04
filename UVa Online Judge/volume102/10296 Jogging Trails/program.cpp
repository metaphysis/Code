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

int dist[MAXN][MAXN], deg[MAXN], n, m;
int minCost, totalCost, used[MAXN];
vector<int> odd;

void dfs(int depth, int cost)
{
    if (cost > minCost) return;

    if (depth * 2 == odd.size())
    {
        minCost = min(minCost, cost);
        return;
    }

    int u = 0;
    for (; u < odd.size(); u++)
        if (!used[u])
        {
            used[u] = 1;
            break;
        }
        
    for (int v = u + 1; v < odd.size(); v++)
        if (!used[v])
        {
            used[v] = 1;
            dfs(depth + 1, cost + dist[odd[u]][odd[v]]);
            used[v] = 0;
        }
        
    if (depth) used[u] = 0;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int u, v, w;

    while (cin >> n, n > 0)
    {
        cin >> m;

        memset(dist, 0x3f, sizeof(dist));
        memset(deg, 0, sizeof(deg));

        totalCost = 0;
        for (int i = 1; i <= m; i++)
        {
            cin >> u >> v >> w;
            dist[u][v] = min(dist[u][v], w);
            dist[v][u] = min(dist[v][u], w);
            deg[u]++, deg[v]++;
            totalCost += w;
        }

        odd.clear();
        for (int i = 1; i <= n; i++)
            if (deg[i] & 1)
                odd.push_back(i);

        for (int k = 1; k <= n; k++)
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

        minCost = INF;
        memset(used, 0, sizeof(used));
        dfs(0, 0);            
        
        cout << (totalCost + minCost) << '\n';
    }

    return 0;
}
