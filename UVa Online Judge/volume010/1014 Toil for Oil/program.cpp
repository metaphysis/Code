#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-9;
const double inf = 1e100;

struct Point {
    double x, y;
    int hole;
};

struct Cell {
    double a, b;
    double l0, r0, l1, r1;
};

struct Edge {
    int to;
    double w;
};

double getX(const Point &p, const Point &q, double y) {
    return p.x + (q.x - p.x) * (y - p.y) / (q.y - p.y);
}

bool inRange(double x, double l, double r) {
    return x >= l - eps && x <= r + eps;
}

double getLeft(const Cell &c, double y) {
    return c.l0 + (c.l1 - c.l0) * (y - c.a) / (c.b - c.a);
}

double getRight(const Cell &c, double y) {
    return c.r0 + (c.r1 - c.r0) * (y - c.a) / (c.b - c.a);
}

bool overlap(const Cell &a, const Cell &b, double y) {
    double l1 = getLeft(a, y), r1 = getRight(a, y);
    double l2 = getLeft(b, y), r2 = getRight(b, y);
    return min(r1, r2) + eps >= max(l1, l2);
}

double getArea(const Cell &c, double h) {
    double y = min(c.b, h);
    if (y <= c.a + eps) return 0.0;
    double w0 = c.r0 - c.l0;
    double t = (y - c.a) / (c.b - c.a);
    double l = c.l0 + (c.l1 - c.l0) * t;
    double r = c.r0 + (c.r1 - c.r0) * t;
    double w1 = r - l;
    return (w0 + w1) * (y - c.a) / 2.0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, tc = 0;
    while (cin >> n && n) {
        vector<Point> p(n);
        vector<double> ys;
        double maxY = -inf;
        int i;
        for (i = 0; i < n; i++) {
            cin >> p[i].x >> p[i].y >> p[i].hole;
            ys.push_back(p[i].y);
            maxY = max(maxY, p[i].y);
        }
        sort(ys.begin(), ys.end());
        ys.erase(unique(ys.begin(), ys.end(), [](double a, double b) {
            return fabs(a - b) < eps;
        }), ys.end());
        vector<Cell> cells;
        int s = ys.size();
        for (i = 0; i + 1 < s; i++) {
            double a = ys[i], b = ys[i + 1];
            double mid = (a + b) / 2.0;
            vector<pair<double, int>> its;
            int j;
            for (j = 0; j < n; j++) {
                int k = (j + 1) % n;
                if (fabs(p[j].y - p[k].y) < eps) continue;
                if (mid > min(p[j].y, p[k].y) && mid < max(p[j].y, p[k].y)) {
                    its.push_back({getX(p[j], p[k], mid), j});
                }
            }
            sort(its.begin(), its.end());
            for (j = 0; j + 1 < (int)its.size(); j += 2) {
                int e1 = its[j].second, e2 = its[j + 1].second;
                int k1 = (e1 + 1) % n, k2 = (e2 + 1) % n;
                double l0 = getX(p[e1], p[k1], a);
                double r0 = getX(p[e2], p[k2], a);
                double l1 = getX(p[e1], p[k1], b);
                double r1 = getX(p[e2], p[k2], b);
                if (l0 > r0) swap(l0, r0);
                if (l1 > r1) swap(l1, r1);
                cells.push_back({a, b, l0, r0, l1, r1});
            }
        }
        int m = cells.size();
        vector<vector<Edge>> graph(m);
        for (i = 0; i < m; i++) {
            int j;
            for (j = i + 1; j < m; j++) {
                if (fabs(cells[i].b - cells[j].a) < eps && overlap(cells[i], cells[j], cells[i].b)) {
                    double w = cells[i].b;
                    graph[i].push_back({j, w});
                    graph[j].push_back({i, w});
                } else if (fabs(cells[j].b - cells[i].a) < eps && overlap(cells[j], cells[i], cells[j].b)) {
                    double w = cells[j].b;
                    graph[i].push_back({j, w});
                    graph[j].push_back({i, w});
                }
            }
        }
        vector<double> dist(m, maxY);
        int h;
        for (h = 0; h < n; h++) {
            if (!p[h].hole) continue;
            for (i = 0; i < m; i++) {
                if (fabs(cells[i].a - p[h].y) < eps && inRange(p[h].x, cells[i].l0, cells[i].r0))
                    dist[i] = min(dist[i], p[h].y);
                if (fabs(cells[i].b - p[h].y) < eps && inRange(p[h].x, cells[i].l1, cells[i].r1))
                    dist[i] = min(dist[i], p[h].y);
            }
        }
        vector<int> used(m, 0);
        for (i = 0; i < m; i++) {
            int u = -1, j;
            for (j = 0; j < m; j++)
                if (!used[j] && (u == -1 || dist[j] < dist[u])) u = j;
            if (u == -1) break;
            used[u] = 1;
            for (const Edge &e : graph[u])
                dist[e.to] = min(dist[e.to], max(dist[u], e.w));
        }
        double ans = 0.0;
        for (i = 0; i < m; i++)
            ans += getArea(cells[i], dist[i]);
        cout << "Cave " << ++tc << ": Oil capacity = " << llround(ans) << "\n\n";
    }
    return 0;
}
