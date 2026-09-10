// Insurrection
// UVa ID: 11146
// Verdict: Accepted
// Submission Date: 2026-07-30
// UVa Run Time: 0.010s

#include <bits/stdc++.h>
using namespace std;

const long double infiniteValue = 1e50L;
const long double epsilonValue = 1e-18L;

struct Road {
    int start;
    int end;
};

struct FlowEdge {
    int to;
    int reverseIndex;
    long double capacity;
};

class Dinic {
private:
    int vertexCount;
    vector<vector<FlowEdge>> graph;
    vector<int> level;
    vector<int> currentEdge;

    bool buildLevelGraph(int source, int target) {
        fill(level.begin(), level.end(), -1);
        queue<int> vertexQueue;
        level[source] = 0;
        vertexQueue.push(source);
        while (!vertexQueue.empty()) {
            int currentVertex = vertexQueue.front();
            vertexQueue.pop();
            for (const FlowEdge &edge : graph[currentVertex]) {
                if (edge.capacity > epsilonValue && level[edge.to] == -1) {
                    level[edge.to] = level[currentVertex] + 1;
                    vertexQueue.push(edge.to);
                }
            }
        }
        return level[target] != -1;
    }

    long double sendFlow(int currentVertex, int target, long double flow) {
        if (currentVertex == target) return flow;
        for (int &edgeIndex = currentEdge[currentVertex]; edgeIndex < static_cast<int>(graph[currentVertex].size()); edgeIndex++) {
            FlowEdge &edge = graph[currentVertex][edgeIndex];
            if (edge.capacity > epsilonValue && level[edge.to] == level[currentVertex] + 1) {
                long double currentFlow = sendFlow(edge.to, target, min(flow, edge.capacity));
                if (currentFlow > epsilonValue) {
                    edge.capacity -= currentFlow;
                    graph[edge.to][edge.reverseIndex].capacity += currentFlow;
                    return currentFlow;
                }
            }
        }
        return 0;
    }

public:
    explicit Dinic(int vertexCount) : vertexCount(vertexCount), graph(vertexCount), level(vertexCount), currentEdge(vertexCount) {
    }

    void addEdge(int start, int end, long double capacity) {
        FlowEdge forwardEdge = {end, static_cast<int>(graph[end].size()), capacity};
        FlowEdge reverseEdge = {start, static_cast<int>(graph[start].size()), 0};
        graph[start].push_back(forwardEdge);
        graph[end].push_back(reverseEdge);
    }

    long double getMaxFlow(int source, int target) {
        long double maxFlow = 0;
        while (buildLevelGraph(source, target)) {
            fill(currentEdge.begin(), currentEdge.end(), 0);
            while (true) {
                long double currentFlow = sendFlow(source, target, infiniteValue);
                if (currentFlow <= epsilonValue) break;
                maxFlow += currentFlow;
            }
        }
        return maxFlow;
    }
};

vector<long double> getShortestDistances(int startVertex, int vertexCount, const vector<Road> &roads, const vector<long double> &territoryCost) {
    vector<long double> distance(vertexCount + 1, infiniteValue);
    distance[startVertex] = 0;
    for (int round = 1; round <= vertexCount - 1; round++) {
        bool hasChanged = false;
        for (const Road &road : roads) {
            long double enterCost = road.end == 1 || road.end == vertexCount ? 0 : territoryCost[road.end];
            if (distance[road.start] < infiniteValue / 2 && distance[road.end] > distance[road.start] + enterCost) {
                distance[road.end] = distance[road.start] + enterCost;
                hasChanged = true;
            }
            enterCost = road.start == 1 || road.start == vertexCount ? 0 : territoryCost[road.start];
            if (distance[road.end] < infiniteValue / 2 && distance[road.start] > distance[road.end] + enterCost) {
                distance[road.start] = distance[road.end] + enterCost;
                hasChanged = true;
            }
        }
        if (!hasChanged) break;
    }
    return distance;
}

int getInVertex(int vertex) {
    return vertex * 2;
}

int getOutVertex(int vertex) {
    return vertex * 2 + 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    cout << fixed << setprecision(4);
    while (testCount--) {
        int vertexCount;
        int roadCount;
        cin >> vertexCount >> roadCount;
        vector<long double> territoryCost(vertexCount + 1, 0);
        for (int vertex = 2; vertex <= vertexCount - 1; vertex++) cin >> territoryCost[vertex];
        vector<Road> roads(roadCount);
        for (Road &road : roads) cin >> road.start >> road.end;
        vector<long double> distanceFromBizz = getShortestDistances(1, vertexCount, roads, territoryCost);
        vector<long double> distanceFromPezz = getShortestDistances(vertexCount, vertexCount, roads, territoryCost);
        if (distanceFromBizz[vertexCount] >= infiniteValue / 2) {
            cout << "0.0000\n";
            continue;
        }
        vector<long double> towerCost(vertexCount + 1, infiniteValue);
        long double negativeCostSum = 0;
        for (int vertex = 2; vertex <= vertexCount - 1; vertex++) {
            if (distanceFromBizz[vertex] < infiniteValue / 2 && distanceFromPezz[vertex] < infiniteValue / 2) {
                towerCost[vertex] = distanceFromBizz[vertex] + distanceFromPezz[vertex];
                if (towerCost[vertex] < 0) negativeCostSum += towerCost[vertex];
            }
        }
        Dinic dinic(vertexCount * 2 + 2);
        int source = getOutVertex(1);
        int target = getInVertex(vertexCount);
        for (int vertex = 1; vertex <= vertexCount; vertex++) {
            long double capacity = infiniteValue;
            if (vertex != 1 && vertex != vertexCount) {
                if (towerCost[vertex] < infiniteValue / 2) capacity = max(static_cast<long double>(0), towerCost[vertex]);
            }
            dinic.addEdge(getInVertex(vertex), getOutVertex(vertex), capacity);
        }
        for (const Road &road : roads) {
            dinic.addEdge(getOutVertex(road.start), getInVertex(road.end), infiniteValue);
            dinic.addEdge(getOutVertex(road.end), getInVertex(road.start), infiniteValue);
        }
        long double minimumCut = dinic.getMaxFlow(source, target);
        if (minimumCut >= infiniteValue / 2) {
            cout << "No Solution!\n";
        } else {
            long double answer = negativeCostSum + minimumCut;
            if (fabsl(answer) < 0.00005L) answer = 0;
            cout << answer << '\n';
        }
    }
    return 0;
}
