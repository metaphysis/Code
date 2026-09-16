#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-9;

struct Point {
    double x, y;
};

double getVal(const Point &p, int type, double val) {
    if (type == 0) return p.x - val;
    if (type == 1) return val - p.x;
    if (type == 2) return p.y - val;
    return val - p.y;
}

vector<Point> clipPoly(const vector<Point> &poly, int type, double val) {
    vector<Point> res;
    int n = poly.size();
    for (int i = 0; i < n; i++) {
        Point a = poly[i], b = poly[(i + 1) % n];
        double fa = getVal(a, type, val), fb = getVal(b, type, val);
        bool ina = fa >= -eps, inb = fb >= -eps;
        if (ina) res.push_back(a);
        if (ina != inb) {
            double t = fa / (fa - fb);
            Point p;
            p.x = a.x + (b.x - a.x) * t;
            p.y = a.y + (b.y - a.y) * t;
            res.push_back(p);
        }
    }
    return res;
}

double getArea(const vector<Point> &poly) {
    double sum = 0;
    int n = poly.size();
    for (int i = 0; i < n; i++)
        sum += poly[i].x * poly[(i + 1) % n].y - poly[i].y * poly[(i + 1) % n].x;
    return fabs(sum) / 2.0;
}

double getInterArea(const vector<Point> &tri, int x, int y) {
    vector<Point> poly = tri;
    poly = clipPoly(poly, 0, x);
    poly = clipPoly(poly, 1, x + 1);
    poly = clipPoly(poly, 2, y);
    poly = clipPoly(poly, 3, y + 1);
    if (poly.size() < 3) return 0;
    return getArea(poly);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    for (int cs = 1; cs <= t; cs++) {
        vector<Point> tri(3);
        int minX = 101, minY = 101, maxX = 0, maxY = 0, ans = 0;
        for (int i = 0; i < 3; i++) {
            cin >> tri[i].x >> tri[i].y;
            minX = min(minX, (int)tri[i].x);
            maxX = max(maxX, (int)tri[i].x);
            minY = min(minY, (int)tri[i].y);
            maxY = max(maxY, (int)tri[i].y);
        }
        for (int x = minX; x < maxX; x++) {
            for (int y = minY; y < maxY; y++) {
                double area = getInterArea(tri, x, y);
                if (area + eps >= 0.5) ans++;
            }
        }
        cout << "Case " << cs << ": " << ans << '\n';
    }
    return 0;
}
