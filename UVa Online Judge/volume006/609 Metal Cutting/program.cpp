// Metal Cutting
// UVa ID: 609
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const double EPSILON = 1e-7;

struct point
{
    double x, y;
    point (double x = 0, double y = 0): x(x), y(y) {}
};

bool pointInBox(point a, point b, point p)
{
    double minx = min(a.x, b.x), maxx = max(a.x, b.x);
    double miny = min(a.y, b.y), maxy = max(a.y, b.y);
    return p.x >= minx && p.x <= maxx && p.y >= miny && p.y <= maxy;
}

struct segment
{
    point p1, p2;
    bool contains(const point &p) { return pointInBox(p1, p2, p); }
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

point getIntersection(line p, line q)
{
    point pi;
    pi.x = (p.b * q.c - p.c * q.b) / (p.a * q.b - p.b * q.a);
    pi.y = (p.a * q.c - p.c * q.a) / (p.b * q.a - p.a * q.b);
    return pi; 
}

double cp(point a, point b, point c)
{
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

bool isIntersected(segment s1, segment s2)
{
    line p = getLine(s1.p1, s1.p2), q = getLine(s2.p1, s2.p2);

    if (fabs(p.a * q.b - q.a * p.b) < EPSILON)
    {
        if (fabs(cp(s1.p1, s1.p2, s2.p1)) < EPSILON)
            return s1.contains(s2.p1) || s1.contains(s2.p2);
        return false;
    }

	point pi = getIntersection(p, q);
	return s1.contains(pi) && s2.contains(pi);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
    }

    return 0;
}
