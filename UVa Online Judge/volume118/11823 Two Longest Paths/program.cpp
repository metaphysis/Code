// Two Longest Paths
// UVa ID: 11823
// Verdict: Accepted
// Submission Date: 2026-06-21
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

struct Edge {
    int to, rev, cap, cost;
};

class MinCostMaxFlow {
public:
    int n;
    vector<vector<Edge>> g;
    MinCostMaxFlow(int n) : n(n), g(n) {}

    void addEdge(int u, int v, int cap, int cost) {
        Edge a{v, (int)g[v].size(), cap, cost};
        Edge b{u, (int)g[u].size(), 0, -cost};
        g[u].push_back(a);
        g[v].push_back(b);
    }

    pair<int, int> minCostFlow(int s, int t, int maxf) {
        int flow = 0, cost = 0;
        vector<int> dist(n), preV(n), preE(n);
        vector<bool> inq(n);

        while (flow < maxf) {
            fill(dist.begin(), dist.end(), INF);
            fill(inq.begin(), inq.end(), false);
            queue<int> q;
            dist[s] = 0;
            q.push(s);
            inq[s] = true;

            while (!q.empty()) {
                int u = q.front(); q.pop();
                inq[u] = false;
                for (int i = 0; i < (int)g[u].size(); ++i) {
                    Edge &e = g[u][i];
                    if (e.cap > 0 && dist[e.to] > dist[u] + e.cost) {
                        dist[e.to] = dist[u] + e.cost;
                        preV[e.to] = u;
                        preE[e.to] = i;
                        if (!inq[e.to]) {
                            q.push(e.to);
                            inq[e.to] = true;
                        }
                    }
                }
            }

            if (dist[t] == INF) break; // 无法继续增广

            int d = maxf - flow;
            for (int v = t; v != s; v = preV[v])
                d = min(d, g[preV[v]][preE[v]].cap);

            flow += d;
            cost += d * dist[t];
            for (int v = t; v != s; v = preV[v]) {
                Edge &e = g[preV[v]][preE[v]];
                e.cap -= d;
                g[v][e.rev].cap += d;
            }
        }
        return {flow, cost};
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int N, M;
        cin >> N >> M;
        int S = 0, TNode = 2 * N + 1;
        MinCostMaxFlow mcmf(TNode + 1);

        // 拆点：入点 i (1..N)，出点 i+N (N+1..2N)
        for (int i = 1; i <= N; ++i) {
            mcmf.addEdge(S, i, 1, 0);                 // S -> 入点
            mcmf.addEdge(i, i + N, 1, -1);            // 入点 -> 出点，费用 -1（收益 1）
            mcmf.addEdge(i + N, TNode, 1, 0);         // 出点 -> T
        }

        for (int i = 0; i < M; ++i) {
            int A, B;
            cin >> A >> B;
            mcmf.addEdge(A + N, B, 1, 0);             // A的出点 -> B的入点
        }

        auto res = mcmf.minCostFlow(S, TNode, 2);
        // 流量可能不足 2，但题目数据保证有解（N>=2 且每个点可单独作为路径）
        int answer = -res.second; // 总收益 = -最小费用
        cout << answer << '\n';
    }
    return 0;
}
