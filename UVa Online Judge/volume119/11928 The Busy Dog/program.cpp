#include <bits/stdc++.h>
using namespace std;

struct Point { long long x, y; };

long long cross(const Point& a, const Point& b) {
    return a.x * b.y - a.y * b.x;
}

long long dot(const Point& a, const Point& b) {
    return a.x * b.x + a.y * b.y;
}

bool onSegment(const Point& a, const Point& b, const Point& p) {
    Point ab = {b.x - a.x, b.y - a.y};
    Point ap = {p.x - a.x, p.y - a.y};
    if (cross(ab, ap) != 0) return false;
    Point pb = {p.x - b.x, p.y - b.y};
    return dot(ap, pb) <= 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while (cin >> n && n) {
        long long px, py;
        cin >> px >> py;
        vector<Point> pts(n);
        for (int i = 0; i < n; ++i) cin >> pts[i].x >> pts[i].y;
        bool ouch = false;
        Point pole = {px, py};
        for (int i = 0; i < n; ++i) {
            int j = (i + 1) % n;
            if (onSegment(pts[i], pts[j], pole)) { ouch = true; break; }
        }
        if (ouch) { cout << "Ouch!\n"; continue; }
        long long winding = 0;
        for (int i = 0; i < n; ++i) {
            int j = (i + 1) % n;
            Point a = {pts[i].x - px, pts[i].y - py};
            Point b = {pts[j].x - px, pts[j].y - py};
            if (a.y <= 0 && b.y > 0 && cross(a, b) > 0) ++winding;
            else if (a.y > 0 && b.y <= 0 && cross(a, b) < 0) --winding;
        }
        if (winding > 0) cout << "+" << winding << "\n";
        else cout << winding << "\n";
    }
    return 0;
}
