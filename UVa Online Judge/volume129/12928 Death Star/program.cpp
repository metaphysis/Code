#include <bits/stdc++.h>
using namespace std;

const long double eps = 1e-12;

struct Point {
    long double x, y;
};

Point p[5], tri[5][3];

long double cross(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

Point getIntersection(Point a, Point b, Point c, Point d) {
    Point u, v, ans;
    long double den, t;
    u.x = b.x - a.x;
    u.y = b.y - a.y;
    v.x = d.x - c.x;
    v.y = d.y - c.y;
    den = u.x * v.y - u.y * v.x;
    t = ((c.x - a.x) * v.y - (c.y - a.y) * v.x) / den;
    ans.x = a.x + t * u.x;
    ans.y = a.y + t * u.y;
    return ans;
}

bool isConvex() {
    int i, sign;
    long double value;
    sign = 0;
    for (i = 0; i < 5; i++) {
        value = cross(p[i], p[(i + 1) % 5], p[(i + 2) % 5]);
        if (fabsl(value) <= eps)
            return false;
        if (sign == 0)
            sign = value > 0 ? 1 : -1;
        else if ((value > 0 ? 1 : -1) != sign)
            return false;
    }
    return true;
}

void buildTriangles() {
    int i;
    Point q1, q2;
    for (i = 0; i < 5; i++) {
        q1 = getIntersection(p[i], p[(i + 2) % 5], p[(i + 4) % 5], p[(i + 1) % 5]);
        q2 = getIntersection(p[i], p[(i + 3) % 5], p[(i + 4) % 5], p[(i + 1) % 5]);
        tri[i][0] = p[i];
        tri[i][1] = q1;
        tri[i][2] = q2;
    }
}

bool inTriangle(Point a, Point b, Point c, Point q) {
    long double v1, v2, v3;
    bool hasPositive, hasNegative;
    v1 = cross(a, b, q);
    v2 = cross(b, c, q);
    v3 = cross(c, a, q);
    hasPositive = v1 > eps || v2 > eps || v3 > eps;
    hasNegative = v1 < -eps || v2 < -eps || v3 < -eps;
    return !(hasPositive && hasNegative);
}

bool inWeakPoint(Point q) {
    int i;
    for (i = 0; i < 5; i++)
        if (inTriangle(tri[i][0], tri[i][1], tri[i][2], q))
            return true;
    return false;
}

int main() {
    int n, i;
    Point q;
    while (cin >> p[0].x >> p[0].y) {
        for (i = 1; i < 5; i++)
            cin >> p[i].x >> p[i].y;
        cin >> n;
        if (!isConvex()) {
            cout << "Impossible\n";
            for (i = 0; i < n; i++)
                cin >> q.x >> q.y;
            continue;
        }
        buildTriangles();
        for (i = 0; i < n; i++) {
            cin >> q.x >> q.y;
            cout << (inWeakPoint(q) ? "Yes" : "No") << '\n';
        }
    }
    return 0;
}
