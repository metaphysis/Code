#include <bits/stdc++.h>
using namespace std;

int n, m, tim;
vector<vector<pair<int, int>>> graph;
vector<int> dfn, low, bridge, vis;

void findBridge(int u, int pe) {
    dfn[u] = low[u] = ++tim;
    for (const auto &e : graph[u]) {
        int v = e.first, id = e.second;
        if (!dfn[v]) {
            findBridge(v, id);
            low[u] = min(low[u], low[v]);
            if (low[v] > dfn[u])
                bridge[id] = 1;
        } else if (id != pe) {
            low[u] = min(low[u], dfn[v]);
        }
    }
}

void markComp(int u) {
    vis[u] = 1;
    for (const auto &e : graph[u]) {
        int v = e.first, id = e.second;
        if (!bridge[id] && !vis[v])
            markComp(v);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, c;
    cin >> t;
    for (int tc = 1; tc <= t; ++tc) {
        cin >> n >> m >> c;
        graph.assign(n + 1, {});
        dfn.assign(n + 1, 0);
        low.assign(n + 1, 0);
        bridge.assign(m, 0);
        vis.assign(n + 1, 0);
        for (int i = 0; i < m; ++i) {
            int x, y;
            cin >> x >> y;
            graph[x].push_back({y, i});
            graph[y].push_back({x, i});
        }
        tim = 0;
        findBridge(c, -1);
        markComp(c);
        cout << "Case " << tc << ":";
        bool found = false;
        for (int i = 1; i <= n; ++i) {
            if (i != c && vis[i]) {
                cout << " " << i;
                found = true;
            }
        }
        if (!found)
            cout << " none";
        cout << '\n';
    }
    return 0;
}
