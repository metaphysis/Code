// Heliport
// UVa ID: 1029
// Verdict: Accepted
// Submission Date: 2026-06-16
// UVa Run Time: 0.080s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
    Point operator + (const Point& p) const { return Point(x + p.x, y + p.y); }
    Point operator - (const Point& p) const { return Point(x - p.x, y - p.y); }
    Point operator * (double t) const { return Point(x * t, y * t); }
    double dot(const Point& p) const { return x * p.x + y * p.y; }
    double cross(const Point& p) const { return x * p.y - y * p.x; }
    double len() const { return hypot(x, y); }
    Point normalize() const { double l = len(); return Point(x / l, y / l); }
};

const double EPS = 1e-6;
int dcmp(double x) { return fabs(x) < EPS ? 0 : (x < 0 ? -1 : 1); }

vector<Point> poly;

double pointToSegDist(Point p, Point a, Point b) {
    Point ab = b - a, ap = p - a;
    double t = ap.dot(ab) / ab.dot(ab);
    if (t < 0) t = 0;
    if (t > 1) t = 1;
    Point closest = a + ab * t;
    return (p - closest).len();
}

bool isInside(Point p) {
    int n = poly.size();
    bool inside = false;
    for (int i = 0, j = n - 1; i < n; j = i++) {
        if (((poly[i].y > p.y) != (poly[j].y > p.y)) &&
            (p.x < (poly[j].x - poly[i].x) * (p.y - poly[i].y) / (poly[j].y - poly[i].y) + poly[i].x))
            inside = !inside;
    }
    return inside;
}

bool isValidCircle(Point c, double r) {
    if (!isInside(c)) return false;
    int n = poly.size();
    for (int i = 0; i < n; ++i) {
        Point a = poly[i], b = poly[(i + 1) % n];
        if (dcmp((a - c).len() - r) < 0) return false;
        if (dcmp((b - c).len() - r) < 0) return false;
        if (dcmp(pointToSegDist(c, a, b) - r) < 0) return false;
    }
    return true;
}

bool isFeasible(double r) {
    int n = poly.size();
    vector<double> horizY, vertX;
    for (int i = 0; i < n; ++i) {
        Point a = poly[i], b = poly[(i + 1) % n];
        if (dcmp(a.y - b.y) == 0) horizY.push_back(a.y);
        else vertX.push_back(a.x);
    }
    
    // 两条垂直边
    for (double y : horizY) for (double x : vertX)
        for (int sx : {-1, 1}) for (int sy : {-1, 1})
            if (isValidCircle(Point(x + sx * r, y + sy * r), r)) return true;
    
    // 一边 + 一顶点
    for (int vi = 0; vi < n; ++vi) {
        Point v = poly[vi];
        for (int ei = 0; ei < n; ++ei) {
            Point a = poly[ei], b = poly[(ei + 1) % n];
            if (vi == ei || vi == (ei + 1) % n) continue;
            if (dcmp(a.y - b.y) == 0) {
                double y = a.y, L = min(a.x, b.x), R = max(a.x, b.x);
                for (int sgn : {-1, 1}) for (int sx : {-1, 1}) {
                    Point c(v.x + sx * r, y + sgn * r);
                    if (dcmp(c.x - L) >= 0 && dcmp(c.x - R) <= 0 && isValidCircle(c, r)) return true;
                }
            } else {
                double x = a.x, D = min(a.y, b.y), U = max(a.y, b.y);
                for (int sgn : {-1, 1}) for (int sy : {-1, 1}) {
                    Point c(x + sgn * r, v.y + sy * r);
                    if (dcmp(c.y - D) >= 0 && dcmp(c.y - U) <= 0 && isValidCircle(c, r)) return true;
                }
            }
        }
    }
    
    // 两个顶点
    for (int i = 0; i < n; ++i) for (int j = i + 1; j < n; ++j) {
        Point v1 = poly[i], v2 = poly[j], mid = (v1 + v2) * 0.5;
        double L = (v1 - v2).len();
        if (dcmp(r - L / 2) < 0) continue;
        double d = sqrt(r * r - L * L / 4);
        Point dir = Point(v1.y - v2.y, v2.x - v1.x).normalize();
        for (int sgn : {-1, 1})
            if (isValidCircle(mid + dir * d * sgn, r)) return true;
    }
    return false;
}

double solve() {
    double lo = 0, hi = 1e4;
    for (int iter = 0; iter < 60; ++iter) {
        double mid = (lo + hi) / 2;
        if (isFeasible(mid)) lo = mid;
        else hi = mid;
    }
    return lo;
}

int main() {
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
    int n, cs = 0;
    while (cin >> n, n) {
        poly.clear();
        poly.emplace_back(0, 0);
        double x = 0, y = 0;
        for (int i = 0; i < n; ++i) {
            int m; char d;
            cin >> m >> d;
            if (d == 'U') y += m;
            else if (d == 'D') y -= m;
            else if (d == 'R') x += m;
            else x -= m;
            poly.emplace_back(x, y);
        }
        poly.pop_back();
        double r = solve();
        if (cs) cout << "\n";
        cout << "Case Number " << ++cs<< " radius is: " << fixed << setprecision(2) << r << "\n";
    }
    return 0;
}
