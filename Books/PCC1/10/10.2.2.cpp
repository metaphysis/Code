#include <bits/stdc++.h>

using namespace std;

const int MAXN = 24, INF = 0x3f3f3f3f;

int g[MAXN][MAXN], degree[MAXN], dp[1 << 16], n, m;
// Vertices with odd degree.
vector<int> odv;

// DP + Memoization.
int dfs(int mask)
{
    if (!mask) return 0;
    if (dp[mask]) return dp[mask];
    int cost = INF;
    for (int i = 0; i < odv.size(); i++)
        if ((mask >> i) & 1)
        {
            for (int j = i + 1; j < odv.size(); j++)
                if ((mask >> j) & 1)
                    cost = min(cost, dfs(mask - (1 << i) - (1 << j)) + g[odv[i]][odv[j]]);
            break;
        }
    return dp[mask] = cost;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> n >> m)
    {
        memset(g, 0x3f, sizeof(g));
        memset(degree, 0, sizeof(degree));
        for (int i = 0; i < n; i++) g[i][i] = 0;

        int cost = 0;
        char u, v;
        int w;
        for (int i = 1; i <= m; i++)
        {
            cin >> u >> v >> w;
            g[u - 'A'][v - 'A'] = min(g[u - 'A'][v - 'A'], w);
            g[v - 'A'][u - 'A'] = min(g[v - 'A'][u - 'A'], w);
            degree[u - 'A']++, degree[v - 'A']++;
            cost += w;
        }

        odv.clear();
        for (int i = 0; i < n; i++)
            if (degree[i] & 1)
                odv.push_back(i);

        for (int k = 0; k < n; k++)
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    g[i][j] = min(g[i][j], g[i][k] + g[k][j]);        
        
        memset(dp, 0, sizeof(dp));
        cout << (cost + dfs((1 << odv.size()) - 1)) << '\n';
    }

    return 0;
}
