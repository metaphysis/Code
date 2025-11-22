// Acme Corporation
// UVa ID: 11613
// Verdict: Accepted
// Submission Date: 2025-11-19
// UVa Run Time: 0.100s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net


#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const LL INF = 1e18;

struct MinCostMaxFlow {
    struct Edge {
        int to, rev;
        LL cap, cost, flow;
    };
    int n;
    vector<vector<Edge>> graph;
    vector<LL> dist, pot;
    vector<pair<int, int>> parent;
    vector<bool> inQueue;

    MinCostMaxFlow(int n) : n(n), graph(n), dist(n), pot(n, 0), parent(n), inQueue(n) {}

    void addEdge(int u, int v, LL cap, LL cost) {
        graph[u].push_back({v, (int)graph[v].size(), cap, cost, 0});
        graph[v].push_back({u, (int)graph[u].size() - 1, 0, -cost, 0});
    }

    bool bellmanFord(int s, int t) {
        fill(dist.begin(), dist.end(), INF);
        dist[s] = 0;
        queue<int> q;
        q.push(s);
        inQueue[s] = true;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            inQueue[u] = false;
            for (int i = 0; i < graph[u].size(); i++) {
                Edge &e = graph[u][i];
                if (e.cap - e.flow > 0 && dist[e.to] > dist[u] + e.cost + pot[u] - pot[e.to]) {
                    dist[e.to] = dist[u] + e.cost + pot[u] - pot[e.to];
                    parent[e.to] = {u, i};
                    if (!inQueue[e.to]) {
                        inQueue[e.to] = true;
                        q.push(e.to);
                    }
                }
            }
        }
        return dist[t] < INF;
    }

    pair<LL, LL> minCostMaxFlow(int s, int t) {
        LL totalFlow = 0, totalCost = 0;
        while (bellmanFord(s, t)) {
            for (int i = 0; i < n; i++) pot[i] += dist[i];
            if (pot[t] >= 0) break; // 关键优化：当增广路费用非负时停止
            
            LL f = INF;
            for (int v = t; v != s; v = parent[v].first) {
                int u = parent[v].first, i = parent[v].second;
                f = min(f, graph[u][i].cap - graph[u][i].flow);
            }
            for (int v = t; v != s; v = parent[v].first) {
                int u = parent[v].first, i = parent[v].second;
                graph[u][i].flow += f;
                graph[v][graph[u][i].rev].flow -= f;
            }
            totalFlow += f;
            totalCost += f * pot[t];
        }
        return {totalFlow, totalCost};
    }
};

int main() {
    int T; cin >> T;
    for (int caseNo = 1; caseNo <= T; caseNo++) {
        int M, I; cin >> M >> I;
        int source = 0, sink = 2 * M + 1;
        MinCostMaxFlow mcmf(2 * M + 2);
        for (int i = 1; i <= M; i++) {
            int mi, ni, pi, si, Ei; cin >> mi >> ni >> pi >> si >> Ei;
            mcmf.addEdge(source, i, ni, mi);
            mcmf.addEdge(M + i, sink, si, -pi);
            for (int j = i; j <= min(M, i + Ei); j++)
                mcmf.addEdge(i, M + j, INF, I * (j - i));
        }
        pair<LL, LL> result = mcmf.minCostMaxFlow(source, sink);
        cout << "Case " << caseNo << ": " << -result.second << endl;
    }
    return 0;
}
