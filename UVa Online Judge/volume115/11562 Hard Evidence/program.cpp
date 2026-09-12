#include <bits/stdc++.h>
using namespace std;

const double pi = acos(-1.0);

struct Point {
    double x, y;
    Point operator + (const Point &p) const {
        return {x + p.x, y + p.y};
    }
    Point operator - (const Point &p) const {
        return {x - p.x, y - p.y};
    }
    Point operator * (double k) const {
        return {x * k, y * k};
    }
};

double dot(Point a, Point b) {
    return a.x * b.x + a.y * b.y;
}

double getCos(Point a, Point b, double radius, double t) {
    double st = sin(t), ct = cos(t);
    Point p = {radius * ct, radius * st};
    Point u = a - p, v = b - p;
    double den = sqrt(dot(u, u) * dot(v, v));
    return dot(u, v) / den;
}

double searchArc(Point a, Point b, double radius, double left, double right) {
    for (int i = 0; i < 55; i++) {
        double mid1 = (2.0 * left + right) / 3.0, mid2 = (left + 2.0 * right) / 3.0;
        if (getCos(a, b, radius, mid1) > getCos(a, b, radius, mid2))
            left = mid1;
        else
            right = mid2;
    }
    return getCos(a, b, radius, (left + right) * 0.5);
}

double getPairCos(Point a, Point b, double radius) {
    Point v = b - a;
    double vv = dot(v, v);
    double t = -dot(a, v) / vv;
    Point h = a + v * t;
    double dis2 = dot(h, h);
    double len = sqrt(max(0.0, radius * radius - dis2));
    double vLen = sqrt(vv);
    Point unit = v * (1.0 / vLen);
    Point p1 = h + unit * len, p2 = h - unit * len;
    double x1 = atan2(p1.y, p1.x), x2 = atan2(p2.y, p2.x);
    double delta = x2 - x1;
    if (delta < 0.0)
        delta += 2.0 * pi;
    double c1 = searchArc(a, b, radius, x1, x1 + delta);
    double c2 = searchArc(a, b, radius, x1 + delta, x1 + 2.0 * pi);
    return min(c1, c2);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, r;
    while (cin >> n >> r) {
        vector<Point> p(n);
        for (int i = 0; i < n; i++)
            cin >> p[i].x >> p[i].y;
        double radius = r, bestCos = 1.0;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                bestCos = min(bestCos, getPairCos(p[i], p[j], radius));
        cout << fixed << setprecision(10) << acos(max(-1.0, min(1.0, bestCos))) << '\n';
    }
    return 0;
}
