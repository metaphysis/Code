// Happy Birthday
// UVa ID: 11373
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.010s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net


#include <bits/stdc++.h>
using namespace std;

const double PI = acos(-1.0);

struct Point {
    double x, y;
};

// 叉积
double cross(double ax, double ay, double bx, double by) {
    return ax * by - ay * bx;
}

// 两条直线的交点（直线1过a,b；直线2过c,d）
Point intersectLines(const Point& a, const Point& b, const Point& c, const Point& d) {
    double rx = b.x - a.x, ry = b.y - a.y;
    double sx = d.x - c.x, sy = d.y - c.y;
    double qx = c.x - a.x, qy = c.y - a.y;
    double denom = cross(rx, ry, sx, sy);
    double t = cross(qx, qy, sx, sy) / denom;
    return {a.x + t * rx, a.y + t * ry};
}

// 直线（过点a，方向向量dir）与圆（半径R）的交点，存入p1,p2
void circleIntersect(const Point& a, const Point& dir, double R, Point& p1, Point& p2) {
    double dx = dir.x, dy = dir.y;
    double A = dx * dx + dy * dy;
    double B = 2 * (a.x * dx + a.y * dy);
    double C = a.x * a.x + a.y * a.y - R * R;
    double delta = B * B - 4 * A * C;
    double sqrtD = sqrt(max(0.0, delta));
    double t1 = (-B - sqrtD) / (2 * A);
    double t2 = (-B + sqrtD) / (2 * A);
    p1 = {a.x + t1 * dx, a.y + t1 * dy};
    p2 = {a.x + t2 * dx, a.y + t2 * dy};
}

int main() {
    double R, h;
    while (cin >> R >> h) {
        Point a, b, c, d;
        cin >> a.x >> a.y >> b.x >> b.y;
        cin >> c.x >> c.y >> d.x >> d.y;
        Point P = intersectLines(a, b, c, d);          // 两条切割线的交点
        Point dir1 = {b.x - a.x, b.y - a.y};
        Point dir2 = {d.x - c.x, d.y - c.y};
        Point p1, p2, p3, p4;
        circleIntersect(a, dir1, R, p1, p2);           // 第一条线与圆的交点
        circleIntersect(c, dir2, R, p3, p4);           // 第二条线与圆的交点
        vector<pair<double, Point>> ang;
        for (const Point& pt : {p1, p2, p3, p4}) {
            double theta = atan2(pt.y, pt.x);
            ang.push_back({theta, pt});
        }
        sort(ang.begin(), ang.end(), [](const pair<double, Point>& u, const pair<double, Point>& v) {
            return u.first < v.first;
        });
        vector<double> areas;
        double R2 = R * R;
        for (int i = 0; i < 4; ++i) {
            const Point& A = ang[i].second;
            const Point& B = ang[(i + 1) % 4].second;
            double delta = ang[(i + 1) % 4].first - ang[i].first;
            if (delta < 0) delta += 2 * PI;
            double term = (B.x * P.y - B.y * P.x) + (P.x * A.y - P.y * A.x);
            double area = 0.5 * (R2 * delta + term);
            if (area < 0) area = -area;   // 防止符号误差
            areas.push_back(area);
        }
        double maxArea = *max_element(areas.begin(), areas.end());
        double minArea = *min_element(areas.begin(), areas.end());
        cout << fixed << setprecision(2) << maxArea * h << " " << minArea * h << endl;
    }
    return 0;
}
