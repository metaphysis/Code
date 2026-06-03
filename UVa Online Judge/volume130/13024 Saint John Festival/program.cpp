// Saint John Festival
// UVa ID: 13024
// Verdict: Accepted
// Submission Date: 2026-06-02
// UVa Run Time: 0.100s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct Point {
    ll x, y;
    Point() {}
    Point(ll x, ll y) : x(x), y(y) {}
    bool operator<(const Point& p) const { return x < p.x || (x == p.x && y < p.y); }
    Point operator-(const Point& p) const { return Point(x - p.x, y - p.y); }
};

ll cross(const Point& a, const Point& b) { return a.x * b.y - a.y * b.x; }
ll dot(const Point& a, const Point& b) { return a.x * b.x + a.y * b.y; }
ll cross(const Point& o, const Point& a, const Point& b) { return cross(a - o, b - o); }

// 判断点 p 是否在线段 ab 上（包括端点）
bool onSegment(const Point& p, const Point& a, const Point& b) {
    if (cross(a, b, p) != 0) return false;
    ll minx = min(a.x, b.x), maxx = max(a.x, b.x);
    ll miny = min(a.y, b.y), maxy = max(a.y, b.y);
    return p.x >= minx && p.x <= maxx && p.y >= miny && p.y <= maxy;
}

// 凸包（Andrew 算法）
vector<Point> convexHull(vector<Point> pts) {
    int n = pts.size();
    if (n <= 1) return pts;
    sort(pts.begin(), pts.end());
    vector<Point> hull(2 * n);
    int k = 0;
    // 下凸包
    for (int i = 0; i < n; ++i) {
        while (k >= 2 && cross(hull[k-2], hull[k-1], pts[i]) <= 0) --k;
        hull[k++] = pts[i];
    }
    // 上凸包
    int t = k + 1;
    for (int i = n-2; i >= 0; --i) {
        while (k >= t && cross(hull[k-2], hull[k-1], pts[i]) <= 0) --k;
        hull[k++] = pts[i];
    }
    hull.resize(k-1);
    return hull;
}

// 判断点是否在凸多边形内部或边界上（凸多边形顶点逆时针）
bool pointInConvexPolygon(const vector<Point>& poly, const Point& p) {
    int n = poly.size();
    if (n == 0) return false;
    // 检查是否在第一个顶点的扇形区域内
    if (cross(poly[0], poly[1], p) < 0 || cross(poly[0], poly[n-1], p) > 0) return false;
    // 二分查找所在三角形
    int lo = 1, hi = n - 1;
    while (hi - lo > 1) {
        int mid = (lo + hi) / 2;
        if (cross(poly[0], poly[mid], p) >= 0) lo = mid;
        else hi = mid;
    }
    // 判断是否在三角形 poly[0], poly[lo], poly[hi] 内
    return cross(poly[lo], poly[hi], p) >= 0 || onSegment(p, poly[lo], poly[hi]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int L;
    while (cin >> L) {
        vector<Point> large(L);
        for (int i = 0; i < L; ++i) cin >> large[i].x >> large[i].y;
        vector<Point> hull = convexHull(large);
        int S;
        cin >> S;
        int ans = 0;
        for (int i = 0; i < S; ++i) {
            Point p;
            cin >> p.x >> p.y;
            if (pointInConvexPolygon(hull, p)) ++ans;
        }
        cout << ans << '\n';
    }
    return 0;
}
