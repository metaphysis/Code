#include <bits/stdc++.h>
using namespace std;

struct Point {
    long long x, y;
};

__int128 cross(Point a, Point b, Point c) {
    return (__int128)(b.x - a.x) * (c.y - a.y) - (__int128)(b.y - a.y) * (c.x - a.x);
}

bool onSegment(Point a, Point b, Point p) {
    if (cross(a, b, p) != 0)
        return false;
    return min(a.x, b.x) <= p.x && p.x <= max(a.x, b.x) && min(a.y, b.y) <= p.y && p.y <= max(a.y, b.y);
}

bool isInside(const vector<Point> &poly, Point p) {
    int n = poly.size();
    for (int i = 0; i < n; i++) {
        Point a = poly[i], b = poly[(i + 1) % n];
        if (onSegment(a, b, p))
            return false;
    }
    bool inside = false;
    for (int i = 0; i < n; i++) {
        Point a = poly[i], b = poly[(i + 1) % n];
        if ((a.y > p.y) != (b.y > p.y)) {
            long long dy = b.y - a.y;
            __int128 value = (__int128)(b.x - a.x) * (p.y - a.y) - (__int128)dy * (p.x - a.x);
            if ((dy > 0 && value > 0) || (dy < 0 && value < 0))
                inside = !inside;
        }
    }
    return inside;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int a, b;
        cin >> a >> b;
        vector<Point> poly(a);
        for (Point &p : poly)
            cin >> p.x >> p.y;
        int ans = 0;
        for (int i = 0; i < b; i++) {
            Point p;
            cin >> p.x >> p.y;
            if (isInside(poly, p))
                ans++;
        }
        cout << ans << '\n';
    }
    return 0;
}
