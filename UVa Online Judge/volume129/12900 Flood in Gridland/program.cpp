#include <bits/stdc++.h>
using namespace std;

struct FlowEdge {
    int to, rev, cap;
    long long cost;
};

struct MinCostFlow {
    int nodeCount;
    vector<vector<FlowEdge>> graph;
    MinCostFlow(int nodeCount) : nodeCount(nodeCount), graph(nodeCount) {}
    void addEdge(int from, int to, int cap, long long cost) {
        FlowEdge forwardEdge = {to, (int)graph[to].size(), cap, cost};
        FlowEdge reverseEdge = {from, (int)graph[from].size(), 0, -cost};
        graph[from].push_back(forwardEdge);
        graph[to].push_back(reverseEdge);
    }
    pair<int, long long> run(int source, int target, int needFlow) {
        int flow = 0;
        long long cost = 0;
        const long long inf = 1LL << 60;
        while (flow < needFlow) {
            vector<long long> dist(nodeCount, inf);
            vector<int> preNode(nodeCount, -1), preEdge(nodeCount, -1), inQueue(nodeCount, 0);
            queue<int> que;
            dist[source] = 0;
            que.push(source);
            inQueue[source] = 1;
            while (!que.empty()) {
                int now = que.front();
                que.pop();
                inQueue[now] = 0;
                for (int i = 0; i < (int)graph[now].size(); i++) {
                    FlowEdge &edge = graph[now][i];
                    if (edge.cap <= 0) continue;
                    if (dist[edge.to] > dist[now] + edge.cost) {
                        dist[edge.to] = dist[now] + edge.cost;
                        preNode[edge.to] = now;
                        preEdge[edge.to] = i;
                        if (!inQueue[edge.to]) {
                            inQueue[edge.to] = 1;
                            que.push(edge.to);
                        }
                    }
                }
            }
            if (dist[target] == inf) break;
            int addFlow = needFlow - flow;
            for (int now = target; now != source; now = preNode[now])
                addFlow = min(addFlow, graph[preNode[now]][preEdge[now]].cap);
            for (int now = target; now != source; now = preNode[now]) {
                FlowEdge &edge = graph[preNode[now]][preEdge[now]];
                edge.cap -= addFlow;
                graph[now][edge.rev].cap += addFlow;
            }
            flow += addFlow;
            cost += 1LL * addFlow * dist[target];
        }
        return {flow, cost};
    }
};

bool checkFeasible(int nodeCount, const vector<tuple<int, int, long long>> &edges) {
    vector<long long> dist(nodeCount, 0);
    for (int round = 0; round < nodeCount; round++) {
        bool changed = false;
        for (auto edge : edges) {
            int from, to;
            long long weight;
            tie(from, to, weight) = edge;
            if (dist[to] > dist[from] + weight) {
                dist[to] = dist[from] + weight;
                changed = true;
            }
        }
        if (!changed) return true;
        if (round == nodeCount - 1) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    for (int testCase = 1; testCase <= testCount; testCase++) {
        int n, m, l, u;
        cin >> n >> m >> l >> u;
        static int height[75][75], rowDegree[75], colDegree[75];
        static bool isLand[75][75];
        memset(rowDegree, 0, sizeof(rowDegree));
        memset(colDegree, 0, sizeof(colDegree));
        vector<tuple<int, int, long long>> differenceEdges;
        int landCount = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                string value;
                cin >> value;
                if (value == "X") {
                    isLand[i][j] = false;
                    continue;
                }
                isLand[i][j] = true;
                height[i][j] = stoi(value);
                rowDegree[i]++;
                colDegree[j]++;
                landCount++;
                int rowNode = i;
                int colNode = n + j;
                differenceEdges.push_back({colNode, rowNode, 1LL * u - height[i][j]});
                differenceEdges.push_back({rowNode, colNode, 1LL * height[i][j] - l});
            }
        }
        cout << "Case " << testCase << ": ";
        if (!checkFeasible(n + m, differenceEdges)) {
            cout << "Impossible\n";
            continue;
        }
        int source = n + m;
        int target = source + 1;
        int totalNode = target + 1;
        MinCostFlow minCostFlow(totalNode);
        static int upperIndex[75][75], lowerIndex[75][75];
        for (int i = 0; i < n; i++)
            minCostFlow.addEdge(source, i, rowDegree[i], 0);
        for (int j = 0; j < m; j++)
            minCostFlow.addEdge(n + j, target, colDegree[j], 0);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (!isLand[i][j]) continue;
                int rowNode = i;
                int colNode = n + j;
                upperIndex[i][j] = minCostFlow.graph[rowNode].size();
                minCostFlow.addEdge(rowNode, colNode, landCount, 1LL * u - height[i][j]);
                lowerIndex[i][j] = minCostFlow.graph[colNode].size();
                minCostFlow.addEdge(colNode, rowNode, landCount, 1LL * height[i][j] - l);
            }
        }
        pair<int, long long> result = minCostFlow.run(source, target, landCount);
        if (result.first != landCount) {
            cout << "Impossible\n";
            continue;
        }
        vector<tuple<int, int, long long>> tightEdges = differenceEdges;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (!isLand[i][j]) continue;
                int rowNode = i;
                int colNode = n + j;
                FlowEdge &upperEdge = minCostFlow.graph[rowNode][upperIndex[i][j]];
                FlowEdge &lowerEdge = minCostFlow.graph[colNode][lowerIndex[i][j]];
                int upperFlow = landCount - upperEdge.cap;
                int lowerFlow = landCount - lowerEdge.cap;
                int netFlow = upperFlow - lowerFlow;
                if (netFlow > 0) {
                    long long bound = 1LL * u - height[i][j];
                    tightEdges.push_back({colNode, rowNode, bound});
                    tightEdges.push_back({rowNode, colNode, -bound});
                } else if (netFlow < 0) {
                    long long bound = 1LL * height[i][j] - l;
                    tightEdges.push_back({rowNode, colNode, bound});
                    tightEdges.push_back({colNode, rowNode, -bound});
                }
            }
        }
        vector<long long> value(n + m, 0);
        for (int round = 0; round < n + m; round++) {
            bool changed = false;
            for (auto edge : tightEdges) {
                int from, to;
                long long weight;
                tie(from, to, weight) = edge;
                if (value[to] > value[from] + weight) {
                    value[to] = value[from] + weight;
                    changed = true;
                }
            }
            if (!changed) break;
        }
        long long minValue = 0;
        for (long long x : value)
            minValue = min(minValue, x);
        for (long long &x : value)
            x -= minValue;
        long long answer = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (!isLand[i][j]) continue;
                long long finalHeight = height[i][j] + value[i] - value[n + j];
                answer += finalHeight;
            }
        }
        cout << answer << '\n';
        for (int i = 0; i < n; i++) {
            if (i) cout << ' ';
            cout << value[i];
        }
        cout << '\n';
        for (int j = 0; j < m; j++) {
            if (j) cout << ' ';
            cout << value[n + j];
        }
        cout << '\n';
    }
    return 0;
}
