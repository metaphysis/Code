// Reduce the Maintenance Cost
// UVa ID: 12587
// Verdict: Accepted
// Submission Date: 2026-07-19
// UVa Run Time: 0.130s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int from;
    int to;
    int length;
    long long cost;
    int child;
};

struct Solver {
    int n;
    int m;
    int timer;
    int componentCount;
    vector<long long> townCost;
    vector<Edge> edges;
    vector<vector<pair<int, int>>> graph;
    vector<vector<pair<int, long long>>> bridgeGraph;
    vector<int> discoveryTime;
    vector<int> lowLink;
    vector<int> componentId;
    vector<int> subTreeSize;
    vector<int> componentSize;
    vector<bool> isBridge;
    vector<int> parent;
    vector<long long> parentEdgeCost;
    vector<int> traversalOrder;
    vector<bool> canWithoutParent;
    vector<bool> canWithParent;
    vector<long long> capacity;

    void tarjan(int current, int parentEdge) {
        discoveryTime[current] = lowLink[current] = ++timer;
        componentId[current] = componentCount;
        subTreeSize[current] = 1;
        componentSize[componentCount]++;
        for (int i = 0; i < (int)graph[current].size(); ++i) {
            int next = graph[current][i].first;
            int edgeId = graph[current][i].second;
            if (edgeId == parentEdge) continue;
            if (!discoveryTime[next]) {
                edges[edgeId].child = next;
                tarjan(next, edgeId);
                subTreeSize[current] += subTreeSize[next];
                lowLink[current] = min(lowLink[current], lowLink[next]);
                if (lowLink[next] > discoveryTime[current]) isBridge[edgeId] = true;
            } else lowLink[current] = min(lowLink[current], discoveryTime[next]);
        }
    }

    void buildBridgeForest() {
        bridgeGraph.assign(n + 1, {});
        for (int i = 0; i < m; ++i) {
            if (!isBridge[i]) continue;
            int child = edges[i].child;
            long long firstPart = subTreeSize[child];
            long long secondPart = componentSize[componentId[child]] - firstPart;
            edges[i].cost = firstPart * secondPart * edges[i].length;
            int u = edges[i].from;
            int v = edges[i].to;
            bridgeGraph[u].push_back(make_pair(v, edges[i].cost));
            bridgeGraph[v].push_back(make_pair(u, edges[i].cost));
        }
    }

    void buildTraversalOrder() {
        parent.assign(n + 1, -2);
        parentEdgeCost.assign(n + 1, 0);
        traversalOrder.clear();
        vector<int> stackValue;
        for (int i = 1; i <= n; ++i) {
            if (bridgeGraph[i].empty() || parent[i] != -2) continue;
            parent[i] = 0;
            stackValue.push_back(i);
            while (!stackValue.empty()) {
                int current = stackValue.back();
                stackValue.pop_back();
                traversalOrder.push_back(current);
                for (int j = 0; j < (int)bridgeGraph[current].size(); ++j) {
                    int next = bridgeGraph[current][j].first;
                    long long edgeCost = bridgeGraph[current][j].second;
                    if (next == parent[current]) continue;
                    parent[next] = current;
                    parentEdgeCost[next] = edgeCost;
                    stackValue.push_back(next);
                }
            }
        }
    }

    bool isFeasible(long long limit) {
        for (int i = 1; i <= n; ++i) {
            if (townCost[i] > limit) return false;
            capacity[i] = limit - townCost[i];
        }
        for (int i = (int)traversalOrder.size() - 1; i >= 0; --i) {
            int current = traversalOrder[i];
            long long requiredCost = 0;
            for (int j = 0; j < (int)bridgeGraph[current].size(); ++j) {
                int next = bridgeGraph[current][j].first;
                long long edgeCost = bridgeGraph[current][j].second;
                if (next == parent[current]) continue;
                if (canWithParent[next]) continue;
                if (!canWithoutParent[next]) return false;
                requiredCost += edgeCost;
                if (requiredCost > capacity[current]) return false;
            }
            canWithoutParent[current] = requiredCost <= capacity[current];
            canWithParent[current] = requiredCost + parentEdgeCost[current] <= capacity[current];
        }
        for (int i = 0; i < (int)traversalOrder.size(); ++i) {
            int current = traversalOrder[i];
            if (parent[current] != 0) continue;
            if (!canWithoutParent[current]) return false;
        }
        return true;
    }

    long long solve() {
        graph.assign(n + 1, {});
        for (int i = 0; i < m; ++i) {
            graph[edges[i].from].push_back(make_pair(edges[i].to, i));
            graph[edges[i].to].push_back(make_pair(edges[i].from, i));
        }
        timer = 0;
        componentCount = 0;
        discoveryTime.assign(n + 1, 0);
        lowLink.assign(n + 1, 0);
        componentId.assign(n + 1, 0);
        subTreeSize.assign(n + 1, 0);
        componentSize.assign(n + 1, 0);
        isBridge.assign(m, false);
        for (int i = 1; i <= n; ++i) {
            if (discoveryTime[i]) continue;
            ++componentCount;
            tarjan(i, -1);
        }
        buildBridgeForest();
        buildTraversalOrder();
        canWithoutParent.assign(n + 1, false);
        canWithParent.assign(n + 1, false);
        capacity.assign(n + 1, 0);
        long long left = 0;
        long long right = 0;
        long long totalBridgeCost = 0;
        for (int i = 1; i <= n; ++i) left = max(left, townCost[i]);
        for (int i = 0; i < m; ++i) {
            if (!isBridge[i]) continue;
            totalBridgeCost += edges[i].cost;
        }
        right = left + totalBridgeCost;
        while (left < right) {
            long long middle = left + (right - left) / 2;
            if (isFeasible(middle)) right = middle;
            else left = middle + 1;
        }
        return left;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCases;
    cin >> testCases;
    for (int caseNumber = 1; caseNumber <= testCases; ++caseNumber) {
        Solver solver;
        cin >> solver.n >> solver.m;
        solver.townCost.assign(solver.n + 1, 0);
        for (int i = 1; i <= solver.n; ++i) cin >> solver.townCost[i];
        solver.edges.resize(solver.m);
        for (int i = 0; i < solver.m; ++i) {
            cin >> solver.edges[i].from >> solver.edges[i].to >> solver.edges[i].length;
            solver.edges[i].cost = 0;
            solver.edges[i].child = 0;
        }
        cout << "Case " << caseNumber << ": " << solver.solve() << '\n';
    }
    return 0;
}
