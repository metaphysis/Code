#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-9;
const double inf = 1e100;

struct Edge {
    int to;
    double z;
};

bool updateRange(double p, double v, double low, double high, double &left, double &right) {
    if (fabs(v) < eps) {
        if (p < low - eps || p > high + eps) return false;
        return true;
    }
    double a = (low - p) / v, b = (high - p) / v;
    if (a > b) swap(a, b);
    left = max(left, a);
    right = min(right, b);
    if (left > right + eps) return false;
    return true;
}

bool getFaceHole(double x1, double y1, double z1, double dx, double dy, double dz, int axis, double pos, double low1, double high1, double low2, double high2, double &holeZ) {
    double left = 0.0, right = inf;
    if (axis == 0) {
        if (fabs(dx) < eps) {
            if (fabs(x1 - pos) > eps) return false;
        } else {
            double t = (pos - x1) / dx;
            left = max(left, t);
            right = min(right, t);
        }
        if (!updateRange(y1, dy, low1, high1, left, right)) return false;
        if (!updateRange(z1, dz, low2, high2, left, right)) return false;
    } else if (axis == 1) {
        if (fabs(dy) < eps) {
            if (fabs(y1 - pos) > eps) return false;
        } else {
            double t = (pos - y1) / dy;
            left = max(left, t);
            right = min(right, t);
        }
        if (!updateRange(x1, dx, low1, high1, left, right)) return false;
        if (!updateRange(z1, dz, low2, high2, left, right)) return false;
    } else {
        if (fabs(dz) < eps) {
            if (fabs(z1 - pos) > eps) return false;
        } else {
            double t = (pos - z1) / dz;
            left = max(left, t);
            right = min(right, t);
        }
        if (!updateRange(x1, dx, low1, high1, left, right)) return false;
        if (!updateRange(y1, dy, low2, high2, left, right)) return false;
    }
    if (right < -eps) return false;
    left = max(left, 0.0);
    if (left > right + eps) return false;
    if (dz >= 0.0) holeZ = z1 + dz * left;
    else holeZ = z1 + dz * right;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, d, trial = 1;
    while (cin >> n && n) {
        cin >> d;
        double x1, y1, z1, x2, y2, z2;
        cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
        double dx = x2 - x1, dy = y2 - y1, dz = z2 - z1;
        double side = static_cast<double>(d) / n;
        double area = side * side;
        int total = n * n * n, outId = total;
        vector<vector<Edge>> graph(total + 1);
        auto getId = [n](int x, int y, int z) {
            return x * n * n + y * n + z;
        };
        auto addEdge = [&](int u, int v, double z) {
            graph[u].push_back({v, z});
            graph[v].push_back({u, z});
        };
        for (int ix = 0; ix < n; ix++) {
            for (int iy = 0; iy < n; iy++) {
                for (int iz = 0; iz < n; iz++) {
                    int id = getId(ix, iy, iz);
                    double xLow = ix * side, xHigh = (ix + 1) * side;
                    double yLow = iy * side, yHigh = (iy + 1) * side;
                    double zLow = iz * side, zHigh = (iz + 1) * side;
                    double holeZ;
                    if (ix + 1 < n) {
                        int next = getId(ix + 1, iy, iz);
                        if (getFaceHole(x1, y1, z1, dx, dy, dz, 0, xHigh, yLow, yHigh, zLow, zHigh, holeZ))
                            addEdge(id, next, holeZ);
                    } else if (getFaceHole(x1, y1, z1, dx, dy, dz, 0, xHigh, yLow, yHigh, zLow, zHigh, holeZ)) {
                        addEdge(id, outId, holeZ);
                    }
                    if (ix == 0 && getFaceHole(x1, y1, z1, dx, dy, dz, 0, xLow, yLow, yHigh, zLow, zHigh, holeZ))
                        addEdge(id, outId, holeZ);
                    if (iy + 1 < n) {
                        int next = getId(ix, iy + 1, iz);
                        if (getFaceHole(x1, y1, z1, dx, dy, dz, 1, yHigh, xLow, xHigh, zLow, zHigh, holeZ))
                            addEdge(id, next, holeZ);
                    } else if (getFaceHole(x1, y1, z1, dx, dy, dz, 1, yHigh, xLow, xHigh, zLow, zHigh, holeZ)) {
                        addEdge(id, outId, holeZ);
                    }
                    if (iy == 0 && getFaceHole(x1, y1, z1, dx, dy, dz, 1, yLow, xLow, xHigh, zLow, zHigh, holeZ))
                        addEdge(id, outId, holeZ);
                    if (iz + 1 < n) {
                        int next = getId(ix, iy, iz + 1);
                        if (getFaceHole(x1, y1, z1, dx, dy, dz, 2, zHigh, xLow, xHigh, yLow, yHigh, holeZ))
                            addEdge(id, next, holeZ);
                    } else if (getFaceHole(x1, y1, z1, dx, dy, dz, 2, zHigh, xLow, xHigh, yLow, yHigh, holeZ)) {
                        addEdge(id, outId, holeZ);
                    }
                    if (iz == 0 && getFaceHole(x1, y1, z1, dx, dy, dz, 2, zLow, xLow, xHigh, yLow, yHigh, holeZ))
                        addEdge(id, outId, holeZ);
                }
            }
        }
        vector<double> dist(total + 1, inf);
        priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> heap;
        dist[outId] = 0.0;
        heap.push({0.0, outId});
        while (!heap.empty()) {
            double cur = heap.top().first;
            int u = heap.top().second;
            heap.pop();
            if (cur > dist[u] + eps) continue;
            for (const Edge &edge : graph[u]) {
                double next = max(cur, edge.z);
                if (next + eps < dist[edge.to]) {
                    dist[edge.to] = next;
                    heap.push({next, edge.to});
                }
            }
        }
        double volume = 0.0;
        for (int ix = 0; ix < n; ix++) {
            for (int iy = 0; iy < n; iy++) {
                for (int iz = 0; iz < n; iz++) {
                    int id = getId(ix, iy, iz);
                    double top = (iz + 1) * side;
                    if (dist[id] < top - eps) volume += area * (top - dist[id]);
                }
            }
        }
        if (trial > 1) cout << '\n';
        cout << fixed << setprecision(2);
        cout << "Trial " << trial << ", Volume = " << volume << '\n';
        trial++;
    }
    return 0;
}
