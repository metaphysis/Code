// Fighting against a Polygonal Monster
// UVa ID: 11177
// Verdict: Accepted
// Submission Date: 2026-01-14
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const double PI = acos(-1.0);
const double EPS = 1e-9;

int dcmp(double x) { return fabs(x) < EPS ? 0 : (x < 0 ? -1 : 1); }

struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
    Point operator - (const Point &p) const { return Point(x - p.x, y - p.y); }
    Point operator + (const Point &p) const { return Point(x + p.x, y + p.y); }
    Point operator * (double d) const { return Point(x * d, y * d); }
    double operator * (const Point &p) const { return x * p.y - y * p.x; } // 叉积
    double dot(const Point &p) const { return x * p.x + y * p.y; }
    double len() const { return sqrt(x * x + y * y); }
    double len2() const { return x * x + y * y; }
};

// 向量夹角（0 ~ 2π）
double angleBetween(Point a, Point b) {
    double dot = a.dot(b);
    double det = a * b;
    double ang = atan2(det, dot);
    if (ang < 0) ang += 2 * PI;
    return ang;
}

// 扇形面积：圆心角 theta，半径 r
double sectorArea(double theta, double r) {
    return 0.5 * theta * r * r;
}

// 三角形 OAB 的有向面积
double triangleArea(Point a, Point b) {
    return fabs(a * b) / 2.0;
}

// 计算三角形 OAB 与半径为 r 的圆的相交面积
double triangleCircleIntersection(Point a, Point b, double r) {
    double da = a.len(), db = b.len();
    // 两个点都在圆内
    if (dcmp(da - r) <= 0 && dcmp(db - r) <= 0) return triangleArea(a, b);
    // 两个点都在圆外且线段与圆无交点
    Point d = b - a;
    double A = d.dot(d);
    double B = 2 * d.dot(a);
    double C = a.dot(a) - r * r;
    double delta = B * B - 4 * A * C;
    if (dcmp(delta) <= 0) {
        double theta = angleBetween(a, b);
        return sectorArea(theta, r);
    }
    double t1 = (-B - sqrt(delta)) / (2 * A);
    double t2 = (-B + sqrt(delta)) / (2 * A);
    if (t2 < 0 || t1 > 1) {
        double theta = angleBetween(a, b);
        return sectorArea(theta, r);
    }
    t1 = max(t1, 0.0);
    t2 = min(t2, 1.0);
    Point p1 = a + d * t1;
    Point p2 = a + d * t2;
    double res = 0;
    // A -> p1
    if (dcmp(da - r) <= 0) {
        res += triangleArea(a, p1);
    } else {
        double theta = angleBetween(a, p1);
        res += sectorArea(theta, r);
    }
    // p1 -> p2
    res += triangleArea(p1, p2);
    // p2 -> B
    if (dcmp(db - r) <= 0) {
        res += triangleArea(p2, b);
    } else {
        double theta = angleBetween(p2, b);
        res += sectorArea(theta, r);
    }
    return res;
}

// 计算圆与多边形的相交面积
double areaCirclePolygon(const vector<Point> &poly, double r) {
    double area = 0;
    int n = poly.size();
    for (int i = 0; i < n; i++) {
        Point a = poly[i], b = poly[(i + 1) % n];
        area += triangleCircleIntersection(a, b, r);
    }
    return area;
}

int main() {
    int n, caseNo = 1;
    double R;
    while (cin >> n && n) {
        cin >> R;
        vector<Point> poly(n);
        for (int i = 0; i < n; i++) cin >> poly[i].x >> poly[i].y;
        // 确保多边形面积为正（逆时针）
        double polyArea = 0;
        for (int i = 0; i < n; i++) polyArea += poly[i] * poly[(i + 1) % n];
        if (dcmp(polyArea) < 0) reverse(poly.begin(), poly.end());
        // 二分搜索半径
        double left = 0, right = 1e5;
        for (int iter = 0; iter < 60; iter++) {
            double mid = (left + right) / 2;
            double interArea = areaCirclePolygon(poly, mid);
            if (interArea >= R) right = mid;
            else left = mid;
        }
        cout << fixed << setprecision(2) << "Case " << caseNo++ << ": " << left << endl;
    }
    return 0;
}
