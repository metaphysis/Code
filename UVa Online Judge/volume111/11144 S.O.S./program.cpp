// S.O.S.
// UVa ID: 11144
// Verdict: Accepted
// Submission Date: 2026-07-19
// UVa Run Time: 0.040s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const long double EPS = 1e-8L;

struct Point {
    long double x, y;
};

long double dist(const Point& a, const Point& b) {
    long double dx = a.x - b.x, dy = a.y - b.y;
    return sqrtl(dx * dx + dy * dy);
}

// 点到线段的最短距离
long double pointToSegDist(const Point& p, const Point& s1, const Point& s2) {
    long double vx = s2.x - s1.x, vy = s2.y - s1.y;
    long double wx = p.x - s1.x, wy = p.y - s1.y;
    long double len2 = vx * vx + vy * vy;
    long double t = (wx * vx + wy * vy) / len2;
    if (t < 0.0L) return dist(p, s1);
    if (t > 1.0L) return dist(p, s2);
    Point proj = {s1.x + t * vx, s1.y + t * vy};
    return dist(p, proj);
}

// 两条线段的最短距离（取四个端点到另一线段距离的最小值）
long double segSegDist(const Point& a1, const Point& a2, const Point& b1, const Point& b2) {
    long double ans = pointToSegDist(a1, b1, b2);
    ans = min(ans, pointToSegDist(a2, b1, b2));
    ans = min(ans, pointToSegDist(b1, a1, a2));
    ans = min(ans, pointToSegDist(b2, a1, a2));
    return ans;
}

// 多边形面积（鞋带公式）
long double polygonArea(const vector<Point>& poly) {
    long double area2 = 0.0L;
    int n = poly.size();
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        area2 += poly[i].x * poly[j].y - poly[i].y * poly[j].x;
    }
    return fabsl(area2) / 2.0L;
}

// 两个多边形之间的最短距离（枚举边对）
long double polyDist(const vector<Point>& a, const vector<Point>& b) {
    long double ans = 1e100L;
    int n = a.size(), m = b.size();
    for (int i = 0; i < n; ++i) {
        int ni = (i + 1) % n;
        for (int j = 0; j < m; ++j) {
            int nj = (j + 1) % m;
            ans = min(ans, segSegDist(a[i], a[ni], b[j], b[nj]));
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tc; cin >> tc;
    while (tc--) {
        int M; cin >> M;
        vector<vector<Point>> poly(M);
        vector<long double> area(M);

        for (int i = 0; i < M; ++i) {
            int L; cin >> L;
            poly[i].resize(L);
            for (int j = 0; j < L; ++j) cin >> poly[i][j].x >> poly[i][j].y;
            area[i] = polygonArea(poly[i]);
        }
        // 建图（有向边，边权为点燃时间）
        vector<vector<pair<int, long long>>> g(M);
        for (int i = 0; i < M; ++i) {
            for (int j = i + 1; j < M; ++j) {
                long double d = polyDist(poly[i], poly[j]);
                if (d < 30.0L - EPS) {
                    long long t_ij = (long long)ceill(10.0L * area[j] / area[i] - EPS);
                    long long t_ji = (long long)ceill(10.0L * area[i] / area[j] - EPS);
                    g[i].push_back({j, t_ij});
                    g[j].push_back({i, t_ji});
                }
            }
        }
        int P, Cycle; cin >> P >> Cycle;
        const long long INF = (1LL << 60);
        vector<long long> time(M, INF);
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
        time[P] = 0;
        pq.push({0, P});
        while (!pq.empty()) {
            auto cur = pq.top(); pq.pop();
            long long t = cur.first;
            int u = cur.second;
            if (t != time[u]) continue;      // 过时节点跳过
            for (auto& e : g[u]) {
                int v = e.first;
                long long nt = t + e.second;
                if (nt < time[v]) {
                    time[v] = nt;
                    pq.push({nt, v});
                }
            }
        }
        // 输出编号升序
        bool first = true;
        for (int i = 0; i < M; ++i) {
            if (time[i] <= Cycle) {
                if (!first) cout << ' ';
                cout << i;
                first = false;
            }
        }
        cout << '\n';
    }
    return 0;
}
