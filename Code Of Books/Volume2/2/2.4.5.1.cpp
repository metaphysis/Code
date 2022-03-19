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

int getLCA(int u, int v)
{
    unordered_set<int> Su;

    while (u != -1) {
        Su.insert(u);
        u = parent[u];
    }

    while (v != -1) {
        if (Su.find(v) != Su.end()) return v;
        v = parent[v];
    }
}

int main(int argc, char *argv[])
{
    int n, q;
    while (cin >> n) {
        for (int i = 0; i < n; i++) g[i].clear();
        for (int i = 1, u, v; i < n; i++) {
            cin >> u >> v;
            g[u].push_back(v);
            g[v].push_back(u);
        }

        memset(parent, -1, sizeof(parent));
        memset(visited, 0, sizeof(visited));
        dfs(0);

        cin >> q;
        for (int i = 0, u, v; i < q; i++) {
            cin >> u >> v;
            cout << "LCA of " << u << " and " << v << " is ";
            cout << getLCA(u, v) << '\n';
        }
    }
}
