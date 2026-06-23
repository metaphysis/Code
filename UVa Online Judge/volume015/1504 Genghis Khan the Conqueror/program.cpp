// Genghis Khan the Conqueror
// UVa ID: 1504
// Verdict: Accepted
// Submission Date: 2026-06-
// UVa Run Time: 0.110s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v, w, id;
};

const long long INF = 1e18;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (true) {
        int N, M;
        cin >> N >> M;
        if (N == 0 && M == 0) break;

        vector<vector<int>> edgeId(N, vector<int>(N, -1));
        vector<Edge> edges(M);
        vector<int> origW(M);
        for (int i = 0; i < M; ++i) {
            int x, y, c;
            cin >> x >> y >> c;
            edges[i] = {x, y, c, i};
            origW[i] = c;
            edgeId[x][y] = edgeId[y][x] = i;
        }

        // ---------- Prim 求 MST ----------
        const int ROOT = 0;
        vector<long long> dist(N, INF);
        vector<bool> vis(N, false);
        vector<int> parentNode(N, -1), parentEdge(N, -1);
        vector<bool> inTree(M, false);

        dist[ROOT] = 0;
        for (int k = 0; k < N; ++k) {
            int u = -1;
            for (int i = 0; i < N; ++i) {
                if (!vis[i] && (u == -1 || dist[i] < dist[u])) u = i;
            }
            vis[u] = true;
            if (u != ROOT) {
                inTree[parentEdge[u]] = true;
            }
            for (int v = 0; v < N; ++v) {
                int eid = edgeId[u][v];
                if (eid != -1 && !vis[v]) {
                    if (origW[eid] < dist[v]) {
                        dist[v] = origW[eid];
                        parentNode[v] = u;
                        parentEdge[v] = eid;
                    }
                }
            }
        }

        long long W0 = 0;
        for (int i = 0; i < N; ++i) {
            if (i != ROOT) W0 += origW[parentEdge[i]];
        }

        // ---------- 构建树的邻接表，计算深度 ----------
        vector<vector<int>> treeAdj(N);
        for (int i = 0; i < N; ++i) {
            if (i != ROOT) {
                int p = parentNode[i];
                treeAdj[p].push_back(i);
                treeAdj[i].push_back(p);
            }
        }
        vector<int> depth(N, 0), father(N, -1);
        function<void(int, int)> dfs = [&](int u, int p) {
            father[u] = p;
            for (int v : treeAdj[u]) {
                if (v == p) continue;
                depth[v] = depth[u] + 1;
                dfs(v, u);
            }
        };
        dfs(ROOT, -1);

        // ---------- 收集非树边并排序 ----------
        vector<Edge> nonTree;
        for (int i = 0; i < M; ++i) {
            if (!inTree[i]) nonTree.push_back(edges[i]);
        }
        sort(nonTree.begin(), nonTree.end(), [](const Edge& a, const Edge& b) {
            return a.w < b.w;
        });

        // ---------- 离线更新每条树边的最小替换权值 ----------
        vector<int> uf(N);
        iota(uf.begin(), uf.end(), 0);
        function<int(int)> findUF = [&](int x) -> int {
            if (uf[x] == x) return x;
            return uf[x] = findUF(uf[x]);
        };

        vector<long long> minReplace(M, INF);  // 只对树边有效

        for (const Edge& e : nonTree) {
            int u = e.u, v = e.v;
            long long w = e.w;
            while (findUF(u) != findUF(v)) {
                if (depth[findUF(u)] < depth[findUF(v)]) swap(u, v);
                int fu = findUF(u);
                int p = father[fu];
                // p 一定存在，因为 fu 不是根
                int eid = parentEdge[fu];
                minReplace[eid] = w;  // 第一次赋值即最小
                // 合并 fu 到其父节点
                uf[fu] = findUF(p);
                u = findUF(u);
            }
        }

        // ---------- 处理查询 ----------
        int Q;
        cin >> Q;
        long double sumAns = 0.0L;
        for (int qi = 0; qi < Q; ++qi) {
            int X, Y, C;
            cin >> X >> Y >> C;
            int eid = edgeId[X][Y];
            int oldW = origW[eid];
            long long ans;
            if (!inTree[eid]) {
                ans = W0;
            } else {
                long long replace = minReplace[eid];
                long long best = min((long long)C, replace);
                ans = W0 - oldW + best;
            }
            sumAns += ans;
        }

        long double expected = sumAns / (long double)Q;
        cout << fixed << setprecision(4) << (double)expected << "\n";
    }

    return 0;
}
