#include <bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f;

int n, m, g[16][16], parent[16][16], dp[16][1 << 16], used[16][1 << 16];

int dfs(int u, int mask)
{
    if (mask == (1 << n) - 1) return g[u][0];
    if (~dp[u][mask]) return dp[u][mask];
    int r = INF, minV = -1;
    for (int v = 0; v < n; v++)
        if (v != u && !(mask & (1 << v)))
        {
            int nr = g[u][v] + dfs(v, mask | (1 << v));
            if (nr < r)
            {
                r = nr;
                minV = v;
            }
        }
    used[u][mask] = minV;
    return dp[u][mask] = r;
}

void printPath(int u, int v)
{
    if (u != v)
    {
        printPath(u, parent[u][v]);
        cout << '-' << (char)(v + 'A');
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    char from, to;
    int weight;

    while (cin >> n >> m)
    {
        memset(g, INF, sizeof(g));
        for (int i = 1; i <= m; i++)
        {
            cin >> from  >> to >> weight;
            g[from - 'A'][to - 'A'] = g[to - 'A'][from - 'A'] = weight;
        }
        for (int i = 0; i < n; i++)
        {
            g[i][i] = 0;
            for (int j = 0; j < n; j++)
                parent[i][j] = i;
        }
        for (int k = 0; k < n; k++)
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    if (g[i][k] + g[k][j] < g[i][j])
                    {
                        g[i][j] = g[i][k] + g[k][j];
                        parent[i][j] = parent[k][j];
                    }
        memset(dp, -1, sizeof(dp));
        cout << dfs(0, 1) << '\n';
        int u = 0, mask = 1;
        vector<int> vs;
        vs.push_back(0);
        while (mask != (1 << n) - 1)
        {
            u = used[u][mask];
            mask |= (1 << u);
            vs.push_back(u);
        }
        vs.push_back(0);
        cout << 'A';
        for (int i = 1; i < vs.size(); i++)
            printPath(vs[i - 1], vs[i]);
        cout << '\n';
    }

    return 0;
}
