#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-10;

struct Point {
    double x, y;
};

struct Point3 {
    double x, y, z;
};

struct Poly {
    Point p[20];
    int n;
};

struct Height {
    double a, b, c;
};

double cross(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

Point mixPoint(Point a, Point b, double t) {
    Point c;
    c.x = a.x + (b.x - a.x) * t;
    c.y = a.y + (b.y - a.y) * t;
    return c;
}

double polyArea(const Poly &p) {
    double sum = 0;
    int i;
    for (i = 0; i < p.n; i++)
        sum += p.p[i].x * p.p[(i + 1) % p.n].y - p.p[i].y * p.p[(i + 1) % p.n].x;
    return fabs(sum) * 0.5;
}

double projArea(const Point3 p[]) {
    double x1 = p[1].x - p[0].x, y1 = p[1].y - p[0].y;
    double x2 = p[2].x - p[0].x, y2 = p[2].y - p[0].y;
    return fabs(x1 * y2 - y1 * x2) * 0.5;
}

Poly makePoly(const Point3 p[]) {
    Poly q;
    int i;
    q.n = 3;
    for (i = 0; i < 3; i++) {
        q.p[i].x = p[i].x;
        q.p[i].y = p[i].y;
    }
    return q;
}

Poly clipEdge(Poly p, Point a, Point b, double sign) {
    Poly q;
    int i;
    q.n = 0;
    for (i = 0; i < p.n; i++) {
        Point u = p.p[i], v = p.p[(i + 1) % p.n];
        double fu = cross(a, b, u) * sign;
        double fv = cross(a, b, v) * sign;
        bool inU = fu >= -eps, inV = fv >= -eps;
        if (inU) q.p[q.n++] = u;
        if (inU != inV) {
            double t = fu / (fu - fv);
            q.p[q.n++] = mixPoint(u, v, t);
        }
    }
    return q;
}

Poly clipLine(Poly p, double a, double b, double c, double sign) {
    Poly q;
    int i;
    q.n = 0;
    for (i = 0; i < p.n; i++) {
        Point u = p.p[i], v = p.p[(i + 1) % p.n];
        double fu = (a * u.x + b * u.y + c) * sign;
        double fv = (a * v.x + b * v.y + c) * sign;
        bool inU = fu >= -eps, inV = fv >= -eps;
        if (inU) q.p[q.n++] = u;
        if (inU != inV) {
            double t = fu / (fu - fv);
            q.p[q.n++] = mixPoint(u, v, t);
        }
    }
    return q;
}

Poly getIntersection(Poly a, Poly b) {
    Poly q = a;
    double dir = cross(b.p[0], b.p[1], b.p[2]);
    double sign = dir >= 0 ? 1.0 : -1.0;
    int i;
    for (i = 0; i < 3; i++)
        q = clipEdge(q, b.p[i], b.p[(i + 1) % 3], sign);
    return q;
}

Height getHeight(const Point3 p[]) {
    double x1 = p[1].x - p[0].x, y1 = p[1].y - p[0].y, z1 = p[1].z - p[0].z;
    double x2 = p[2].x - p[0].x, y2 = p[2].y - p[0].y, z2 = p[2].z - p[0].z;
    double nx = y1 * z2 - z1 * y2;
    double ny = z1 * x2 - x1 * z2;
    double nz = x1 * y2 - y1 * x2;
    Height h;
    h.a = -nx / nz;
    h.b = -ny / nz;
    h.c = (nx * p[0].x + ny * p[0].y + nz * p[0].z) / nz;
    return h;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(4);
    int t;
    cin >> t;
    while (t--) {
        Point3 red[3], blue[3];
        int i;
        for (i = 0; i < 3; i++)
            cin >> red[i].x >> red[i].y >> red[i].z;
        for (i = 0; i < 3; i++)
            cin >> blue[i].x >> blue[i].y >> blue[i].z;
        double redArea = projArea(red), blueArea = projArea(blue);
        if (redArea < eps && blueArea < eps) {
            cout << "0.0000 0.0000\n";
            continue;
        }
        if (redArea < eps) {
            cout << "0.0000 " << blueArea << "\n";
            continue;
        }
        if (blueArea < eps) {
            cout << redArea << " 0.0000\n";
            continue;
        }
        Poly redPoly = makePoly(red), bluePoly = makePoly(blue);
        Poly inter = getIntersection(redPoly, bluePoly);
        Height redHeight = getHeight(red), blueHeight = getHeight(blue), diff;
        diff.a = redHeight.a - blueHeight.a;
        diff.b = redHeight.b - blueHeight.b;
        diff.c = redHeight.c - blueHeight.c;
        Poly redBlocked = clipLine(inter, diff.a, diff.b, diff.c, -1.0);
        Poly blueBlocked = clipLine(inter, diff.a, diff.b, diff.c, 1.0);
        double redAns = max(0.0, redArea - polyArea(redBlocked));
        double blueAns = max(0.0, blueArea - polyArea(blueBlocked));
        cout << redAns << " " << blueAns << "\n";
    }
    return 0;
}
