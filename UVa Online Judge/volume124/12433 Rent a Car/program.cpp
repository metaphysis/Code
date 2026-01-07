// Rent a Car
// UVa ID: 12433
// Verdict: Accepted
// Submission Date: 2026-01-05
// UVa Run Time: 0.070s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;
const int MAXN = 205;

struct Edge {
    int to, capacity, cost, rev;
    Edge(int t, int cap, int c, int r) : to(t), capacity(cap), cost(c), rev(r) {}
};

class MinCostMaxFlow {
    int n;
    vector<vector<Edge>> graph;
    vector<int> dist, inq, prevNode, prevEdge;
    
public:
    MinCostMaxFlow(int size) : n(size) {
        graph.resize(n);
        dist.resize(n);
        inq.resize(n);
        prevNode.resize(n);
        prevEdge.resize(n);
    }
    
    void addEdge(int from, int to, int capacity, int cost) {
        graph[from].emplace_back(to, capacity, cost, graph[to].size());
        graph[to].emplace_back(from, 0, -cost, graph[from].size() - 1);
    }
    
    bool spfa(int source, int sink) {
        fill(dist.begin(), dist.end(), INF);
        fill(inq.begin(), inq.end(), 0);
        queue<int> q;
        q.push(source);
        dist[source] = 0;
        inq[source] = 1;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            inq[u] = 0;
            for (int i = 0; i < graph[u].size(); i++) {
                Edge& e = graph[u][i];
                if (e.capacity > 0 && dist[u] + e.cost < dist[e.to]) {
                    dist[e.to] = dist[u] + e.cost;
                    prevNode[e.to] = u;
                    prevEdge[e.to] = i;
                    if (!inq[e.to]) {
                        inq[e.to] = 1;
                        q.push(e.to);
                    }
                }
            }
        }
        return dist[sink] < INF;
    }
    
    pair<int, int> solve(int source, int sink) {
        int flow = 0, cost = 0;
        while (spfa(source, sink)) {
            // 计算增广路的流量
            int f = INF;
            for (int v = sink; v != source; v = prevNode[v]) {
                int u = prevNode[v];
                int idx = prevEdge[v];
                f = min(f, graph[u][idx].capacity);
            }
            // 更新流量和费用
            flow += f;
            cost += f * dist[sink];
            // 更新残余网络
            for (int v = sink; v != source; v = prevNode[v]) {
                int u = prevNode[v];
                int idx = prevEdge[v];
                graph[u][idx].capacity -= f;
                int rev = graph[u][idx].rev;
                graph[v][rev].capacity += f;
            }
        }
        return {flow, cost};
    }
};

int main() {
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
    int T;  cin >> T;
    for (int caseNo = 1; caseNo <= T; caseNo++) {
        int N, C, R;
        cin >> N >> C >> R;
        vector<int> req(N + 1);
        int totalReq = 0;
        for (int i = 1; i <= N; i++) {
            cin >> req[i];
            totalReq += req[i];
        }
        vector<pair<int, int>> companies(C);
        for (int i = 0; i < C; i++)
            cin >> companies[i].first >> companies[i].second;
        vector<pair<int, int>> services(R);
        for (int i = 0; i < R; i++)
            cin >> services[i].first >> services[i].second;
        // 节点编号：
        // 0: 源点
        // 1..N: 需求节点 (Day_i_demand)
        // N+1..2N: 供应节点 (Day_i_supply)
        // 2N+1: 购买节点
        // 2N+2: 汇点
         int S = 0;
        int demandStart = 1;
        int supplyStart = demandStart + N;
        int purchaseNode = supplyStart + N;
        int T = purchaseNode + 1;
        int totalNodes = T + 1;
        MinCostMaxFlow mcmf(totalNodes);
        // 1. 源点到需求节点：每天必须有r[i]的流量流出
        for (int i = 1; i <= N; i++)
            mcmf.addEdge(S, demandStart + i - 1, req[i], 0);
        // 2. 供应节点到汇点：每天必须有r[i]的流量流入
        for (int i = 1; i <= N; i++)
            mcmf.addEdge(supplyStart + i - 1, T, req[i], 0);
        // 3. 购买边：源点到购买节点
        for (int i = 0; i < C; i++)
            mcmf.addEdge(S, purchaseNode, companies[i].first, companies[i].second);
        // 4. 购买节点到供应节点：购买的车可以在任何天使用
        for (int i = 1; i <= N; i++)
            mcmf.addEdge(purchaseNode, supplyStart + i - 1, INF, 0);
        // 5. 库存传递：今天的未使用需求可以传递到明天
        for (int i = 1; i < N; i++)
            mcmf.addEdge(demandStart + i - 1, demandStart + i, INF, 0);
        // 6. 维修边：今天使用的车，维修d天后，在d+1天后可用
        // 注意：天数是 i + d[j] + 1，不是 i + d[j]
        for (int i = 1; i <= N; i++)
            for (int j = 0; j < R; j++) {
                int serviceDays = services[j].first;
                int serviceCost = services[j].second;
                int futureDay = i + serviceDays + 1;  // 关键：+1
                if (futureDay <= N)
                    // 从需求节点i到供应节点futureDay
                    mcmf.addEdge(demandStart + i - 1, 
                                supplyStart + futureDay - 1, 
                                INF, serviceCost);
            }
        // 运行最小费用最大流
        auto [flow, cost] = mcmf.solve(S, T);
        cout << "Case " << caseNo << ": ";
        if (flow < totalReq) cout << "impossible\n";
        else cout << cost << "\n";
    }
    return 0;
}
