#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v;
};

int rowCount, colCount, vertexCount, edgeCount;
vector<string> grid;
vector<int> edgeState;
vector<Edge> edges;
vector<vector<int>> vertexEdges;
vector<vector<int>> cellEdges;

bool setEdge(int id, int value) {
    if (edgeState[id] != -1 && edgeState[id] != value) return false;
    if (edgeState[id] == -1) edgeState[id] = value;
    return true;
}

bool propagate() {
    bool changed = true;
    while (changed) {
        changed = false;
        for (int r = 0; r < rowCount; r++) {
            for (int c = 0; c < colCount; c++) {
                if (grid[r][c] == '.') continue;
                int target = grid[r][c] - '0', selected = 0, unknown = 0;
                for (int edgeId : cellEdges[r * colCount + c]) {
                    if (edgeState[edgeId] == 1) selected++;
                    if (edgeState[edgeId] == -1) unknown++;
                }
                if (selected > target || selected + unknown < target) return false;
                if (selected == target) {
                    for (int edgeId : cellEdges[r * colCount + c]) {
                        if (edgeState[edgeId] == -1) {
                            if (!setEdge(edgeId, 0)) return false;
                            changed = true;
                        }
                    }
                } else if (selected + unknown == target) {
                    for (int edgeId : cellEdges[r * colCount + c]) {
                        if (edgeState[edgeId] == -1) {
                            if (!setEdge(edgeId, 1)) return false;
                            changed = true;
                        }
                    }
                }
            }
        }
        for (int vertex = 0; vertex < vertexCount; vertex++) {
            int selected = 0, unknown = 0;
            for (int edgeId : vertexEdges[vertex]) {
                if (edgeState[edgeId] == 1) selected++;
                if (edgeState[edgeId] == -1) unknown++;
            }
            if (selected > 2) return false;
            if (selected == 1 && unknown == 0) return false;
            if (selected == 2) {
                for (int edgeId : vertexEdges[vertex]) {
                    if (edgeState[edgeId] == -1) {
                        if (!setEdge(edgeId, 0)) return false;
                        changed = true;
                    }
                }
            } else if (selected == 1 && unknown == 1) {
                for (int edgeId : vertexEdges[vertex]) {
                    if (edgeState[edgeId] == -1) {
                        if (!setEdge(edgeId, 1)) return false;
                        changed = true;
                    }
                }
            } else if (selected == 0 && unknown == 1) {
                for (int edgeId : vertexEdges[vertex]) {
                    if (edgeState[edgeId] == -1) {
                        if (!setEdge(edgeId, 0)) return false;
                        changed = true;
                    }
                }
            }
        }
    }
    return true;
}

int checkCycleState() {
    vector<int> visited(vertexCount, 0);
    int selectedEdges = 0;
    for (int state : edgeState) {
        if (state == 1) selectedEdges++;
    }
    for (int start = 0; start < vertexCount; start++) {
        if (visited[start] || vertexEdges[start].empty()) continue;
        bool hasSelected = false;
        for (int edgeId : vertexEdges[start]) {
            if (edgeState[edgeId] == 1) {
                hasSelected = true;
                break;
            }
        }
        if (!hasSelected) continue;
        queue<int> queueData;
        queueData.push(start);
        visited[start] = 1;
        int vertexTotal = 0, edgeTotal = 0;
        while (!queueData.empty()) {
            int vertex = queueData.front();
            queueData.pop();
            vertexTotal++;
            for (int edgeId : vertexEdges[vertex]) {
                if (edgeState[edgeId] != 1) continue;
                edgeTotal++;
                int nextVertex = edges[edgeId].u ^ edges[edgeId].v ^ vertex;
                if (!visited[nextVertex]) {
                    visited[nextVertex] = 1;
                    queueData.push(nextVertex);
                }
            }
        }
        edgeTotal /= 2;
        if (edgeTotal == vertexTotal) {
            if (selectedEdges != edgeTotal) return -1;
            for (int r = 0; r < rowCount; r++) {
                for (int c = 0; c < colCount; c++) {
                    if (grid[r][c] == '.') continue;
                    int count = 0;
                    for (int edgeId : cellEdges[r * colCount + c]) {
                        if (edgeState[edgeId] == 1) count++;
                    }
                    if (count != grid[r][c] - '0') return -1;
                }
            }
            return 1;
        }
    }
    return 0;
}

