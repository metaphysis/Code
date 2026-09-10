#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    while (testCount--) {
        int vertexCount, edgeCount;
        cin >> vertexCount >> edgeCount;
        vector<pair<int, int>> edges(edgeCount);
        vector<vector<pair<int, int>>> graph(vertexCount);
        vector<vector<char>> hasEdge(vertexCount, vector<char>(vertexCount, 0));
        for (int i = 0; i < edgeCount; ++i) {
            int from, to;
            cin >> from >> to;
            edges[i] = {from, to};
            graph[from].push_back({to, i});
            hasEdge[from][to] = 1;
        }
        vector<int> visitState(vertexCount, 0);
        vector<int> parentVertex(vertexCount, -1);
        vector<int> parentEdge(vertexCount, -1);
        vector<int> cycleEdges;
        function<bool(int)> findCycle = [&](int currentVertex) {
            visitState[currentVertex] = 1;
            for (auto edgeInfo : graph[currentVertex]) {
                int nextVertex = edgeInfo.first;
                int edgeIndex = edgeInfo.second;
                if (visitState[nextVertex] == 0) {
                    parentVertex[nextVertex] = currentVertex;
                    parentEdge[nextVertex] = edgeIndex;
                    if (findCycle(nextVertex)) return true;
                } else if (visitState[nextVertex] == 1) {
                    cycleEdges.push_back(edgeIndex);
                    int vertex = currentVertex;
                    while (vertex != nextVertex) {
                        cycleEdges.push_back(parentEdge[vertex]);
                        vertex = parentVertex[vertex];
                    }
                    return true;
                }
            }
            visitState[currentVertex] = 2;
            return false;
        };
        bool hasCycle = false;
        for (int i = 0; i < vertexCount; ++i)
            if (visitState[i] == 0 && findCycle(i)) {
                hasCycle = true;
                break;
            }
        bool possible = false;
        if (hasCycle) {
            for (int removedEdge : cycleEdges) {
                int startVertex = edges[removedEdge].first;
                int endVertex = edges[removedEdge].second;
                vector<int> indegree(vertexCount, 0);
                for (int i = 0; i < edgeCount; ++i)
                    if (i != removedEdge)
                        ++indegree[edges[i].second];
                queue<int> vertexQueue;
                for (int i = 0; i < vertexCount; ++i)
                    if (indegree[i] == 0)
                        vertexQueue.push(i);
                vector<int> topologicalOrder;
                while (!vertexQueue.empty()) {
                    int currentVertex = vertexQueue.front();
                    vertexQueue.pop();
                    topologicalOrder.push_back(currentVertex);
                    for (auto edgeInfo : graph[currentVertex]) {
                        int nextVertex = edgeInfo.first;
                        int edgeIndex = edgeInfo.second;
                        if (edgeIndex == removedEdge) continue;
                        if (--indegree[nextVertex] == 0)
                            vertexQueue.push(nextVertex);
                    }
                }
                if (static_cast<int>(topologicalOrder.size()) != vertexCount)
                    continue;
                if (topologicalOrder.front() != endVertex || topologicalOrder.back() != startVertex)
                    continue;
                bool isHamiltonianPath = true;
                for (int i = 0; i + 1 < vertexCount; ++i)
                    if (!hasEdge[topologicalOrder[i]][topologicalOrder[i + 1]]) {
                        isHamiltonianPath = false;
                        break;
                    }
                if (isHamiltonianPath) {
                    possible = true;
                    break;
                }
            }
        }
        if (possible)
            cout << "Yeah, I'm superman\n";
        else
            cout << "Your DAGy was initially defected!\n";
    }
    return 0;
}
