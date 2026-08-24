#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-9, pi = acos(-1.0);

struct Point {
    double x, y;
    Point() {}
    Point(double x, double y) : x(x), y(y) {}
    Point operator + (const Point &p) const { return Point(x + p.x, y + p.y); }
    Point operator - (const Point &p) const { return Point(x - p.x, y - p.y); }
    Point operator * (double k) const { return Point(x * k, y * k); }
};

struct Circle {
    Point c;
    double r;
};

struct Mark {
    int id;
    double ang;
    bool bad;
};

double dot(Point a, Point b) {
    return a.x * b.x + a.y * b.y;
}

double cross(Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

double dis(Point a, Point b) {
    return hypot(a.x - b.x, a.y - b.y);
}

Point turn(Point p) {
    return Point(-p.y, p.x);
}

bool onSeg(Point p, Point a, Point b) {
    if (fabs(cross(b - a, p - a)) > 1e-7) return false;
    return dot(a - p, b - p) < -eps;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tt;
    cin >> tt;
    for (int cs = 1; cs <= tt; cs++) {
        Point st, ed;
        int n;
        cin >> st.x >> st.y >> ed.x >> ed.y >> n;
        vector<Circle> cir(n);
        for (int i = 0; i < n; i++) cin >> cir[i].c.x >> cir[i].c.y >> cir[i].r;
        vector<Point> ver, touch;
        vector<vector<Mark>> mark(n);
        vector<pair<int, int>> seg;
        ver.push_back(st);
        ver.push_back(ed);
        auto addMark = [&](int x, Point p, bool bad) {
            for (Mark &m : mark[x]) {
                if (dis(ver[m.id], p) < 1e-7) {
                    m.bad = m.bad || bad;
                    return m.id;
                }
            }
            int id = ver.size();
            double ang = atan2(p.y - cir[x].c.y, p.x - cir[x].c.x);
            ver.push_back(p);
            mark[x].push_back({id, ang, bad});
            return id;
        };
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                double d = dis(cir[i].c, cir[j].c);
                if (fabs(d - cir[i].r - cir[j].r) < 1e-8) {
                    Point p = cir[i].c + (cir[j].c - cir[i].c) * (cir[i].r / d);
                    addMark(i, p, true);
                    addMark(j, p, true);
                    touch.push_back(p);
                }
            }
        }
        auto addPointTan = [&](Point p, int x, int pid) {
            Point v = p - cir[x].c;
            double d2 = dot(v, v), h = sqrt(max(0.0, d2 - cir[x].r * cir[x].r));
            Point q = v * (cir[x].r * cir[x].r / d2), w = turn(v) * (cir[x].r * h / d2);
            Point a = cir[x].c + q + w, b = cir[x].c + q - w;
            int ia = addMark(x, a, false), ib = addMark(x, b, false);
            seg.push_back({pid, ia});
            seg.push_back({pid, ib});
        };
        for (int i = 0; i < n; i++) {
            addPointTan(st, i, 0);
            addPointTan(ed, i, 1);
        }
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                Point v = cir[j].c - cir[i].c, pv = turn(v);
                double z = dot(v, v);
                for (int s : {-1, 1}) {
                    double r = cir[i].r - s * cir[j].r;
                    double h2 = z - r * r;
                    if (h2 < -eps) continue;
                    double h = sqrt(max(0.0, h2));
                    for (int k : {-1, 1}) {
                        Point u = (v * r + pv * (h * k)) * (1.0 / z);
                        Point a = cir[i].c + u * cir[i].r;
                        Point b = cir[j].c + u * (s * cir[j].r);
                        int ia = addMark(i, a, false), ib = addMark(j, b, false);
                        seg.push_back({ia, ib});
                    }
                }
            }
        }
        int m = ver.size();
        vector<bool> bad(m, false);
        for (int i = 0; i < n; i++) {
            for (Mark x : mark[i]) bad[x.id] = bad[x.id] || x.bad;
        }
        auto valid = [&](int x, int y) {
            if (bad[x] || bad[y]) return false;
            for (Circle c : cir) {
                Point v = ver[y] - ver[x];
                double z = dot(v, v), t = dot(c.c - ver[x], v) / z;
                t = max(0.0, min(1.0, t));
                Point q = ver[x] + v * t;
                if (dis(q, c.c) < c.r - 1e-8) return false;
            }
            for (Point p : touch) {
                if (onSeg(p, ver[x], ver[y])) return false;
            }
            return true;
        };
        vector<vector<pair<int, double>>> graph(m);
        auto addEdge = [&](int x, int y, double w) {
            if (valid(x, y)) {
                graph[x].push_back({y, w});
                graph[y].push_back({x, w});
            }
        };
        addEdge(0, 1, dis(st, ed));
        for (pair<int, int> e : seg) addEdge(e.first, e.second, dis(ver[e.first], ver[e.second]));
        for (int i = 0; i < n; i++) {
            sort(mark[i].begin(), mark[i].end(), [](Mark a, Mark b) { return a.ang < b.ang; });
            int sz = mark[i].size();
            for (int j = 0; j < sz; j++) {
                Mark a = mark[i][j], b = mark[i][(j + 1) % sz];
                if (a.bad || b.bad) continue;
                double ang = b.ang - a.ang;
                if (ang < 0) ang += 2.0 * pi;
                graph[a.id].push_back({b.id, ang * cir[i].r});
                graph[b.id].push_back({a.id, ang * cir[i].r});
            }
        }
        vector<double> ds(m, 1e100);
        priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> que;
        ds[0] = 0;
        que.push({0, 0});
        while (!que.empty()) {
            double d = que.top().first;
            int x = que.top().second;
            que.pop();
            if (d > ds[x] + eps) continue;
            for (pair<int, double> e : graph[x]) {
                if (ds[e.first] > d + e.second) {
                    ds[e.first] = d + e.second;
                    que.push({ds[e.first], e.first});
                }
            }
        }
        cout << fixed << setprecision(8) << "Case " << cs << ": " << ds[1] << '\n';
    }
    return 0;
}
