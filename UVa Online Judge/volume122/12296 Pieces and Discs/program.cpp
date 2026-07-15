// Pieces and Discs
// UVa ID: 12296
// Verdict: Accepted
// Submission Date: 2026-07-15
// UVa Run Time: 0.010s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9;

struct Point {
    double x, y;
    Point(double x_ = 0, double y_ = 0) : x(x_), y(y_) {}
    bool operator<(const Point& o) const { return x < o.x - EPS || (fabs(x - o.x) < EPS && y < o.y - EPS); }
    bool operator==(const Point& o) const { return fabs(x - o.x) < EPS && fabs(y - o.y) < EPS; }
    Point operator+(const Point& o) const { return Point(x + o.x, y + o.y); }
    Point operator-(const Point& o) const { return Point(x - o.x, y - o.y); }
    Point operator*(double k) const { return Point(x * k, y * k); }
    double dot(const Point& o) const { return x * o.x + y * o.y; }
    double cross(const Point& o) const { return x * o.y - y * o.x; }
    double len2() const { return x * x + y * y; }
    double len() const { return sqrt(len2()); }
};

struct Segment { Point a, b; Segment(Point a_ = Point(), Point b_ = Point()) : a(a_), b(b_) {} };
struct Circle { Point c; double r; Circle(Point c_ = Point(), double r_ = 0) : c(c_), r(r_) {} };

double dist(const Point& p1, const Point& p2) { return (p1 - p2).len(); }

double projectParam(const Point& p, const Segment& s) {
    Point v = s.b - s.a;
    return (p - s.a).dot(v) / v.len2();
}

void segmentIntersections(const Segment& s1, const Segment& s2, vector<Point>& out) {
    Point p = s1.a, q = s1.b, r = s2.a, s = s2.b;
    Point v1 = q - p, v2 = s - r;
    double d1 = v1.cross(v2);
    if (fabs(d1) < EPS) return;
    double t = (r - p).cross(v2) / d1;
    double u = (r - p).cross(v1) / d1;
    if (t >= -EPS && t <= 1 + EPS && u >= -EPS && u <= 1 + EPS)
        out.push_back(p + v1 * t);
}

double polygonArea(const vector<Point>& poly) {
    double area = 0;
    int n = poly.size();
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        area += poly[i].x * poly[j].y - poly[i].y * poly[j].x;
    }
    return fabs(area) * 0.5;
}

bool pointInPolygon(const Point& p, const vector<Point>& poly) {
    int n = poly.size();
    bool inside = false;
    for (int i = 0, j = n - 1; i < n; j = i++) {
        Point a = poly[i], b = poly[j];
        if (fabs((b - a).cross(p - a)) < EPS && (p - a).dot(p - b) < EPS + 1e-12)
            return false;
        if (((a.y > p.y) != (b.y > p.y)) &&
            (p.x < (b.x - a.x) * (p.y - a.y) / (b.y - a.y) + a.x + EPS))
            inside = !inside;
    }
    return inside;
}

double lineCircleOverlapLength(const Point& A, const Point& B, const Circle& c) {
    Point d = B - A, f = A - c.c;
    double a = d.dot(d), b = 2.0 * f.dot(d), cc = f.dot(f) - c.r * c.r;
    double delta = b * b - 4 * a * cc;
    if (delta < -EPS) return 0.0;
    if (delta < 0) delta = 0;
    double sqrtDelta = sqrt(delta);
    double t1 = (-b - sqrtDelta) / (2 * a), t2 = (-b + sqrtDelta) / (2 * a);
    double low = max(0.0, min(t1, t2));
    double high = min(1.0, max(t1, t2));
    if (low < high - EPS)
        return (high - low) * sqrt(a);
    return 0.0;
}

bool polygonIntersectsCircle(const vector<Point>& poly, const Circle& c) {
    if (pointInPolygon(c.c, poly)) return true;
    for (const auto& p : poly)
        if ((p - c.c).len2() < c.r * c.r - EPS) return true;
    for (size_t i = 0; i < poly.size(); ++i) {
        size_t j = (i + 1) % poly.size();
        if (lineCircleOverlapLength(poly[i], poly[j], c) > EPS)
            return true;
    }
    return false;
}

vector<vector<Point>> splitPolygon(const vector<Point>& P, const Segment& S) {
    vector<vector<Point>> res;
    int n = P.size();
    vector<pair<int, Point>> inter;
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        Segment edge(P[i], P[j]);
        vector<Point> pts;
        segmentIntersections(edge, S, pts);
        for (auto& p : pts) {
            bool dup = false;
            for (auto& q : inter)
                if (dist(p, q.second) < EPS) { dup = true; break; }
            if (!dup) inter.push_back({i, p});
        }
    }
    if (inter.size() < 2) return res;
    sort(inter.begin(), inter.end(), [&](pair<int, Point>& a, pair<int, Point>& b) {
        if (a.first != b.first) return a.first < b.first;
        return projectParam(a.second, Segment(P[a.first], P[(a.first + 1) % n])) <
               projectParam(b.second, Segment(P[b.first], P[(b.first + 1) % n]));
    });
    Point p1 = inter[0].second, p2 = inter[1].second;
    int idx1 = inter[0].first, idx2 = inter[1].first;
    vector<Point> chain1, chain2;
    chain1.push_back(p1);
    int cur = idx1;
    while (cur != idx2) {
        int nxt = (cur + 1) % n;
        chain1.push_back(P[nxt]);
        cur = nxt;
    }
    chain1.push_back(p2);
    chain2.push_back(p2);
    cur = idx2;
    while (cur != idx1) {
        int nxt = (cur + 1) % n;
        chain2.push_back(P[nxt]);
        cur = nxt;
    }
    chain2.push_back(p1);
    if (dist(chain1[0], chain1.back()) < EPS) chain1.pop_back();
    if (dist(chain2[0], chain2.back()) < EPS) chain2.pop_back();
    res.push_back(chain1);
    res.push_back(chain2);
    return res;
}

int main() {
    int n, m, L, W;
    while (scanf("%d%d%d%d", &n, &m, &L, &W) == 4 && (n || m || L || W)) {
        vector<Segment> segs;
        for (int i = 0; i < n; ++i) {
            int x1, y1, x2, y2;
            scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
            segs.push_back(Segment(Point(x1, y1), Point(x2, y2)));
        }
        vector<vector<Point>> polygons;
        polygons.push_back({Point(0, 0), Point(L, 0), Point(L, W), Point(0, W)});
        for (auto& seg : segs) {
            vector<vector<Point>> newPolys;
            for (auto& poly : polygons) {
                auto parts = splitPolygon(poly, seg);
                if (parts.empty())
                    newPolys.push_back(poly);
                else {
                    for (auto& p : parts)
                        newPolys.push_back(p);
                }
            }
            polygons = move(newPolys);
        }
        vector<Circle> discs;
        for (int i = 0; i < m; ++i) {
            int x, y, R;
            scanf("%d%d%d", &x, &y, &R);
            discs.push_back(Circle(Point(x, y), R));
        }
        for (auto& c : discs) {
            vector<double> areas;
            for (auto& poly : polygons) {
                if (polygonIntersectsCircle(poly, c))
                    areas.push_back(polygonArea(poly));
            }
            sort(areas.begin(), areas.end());
            printf("%d", (int)areas.size());
            for (double a : areas)
                printf(" %.2f", a + 1e-9);
            printf("\n");
        }
        printf("\n");
    }
    return 0;
}
