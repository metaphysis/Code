// Jungle Outpost
// UVa ID: 1475
// Verdict: Accepted
// Submission Date: 2026-05-31
// UVa Run Time: 4.110s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9;

struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
    Point operator + (const Point& p) const { return Point(x + p.x, y + p.y); }
    Point operator - (const Point& p) const { return Point(x - p.x, y - p.y); }
    Point operator * (double c) const { return Point(x * c, y * c); }
    double dot(const Point& p) const { return x * p.x + y * p.y; }
    double cross(const Point& p) const { return x * p.y - y * p.x; }
};

typedef Point Vector;

struct Line {
    Point p;
    Vector v;
    double ang;
    Line(Point p = Point(), Vector v = Vector()) : p(p), v(v) { ang = atan2(v.y, v.x); }
    bool operator < (const Line& l) const { return ang < l.ang; }
};

bool onLeft(const Line& l, const Point& p) {
    return l.v.cross(p - l.p) > EPS;
}

Point intersect(const Line& a, const Line& b) {
    Vector u = a.p - b.p;
    double t = b.v.cross(u) / a.v.cross(b.v);
    return a.p + a.v * t;
}

bool halfplaneIntersection(vector<Line>& lines, vector<Point>& poly) {
    sort(lines.begin(), lines.end());
    deque<Line> dq;
    deque<Point> pts;
    for (size_t i = 0; i < lines.size(); ++i) {
        // 去掉极角相同的直线中靠后的
        if (i > 0 && fabs(lines[i].ang - lines[i-1].ang) < EPS) continue;
        while (pts.size() > 0 && !onLeft(lines[i], pts.back())) {
            pts.pop_back();
            dq.pop_back();
        }
        while (pts.size() > 0 && !onLeft(lines[i], pts.front())) {
            pts.pop_front();
            dq.pop_front();
        }
        if (dq.size() > 0 && fabs(lines[i].v.cross(dq.back().v)) < EPS) {
            if (onLeft(dq.back(), lines[i].p)) {
                dq.back() = lines[i];
                if (pts.size() > 0) pts.pop_back();
            }
            continue;
        }
        if (dq.size() > 0) pts.push_back(intersect(dq.back(), lines[i]));
        dq.push_back(lines[i]);
    }
    while (pts.size() > 0 && !onLeft(dq.front(), pts.back())) {
        pts.pop_back();
        dq.pop_back();
    }
    if (dq.size() <= 2) return false;
    pts.push_back(intersect(dq.front(), dq.back()));
    poly.clear();
    for (const Point& p : pts) poly.push_back(p);
    double area = 0;
    for (size_t i = 0; i < poly.size(); ++i)
        area += poly[i].cross(poly[(i + 1) % poly.size()]);
    return fabs(area) > EPS;
}

int n;
vector<Point> points;

bool check(int k) {
    if (k == 0) return true;
    if (k >= n - 2) return false;
    vector<Line> lines;
    // 原多边形边：取反向，使内部在左侧
    for (int i = 0; i < n; ++i) {
        Point a = points[(i + 1) % n];  // 反向起点
        Point b = points[i];            // 反向终点
        Vector v = b - a;
        lines.push_back(Line(a, v));
    }
    // 删除连续 k 个顶点后的新边：同样取反向
    for (int i = 0; i < n; ++i) {
        int j = (i + k + 1) % n;
        Point a = points[j];   // 反向：从 v_j 到 v_i
        Point b = points[i];
        Vector v = b - a;
        lines.push_back(Line(a, v));
    }
    vector<Point> poly;
    return halfplaneIntersection(lines, poly);
}

int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    while (scanf("%d", &n) == 1) {
        points.resize(n);
        for (int i = 0; i < n; ++i) scanf("%lf %lf", &points[i].x, &points[i].y);
        int left = 0, right = n - 3, ans = 0;
        while (left <= right) {
            int mid = (left + right) / 2;
            if (check(mid)) {
                ans = mid;
                left = mid + 1;
            } else right = mid - 1;
        }
        printf("%d\n", ans + 1);
    }
    return 0;
}
