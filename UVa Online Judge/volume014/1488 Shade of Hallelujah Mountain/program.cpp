#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-9;

struct Point3 {
    double x, y, z;
    Point3() {}
    Point3(double x, double y, double z) : x(x), y(y), z(z) {}
    Point3 operator + (const Point3 &p) const {
        return Point3(x + p.x, y + p.y, z + p.z);
    }
    Point3 operator - (const Point3 &p) const {
        return Point3(x - p.x, y - p.y, z - p.z);
    }
    Point3 operator * (double k) const {
        return Point3(x * k, y * k, z * k);
    }
};

struct Point2 {
    double x, y;
    bool operator < (const Point2 &p) const {
        if (fabs(x - p.x) > eps) return x < p.x;
        return y < p.y;
    }
};

double dot(const Point3 &a, const Point3 &b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Point3 cross(const Point3 &a, const Point3 &b) {
    return Point3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

double length(const Point3 &p) {
    return sqrt(dot(p, p));
}

Point3 normalize(const Point3 &p) {
    double len = length(p);
    return p * (1.0 / len);
}

double cross(const Point2 &a, const Point2 &b, const Point2 &c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

vector<Point2> getHull(vector<Point2> pts) {
    int n = pts.size(), m = 0;
    vector<Point2> hull;
    sort(pts.begin(), pts.end());
    for (int i = 0; i < n; i++) {
        while (m >= 2 && cross(hull[m - 2], hull[m - 1], pts[i]) <= eps) {
            hull.pop_back();
            m--;
        }
        hull.push_back(pts[i]);
        m++;
    }
    int lower = m;
    for (int i = n - 2; i >= 0; i--) {
        while (m > lower && cross(hull[m - 2], hull[m - 1], pts[i]) <= eps) {
            hull.pop_back();
            m--;
        }
        hull.push_back(pts[i]);
        m++;
    }
    if (hull.size() > 1) hull.pop_back();
    return hull;
}

double getArea(const vector<Point2> &poly) {
    int n = poly.size();
    double sum = 0;
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        sum += poly[i].x * poly[j].y - poly[i].y * poly[j].x;
    }
    return fabs(sum) * 0.5;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    double a, b, c, d;
    while (cin >> a >> b >> c >> d) {
        if (fabs(a) < eps && fabs(b) < eps && fabs(c) < eps && fabs(d) < eps) break;
        int n;
        cin >> n;
        vector<Point3> ver(n);
        for (int i = 0; i < n; i++) cin >> ver[i].x >> ver[i].y >> ver[i].z;
        Point3 light;
        cin >> light.x >> light.y >> light.z;
        if (n == 0) {
            cout << "0.00\n";
            continue;
        }
        Point3 rawN(a, b, c), base = rawN * (d / dot(rawN, rawN));
        Point3 norm = normalize(rawN);
        double h = dot(light - base, norm);
        if (h < 0) {
            norm = norm * -1.0;
            h = -h;
        }
        Point3 ref;
        if (fabs(norm.x) < 0.8) ref = Point3(1, 0, 0);
        else ref = Point3(0, 1, 0);
        Point3 axisX = normalize(cross(ref, norm)), axisY = cross(norm, axisX);
        vector<double> vx(n), vy(n), vz(n);
        double minZ = 1e100, maxZ = -1e100, sx, sy;
        Point3 ls = light - base;
        sx = dot(ls, axisX);
        sy = dot(ls, axisY);
        for (int i = 0; i < n; i++) {
            Point3 cur = ver[i] - base;
            vx[i] = dot(cur, axisX);
            vy[i] = dot(cur, axisY);
            vz[i] = dot(cur, norm);
            minZ = min(minZ, vz[i]);
            maxZ = max(maxZ, vz[i]);
        }
        if (minZ >= h - eps) {
            cout << "0.00\n";
            continue;
        }
        if (maxZ >= h - eps) {
            cout << "Infi\n";
            continue;
        }
        vector<Point2> pts;
        for (int i = 0; i < n; i++) {
            double k = h / (h - vz[i]);
            pts.push_back({sx + (vx[i] - sx) * k, sy + (vy[i] - sy) * k});
        }
        vector<Point2> hull = getHull(pts);
        double area = getArea(hull);
        if (area < 0.0005) area = 0;
        cout << fixed << setprecision(2) << area << '\n';
    }
    return 0;
}
