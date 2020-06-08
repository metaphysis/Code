#include <bits/stdc++.h>

using namespace std;

const int MAXV = 10010;

vector<int> g[MAXV];
int parent[MAXV], depth[MAXV], visited[MAXV];

void dfs(int u)
{
    visited[u] = 1;

    for (auto v : g[u])
        if (!visited[v])
        {
            parent[v] = u;
            depth[v] = depth[u] + 1;
            dfs(v);
        }
}

int getLCA(int u, int v)
{
    if (depth[u] < depth[v]) swap(u, v);

    int diff = depth[u] - depth[v];
    while (diff--) u = parent[u];

    if (u != v)
        while (u != v) u = parent[u], v = parent[v];

    return u;
}

int main(int argc, char *argv[])
{
    int n;

    while (cin >> n)
    {
        for (int u = 0; u < n; u++)
            g[u].clear();
            
        for (int u = 0, m; u < n; u++)
        {
            cin >> m;
            for (int j = 0, v; j < m; j++)
            {
                cin >> v;
                v--;
                g[u].push_back(v);
                g[v].push_back(u);
            }
        }

        memset(parent, -1, sizeof(parent));
        memset(visited, 0, sizeof(visited));
        memset(depth, 0, sizeof(depth));
        
        dfs(0);

        cin >> n;
        for (int i = 0, u, v; i < n; i++)
        {
            cin >> u >> v;
            cout << "LCA of " << u << " and " << v << " is ";
            cout << (lca(--u, --v) + 1) << '\n';
        }
    }
}
