#include <bits/stdc++.h>
using namespace std;

const long double eps = 1e-10L;

struct Point {
    long double x, y, z;
};

long double calc(Point a, Point b, Point m, long double h, long double r, long double t) {
    long double dx, dy, dz, xx, yy, zz, rr;
    dx = b.x - a.x;
    dy = b.y - a.y;
    dz = b.z - a.z;
    xx = a.x + dx * t - m.x;
    yy = a.y + dy * t - m.y;
    zz = h - a.z - dz * t;
    rr = r / h;
    return xx * xx + yy * yy - rr * rr * zz * zz;
}

bool hit(Point a, Point b, Point m, long double h, long double r) {
    long double dz, l, u, dx, dy, xx, yy, cc, aa, bb, t, val;
    if (h <= 0) return false;
    if (a.z <= 0 || b.z <= 0) return true;
    dz = b.z - a.z;
    l = 0;
    u = 1;
    if (dz > 0) {
        u = min((long double)1, (h - a.z) / dz);
    } else if (dz < 0) {
        l = max((long double)0, (h - a.z) / dz);
    } else if (a.z > h) {
        return false;
    }
    if (l > u) return false;
    dx = b.x - a.x;
    dy = b.y - a.y;
    xx = a.x - m.x;
    yy = a.y - m.y;
    cc = r / h;
    aa = dx * dx + dy * dy - cc * cc * dz * dz;
    bb = 2 * (xx * dx + yy * dy) + 2 * cc * cc * (h - a.z) * dz;
    val = min(calc(a, b, m, h, r, l), calc(a, b, m, h, r, u));
    if (aa > 0) {
        t = -bb / (2 * aa);
        if (t >= l && t <= u) val = min(val, calc(a, b, m, h, r, t));
    }
    return val <= eps;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int k;
    while (cin >> k && k != -1) {
        vector<Point> top(k);
        vector<long double> hei(k), rad(k);
        int i;
        for (i = 0; i < k; i++) cin >> top[i].x >> top[i].y >> hei[i] >> rad[i];
        Point a, b;
        bool ok = true;
        cin >> a.x >> a.y >> a.z;
        cin >> b.x >> b.y >> b.z;
        if (a.z <= 0 || b.z <= 0) ok = false;
        for (i = 0; i < k && ok; i++)
            if (hit(a, b, top[i], hei[i], rad[i])) ok = false;
        cout << (ok ? "Yes" : "No") << '\n';
    }
    return 0;
}
