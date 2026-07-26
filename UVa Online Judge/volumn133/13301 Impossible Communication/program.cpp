// Impossible Communication
// UVa ID: 13301
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.030s
// https://blog.csdn.net/metaphysis/article/details/163173366

#include <bits/stdc++.h>
using namespace std;

class UnionFind {
public:
    vector<int> parent;
    UnionFind(int n) { parent.resize(n + 1); for (int i = 1; i <= n; ++i) parent[i] = i; }
    int find(int x) { return parent[x] == x ? x : parent[x] = find(parent[x]); }
    void unite(int a, int b) { int ra = find(a), rb = find(b); if (ra != rb) parent[rb] = ra; }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, M;
    while (cin >> N >> M) {
        UnionFind uf(N);
        vector<pair<int, int>> edges;
        for (int i = 0; i < M; ++i) {
            int k;
            cin >> k;
            if (k == 1) {
                int u, v;
                cin >> u >> v;
                edges.push_back({u, v});
            } else {
                vector<int> nodes(k);
                for (int j = 0; j < k; ++j) cin >> nodes[j];
                for (int j = 1; j < k; ++j) uf.unite(nodes[0], nodes[j]);
            }
        }
        vector<int> rootToId(N + 1, -1);
        int cnt = 0;
        for (int i = 1; i <= N; ++i) {
            int r = uf.find(i);
            if (rootToId[r] == -1) rootToId[r] = cnt++;
        }
        vector<vector<int>> adj(cnt);
        for (auto &e : edges) {
            int ru = uf.find(e.first);
            int rv = uf.find(e.second);
            if (ru != rv) {
                int u = rootToId[ru];
                int v = rootToId[rv];
                adj[u].push_back(v);
            }
        }
        vector<int> dfn(cnt, -1), low(cnt, 0), stk;
        vector<bool> inStack(cnt, false);
        int timer = 0, sccCnt = 0;
        function<void(int)> dfs = [&](int u) {
            dfn[u] = low[u] = timer++;
            stk.push_back(u);
            inStack[u] = true;
            for (int v : adj[u]) {
                if (dfn[v] == -1) {
                    dfs(v);
                    low[u] = min(low[u], low[v]);
                } else if (inStack[v]) {
                    low[u] = min(low[u], dfn[v]);
                }
            }
            if (low[u] == dfn[u]) {
                ++sccCnt;
                while (true) {
                    int x = stk.back(); stk.pop_back();
                    inStack[x] = false;
                    if (x == u) break;
                }
            }
        };
        for (int i = 0; i < cnt; ++i) if (dfn[i] == -1) dfs(i);
        cout << (sccCnt == 1 ? "YES" : "NO") << '\n';
    }
    return 0;
}
