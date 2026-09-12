#include <bits/stdc++.h>
using namespace std;

struct Point {
    long double x, y;
};

struct Line {
    long double x1, y1, dx, dy;
};

long double cross(const Line &line, const Point &p) {
    return line.dx * (p.y - line.y1) - line.dy * (p.x - line.x1);
}

vector<Point> clip(vector<Point> poly, const Line &line, int sign) {
    vector<Point> res;
    int n = poly.size();
    for (int i = 0; i < n; i++) {
        Point a = poly[i], b = poly[(i + 1) % n];
        long double va = cross(line, a) * sign, vb = cross(line, b) * sign;
        bool ina = va >= -1e-15L, inb = vb >= -1e-15L;
        if (ina) res.push_back(a);
        if (ina != inb) {
            long double t = va / (va - vb);
            res.push_back({a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t});
        }
    }
    return res;
}

long double getArea(const vector<Point> &poly) {
    long double sum = 0;
    int n = poly.size();
    for (int i = 0; i < n; i++)
        sum += poly[i].x * poly[(i + 1) % n].y - poly[i].y * poly[(i + 1) % n].x;
    return fabsl(sum) / 2;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int l, c, k;
    while (cin >> l >> c >> k, l || c || k) {
        vector<Point> chip(c);
        for (Point &p : chip) cin >> p.x >> p.y;
        vector<Line> line(k);
        for (Line &v : line) {
            long double x2, y2;
            cin >> v.x1 >> v.y1 >> x2 >> y2;
            v.dx = x2 - v.x1;
            v.dy = y2 - v.y1;
        }
        map<unsigned long long, int> cnt;
        for (const Point &p : chip) {
            unsigned long long mask = 0;
            bool destroyed = false;
            for (int i = 0; i < k; i++) {
                long double v = cross(line[i], p);
                if (fabsl(v) < 1e-15L) {
                    destroyed = true;
                    break;
                }
                if (v > 0) mask |= 1ULL << i;
            }
            if (!destroyed) cnt[mask]++;
        }
        long double ans = 0;
        for (const auto &item : cnt) {
            vector<Point> poly = {{0, 0}, {(long double)l, 0}, {(long double)l, (long double)l}, {0, (long double)l}};
            for (int i = 0; i < k && !poly.empty(); i++) {
                int sign = ((item.first >> i) & 1ULL) ? 1 : -1;
                poly = clip(poly, line[i], sign);
            }
            long double area = getArea(poly);
            if (area > 1e-15L) ans = max(ans, item.second / area);
        }
        long long out = (long long)floorl(ans * 1000 + 0.5L + 1e-12L);
        cout << out / 1000 << '.' << setw(3) << setfill('0') << out % 1000 << setfill(' ') << '\n';
    }
    return 0;
}