bool checkFinal() {
    int selectedEdges = 0;
    for (int edgeId = 0; edgeId < edgeCount; edgeId++) {
        if (edgeState[edgeId] == 1) selectedEdges++;
    }
    if (selectedEdges == 0) return false;
    vector<int> degree(vertexCount, 0);
    vector<vector<int>> graph(vertexCount);
    for (int edgeId = 0; edgeId < edgeCount; edgeId++) {
        if (edgeState[edgeId] != 1) continue;
        int u = edges[edgeId].u, v = edges[edgeId].v;
        degree[u]++;
        degree[v]++;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    for (int vertex = 0; vertex < vertexCount; vertex++) {
        if (degree[vertex] != 0 && degree[vertex] != 2) return false;
    }
    int start = -1;
    for (int vertex = 0; vertex < vertexCount; vertex++) {
        if (degree[vertex] == 2) {
            start = vertex;
            break;
        }
    }
    if (start == -1) return false;
    vector<int> visited(vertexCount, 0);
    queue<int> queueData;
    queueData.push(start);
    visited[start] = 1;
    while (!queueData.empty()) {
        int vertex = queueData.front();
        queueData.pop();
        for (int nextVertex : graph[vertex]) {
            if (!visited[nextVertex]) {
                visited[nextVertex] = 1;
                queueData.push(nextVertex);
            }
        }
    }
    for (int vertex = 0; vertex < vertexCount; vertex++) {
        if (degree[vertex] == 2 && !visited[vertex]) return false;
    }
    for (int r = 0; r < rowCount; r++) {
        for (int c = 0; c < colCount; c++) {
            if (grid[r][c] == '.') continue;
            int count = 0;
            for (int edgeId : cellEdges[r * colCount + c]) {
                if (edgeState[edgeId] == 1) count++;
            }
            if (count != grid[r][c] - '0') return false;
        }
    }
    return true;
}

bool dfs() {
    if (!propagate()) return false;
    int cycleState = checkCycleState();
    if (cycleState == 1) return true;
    if (cycleState == -1) return false;
    int chooseEdge = -1, bestScore = -1;
    for (int edgeId = 0; edgeId < edgeCount; edgeId++) {
        if (edgeState[edgeId] != -1) continue;
        int score = 0;
        for (int r = 0; r < rowCount; r++) {
            for (int c = 0; c < colCount; c++) {
                if (grid[r][c] == '.') continue;
                for (int cellEdge : cellEdges[r * colCount + c]) {
                    if (cellEdge == edgeId) score++;
                }
            }
        }
        if (score > bestScore) {
            bestScore = score;
            chooseEdge = edgeId;
        }
    }
    if (chooseEdge == -1) return checkFinal();
    vector<int> backup = edgeState;
    if (setEdge(chooseEdge, 1) && dfs()) return true;
    edgeState = backup;
    if (setEdge(chooseEdge, 0) && dfs()) return true;
    edgeState = backup;
    return false;
}

void buildGraph() {
    vector<vector<int>> horizontal(rowCount + 1, vector<int>(colCount, -1));
    vector<vector<int>> vertical(rowCount, vector<int>(colCount + 1, -1));
    vertexCount = (rowCount + 1) * (colCount + 1);
    vertexEdges.assign(vertexCount, vector<int>());
    edges.clear();
    for (int r = 0; r <= rowCount; r++) {
        for (int c = 0; c < colCount; c++) {
            int u = r * (colCount + 1) + c;
            int v = u + 1;
            horizontal[r][c] = edges.size();
            edges.push_back({u, v});
        }
    }
    for (int r = 0; r < rowCount; r++) {
        for (int c = 0; c <= colCount; c++) {
            int u = r * (colCount + 1) + c;
            int v = u + colCount + 1;
            vertical[r][c] = edges.size();
            edges.push_back({u, v});
        }
    }
    edgeCount = edges.size();
    edgeState.assign(edgeCount, -1);
    for (int edgeId = 0; edgeId < edgeCount; edgeId++) {
        vertexEdges[edges[edgeId].u].push_back(edgeId);
        vertexEdges[edges[edgeId].v].push_back(edgeId);
    }
    cellEdges.assign(rowCount * colCount, vector<int>());
    for (int r = 0; r < rowCount; r++) {
        for (int c = 0; c < colCount; c++) {
            cellEdges[r * colCount + c].push_back(horizontal[r][c]);
            cellEdges[r * colCount + c].push_back(horizontal[r + 1][c]);
            cellEdges[r * colCount + c].push_back(vertical[r][c]);
            cellEdges[r * colCount + c].push_back(vertical[r][c + 1]);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> rowCount >> colCount) {
        if (rowCount == 0 && colCount == 0) break;
        grid.assign(rowCount, "");
        for (int r = 0; r < rowCount; r++) cin >> grid[r];
        buildGraph();
        cout << (dfs() ? "YES" : "NO") << '\n';
    }
    return 0;
}
