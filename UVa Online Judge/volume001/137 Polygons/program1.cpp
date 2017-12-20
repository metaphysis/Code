// Polygons
// UVa ID: 137
// Verdict: Accepted
// Submission Date: 2017-12-20
// UVa Run Time: 0.000s
//
// 版权所有（C）2016 - 2017，邱秋。metaphysis # yeah dot net

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

const int MAXV = 1100;
const double EPSILON = 1E-7;

struct point {
    double x, y;
    point (double x = 0, double y = 0): x(x), y(y) {}
    point operator + (point p) { return point(x + p.x, y + p.y); };
    point operator - (point p) { return point(x - p.x, y - p.y); };
    point operator * (double k) { return point(x * k, y * k); };
    point operator / (double k) { return point(x / k, y / k); };
};

typedef vector<point> polygon;

double cross(point a, point b)
{
    return a.x * b.y - a.y * b.x;
}

struct line
{
    point a, b;
    double angle;
};

double cp(point a, point b, point c)
{
    return cross(b - a, c - a);
}

bool cw(point a, point b, point c)
{
    return cp(a, b, c) < -EPSILON;
}

bool cmpLine(line p, line q)
{
    if (fabs(p.angle - q.angle) <= EPSILON)
        return cp(q.a, q.b, p.a) < EPSILON;
    return p.angle < q.angle;
}

bool cmpAngle(line p, line q)
{
    return fabs(p.angle - q.angle) <= EPSILON;
}

bool parallel(line p, line q)
{
    return fabs((p.a.x - p.b.x) * (q.a.y - q.b.y) -
        (q.a.x - q.b.x) * (p.a.y - p.b.y)) <= EPSILON;
}

point getIntersection(line p, line q)
{
    point p1 = p.a;
    double scale =
        ((p.a.x - q.a.x) * (q.a.y - q.b.y) - (p.a.y - q.a.y) * (q.a.x - q.b.x)) /
        ((p.a.x - p.b.x) * (q.a.y - q.b.y) - (p.a.y - p.b.y) * (q.a.x - q.b.x));
    p1.x += (p.b.x - p.a.x) * scale;
    p1.y += (p.b.y - p.a.y) * scale;
    return p1;
}

line pointToLine(point a, point b)
{
    line lr;
    lr.a = a, lr.b = b, lr.angle = atan2(b.y - a.y, b.x - a.x);
    return lr;
}

double area(polygon &pg)
{
    if (pg.size() < 3) return 0.0;
    double A = 0.0;
    int n = pg.size();
    for (int i = 0, j = (i + 1) % n; i < n; i++, j = (i + 1) % n)
        A += (pg[i].x * pg[j].y - pg[j].x * pg[i].y);
    return fabs(A / 2.0);
}

polygon halfPlaneIntersection(line *sides, int nLine)
{
    polygon pg;
    line deq[MAXV];

    sort(sides, sides + nLine, cmpLine);
    nLine = unique(sides, sides + nLine, cmpAngle) - sides;

    int btm = 0, top = 1;
    deq[0] = sides[0], deq[1] = sides[1];

    for (int i = 2; i < nLine; i++)
    {
        if (parallel(deq[top], deq[top - 1]) || parallel(deq[btm], deq[btm + 1]))
            return pg;

        while (btm < top &&
            cw(sides[i].a, sides[i].b, getIntersection(deq[top], deq[top - 1])))
            top--;
        while (btm < top &&
            cw(sides[i].a, sides[i].b, getIntersection(deq[btm], deq[btm + 1])))
            btm++;

        deq[++top] = sides[i];
    }

    while (btm < top &&
        cw(deq[btm].a, deq[btm].b, getIntersection(deq[top], deq[top - 1])))
        top--;
    while (btm < top &&
        cw(deq[top].a, deq[top].b, getIntersection(deq[btm], deq[btm + 1])))
        btm++;

    if (top <= (btm + 1)) return pg;

    for (int i = btm; i < top; i++)
        pg.push_back(getIntersection(deq[i], deq[i + 1]));
    if (btm < (top + 1))
        pg.push_back(getIntersection(deq[btm], deq[top]));

    return pg;
}

void exclusiveOr(polygon &a, polygon &b)
{
    double areaA = area(a), areaB = area(b);

    line sides[MAXV];
    int nLine = 0;

    
    for (int i = 0; i < a.size() - 1; i++)
        sides[nLine++] = pointToLine(a[i + 1], a[i]);
    sides[nLine++] = pointToLine(a[0], a.back());

    for (int i = 0; i < b.size() - 1; i++)
        sides[nLine++] = pointToLine(b[i + 1], b[i]);
    sides[nLine++] = pointToLine(b[0], b.back());

    polygon c = halfPlaneIntersection(sides, nLine);

    double area1 = area(c);
    double area2 = areaA + areaB - 2 * area1;
    cout << fixed << setw(8) << setfill(' ') << setprecision(2) << (area2 + 1e-9);
}

int main(int argc, char *argv[])
{
    int n;
    double xi, yi;

    while (cin >> n, n > 0)
    {
        polygon a, b;

        for (int i = 1; i <= n; i++)
        {
            cin >> xi >> yi;
            a.push_back(point(xi, yi));
        }

        cin >> n;
        for (int i = 1; i <= n; i++)
        {
            cin >> xi >> yi;
            b.push_back(point(xi, yi));
        }

        exclusiveOr(a, b);
    }

    cout << '\n';

    return 0;
}
