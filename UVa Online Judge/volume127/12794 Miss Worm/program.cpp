// Miss Worm
// UVa ID: 12794
// Verdict: Accepted
// Submission Date: 2026-06-13
// UVa Run Time: 0.330s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Edge { int to, w; };

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int S, T;
    while (cin >> S >> T) {
        vector<vector<Edge>> g(S + 1);
        for (int i = 0; i < T; ++i) {
            int a, b, c;
            cin >> a >> b >> c;
            g[a].push_back({b, c});
            g[b].push_back({a, c});
        }

        // 找环
        vector<int> parent(S + 1, -1), depth(S + 1, 0), d1(S + 1, 0);
        vector<int> cycleId(S + 1, -1), cycleLength;
        vector<bool> visited(S + 1, false);

        function<void(int, int)> dfs = [&](int u, int p) {
            visited[u] = true;
            for (auto& e : g[u]) {
                int v = e.to;
                if (v == p) continue;
                if (visited[v]) {
                    if (depth[v] < depth[u]) {
                        int cid = cycleLength.size();
                        int w = 0;
                        int uu = u;
                        while (uu != v) {
                            cycleId[uu] = cid;
                            w += d1[uu];
                            uu = parent[uu];
                        }
                        cycleId[v] = cid;
                        w += e.w;
                        cycleLength.push_back(w);
                    }
                } else {
                    parent[v] = u;
                    depth[v] = depth[u] + 1;
                    d1[v] = e.w;
                    dfs(v, u);
                }
            }
        };

        for (int i = 1; i <= S; ++i) if (!visited[i]) dfs(i, -1);
        for (int i = 1; i <= S; ++i) if (cycleId[i] == -1) cycleId[i] = -2;

        int nc = cycleLength.size();
        vector<vector<int>> d2(S + 1, vector<int>(nc, -1));
        for (int cid = 0; cid < nc; ++cid) {
            priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
            vector<bool> done(S + 1, false);
            for (int i = 1; i <= S; ++i)
                if (cycleId[i] == cid) {
                    d2[i][cid] = 0;
                    pq.push(make_pair(0, i));
                }
            while (!pq.empty()) {
                pair<int, int> top = pq.top(); pq.pop();
                int d = top.first, u = top.second;
                if (done[u]) continue;
                done[u] = true;
                for (size_t j = 0; j < g[u].size(); ++j) {
                    Edge& e = g[u][j];
                    int v = e.to, nd = d + e.w;
                    if (d2[v][cid] == -1 || nd < d2[v][cid]) {
                        d2[v][cid] = nd;
                        pq.push(make_pair(nd, v));
                    }
                }
            }
        }

        int Q;
        cin >> Q;
        while (Q--) {
            int X, M;
            cin >> X >> M;
            int r = -1;
            for (int cid = 0; cid < nc; ++cid) {
                if (cycleLength[cid] < M) continue;
                int d = d2[X][cid];
                if (d == -1) continue;
                int total = (cycleId[X] == cid) ? cycleLength[cid] : (2 * d + cycleLength[cid]);
                if (r == -1 || total < r) r = total;
            }
            cout << r << '\n';
        }
    }
    return 0;
}
