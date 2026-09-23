#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>
using namespace std;
using boost::multiprecision::int128_t;

struct Point {
    long long x, y;
};

struct Cone {
    Point low, high;
    bool valid;
};

bool samePoint(const Point &a, const Point &b) {
    return a.x == b.x && a.y == b.y;
}

int128_t cross(const Point &a, const Point &b) {
    return int128_t(a.x) * b.y - int128_t(a.y) * b.x;
}

long long rayLen(const Point &a) {
    return max(abs(a.x), abs(a.y));
}

bool sameDir(const Point &a, const Point &b) {
    if (a.x != 0) return (a.x > 0 && b.x > 0) || (a.x < 0 && b.x < 0);
    return (a.y > 0 && b.y > 0) || (a.y < 0 && b.y < 0);
}

Cone buildCone(const Point &a, const vector<Point> &rats) {
    Point base = {0, 0};
    for (const Point &p : rats) if (!samePoint(a, p)) {
        base = {p.x - a.x, p.y - a.y};
        break;
    }
    Cone cone = {base, base, true};
    if (base.x == 0 && base.y == 0) return cone;
    for (const Point &p : rats) {
        Point v = {p.x - a.x, p.y - a.y};
        if (v.x == 0 && v.y == 0) continue;
        int128_t side = cross(base, v);
        if (side < 0) {
            int128_t turn = cross(v, cone.low);
            if (turn > 0 || (turn == 0 && rayLen(v) > rayLen(cone.low))) cone.low = v;
        } else if (side > 0) {
            int128_t turn = cross(cone.high, v);
            if (turn > 0 || (turn == 0 && rayLen(v) > rayLen(cone.high))) cone.high = v;
        } else {
            if (!sameDir(base, v)) {
                cone.valid = false;
                return cone;
            }
            if (cross(cone.low, v) == 0 && rayLen(v) > rayLen(cone.low)) cone.low = v;
            if (cross(cone.high, v) == 0 && rayLen(v) > rayLen(cone.high)) cone.high = v;
        }
    }
    int128_t turn = cross(cone.low, cone.high);
    if (turn < 0 || (turn == 0 && !sameDir(cone.low, cone.high))) cone.valid = false;
    return cone;
}

bool validEdge(const Point &a, const Point &b, const Cone &cone) {
    if (!cone.valid || samePoint(a, b)) return false;
    Point d = {b.x - a.x, b.y - a.y};
    int128_t lowSide = cross(d, cone.low), highSide = cross(d, cone.high);
    if (lowSide < 0 || highSide < 0) return false;
    if (lowSide == 0 && (!sameDir(d, cone.low) || rayLen(d) < rayLen(cone.low))) return false;
    if (highSide == 0 && (!sameDir(d, cone.high) || rayLen(d) < rayLen(cone.high))) return false;
    return true;
}

int shortestCycle(const vector<vector<int>> &adj) {
    int m = adj.size(), ans = m + 1;
    vector<int> dist(m), que(m);
    for (int start = 0; start < m; ++start) {
        if (adj[start].empty()) continue;
        fill(dist.begin(), dist.end(), -1);
        int head = 0, tail = 0;
        dist[start] = 0;
        que[tail++] = start;
        while (head < tail) {
            int u = que[head++];
            if (dist[u] + 1 >= ans) continue;
            for (int v : adj[u]) {
                if (v == start) {
                    ans = dist[u] + 1;
                    if (ans == 3) return ans;
                } else if (dist[v] == -1 && dist[u] + 2 < ans) {
                    dist[v] = dist[u] + 1;
                    que[tail++] = v;
                }
            }
        }
    }
    return ans == m + 1 ? -1 : ans;
}

int solve(const vector<Point> &rats, const vector<Point> &devices) {
    int m = devices.size();
    bool allSame = true;
    for (const Point &p : rats) if (!samePoint(p, rats[0])) allSame = false;
    if (allSame) for (const Point &p : devices) if (samePoint(p, rats[0])) return 1;
    vector<Cone> cones(m);
    vector<vector<int>> adj(m);
    vector<vector<unsigned char>> hasEdge(m, vector<unsigned char>(m, 0));
    for (int i = 0; i < m; ++i) cones[i] = buildCone(devices[i], rats);
    for (int i = 0; i < m; ++i) {
        if (!cones[i].valid) continue;
        for (int j = 0; j < m; ++j) {
            if (i == j || !validEdge(devices[i], devices[j], cones[i])) continue;
            if (hasEdge[j][i]) return 2;
            hasEdge[i][j] = 1;
            adj[i].push_back(j);
        }
    }
    return shortestCycle(adj);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    while (cin >> n >> m) {
        vector<Point> rats(n), devices(m);
        for (Point &p : rats) cin >> p.x >> p.y;
        for (Point &p : devices) cin >> p.x >> p.y;
        cout << solve(rats, devices) << '\n';
    }
    return 0;
}
