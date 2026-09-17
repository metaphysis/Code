#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v, type, layer, lower, upper, factor;
};

int n, m, k, vertexCnt;
vector<Edge> edges;

int getVertex(int layer, int pos) {
    return (layer - 1) * m + pos;
}

bool assignFactors(int layer, int parity) {
    vector<vector<int>> adj(m + 1);
    int edgeCnt = edges.size(), start = parity ? 1 : 2;
    for (int i = 0; i < edgeCnt; i++) {
        Edge &edge = edges[i];
        if (edge.type == 1 && edge.layer == layer && edge.lower % 2 == parity) adj[edge.lower].push_back(i);
    }
    for (int round = 0; round < k; round++) {
        vector<int> matchUp(m + 1, -1);
        vector<char> seen(m + 1);
        function<bool(int)> augment = [&](int low) {
            for (int edgeId : adj[low]) {
                Edge &edge = edges[edgeId];
                int up = edge.upper;
                if (edge.factor != -1 || seen[up]) continue;
                seen[up] = 1;
                if (matchUp[up] == -1 || augment(edges[matchUp[up]].lower)) {
                    matchUp[up] = edgeId;
                    return true;
                }
            }
            return false;
        };
        for (int low = start; low <= m; low += 2) {
            fill(seen.begin(), seen.end(), 0);
            if (!augment(low)) return false;
        }
        for (int up = start; up <= m; up += 2) {
            if (matchUp[up] == -1) return false;
            edges[matchUp[up]].factor = round;
        }
    }
    return true;
}

void buildOrientation(int person, vector<int> &from, vector<int> &to, vector<char> &tree) {
    int edgeCnt = edges.size(), selectedParity = person == 0 ? 1 : 0, h = (k - 1) / 2;
    from.resize(edgeCnt);
    to.resize(edgeCnt);
    tree.assign(edgeCnt, 0);
    for (int i = 0; i < edgeCnt; i++) {
        Edge &edge = edges[i];
        if (edge.type == 0) {
            from[i] = edge.u;
            to[i] = edge.v;
            if (edge.lower % 2 == selectedParity) tree[i] = 1;
        } else if (edge.type == 1) {
            int parity = edge.lower % 2;
            bool upward;
            if (parity == selectedParity) {
                upward = edge.factor <= h;
                if (edge.factor == 0) tree[i] = 1;
            } else {
                upward = edge.factor < h;
            }
            if (upward) {
                from[i] = edge.u;
                to[i] = edge.v;
            } else {
                from[i] = edge.v;
                to[i] = edge.u;
            }
        } else if (edge.type == 2) {
            if (edge.lower % 2 == selectedParity) {
                from[i] = edge.u;
                to[i] = edge.v;
                tree[i] = 1;
            } else {
                from[i] = edge.v;
                to[i] = edge.u;
            }
        } else {
            if (edge.lower % 2 == selectedParity) {
                from[i] = edge.u;
                to[i] = edge.v;
                if (edge.lower == person + 1) tree[i] = 1;
            } else {
                from[i] = edge.v;
                to[i] = edge.u;
            }
        }
    }
}

bool buildRoute(const vector<int> &from, const vector<int> &to, const vector<char> &tree, vector<int> &route) {
    int edgeCnt = edges.size(), cur = 0;
    vector<vector<int>> adj(vertexCnt);
    vector<int> ptr(vertexCnt), path;
    for (int i = 0; i < edgeCnt; i++) if (!tree[i]) adj[to[i]].push_back(i);
    for (int i = 0; i < edgeCnt; i++) if (tree[i]) adj[to[i]].push_back(i);
    path.push_back(0);
    for (int step = 0; step < edgeCnt; step++) {
        if (ptr[cur] == (int)adj[cur].size()) return false;
        int edgeId = adj[cur][ptr[cur]++];
        cur = from[edgeId];
        path.push_back(cur);
    }
    if (cur != 0) return false;
    reverse(path.begin(), path.end());
    route.assign(path.begin() + 1, path.end());
    return true;
}

void printVertex(int vertex) {
    if (vertex == 0) {
        cout << "0 0\n";
    } else if (vertex == vertexCnt - 1) {
        cout << n + 1 << " 0\n";
    } else {
        int layer = (vertex - 1) / m + 1, pos = (vertex - 1) % m + 1;
        cout << layer << ' ' << pos << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCnt;
    cin >> testCnt;
    for (int testCase = 1; testCase <= testCnt; testCase++) {
        cin >> n >> m >> k;
        edges.clear();
        vertexCnt = n * m + 2;
        for (int layer = 1; layer <= n; layer++) {
            for (int pos = 1; pos <= m; pos++) {
                int nextPos = pos % m + 1;
                edges.push_back({getVertex(layer, pos), getVertex(layer, nextPos), 0, layer, pos, nextPos, -1});
            }
        }
        for (int layer = 1; layer < n; layer++) {
            for (int low = 1; low <= m; low++) {
                for (int j = 0; j < k; j++) {
                    int up;
                    cin >> up;
                    edges.push_back({getVertex(layer, low), getVertex(layer + 1, up), 1, layer, low, up, -1});
                }
            }
        }
        for (int pos = 1; pos <= m; pos++) edges.push_back({0, getVertex(1, pos), 2, 0, pos, 0, -1});
        for (int pos = 1; pos <= m; pos++) edges.push_back({getVertex(n, pos), vertexCnt - 1, 3, n, pos, 0, -1});
        bool possible = true;
        for (int layer = 1; layer < n; layer++) {
            if (!assignFactors(layer, 1)) possible = false;
            if (!assignFactors(layer, 0)) possible = false;
        }
        vector<int> fromChris, toChris, fromChrit, toChrit, routeChris, routeChrit;
        vector<char> treeChris, treeChrit;
        if (possible) {
            buildOrientation(0, fromChris, toChris, treeChris);
            buildOrientation(1, fromChrit, toChrit, treeChrit);
            if (!buildRoute(fromChris, toChris, treeChris, routeChris)) possible = false;
            if (!buildRoute(fromChrit, toChrit, treeChrit, routeChrit)) possible = false;
        }
        cout << "Case " << testCase << ": " << (possible ? "Yes" : "No") << '\n';
        if (!possible) continue;
        for (int vertex : routeChris) printVertex(vertex);
        for (int vertex : routeChrit) printVertex(vertex);
    }
    return 0;
}
