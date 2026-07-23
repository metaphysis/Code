// Star War
// UVa ID: 11836
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.480s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9;
const double INF = 1e100;

struct Point3 {
    double x, y, z;
    Point3(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}
    Point3 operator + (const Point3& o) const { return {x + o.x, y + o.y, z + o.z}; }
    Point3 operator - (const Point3& o) const { return {x - o.x, y - o.y, z - o.z}; }
    Point3 operator * (double k) const { return {x * k, y * k, z * k}; }
    double dot(const Point3& o) const { return x * o.x + y * o.y + z * o.z; }
    Point3 cross(const Point3& o) const { return {y * o.z - z * o.y, z * o.x - x * o.z, x * o.y - y * o.x}; }
    double len() const { return sqrt(dot(*this)); }
};

struct LineSegment { Point3 a, b; };
struct Triangle { Point3 a, b, c; };

double distPointPoint(const Point3& p, const Point3& q) { return (p - q).len(); }

double distPointLineSegment(const Point3& p, const LineSegment& seg) {
    Point3 u = seg.b - seg.a;
    double len2 = u.dot(u);
    if (len2 < EPS) return distPointPoint(p, seg.a);
    double t = (p - seg.a).dot(u) / len2;
    if (t < 0) t = 0;
    if (t > 1) t = 1;
    Point3 proj = seg.a + u * t;
    return (p - proj).len();
}

bool pointInTriangle(const Point3& p, const Triangle& tri) {
    Point3 ab = tri.b - tri.a, ac = tri.c - tri.a, ap = p - tri.a;
    double d1 = ab.dot(ab), d2 = ab.dot(ac), d3 = ac.dot(ac);
    double det = d1 * d3 - d2 * d2;
    if (fabs(det) < EPS) return false;
    double u = (d3 * (ap.dot(ab)) - d2 * (ap.dot(ac))) / det;
    double v = (d1 * (ap.dot(ac)) - d2 * (ap.dot(ab))) / det;
    return (u >= -EPS) && (v >= -EPS) && (u + v <= 1 + EPS);
}

double distPointTriangle(const Point3& p, const Triangle& tri) {
    Point3 ab = tri.b - tri.a, ac = tri.c - tri.a;
    Point3 n = ab.cross(ac);
    double nlen = n.len();
    if (nlen < EPS) return distPointPoint(p, tri.a);
    double d = (p - tri.a).dot(n) / nlen;
    Point3 proj = p - n * (d / nlen);
    if (pointInTriangle(proj, tri)) return fabs(d);
    LineSegment e1{tri.a, tri.b}, e2{tri.b, tri.c}, e3{tri.c, tri.a};
    double d1 = distPointLineSegment(p, e1);
    double d2 = distPointLineSegment(p, e2);
    double d3 = distPointLineSegment(p, e3);
    return min(min(d1, d2), d3);
}

double distLineSegmentLineSegment(const LineSegment& s1, const LineSegment& s2) {
    Point3 u = s1.b - s1.a, v = s2.b - s2.a, w = s1.a - s2.a;
    double a = u.dot(u), b = u.dot(v), c = v.dot(v), d = u.dot(w), e = v.dot(w);
    double ans = INF;
    double denom = a * c - b * b;
    if (fabs(denom) > EPS) {
        double s0 = (-d * c + b * e) / denom;
        double t0 = (a * e - b * d) / denom;
        if (s0 >= 0 && s0 <= 1 && t0 >= 0 && t0 <= 1) {
            Point3 p1 = s1.a + u * s0;
            Point3 p2 = s2.a + v * t0;
            ans = min(ans, (p1 - p2).len());
        }
    }
    ans = min(ans, distPointLineSegment(s1.a, s2));
    ans = min(ans, distPointLineSegment(s1.b, s2));
    ans = min(ans, distPointLineSegment(s2.a, s1));
    ans = min(ans, distPointLineSegment(s2.b, s1));
    ans = min(ans, distPointPoint(s1.a, s2.a));
    ans = min(ans, distPointPoint(s1.a, s2.b));
    ans = min(ans, distPointPoint(s1.b, s2.a));
    ans = min(ans, distPointPoint(s1.b, s2.b));
    return ans;
}

double distLineSegmentTriangle(const LineSegment& seg, const Triangle& tri) {
    auto f = [&](double s) {
        Point3 p = seg.a + (seg.b - seg.a) * s;
        return distPointTriangle(p, tri);
    };
    double l = 0, r = 1;
    for (int i = 0; i < 100; ++i) {
        double m1 = l + (r - l) / 3;
        double m2 = r - (r - l) / 3;
        if (f(m1) < f(m2)) r = m2;
        else l = m1;
    }
    return f((l + r) / 2);
}

vector<LineSegment> getEdges(const vector<Point3>& verts) {
    vector<LineSegment> edges;
    for (int i = 0; i < 4; ++i)
        for (int j = i + 1; j < 4; ++j)
            edges.push_back({verts[i], verts[j]});
    return edges;
}

vector<Triangle> getFaces(const vector<Point3>& verts) {
    vector<Triangle> faces;
    int idx[4][3] = {{1,2,3},{0,2,3},{0,1,3},{0,1,2}};
    for (int i = 0; i < 4; ++i)
        faces.push_back({verts[idx[i][0]], verts[idx[i][1]], verts[idx[i][2]]});
    return faces;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    cout << fixed << setprecision(2);
    while (T--) {
        vector<Point3> v1(4), v2(4);
        for (int i = 0; i < 4; ++i) cin >> v1[i].x >> v1[i].y >> v1[i].z;
        for (int i = 0; i < 4; ++i) cin >> v2[i].x >> v2[i].y >> v2[i].z;

        auto edges1 = getEdges(v1), edges2 = getEdges(v2);
        auto faces1 = getFaces(v1), faces2 = getFaces(v2);

        double ans = INF;

        for (const auto& p : v1)
            for (const auto& q : v2)
                ans = min(ans, distPointPoint(p, q));

        for (const auto& p : v1)
            for (const auto& e : edges2)
                ans = min(ans, distPointLineSegment(p, e));
        for (const auto& e : edges1)
            for (const auto& q : v2)
                ans = min(ans, distPointLineSegment(q, e));

        for (const auto& p : v1)
            for (const auto& f : faces2)
                ans = min(ans, distPointTriangle(p, f));
        for (const auto& f : faces1)
            for (const auto& q : v2)
                ans = min(ans, distPointTriangle(q, f));

        for (const auto& e1 : edges1)
            for (const auto& e2 : edges2)
                ans = min(ans, distLineSegmentLineSegment(e1, e2));

        for (const auto& e : edges1)
            for (const auto& f : faces2)
                ans = min(ans, distLineSegmentTriangle(e, f));
        for (const auto& f : faces1)
            for (const auto& e : edges2)
                ans = min(ans, distLineSegmentTriangle(e, f));

        cout << ans << '\n';
    }
    return 0;
}
