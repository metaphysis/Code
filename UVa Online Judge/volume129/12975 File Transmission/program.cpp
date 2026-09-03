#include <bits/stdc++.h>
using namespace std;

const int maxN = 10005;
const int maxLog = 16;

struct Edge {
    int to, id;
};

int n, m, timer, compCnt;
vector<Edge> graph[maxN];
vector<int> tree[maxN];
int dfn[maxN], low[maxN], comp[maxN], depth[maxN];
int up[maxLog][maxN];
bool isBridge[20005];

void findBridge(int u, int edgeId) {
    dfn[u] = low[u] = ++timer;
    for (Edge edge : graph[u]) {
        if (edge.id == edgeId) continue;
        int v = edge.to;
        if (!dfn[v]) {
            findBridge(v, edge.id);
            low[u] = min(low[u], low[v]);
            if (low[v] > dfn[u]) isBridge[edge.id] = true;
        } else {
            low[u] = min(low[u], dfn[v]);
        }
    }
}

void findComponent(int start) {
    ++compCnt;
    stack<int> nodes;
    nodes.push(start);
    comp[start] = compCnt;
    while (!nodes.empty()) {
        int u = nodes.top();
        nodes.pop();
        for (Edge edge : graph[u]) {
            if (isBridge[edge.id]) continue;
            int v = edge.to;
            if (comp[v]) continue;
            comp[v] = compCnt;
            nodes.push(v);
        }
    }
}

void buildTree(int u, int parent) {
    up[0][u] = parent;
    for (int k = 1; k < maxLog; ++k)
        up[k][u] = up[k - 1][up[k - 1][u]];
    for (int v : tree[u]) {
        if (v == parent) continue;
        depth[v] = depth[u] + 1;
        buildTree(v, u);
    }
}

int getLca(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    int diff = depth[u] - depth[v];
    for (int k = 0; k < maxLog; ++k)
        if (diff & (1 << k)) u = up[k][u];
    if (u == v) return u;
    for (int k = maxLog - 1; k >= 0; --k) {
        if (up[k][u] != up[k][v]) {
            u = up[k][u];
            v = up[k][v];
        }
    }
    return up[0][u];
}

int solveQuery(int u, int v) {
    int x = comp[u], y = comp[v];
    int lca = getLca(x, y);
    return (depth[x] + depth[y] - 2 * depth[lca]) * 50;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int caseId = 0;
    while (cin >> n >> m) {
        if (n == 0 && m == 0) break;
        for (int i = 1; i <= n; ++i) {
            graph[i].clear();
            tree[i].clear();
        }
        memset(dfn, 0, sizeof(dfn));
        memset(low, 0, sizeof(low));
        memset(comp, 0, sizeof(comp));
        memset(isBridge, false, sizeof(isBridge));
        timer = 0;
        compCnt = 0;
        for (int i = 1; i <= m; ++i) {
            int a, b;
            cin >> a >> b;
            graph[a].push_back({b, i});
            graph[b].push_back({a, i});
        }
        findBridge(1, 0);
        for (int i = 1; i <= n; ++i)
            if (!comp[i]) findComponent(i);
        for (int u = 1; u <= n; ++u) {
            for (Edge edge : graph[u]) {
                int v = edge.to;
                if (!isBridge[edge.id]) continue;
                tree[comp[u]].push_back(comp[v]);
            }
        }
        memset(up, 0, sizeof(up));
        memset(depth, 0, sizeof(depth));
        for (int i = 1; i <= compCnt; ++i)
            if (up[0][i] == 0) buildTree(i, 0);
        int q;
        cin >> q;
        if (caseId > 0) cout << '\n';
        ++caseId;
        cout << "Case #" << caseId << ":\n";
        while (q--) {
            int u, v;
            cin >> u >> v;
            cout << solveQuery(u, v) << '\n';
        }
    }
    return 0;
}
