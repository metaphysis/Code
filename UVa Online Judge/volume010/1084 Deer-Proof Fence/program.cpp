// Deer-Proof Fence
// UVa ID: 1084
// Verdict: Accepted
// Submission Date: 2026-01-14
// UVa Run Time: 0.010s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const double PI = acos(-1.0);
const double EPS = 1e-8;

struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
    // 向量加法
    Point operator+(const Point& p) const { return Point(x + p.x, y + p.y); }
    // 向量减法
    Point operator-(const Point& p) const { return Point(x - p.x, y - p.y); }
    // 叉积
    double cross(const Point& p) const { return x * p.y - y * p.x; }
    // 向量模长
    double dist() const { return hypot(x, y); }
    // 排序：先 x 后 y
    bool operator<(const Point& p) const {
        return fabs(x - p.x) < EPS ? y < p.y : x < p.x;
    }
};

// 计算点集凸包的周长（Andrew 算法）
double convexHullPerimeter(vector<Point> pts) {
    if (pts.size() <= 1) return 0;
    sort(pts.begin(), pts.end());
    vector<Point> hull;
    // 构建下凸壳和上凸壳
    for (int phase = 0; phase < 2; ++phase) {
        int start = hull.size();
        for (Point& p : pts) {
            while (hull.size() >= start + 2 && 
                   (hull.back() - hull[hull.size()-2]).cross(p - hull.back()) <= EPS)
                hull.pop_back();
            hull.push_back(p);
        }
        hull.pop_back(); // 删除重复的起点
        reverse(pts.begin(), pts.end());
    }
    // 计算凸包周长
    double len = 0;
    for (int i = 0; i < (int)hull.size(); ++i) {
        Point cur = hull[i], nxt = hull[(i+1)%hull.size()];
        len += (nxt - cur).dist();
    }
    return len;
}

int main() {
    int n, m, tc = 0;
    while (cin >> n >> m, n || m) {
        vector<Point> pts(n);
        for (int i = 0; i < n; ++i) cin >> pts[i].x >> pts[i].y;
        // 枚举所有子集，计算 dp
        int totalMask = (1 << n) - 1;
        vector<double> dp(totalMask + 1, 1e18);
        dp[0] = 0;
        for (int mask = 1; mask <= totalMask; ++mask) {
            // 收集该子集对应的点
            vector<Point> group;
            for (int i = 0; i < n; ++i) if (mask >> i & 1) group.push_back(pts[i]);
            // 计算该组单独围栏的长度：凸包周长 + 一个整圆周长
            double hullLen = convexHullPerimeter(group);
            double roundLen = 2 * PI * m;
            dp[mask] = hullLen + roundLen;
            // 枚举子集，尝试拆分
            for (int sub = (mask - 1) & mask; sub; sub = (sub - 1) & mask)
                dp[mask] = min(dp[mask], dp[sub] + dp[mask ^ sub]);
        }
        printf("Case %d: length = %.2lf\n", ++tc, dp[totalMask]);
    }
    return 0;
}
