// Concert Hall Scheduling
// UVa ID: 1317
// Verdict: Accepted
// Submission Date: 2026-01-22
// UVa Run Time: 0.120s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
const int DAYS = 367;  // 第366天作为虚拟结束点

struct Edge {
    int to, rev, cap, cost;
};

struct MinCostMaxFlow {
    vector<vector<Edge>> g;
    vector<int> dist, potential, prevv, preve;
    int n;
    
    MinCostMaxFlow(int n) : n(n), g(n), dist(n), potential(n), prevv(n), preve(n) {}
    
    void addEdge(int from, int to, int cap, int cost) {
        g[from].push_back({to, (int)g[to].size(), cap, cost});
        g[to].push_back({from, (int)g[from].size() - 1, 0, -cost});
    }
    
    pair<int, int> minCostMaxFlow(int s, int t, int maxf) {
        int flow = 0, cost = 0;
        fill(potential.begin(), potential.end(), 0);
        while (flow < maxf) {
            fill(dist.begin(), dist.end(), INF);
            dist[s] = 0;
            using P = pair<int, int>;
            priority_queue<P, vector<P>, greater<P>> pq;
            pq.push({0, s});
            while (!pq.empty()) {
                auto [d, v] = pq.top(); pq.pop();
                if (dist[v] < d) continue;
                for (int i = 0; i < g[v].size(); i++) {
                    Edge& e = g[v][i];
                    if (e.cap > 0 && dist[e.to] > dist[v] + e.cost + potential[v] - potential[e.to]) {
                        dist[e.to] = dist[v] + e.cost + potential[v] - potential[e.to];
                        prevv[e.to] = v;
                        preve[e.to] = i;
                        pq.push({dist[e.to], e.to});
                    }
                }
            }
            if (dist[t] == INF) break;
            for (int v = 0; v < n; v++) potential[v] += dist[v];
            int d = maxf - flow;
            for (int v = t; v != s; v = prevv[v]) {
                d = min(d, g[prevv[v]][preve[v]].cap);
            }
            flow += d;
            cost += d * potential[t];
            for (int v = t; v != s; v = prevv[v]) {
                Edge& e = g[prevv[v]][preve[v]];
                e.cap -= d;
                g[v][e.rev].cap += d;
            }
        }
        return {flow, cost};
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while (cin >> n && n) {
        // 节点编号：
        // 0: 源点 S
        // 1-366: 第1-366天（其中第366天是虚拟结束点）
        // 367-366+n: 区间节点
        // 367+n: 汇点 T
        int S = 0;
        int T = DAYS + n + 1;
        int dayStart = 1;
        int intervalStart = DAYS + 1;
        int totalNodes = T + 1;
        MinCostMaxFlow mcmf(totalNodes);
        // 从源点到第1天，容量为2（两个厅室）
        mcmf.addEdge(S, dayStart, 2, 0);
        // 天数之间的连接边，容量为2
        for (int d = 1; d < DAYS; d++)
            mcmf.addEdge(dayStart + d - 1, dayStart + d, 2, 0);
        // 从第366天到汇点
        mcmf.addEdge(dayStart + DAYS - 1, T, 2, 0);
        // 添加区间
        for (int i = 0; i < n; i++) {
            int start, end, value;
            cin >> start >> end >> value;
            int intervalNode = intervalStart + i;
            // 从第start天到区间节点，容量为1，费用为0
            mcmf.addEdge(dayStart + start - 1, intervalNode, 1, 0);
            // 从区间节点到第end+1天，容量为1，费用为-value
            // 注意：如果end+1超过365，则连接到第366天
            int nextDay = min(end + 1, DAYS);
            mcmf.addEdge(intervalNode, dayStart + nextDay - 1, 1, -value);
        }
        // 求最小费用最大流，最大流量为2
        auto result = mcmf.minCostMaxFlow(S, T, 2);
        int maxIncome = -result.second;
        cout << maxIncome << "\n";
    }
    return 0;
}
