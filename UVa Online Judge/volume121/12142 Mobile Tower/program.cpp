#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to, rev, cap, cost;
};

struct Cell {
    int x, y, typeTwoLine, typeThreeLine, cost;
    bool used;
};

class MinCostMaxFlow {
public:
    int nodeCount;
    vector<vector<Edge> > graph;

    MinCostMaxFlow(int nodeCount) {
        this->nodeCount = nodeCount;
        graph.resize(nodeCount);
    }

    int addEdge(int from, int to, int cap, int cost) {
        int edgeIndex = graph[from].size();
        Edge forward = {to, (int)graph[to].size(), cap, cost};
        Edge backward = {from, edgeIndex, 0, -cost};
        graph[from].push_back(forward);
        graph[to].push_back(backward);
        return edgeIndex;
    }

    pair<int, long long> solve(int source, int sink, int requiredFlow) {
        int flow = 0;
        long long totalCost = 0;
        const int inf = 0x3f3f3f3f;
        while (flow < requiredFlow) {
            vector<int> distance(nodeCount, inf), inQueue(nodeCount, 0), preNode(nodeCount, -1), preEdge(nodeCount, -1);
            queue<int> nodeQueue;
            distance[source] = 0;
            nodeQueue.push(source);
            inQueue[source] = 1;
            while (!nodeQueue.empty()) {
                int current = nodeQueue.front();
                nodeQueue.pop();
                inQueue[current] = 0;
                for (int i = 0; i < (int)graph[current].size(); i++) {
                    Edge &edge = graph[current][i];
                    if (edge.cap > 0 && distance[edge.to] > distance[current] + edge.cost) {
                        distance[edge.to] = distance[current] + edge.cost;
                        preNode[edge.to] = current;
                        preEdge[edge.to] = i;
                        if (!inQueue[edge.to]) {
                            inQueue[edge.to] = 1;
                            nodeQueue.push(edge.to);
                        }
                    }
                }
            }
            if (distance[sink] == inf) break;
            int addFlow = requiredFlow - flow;
            for (int current = sink; current != source; current = preNode[current]) addFlow = min(addFlow, graph[preNode[current]][preEdge[current]].cap);
            for (int current = sink; current != source; current = preNode[current]) {
                Edge &edge = graph[preNode[current]][preEdge[current]];
                edge.cap -= addFlow;
                graph[current][edge.rev].cap += addFlow;
            }
            flow += addFlow;
            totalCost += 1LL * addFlow * distance[sink];
        }
        return make_pair(flow, totalCost);
    }
};

vector<Cell> buildCells(int level) {
    const int directionCount = 6;
    int dx[directionCount] = {0, -1, -1, 0, 1, 1};
    int dy[directionCount] = {-2, -1, 1, 2, 1, -1};
    vector<Cell> cells;
    cells.push_back({0, 0, 0, 0, 0, false});
    for (int radius = 1; radius < level; radius++) {
        int x = radius * dx[0], y = radius * dy[0];
        for (int side = 0; side < directionCount; side++) {
            int moveDirection = (side + 2) % directionCount;
            for (int step = 0; step < radius; step++) {
                cells.push_back({x, y, 0, 0, 0, false});
                x += dx[moveDirection];
                y += dy[moveDirection];
            }
        }
    }
    int typeTwoX = cells[2].x, typeTwoY = cells[2].y;
    int typeThreeX = cells[3].x, typeThreeY = cells[3].y;
    for (int i = 0; i < (int)cells.size(); i++) {
        cells[i].typeTwoLine = typeTwoX * cells[i].y - typeTwoY * cells[i].x;
        cells[i].typeThreeLine = typeThreeX * cells[i].y - typeThreeY * cells[i].x;
    }
    return cells;
}

long long solveMonth(vector<Cell> &cells, int monthIndex, int towerCount) {
    map<int, int> typeTwoId, typeThreeId;
    for (int i = 0; i < (int)cells.size(); i++) {
        if (cells[i].used) continue;
        if (!typeTwoId.count(cells[i].typeTwoLine)) {
            int lineId = typeTwoId.size();
            typeTwoId[cells[i].typeTwoLine] = lineId;
        }
        if (!typeThreeId.count(cells[i].typeThreeLine)) {
            int lineId = typeThreeId.size();
            typeThreeId[cells[i].typeThreeLine] = lineId;
        }
    }
    int typeTwoCount = typeTwoId.size(), typeThreeCount = typeThreeId.size();
    int source = 0, typeTwoStart = 1;
    int typeThreeStart = typeTwoStart + typeTwoCount;
    int sink = typeThreeStart + typeThreeCount;
    MinCostMaxFlow minCostFlow(sink + 1);
    for (int i = 0; i < typeTwoCount; i++) minCostFlow.addEdge(source, typeTwoStart + i, 2, 0);
    for (int i = 0; i < typeThreeCount; i++) minCostFlow.addEdge(typeThreeStart + i, sink, 3, 0);
    vector<tuple<int, int, int> > cellEdges;
    for (int i = 0; i < (int)cells.size(); i++) {
        if (cells[i].used) continue;
        int from = typeTwoStart + typeTwoId[cells[i].typeTwoLine];
        int to = typeThreeStart + typeThreeId[cells[i].typeThreeLine];
        int edgeIndex = minCostFlow.addEdge(from, to, 1, cells[i].cost + monthIndex);
        cellEdges.push_back(make_tuple(i, from, edgeIndex));
    }
    pair<int, long long> result = minCostFlow.solve(source, sink, towerCount);
    for (int i = 0; i < (int)cellEdges.size(); i++) {
        int cellId = get<0>(cellEdges[i]), from = get<1>(cellEdges[i]), edgeIndex = get<2>(cellEdges[i]);
        if (minCostFlow.graph[from][edgeIndex].cap == 0) cells[cellId].used = true;
    }
    return result.second;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    for (int testCase = 1; testCase <= testCount; testCase++) {
        int level, monthCount;
        cin >> level >> monthCount;
        int cellCount = 3 * level * level - 3 * level + 1;
        vector<Cell> cells = buildCells(level);
        for (int i = 0; i < cellCount; i++) cin >> cells[i].cost;
        vector<int> towerCounts(monthCount);
        for (int i = 0; i < monthCount; i++) cin >> towerCounts[i];
        cout << "Case " << testCase << ":\n";
        for (int i = 0; i < monthCount; i++) {
            long long answer = solveMonth(cells, i, towerCounts[i]);
            cout << "Month " << i + 1 << ": " << answer << " unit of money\n";
        }
        cout << '\n';
    }
    return 0;
}
