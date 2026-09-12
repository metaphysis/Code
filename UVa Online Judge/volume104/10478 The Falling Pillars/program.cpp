// The Falling Pillars
// UVa ID: 10478
// Verdict: Accepted
// Submission Date: 2026-08-08
// UVa Run Time: 0.000s

#include <bits/stdc++.h>
using namespace std;

const double PI = acos(-1.0);
const double EPS = 1e-7;

struct Point {
    double x, y;
    Point operator + (const Point &p) const { return {x + p.x, y + p.y}; }
    Point operator - (const Point &p) const { return {x - p.x, y - p.y}; }
    Point operator * (double k) const { return {x * k, y * k}; }
};

double dot(Point a, Point b) { return a.x * b.x + a.y * b.y; }

double len(Point a) { return sqrt(dot(a, a)); }

Point unit(Point a) {
    double l = len(a);
    return a * (1.0 / l);
}

void getContact(Point c, Point p, Point u, double h, Point &a) {
    double b = 2.0 * dot(p - c, u);
    double cc = dot(p - c, p - c) - h * h;
    double delta = b * b - 4.0 * cc;
    double root = sqrt(max(0.0, delta));
    double t1 = (-b - root) / 2.0;
    double t2 = (-b + root) / 2.0;
    Point a1 = p + u * t1, a2 = p + u * t2;
    if (a1.x < EPS && a1.y > EPS) a = a1;
    else a = a2;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, d, h, w, tc;
    cin >> tc;
    cout << fixed << setprecision(3);
    for (int cs = 1; cs <= tc; cs++) {
        cin >> n >> d >> h >> w;
        cout << "Case " << cs << ":\n";
        if (n <= 1) continue;
        if (d < w) {
            cout << "Impossible.\n";
            continue;
        }
        if (d == w) {
            for (int i = 1; i < n; i++) cout << "90.000\n";
            continue;
        }
        if (d - w >= h) {
            for (int i = 1; i < n; i++) cout << "0.000\n";
            continue;
        }
        bool unstable = false;
        double value = (double)(d - w) / h;
        value = max(-1.0, min(1.0, value));
        double check = acos(value) + atan((double)w / h);
        unstable = check > PI / 2.0 + EPS;
        if (unstable) cout << "Unstable Situation.\n";
        Point side = {(double)-w, 0.0}, dir = {0.0, 1.0};
        for (int i = 1; i < n; i++) {
            Point base = {(double)-i * d, 0.0}, contact;
            getContact(base, side, dir, h, contact);
            Point axis = unit(contact - base);
            double angle = atan2(axis.y, axis.x) * 180.0 / PI;
            if (fabs(angle) < EPS) angle = 0.0;
            cout << angle << "\n";
            Point leftNormal = {-axis.y, axis.x};
            side = base + leftNormal * w;
            dir = axis;
        }
    }
    return 0;
}
