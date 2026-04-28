// Towers for Mobile Telephony
// UVa ID: 11681
// Verdict: Accepted
// Submission Date: 2026-04-27
// UVa Run Time: 0.030s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-8;
const double INF = 1e20;

inline int dcmp(double x) {
    if (fabs(x) < eps) return 0;
    return x < 0 ? -1 : 1;
}

struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
    Point operator+(const Point& p) const { return Point(x + p.x, y + p.y); }
    Point operator-(const Point& p) const { return Point(x - p.x, y - p.y); }
    Point operator/(double t) const { return Point(x / t, y / t); }
};

double dist(const Point& a, const Point& b) { 
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)); 
}

// 全局数组用于存储未覆盖的点
Point remaining[40];
int remainCnt;

// 两点确定圆心（直径为两点连线）
Point getCenterByDiameter(const Point& a, const Point& b) {
    return Point((a.x + b.x) / 2, (a.y + b.y) / 2);
}

// 三点确定外接圆圆心
Point getCircumcenter(const Point& a, const Point& b, const Point& c) {
    double d = 2 * (a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y));
    if (fabs(d) < eps) return Point(INF, INF);
    double ux = ((a.x * a.x + a.y * a.y) * (b.y - c.y) + 
                 (b.x * b.x + b.y * b.y) * (c.y - a.y) + 
                 (c.x * c.x + c.y * c.y) * (a.y - b.y)) / d;
    double uy = ((a.x * a.x + a.y * a.y) * (c.x - b.x) + 
                 (b.x * b.x + b.y * b.y) * (a.x - c.x) + 
                 (c.x * c.x + c.y * c.y) * (b.x - a.x)) / d;
    return Point(ux, uy);
}

// 随机增量法求最小圆覆盖（覆盖数组中的点，n为点数）
double minEnclosingCircle(Point* pts, int n) {
    Point center = pts[0];
    double r = 0;
    
    for (int i = 1; i < n; ++i) {
        if (dist(pts[i], center) <= r + eps) continue;
        center = pts[i];
        r = 0;
        for (int j = 0; j < i; ++j) {
            if (dist(pts[j], center) <= r + eps) continue;
            center = getCenterByDiameter(pts[i], pts[j]);
            r = dist(pts[i], center);
            for (int k = 0; k < j; ++k) {
                if (dist(pts[k], center) <= r + eps) continue;
                center = getCircumcenter(pts[i], pts[j], pts[k]);
                r = dist(center, pts[i]);
            }
        }
    }
    return r;
}

double solveTestCase(int N, Point* points) {
    double ans = INF;
    
    // 情况1：两点定圆（直径为两点连线）
    for (int i = 0; i < N; ++i) for (int j = i + 1; j < N; ++j) {
        Point c1 = getCenterByDiameter(points[i], points[j]);
        double r1 = dist(c1, points[i]);
        if (r1 >= ans) continue;
        
        remainCnt = 0;
        for (int k = 0; k < N; ++k) 
            if (dist(points[k], c1) > r1 + eps) remaining[remainCnt++] = points[k];
        
        double r2 = minEnclosingCircle(remaining, remainCnt);
        ans = min(ans, max(r1, r2));
    }
    
    // 情况2：三点定圆（外接圆）
    for (int i = 0; i < N; ++i) for (int j = i + 1; j < N; ++j) for (int k = j + 1; k < N; ++k) {
        Point c1 = getCircumcenter(points[i], points[j], points[k]);
        if (c1.x > INF / 2) continue;
        double r1 = dist(c1, points[i]);
        if (r1 >= ans) continue;
        
        remainCnt = 0;
        for (int m = 0; m < N; ++m) 
            if (dist(points[m], c1) > r1 + eps) remaining[remainCnt++] = points[m];
        
        double r2 = minEnclosingCircle(remaining, remainCnt);
        ans = min(ans, max(r1, r2));
    }
    
    // 特殊情况：所有点用一个圆覆盖
    ans = min(ans, minEnclosingCircle(points, N));
    
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    Point points[40];
    while (cin >> N && N != 0) {
        for (int i = 0; i < N; ++i) cin >> points[i].x >> points[i].y;
        double result = solveTestCase(N, points);
        cout << fixed << setprecision(2) << result << '\n';
    }
    return 0;
}
