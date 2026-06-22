// Inglorious Gangs
// UVa ID: 11896
// Verdict: Accepted
// Submission Date: 2026-06-22
// UVa Run Time: 0.370s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

void solve() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int N, M; cin >> N >> M;
        vector<vector<int>> g(N + 1);
        vector<int> od(N + 1), id(N + 1);
        bool parallel = false;
        unordered_set<long long> E;
        for (int i = 0; i < M; ++i) {
            int u, v; cin >> u >> v;
            g[u].push_back(v);
            od[u]++; id[v]++;
            long long key = 1LL * u * (N + 1) + v;
            if (!E.insert(key).second) parallel = true;
        }
        if (parallel) { cout << "Not Trapped\n"; continue; }

        // Tarjan算法缩点
        vector<int> dfn(N + 1), low(N + 1), comp(N + 1);
        vector<bool> inSt(N + 1);
        stack<int> st;
        int tm = 0, sc = 0;
        function<void(int)> dfs = [&](int u) {
            dfn[u] = low[u] = ++tm;
            st.push(u); inSt[u] = true;
            for (int v : g[u]) {
                if (!dfn[v]) {
                    dfs(v);
                    low[u] = min(low[u], low[v]);
                } else if (inSt[v]) low[u] = min(low[u], dfn[v]);
            }
            if (low[u] == dfn[u]) {
                ++sc;
                int v;
                do {
                    v = st.top(); st.pop();
                    inSt[v] = false;
                    comp[v] = sc;
                } while (v != u);
            }
        };
        for (int i = 1; i <= N; ++i) if (!dfn[i]) dfs(i);

        // SCC 内部出度与大小
        vector<int> innerOut(N + 1), sz(sc + 1);
        for (int i = 1; i <= N; ++i) sz[comp[i]]++;
        for (int u = 1; u <= N; ++u)
            for (int v : g[u])
                if (comp[u] == comp[v]) innerOut[u]++;

        bool escaped = false;
        for (int c = 1; c <= sc && !escaped; ++c) {
            if (sz[c] < 2) continue;
            for (int u = 1; u <= N; ++u)
                if (comp[u] == c && innerOut[u] >= 2) { escaped = true; break; }
        }
        if (escaped) { cout << "Not Trapped\n"; continue; }

        // 检查原图中节点出度>=2且两条边进入同一个大小>=2的SCC
        for (int u = 1; u <= N && !escaped; ++u) {
            if (od[u] < 2) continue;
            unordered_set<int> seenSCC;
            for (int v : g[u]) {
                int c = comp[v];
                if (sz[c] >= 2 && !seenSCC.insert(c).second) { escaped = true; break; }
            }
        }
        if (escaped) { cout << "Not Trapped\n"; continue; }

        // 缩点 DAG
        vector<vector<int>> dag(sc + 1);
        vector<int> dout(sc + 1), din(sc + 1);
        vector<unordered_set<int>> tmp(sc + 1);
        for (int u = 1; u <= N; ++u)
            for (int v : g[u])
                if (comp[u] != comp[v])
                    if (tmp[comp[u]].insert(comp[v]).second) {
                        dag[comp[u]].push_back(comp[v]);
                        dout[comp[u]]++;
                        din[comp[v]]++;
                    }

        // 拓扑排序
        vector<int> tp;
        queue<int> q;
        for (int i = 1; i <= sc; ++i) if (din[i] == 0) q.push(i);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            tp.push_back(u);
            for (int v : dag[u]) if (--din[v] == 0) q.push(v);
        }

        // 计算每个SCC的可达集
        vector<bitset<5005>> R(sc + 1);
        for (auto it = tp.rbegin(); it != tp.rend(); ++it) {
            int u = *it;
            R[u].set(u);
            for (int v : dag[u]) R[u] |= R[v];
        }

        // DAG中出度>=2的SCC检查可达集交集
        for (int c = 1; c <= sc && !escaped; ++c) {
            if (dout[c] < 2) continue;
            bitset<5005> seen;
            for (int v : dag[c]) {
                if ((seen & R[v]).any()) { escaped = true; break; }
                seen |= R[v];
            }
        }

        cout << (escaped ? "Not Trapped" : "Trapped") << '\n';
    }
}

int main() { solve(); return 0; }
