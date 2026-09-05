#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-10;
const double pi = acos(-1.0);

struct Point {
    double x, y;
};

double cross(Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

double getArea(const vector<Point>& poly) {
    int n = poly.size();
    double sum = 0;
    for (int i = 0; i < n; i++)
        sum += cross(poly[i], poly[(i + 1) % n]);
    return fabs(sum) * 0.5;
}

double getVal(Point p, double nx, double ny) {
    return p.x * nx + p.y * ny;
}

vector<Point> cutPoly(const vector<Point>& poly, double nx, double ny, double c) {
    int n = poly.size();
    vector<Point> res;
    for (int i = 0; i < n; i++) {
        Point a = poly[i], b = poly[(i + 1) % n];
        double va = getVal(a, nx, ny) - c, vb = getVal(b, nx, ny) - c;
        bool ina = va <= eps, inb = vb <= eps;
        if (ina) res.push_back(a);
        if (ina != inb) {
            double t = va / (va - vb);
            res.push_back({a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t});
        }
    }
    return res;
}

double getMedian(const vector<Point>& poly, double nx, double ny) {
    double low = 1e100, high = -1e100, half = getArea(poly) * 0.5;
    for (Point p : poly) {
        double v = getVal(p, nx, ny);
        low = min(low, v);
        high = max(high, v);
    }
    for (int i = 0; i < 70; i++) {
        double mid = (low + high) * 0.5;
        vector<Point> part = cutPoly(poly, nx, ny, mid);
        if (getArea(part) < half) low = mid;
        else high = mid;
    }
    return (low + high) * 0.5;
}

double getDiff(const vector<Point>& a, const vector<Point>& b, double ang) {
    double nx = cos(ang), ny = sin(ang);
    return getMedian(a, nx, ny) - getMedian(b, nx, ny);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    for (int tc = 1; tc <= t; tc++) {
        int n, m;
        cin >> n;
        vector<Point> a(n);
        for (int i = 0; i < n; i++)
            cin >> a[i].x >> a[i].y;
        cin >> m;
        vector<Point> b(m);
        for (int i = 0; i < m; i++)
            cin >> b[i].x >> b[i].y;
        double low = 0, high = pi, fl = getDiff(a, b, low);
        for (int i = 0; i < 70; i++) {
            double mid = (low + high) * 0.5;
            double fm = getDiff(a, b, mid);
            if (fl * fm <= 0) high = mid;
            else {
                low = mid;
                fl = fm;
            }
        }
        double ang = (low + high) * 0.5;
        double nx = cos(ang), ny = sin(ang);
        double c = getMedian(a, nx, ny);
        double k = -nx / ny, bb = c / ny;
        if (fabs(k) < eps) k = 0;
        if (fabs(bb) < eps) bb = 0;
        cout << fixed << setprecision(6);
        cout << "Case #" << tc << ": " << k << " " << bb << '\n';
    }
    return 0;
}
