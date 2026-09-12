#include <bits/stdc++.h>
using namespace std;

const double pi = acos(-1.0);
const double eps = 1e-10;

struct Point {
    double x, y;
};

struct Circle {
    Point c;
    double r;
};

double getDist(Point a, Point b) {
    double dx = a.x - b.x, dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

double clampVal(double x) {
    if (x < -1.0) return -1.0;
    if (x > 1.0) return 1.0;
    return x;
}

double getInterArea(Circle a, Circle b) {
    double d = getDist(a.c, b.c);
    if (d >= a.r + b.r - eps) return 0.0;
    if (d <= fabs(a.r - b.r) + eps) {
        double r = min(a.r, b.r);
        return pi * r * r;
    }
    double x1 = (a.r * a.r + d * d - b.r * b.r) / (2.0 * a.r * d);
    double x2 = (b.r * b.r + d * d - a.r * a.r) / (2.0 * b.r * d);
    double ang1 = acos(clampVal(x1)), ang2 = acos(clampVal(x2));
    double s = a.r * a.r * ang1 + b.r * b.r * ang2;
    double tri = 0.5 * sqrt(max(0.0, (-d + a.r + b.r) * (d + a.r - b.r) * (d - a.r + b.r) * (d + a.r + b.r)));
    return s - tri;
}

Circle getCircle(Point r, Point j, double k) {
    double den = 1.0 - k * k;
    Point c;
    c.x = (j.x - k * k * r.x) / den;
    c.y = (j.y - k * k * r.y) / den;
    Circle res;
    res.c = c;
    res.r = k * getDist(r, j) / den;
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    for (int tc = 1; tc <= n; tc++) {
        Point r, j, t;
        int tr, sr, sj1, sj2;
        cin >> r.x >> r.y >> j.x >> j.y;
        cin >> t.x >> t.y >> tr;
        cin >> sr >> sj1 >> sj2;
        double k1 = 1.0 * sj1 / sr, k2 = 1.0 * sj2 / sr;
        Circle c1 = getCircle(r, j, k1), c2 = getCircle(r, j, k2);
        Circle tower;
        tower.c = t;
        tower.r = tr;
        double total = pi * (c2.r * c2.r - c1.r * c1.r);
        double seen = getInterArea(tower, c2) - getInterArea(tower, c1);
        double ans;
        if (total <= eps) ans = 0.0;
        else ans = max(0.0, min(1.0, seen / total));
        cout << "Scenario " << tc << ": " << fixed << setprecision(4) << ans << '\n';
    }
    return 0;
}
