#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v, faceA, faceB;
};

vector<Edge> edges;
vector<vector<int>> vertexEdges(60), faceEdges(32);
int vertexId[12][12], vertexCount;

int getVertex(int u, int v) {
    if (vertexId[u][v] == -1) vertexId[u][v] = vertexCount++;
    return vertexId[u][v];
}

void addEdge(int u, int v, int faceA, int faceB) {
    int edgeId = edges.size();
    edges.push_back({u, v, faceA, faceB});
    vertexEdges[u].push_back(edgeId);
    vertexEdges[v].push_back(edgeId);
    faceEdges[faceA].push_back(edgeId);
    faceEdges[faceB].push_back(edgeId);
}

int getOtherFace(int edgeId, int faceId) {
    return edges[edgeId].faceA == faceId ? edges[edgeId].faceB : edges[edgeId].faceA;
}

int buildBall() {
    vector<array<int, 3>> triangles;
    vector<int> sideFaces[12][12];
    int startEdge = -1;
    memset(vertexId, -1, sizeof(vertexId));
    for (int i = 0; i < 5; i++) {
        int nextI = (i + 1) % 5, prevI = (i + 4) % 5;
        triangles.push_back({0, 2 + i, 2 + nextI});
        triangles.push_back({1, 7 + i, 7 + nextI});
        triangles.push_back({2 + i, 7 + i, 2 + nextI});
        triangles.push_back({2 + i, 7 + prevI, 7 + i});
    }
    for (int i = 0; i < 20; i++) {
        int hexFace = 12 + i;
        for (int j = 0; j < 3; j++) {
            int u = triangles[i][j], v = triangles[i][(j + 1) % 3];
            int w = triangles[i][(j + 2) % 3];
            int firstV = getVertex(u, v), secondV = getVertex(u, w);
            addEdge(firstV, secondV, u, hexFace);
            sideFaces[min(u, v)][max(u, v)].push_back(hexFace);
        }
    }
    for (int u = 0; u < 12; u++) {
        for (int v = u + 1; v < 12; v++) {
            if (sideFaces[u][v].empty()) continue;
            if (startEdge == -1) startEdge = edges.size();
            addEdge(vertexId[u][v], vertexId[v][u],
                    sideFaces[u][v][0], sideFaces[u][v][1]);
        }
    }
    return startEdge;
}

void solve(int n, int startEdge) {
    vector<bool> blocked(edges.size(), false), visited(32, false);
    queue<int> faceQueue;
    int inEdge = startEdge, curVertex = edges[startEdge].v;
    int greenFace = edges[startEdge].faceA, seedFace = greenFace;
    int greenBlack = 0, greenWhite = 0;
    blocked[startEdge] = true;
    for (int i = 0; i < n; i++) {
        int greenCount, nextEdge = -1, targetFace;
        cin >> greenCount;
        targetFace = greenCount == 1 ? greenFace : getOtherFace(inEdge, greenFace);
        for (int edgeId : vertexEdges[curVertex]) {
            if (edgeId == inEdge) continue;
            if (edges[edgeId].faceA == targetFace || edges[edgeId].faceB == targetFace) {
                nextEdge = edgeId;
                break;
            }
        }
        if (greenCount == 2) greenFace = getOtherFace(nextEdge, targetFace);
        blocked[nextEdge] = true;
        curVertex = edges[nextEdge].u == curVertex ? edges[nextEdge].v : edges[nextEdge].u;
        inEdge = nextEdge;
    }
    visited[seedFace] = true;
    faceQueue.push(seedFace);
    while (!faceQueue.empty()) {
        int curFace = faceQueue.front();
        faceQueue.pop();
        if (curFace < 12) greenBlack++;
        else greenWhite++;
        for (int edgeId : faceEdges[curFace]) {
            if (blocked[edgeId]) continue;
            int nextFace = getOtherFace(edgeId, curFace);
            if (visited[nextFace]) continue;
            visited[nextFace] = true;
            faceQueue.push(nextFace);
        }
    }
    cout << 12 - greenBlack << ' ' << 20 - greenWhite << ' ';
    cout << greenBlack + greenWhite << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int startEdge = buildBall(), n;
    int T;
    cin >> T;
    for (int cs = 0; cs < T; cs++) {
        if (cs) cout << '\n';
        cin >> n;
        solve(n, startEdge);
    }
    return 0;
}
