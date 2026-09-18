#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u1, v1, u2, v2;
};

struct Dsu {
    vector<int> parent, sz;
    Dsu(int n) {
        reset(n);
    }

    void reset(int n) {
        parent.resize(n);
        sz.assign(n, 1);
        iota(parent.begin(), parent.end(), 0);
    }

    int findRoot(int x) {
        if (parent[x] != x) parent[x] = findRoot(parent[x]);
        return parent[x];
    }

    void unite(int x, int y) {
        x = findRoot(x);
        y = findRoot(y);
        if (x == y) return;
        if (sz[x] < sz[y]) swap(x, y);
        parent[y] = x;
        sz[x] += sz[y];
    }

    bool canAdd(int x, int y) {
        return findRoot(x) != findRoot(y);
    }
};

bool augment(int n1, int n2, const vector<Edge>& edges,
             const vector<bool>& enabled, vector<bool>& inSet) {
    int m = (int)edges.size();
    Dsu d1(n1), d2(n2);
    vector<int> chosen, prev(m, -2);
    vector<bool> isSink(m, false);
    vector<vector<int>> adj(m);
    queue<int> bfs;
    for (int i = 0; i < m; ++i) {
        if (!inSet[i]) continue;
        chosen.push_back(i);
        d1.unite(edges[i].u1, edges[i].v1);
        d2.unite(edges[i].u2, edges[i].v2);
    }
    for (int i = 0; i < m; ++i) {
        if (!enabled[i] || inSet[i]) continue;
        bool can1 = d1.canAdd(edges[i].u1, edges[i].v1), can2 = d2.canAdd(edges[i].u2, edges[i].v2);
        isSink[i] = can2;
        if (can1 && can2) {
            inSet[i] = true;
            return true;
        }
        if (can1) {
            prev[i] = -1;
            bfs.push(i);
        }
    }
    if (bfs.empty()) return false;
    for (int outId : chosen) {
        d1.reset(n1);
        d2.reset(n2);
        for (int id : chosen) {
            if (id == outId) continue;
            d1.unite(edges[id].u1, edges[id].v1);
            d2.unite(edges[id].u2, edges[id].v2);
        }
        for (int i = 0; i < m; ++i) {
            if (!enabled[i] || inSet[i]) continue;
            if (d1.canAdd(edges[i].u1, edges[i].v1)) adj[outId].push_back(i);
            if (d2.canAdd(edges[i].u2, edges[i].v2)) adj[i].push_back(outId);
        }
    }
    while (!bfs.empty()) {
        int cur = bfs.front();
        bfs.pop();
        if (isSink[cur]) {
            for (int id = cur; id != -1; id = prev[id]) inSet[id] = !inSet[id];
            return true;
        }
        for (int nextId : adj[cur]) {
            if (prev[nextId] != -2) continue;
            prev[nextId] = cur;
            bfs.push(nextId);
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    while (testCount--) {
        int n1, n2, m, ans = 0;
        cin >> n1 >> n2 >> m;
        vector<Edge> edges(m);
        vector<bool> enabled(m, true), inSet(m, false);
        for (int i = 0; i < m; ++i) cin >> edges[i].u1 >> edges[i].v1 >> edges[i].u2 >> edges[i].v2;
        while (augment(n1, n2, edges, enabled, inSet)) ++ans;
        for (int i = m - 1; i >= 0; --i) {
            enabled[i] = false;
            if (!inSet[i]) continue;
            inSet[i] = false;
            if (!augment(n1, n2, edges, enabled, inSet)) {
                enabled[i] = true;
                inSet[i] = true;
            }
        }
        cout << ans;
        for (int i = 0; i < m; ++i) if (inSet[i]) cout << ' ' << i;
        cout << '\n';
    }
    return 0;
}
