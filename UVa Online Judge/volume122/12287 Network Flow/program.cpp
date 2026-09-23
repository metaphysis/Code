#include <bits/stdc++.h>
using namespace std;

struct Dsu {
    vector<int> parent, size;
    int compCount;
    Dsu(int n) : parent(n), size(n, 1), compCount(n) {
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }
    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;
        if (size[a] < size[b]) swap(a, b);
        parent[b] = a;
        size[a] += size[b];
        --compCount;
        return true;
    }
};

struct Node {
    int x, y;
    vector<int> halfEdges;
    Node(int xVal, int yVal) : x(xVal), y(yVal) {}
};

struct Link {
    int a, b;
    long double weight;
    bool operator<(const Link &other) const {
        return weight < other.weight;
    }
};

long double getTurn(long double ax, long double ay, long double bx, long double by) {
    long double cross = fabsl(ax * by - ay * bx);
    long double dot = fabsl(ax * bx + ay * by);
    return atan2l(cross, dot);
}

long double getCapacity(long double energy, int a, int b, int c, int d) {
    return ((a * energy + b) * energy + c) * energy + d;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    const long double pi = acosl(-1.0L), eps = 1e-10L;
    int edgeCount, caseNum = 0;
    cout << fixed << setprecision(2);
    while (cin >> edgeCount && edgeCount) {
        int a, b, c, d, energy;
        cin >> a >> b >> c >> d >> energy;
        map<pair<int, int>, int> nodeIds;
        vector<Node> nodes;
        vector<int> endNode(edgeCount * 2);
        auto getId = [&](int x, int y) -> int {
            pair<int, int> key = {x, y};
            auto it = nodeIds.find(key);
            if (it != nodeIds.end()) return it->second;
            int id = nodes.size();
            nodeIds[key] = id;
            nodes.emplace_back(x, y);
            return id;
        };
        for (int i = 0; i < edgeCount; ++i) {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            int u = getId(x1, y1), v = getId(x2, y2);
            endNode[i * 2] = u;
            endNode[i * 2 + 1] = v;
            nodes[u].halfEdges.push_back(i * 2);
            nodes[v].halfEdges.push_back(i * 2 + 1);
        }
        Dsu dsu(edgeCount);
        vector<Link> links;
        long double totalTurn = 0;
        bool valid = true;
        int pairIdx[3][4] = {{0, 1, 2, 3}, {0, 2, 1, 3}, {0, 3, 1, 2}};
        for (const Node &node : nodes) {
            int degree = node.halfEdges.size();
            if (degree != 2 && degree != 4) {
                valid = false;
                continue;
            }
            long double dx[4], dy[4], turn[4][4] = {};
            for (int i = 0; i < degree; ++i) {
                int other = endNode[node.halfEdges[i] ^ 1];
                dx[i] = nodes[other].x - node.x;
                dy[i] = nodes[other].y - node.y;
                if (dx[i] == 0 && dy[i] == 0) valid = false;
            }
            for (int i = 0; i < degree; ++i) for (int j = i + 1; j < degree; ++j) turn[i][j] = turn[j][i] = getTurn(dx[i], dy[i], dx[j], dy[j]);
            if (degree == 2) {
                totalTurn += turn[0][1];
                dsu.unite(node.halfEdges[0] / 2, node.halfEdges[1] / 2);
            } else {
                long double cost[3], extra = numeric_limits<long double>::max();
                int best = 0;
                for (int i = 0; i < 3; ++i) {
                    cost[i] = turn[pairIdx[i][0]][pairIdx[i][1]] + turn[pairIdx[i][2]][pairIdx[i][3]];
                    if (cost[i] < cost[best]) best = i;
                }
                for (int i = 0; i < 3; ++i) if (i != best) extra = min(extra, cost[i] - cost[best]);
                int p0 = node.halfEdges[pairIdx[best][0]] / 2, p1 = node.halfEdges[pairIdx[best][1]] / 2;
                int p2 = node.halfEdges[pairIdx[best][2]] / 2, p3 = node.halfEdges[pairIdx[best][3]] / 2;
                totalTurn += cost[best];
                dsu.unite(p0, p1);
                dsu.unite(p2, p3);
                links.push_back({p0, p2, max(0.0L, extra)});
            }
        }
        sort(links.begin(), links.end());
        for (const Link &link : links) if (dsu.unite(link.a, link.b)) totalTurn += link.weight;
        long double need = totalTurn / (2 * pi), capacity = getCapacity(energy, a, b, c, d);
        cout << "Case " << ++caseNum << ": ";
        if (!valid || dsu.compCount != 1 || capacity + eps < need) {
            cout << "Impossible\n";
            continue;
        }
        long double answer = 100;
        if (capacity > 0) answer = (capacity - need) / capacity * 100;
        cout << max(0.0L, min(100.0L, answer)) << '\n';
    }
    return 0;
}
