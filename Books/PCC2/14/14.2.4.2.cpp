#include <bits/stdc++.h>

using namespace std;

const double EPSILON = 1e-6;

struct point {
    double x, y;
    point (double x = 0, double y = 0): x(x), y(y) {}
    point operator + (point p) { return point(x + p.x, y + p.y); };
    point operator - (point p) { return point(x - p.x, y - p.y); };
    point operator * (double k) { return point(x * k, y * k); };
    point operator / (double k) { return point(x / k, y / k); };
    bool operator==(point &p)
    {
        return fabs(x - p.x) < EPSILON && fabs(y - p.y) < EPSILON;
    }
};

double cross(point a, point b) { return a.x * b.y - a.y * b.x; }

struct line { point a, b; };

point getIntersection(line p, line q)
{
    if (p.a == q.a) return p.a;
    double k = cross(q.a - p.a, q.b - q.a) / cross(p.b - p.a, q.b - q.a);
    return p.a + (p.b - p.a) * k;
}

int main(int argc, char *argv[])
{
    return 0;
}
