#include <bits/stdc++.h>
using namespace std;

using int64 = long long;

const int64 INF = (1LL << 60);

struct Edge {
    int from, to;
    int64 weight;
};

vector<int64> dijkstra(
    int vertexCount,
    const vector<vector<pair<int, int64>>>& graph, int source) {
    vector<int64> distance(vertexCount + 1, INF);
    using State = pair<int64, int>;
    priority_queue<State, vector<State>, greater<State>> minHeap;
    distance[source] = 0;
    minHeap.push({0, source});
    while (!minHeap.empty()) {
        int64 currentDistance = minHeap.top().first;
        int currentVertex = minHeap.top().second;
        minHeap.pop();
        if (currentDistance != distance[currentVertex]) continue;
        for (const pair<int, int64>& next : graph[currentVertex]) {
            int nextVertex = next.first;
            int64 edgeWeight = next.second;
            int64 newDistance = currentDistance + edgeWeight;
            if (newDistance < distance[nextVertex]) {
                distance[nextVertex] = newDistance;
                minHeap.push({newDistance, nextVertex});
            }
        }
    }
    return distance;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    for (int cs = 1; cs <= T; ++cs) {
        int vertexCount;
        int edgeCount;
        cin >> vertexCount >> edgeCount;
        vector<Edge> edges(edgeCount + 1);
        vector<vector<pair<int, int64>>> graph(vertexCount + 1);
        for (int edgeIndex = 1; edgeIndex <= edgeCount; ++edgeIndex) {
            int from;
            int to;
            int64 weight;
            cin >> from >> to >> weight;
            edges[edgeIndex] = {from, to, weight};
            graph[from].push_back({to, weight});
        }
        vector<int64> distance = dijkstra(vertexCount, graph, 1);
        vector<int> shortestIncomingCount(vertexCount + 1, 0);
        shortestIncomingCount[1] = 1;
        for (int edgeIndex = 1; edgeIndex <= edgeCount; ++edgeIndex) {
            const Edge& edge = edges[edgeIndex];
            if (distance[edge.from] + edge.weight == distance[edge.to]) ++shortestIncomingCount[edge.to];
        }
        int64 answer = 0;
        for (int edgeIndex = 1; edgeIndex <= edgeCount; ++edgeIndex) {
            const Edge& edge = edges[edgeIndex];
            int64 edgeSlack =
                distance[edge.from] + edge.weight - distance[edge.to];
            int64 coefficientA = (distance[edge.from] + edge.weight > distance[edge.to] || shortestIncomingCount[edge.to] > 1) ? -1 : 0;
            int64 coefficientB = edgeSlack;
            int64 index = edgeIndex;
            answer += index * coefficientA + index * index * coefficientB;
        }
        cout << "Case " << cs << ": " << answer << '\n';
    }
    return 0;
}
