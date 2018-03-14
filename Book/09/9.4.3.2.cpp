#include <bits/stdc++.h>

using namespace std;

const int MAXV = 10000;

vector<int> edges[MAXV];
int parent[MAXV], depth[MAXV], visited[MAXV];

void dfs(int u)
{
    visited[u] = 1;

    for (auto v : edges[u])
        if (!visited[v])
        {
            parent[v] = u;
            depth[v] = depth[u] + 1;
            dfs(v);
        }
}

int lca(int u, int v)
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
            edges[u].clear();
            
        for (int u = 0, m; u < n; u++)
        {
            cin >> m;
            for (int j = 0, v; j < m; j++)
            {
                cin >> v;
                v--;
                edges[u].push_back(v);
                edges[v].push_back(u);
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
