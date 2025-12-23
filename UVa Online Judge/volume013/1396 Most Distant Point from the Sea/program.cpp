// Most Distant Point from the Sea
// UVa ID: 1396
// Verdict: Accepted
// Submission Date: 2025-12-15
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-8;          // 精度控制
const double INF = 1e10;          // 无穷大

// 点与向量
struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
    Point operator+(const Point& b) const { return Point(x + b.x, y + b.y); }
    Point operator-(const Point& b) const { return Point(x - b.x, y - b.y); }
    Point operator*(double k) const { return Point(x * k, y * k); }
    Point operator/(double k) const { return Point(x / k, y / k); }
    double dot(const Point& b) const { return x * b.x + y * b.y; }
    double cross(const Point& b) const { return x * b.y - y * b.x; }
    double length() const { return sqrt(x * x + y * y); }
    Point normal() const { return Point(-y, x); } // 逆时针旋转90度（法向量）
};

// 直线/半平面：点p，方向向量v，左侧为半平面
struct Line {
    Point p, v;
    double angle;
    Line() {}
    Line(Point p, Point v) : p(p), v(v) { angle = atan2(v.y, v.x); }
    bool operator<(const Line& b) const { return angle < b.angle; }
    Point intersect(const Line& b) const {
        Point u = p - b.p;
        double t = b.v.cross(u) / v.cross(b.v);
        return p + v * t;
    }
    bool onLeft(Point pt) const { return v.cross(pt - p) > EPS; } // 点在半平面左侧（严格）
};

// 半平面交（返回多边形点集，若为空表示无解）
vector<Point> halfplaneIntersection(vector<Line> lines) {
    int n = lines.size();
    sort(lines.begin(), lines.end());
    int first = 0, last = 0;
    vector<Point> p(n);
    vector<Line> q(n);
    q[0] = lines[0];
    for (int i = 1; i < n; i++) {
        while (first < last && !lines[i].onLeft(p[last - 1])) last--;
        while (first < last && !lines[i].onLeft(p[first])) first++;
        q[++last] = lines[i];
        if (fabs(q[last].v.cross(q[last - 1].v)) < EPS) { // 平行
            last--;
            if (q[last].onLeft(lines[i].p)) q[last] = lines[i];
        }
        if (first < last) p[last - 1] = q[last - 1].intersect(q[last]);
    }
    while (first < last && !q[first].onLeft(p[last - 1])) last--;
    if (last - first <= 1) return vector<Point>(); // 空集
    p[last] = q[last].intersect(q[first]);
    vector<Point> res;
    for (int i = first; i <= last; i++) res.push_back(p[i]);
    return res;
}

int main() {
    int n;
    while (cin >> n && n) {
        vector<Point> poly(n);
        for (int i = 0; i < n; i++) cin >> poly[i].x >> poly[i].y;

        double left = 0, right = 20000; // 最大距离不超过坐标范围
        while (right - left > EPS) {
            double mid = (left + right) / 2;
            vector<Line> lines;
            // 构造向内缩进mid的半平面
            for (int i = 0; i < n; i++) {
                Point a = poly[i], b = poly[(i + 1) % n];
                Point dir = b - a;
                Point normal = Point(-dir.y, dir.x); // 法向量（指向多边形内部，因为顶点逆时针）
                normal = normal / normal.length();   // 单位化
                lines.push_back(Line(a + normal * mid, dir)); // 边向内平移mid
            }
            vector<Point> res = halfplaneIntersection(lines);
            if (res.empty()) right = mid; // 无解，距离太大
            else left = mid;              // 有解，可以尝试更大距离
        }
        printf("%.6lf\n", left); // 输出左端点（满足条件）
    }
    return 0;
}
