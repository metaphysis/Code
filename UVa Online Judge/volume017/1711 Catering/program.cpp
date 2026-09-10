#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to;
    int reverseIndex;
    int capacity;
    long long cost;
};

void addEdge(vector<vector<Edge>>& graph, int from, int to, int capacity, long long cost) {
    Edge forwardEdge = {to, static_cast<int>(graph[to].size()), capacity, cost};
    Edge reverseEdge = {from, static_cast<int>(graph[from].size()), 0, -cost};
    graph[from].push_back(forwardEdge);
    graph[to].push_back(reverseEdge);
}

bool spfa(
    vector<vector<Edge>>& graph,
    int source,
    int sink,
    vector<long long>& distance,
    vector<int>& parentVertex,
    vector<int>& parentEdge
) {
    int vertexCount = graph.size();
    const long long infinity = numeric_limits<long long>::max() / 4;
    vector<bool> inQueue(vertexCount, false);
    queue<int> pendingVertices;
    fill(distance.begin(), distance.end(), infinity);
    fill(parentVertex.begin(), parentVertex.end(), -1);
    fill(parentEdge.begin(), parentEdge.end(), -1);
    distance[source] = 0;
    pendingVertices.push(source);
    inQueue[source] = true;
    while (!pendingVertices.empty()) {
        int currentVertex = pendingVertices.front();
        pendingVertices.pop();
        inQueue[currentVertex] = false;
        for (int edgeIndex = 0; edgeIndex < static_cast<int>(graph[currentVertex].size()); edgeIndex++) {
            Edge& edge = graph[currentVertex][edgeIndex];
            if (edge.capacity > 0 && distance[edge.to] > distance[currentVertex] + edge.cost) {
                distance[edge.to] = distance[currentVertex] + edge.cost;
                parentVertex[edge.to] = currentVertex;
                parentEdge[edge.to] = edgeIndex;
                if (!inQueue[edge.to]) {
                    inQueue[edge.to] = true;
                    pendingVertices.push(edge.to);
                }
            }
        }
    }
    return distance[sink] != infinity;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    while (cin >> n >> k) {
        vector<vector<long long>> transportCost(n + 2, vector<long long>(n + 2, 0));
        for (int fromLocation = 1; fromLocation <= n; fromLocation++) {
            for (int toLocation = fromLocation + 1; toLocation <= n + 1; toLocation++) {
                cin >> transportCost[fromLocation][toLocation];
            }
        }
        vector<long long> startCost(n + 1, 0);
        long long baseCost = 0;
        for (int activity = 1; activity <= n; activity++) {
            startCost[activity] = transportCost[1][activity + 1];
            baseCost += startCost[activity];
        }
        int source = 0;
        int leftStart = 1;
        int rightStart = n + 1;
        int sink = 2 * n + 1;
        int vertexCount = sink + 1;
        vector<vector<Edge>> graph(vertexCount);
        for (int activity = 1; activity <= n; activity++) {
            addEdge(graph, source, leftStart + activity - 1, 1, 0);
            addEdge(graph, rightStart + activity - 1, sink, 1, 0);
        }
        for (int firstActivity = 1; firstActivity <= n; firstActivity++) {
            for (int secondActivity = firstActivity + 1; secondActivity <= n; secondActivity++) {
                long long changeCost = transportCost[firstActivity + 1][secondActivity + 1] - startCost[secondActivity];
                addEdge(
                    graph,
                    leftStart + firstActivity - 1,
                    rightStart + secondActivity - 1,
                    1,
                    changeCost
                );
            }
        }
        int requiredMatchCount = max(0, n - k);
        int maximumMatchCount = n - 1;
        vector<long long> distance(vertexCount);
        vector<int> parentVertex(vertexCount);
        vector<int> parentEdge(vertexCount);
        long long minimumChangeCost = numeric_limits<long long>::max();
        long long currentChangeCost = 0;
        int currentMatchCount = 0;
        if (requiredMatchCount == 0) {
            minimumChangeCost = 0;
        }
        while (currentMatchCount < maximumMatchCount && spfa(
            graph,
            source,
            sink,
            distance,
            parentVertex,
            parentEdge
        )) {
            currentMatchCount++;
            currentChangeCost += distance[sink];
            int currentVertex = sink;
            while (currentVertex != source) {
                int previousVertex = parentVertex[currentVertex];
                int edgeIndex = parentEdge[currentVertex];
                Edge& edge = graph[previousVertex][edgeIndex];
                edge.capacity--;
                graph[currentVertex][edge.reverseIndex].capacity++;
                currentVertex = previousVertex;
            }
            if (currentMatchCount >= requiredMatchCount) {
                minimumChangeCost = min(minimumChangeCost, currentChangeCost);
            }
        }
        cout << baseCost + minimumChangeCost << '\n';
    }
    return 0;
}
