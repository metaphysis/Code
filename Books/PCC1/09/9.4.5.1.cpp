#include <bits/stdc++.h>

using namespace std;

const int MAXV = 10010;

vector<int> g[MAXV];
int parent[MAXV], visited[MAXV];

void dfs(int u)
{
    visited[u] = 1;

    for (auto v : g[u])
        if (!visited[v])
        {
            parent[v] = u;
            dfs(v);
        }
}

int lca(int u, int v)
{
    unordered_set<int> ancestors;

    while (u != -1) {
        ancestors.insert(u);
        u = parent[u];
    }

    while (v != -1) {
        if (ancestors.find(v) != ancestors.end())
            return v;
        v = parent[v];
    }
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
