#include <bits/stdc++.h>
using namespace std;

const long long Inf = (1LL << 60);

struct Edge {
    int to, rev, cap, cost;
};

vector<Edge> graph[105];

void addEdge(int from, int to, int cap, int cost) {
    Edge forwardEdge = {to, (int)graph[to].size(), cap, cost};
    Edge reverseEdge = {from, (int)graph[from].size(), 0, -cost};
    graph[from].push_back(forwardEdge);
    graph[to].push_back(reverseEdge);
}

pair<bool, long long> minCostFlow(int source, int sink, int need, int vertexCount) {
    int flow = 0;
    long long totalCost = 0;
    vector<long long> potential(vertexCount, 0);
    while (flow < need) {
        vector<long long> dis(vertexCount, Inf);
        vector<int> preVertex(vertexCount, -1), preEdge(vertexCount, -1);
        priority_queue<pair<long long, int>, vector<pair<long long, int> >, greater<pair<long long, int> > > que;
        dis[source] = 0;
        que.push({0, source});
        while (!que.empty()) {
            long long currentDis = que.top().first;
            int u = que.top().second;
            que.pop();
            if (currentDis != dis[u])
                continue;
            for (int i = 0; i < (int)graph[u].size(); i++) {
                Edge &edge = graph[u][i];
                if (edge.cap == 0)
                    continue;
                long long newDis = currentDis + edge.cost + potential[u] - potential[edge.to];
                if (newDis < dis[edge.to]) {
                    dis[edge.to] = newDis;
                    preVertex[edge.to] = u;
                    preEdge[edge.to] = i;
                    que.push({newDis, edge.to});
                }
            }
        }
        if (dis[sink] == Inf)
            return {false, 0};
        for (int i = 0; i < vertexCount; i++)
            if (dis[i] != Inf)
                potential[i] += dis[i];
        int addFlow = need - flow;
        for (int v = sink; v != source; v = preVertex[v])
            addFlow = min(addFlow, graph[preVertex[v]][preEdge[v]].cap);
        for (int v = sink; v != source; v = preVertex[v]) {
            Edge &edge = graph[preVertex[v]][preEdge[v]];
            edge.cap -= addFlow;
            graph[v][edge.rev].cap += addFlow;
        }
        flow += addFlow;
        totalCost += 1LL * addFlow * potential[sink];
    }
    return {true, totalCost};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    for (int caseNumber = 1; caseNumber <= testCount; caseNumber++) {
        int n, m;
        cin >> n >> m;
        for (int i = 0; i < 105; i++)
            graph[i].clear();
        int inDegree[105] = {}, outDegree[105] = {};
        long long baseCost = 0;
        bool possible = true;
        for (int i = 0; i < m; i++) {
            int u, v, t, q, p;
            cin >> u >> v >> t >> q >> p;
            if (q > p)
                possible = false;
            baseCost += 1LL * q * t;
            outDegree[u] += q;
            inDegree[v] += q;
            addEdge(u, v, max(0, p - q), t);
        }
        int source = n + 1, sink = n + 2;
        int need = 0;
        for (int i = 1; i <= n; i++) {
            int balance = inDegree[i] - outDegree[i];
            if (balance > 0) {
                addEdge(source, i, balance, 0);
                need += balance;
            } else if (balance < 0) {
                addEdge(i, sink, -balance, 0);
            }
        }
        pair<bool, long long> result = {false, 0};
        if (possible)
            result = minCostFlow(source, sink, need, n + 3);
        cout << "Case #" << caseNumber << ": ";
        if (!possible || !result.first)
            cout << "Impossible\n";
        else
            cout << baseCost + result.second << '\n';
    }
    return 0;
}
