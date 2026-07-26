// Farmer Jane 
// UVa ID: 12945
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.010s
// https://blog.csdn.net/metaphysis/article/details/163173874

#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9;

struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
    Point operator - (const Point& o) const { return Point(x - o.x, y - o.y); }
    Point operator + (const Point& o) const { return Point(x + o.x, y + o.y); }
    double dot(const Point& o) const { return x * o.x + y * o.y; }
    double cross(const Point& o) const { return x * o.y - y * o.x; }
    double len2() const { return x * x + y * y; }
};

double cross(const Point& a, const Point& b, const Point& c) {
    return (b - a).cross(c - a);
}

bool cmp(const Point& a, const Point& b) {
    if (fabs(a.x - b.x) > EPS) return a.x < b.x;
    return a.y < b.y;
}

vector<Point> convexHull(vector<Point> pts) {
    sort(pts.begin(), pts.end(), cmp);
    int n = pts.size();
    vector<Point> H(2 * n);
    int k = 0;
    // 下凸包
    for (int i = 0; i < n; ++i) {
        while (k >= 2 && cross(H[k - 2], H[k - 1], pts[i]) <= EPS) --k;
        H[k++] = pts[i];
    }
    // 上凸包
    for (int i = n - 2, t = k + 1; i >= 0; --i) {
        while (k >= t && cross(H[k - 2], H[k - 1], pts[i]) <= EPS) --k;
        H[k++] = pts[i];
    }
    H.resize(k - 1);
    return H;
}

bool pointInConvex(const vector<Point>& poly, const Point& p) {
    for (int i = 0; i < (int)poly.size(); ++i) {
        Point a = poly[i], b = poly[(i + 1) % poly.size()];
        if (cross(a, b, p) < -EPS) return false;
    }
    return true;
}

double pointToSegment(const Point& p, const Point& a, const Point& b, Point& q) {
    Point ab = b - a;
    Point ap = p - a;
    double t = ap.dot(ab) / ab.dot(ab);
    if (t < 0) t = 0;
    else if (t > 1) t = 1;
    q = a + Point(ab.x * t, ab.y * t);
    return (p - q).len2();
}

int main() {
    int N;
    while (cin >> N) {
        vector<Point> trees;
        vector<int> w(N);
        double sumW = 0, sumX = 0, sumY = 0;
        for (int i = 0; i < N; ++i) {
            double x, y;
            int wi;
            cin >> x >> y >> wi;
            trees.push_back(Point(x, y));
            w[i] = wi;
            sumW += wi;
            sumX += wi * x;
            sumY += wi * y;
        }
        Point center(sumX / sumW, sumY / sumW);
        vector<Point> poly = convexHull(trees);
        Point bestPoint;
        if (pointInConvex(poly, center)) {
            bestPoint = center;
        } else {
            double minDist2 = 1e100;
            for (int i = 0; i < (int)poly.size(); ++i) {
                Point a = poly[i], b = poly[(i + 1) % poly.size()];
                Point q;
                double d2 = pointToSegment(center, a, b, q);
                if (d2 < minDist2 - EPS) {
                    minDist2 = d2;
                    bestPoint = q;
                }
            }
        }
        double cost = 0;
        for (int i = 0; i < N; ++i) {
            double dx = trees[i].x - bestPoint.x;
            double dy = trees[i].y - bestPoint.y;
            cost += w[i] * (dx * dx + dy * dy);
        }
        // 四舍五入保留三位小数（.5 向上）
        long long scaled = (long long)(cost * 1000 + 0.5 + 1e-9);
        printf("%lld.%03lld\n", scaled / 1000, scaled % 1000);
    }
    return 0;
}
