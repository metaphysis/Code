#include <bits/stdc++.h>

using namespace std;

const double EPSILON = 1e-7;

struct point
{
    double x, y;
    point (double x = 0, double y = 0): x(x), y(y) {}
};

struct line
{
    double a, b, c;
    line (double a = 0, double b = 0, double c = 0): a(a), b(b), c(c) {}
};

line getLine(double x1, double y1, double x2, double y2)
{
    return line(y2 - y1, x1 - x2, y1 * (x2 - x1) - x1 * (y2 - y1));
}

line getLine(point p, point q)
{
    return getLine(p.x, p.y, q.x, q.y);
}

bool parallel(line p, line q)
{
    return fabs(p.a * q.b - q.a * p.b) < EPSILON;
}

bool same(line p, line q)
{
    return parallel(p, q) && fabs(p.c - q.c) < EPSILON;
}

bool getIntersection(line p, line q, point &pi)
{
    if (fabs(p.a * q.b - q.a * p.b) < EPSILON) return false;  
    pi.x = (q.c * p.b - p.c * q.b) / (p.a * q.b - q.a * p.b);  
    pi.y = (q.c * p.a - p.c * q.a) / (p.b * q.a - q.b * p.a);  
    return true;
}
