// Tri Tri
// UVa ID: 11122
// Verdict: Accepted
// Submission Date: 2018-12-16
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

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

double norm(point a)
{
    return a.x * a.x + a.y * a.y;
}

double abs(point a)
{
    return sqrt(norm(a));
}

double dot(point a, point b)
{
    return a.x * b.x + a.y * b.y;
}

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
    if (fabs(p.angle - q.angle) <= EPSILON) return cw(p.a, p.b, q.a);
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

line shiftLine(point a, point b, double d)
{
    double D = abs(a - b);
    point offset(a.y - b.y, b.x - a.x);
    offset = offset * d / D;
    return pointToLine(a + offset, b + offset);
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

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    point p1, p2, p3;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        line sides[6];
        cin >> p1.x >> p1.y >> p2.x >> p2.y >> p3.x >> p3.y;
        if (cw(p1, p2, p3))
        {
            sides[0] = pointToLine(p1, p3);
            sides[1] = pointToLine(p3, p2);
            sides[2] = pointToLine(p2, p1);
        }
        else
        {
            sides[0] = pointToLine(p1, p2);
            sides[1] = pointToLine(p2, p3);
            sides[2] = pointToLine(p3, p1);
        }
        cin >> p1.x >> p1.y >> p2.x >> p2.y >> p3.x >> p3.y;
        if (cw(p1, p2, p3))
        {
            sides[3] = pointToLine(p1, p3);
            sides[4] = pointToLine(p3, p2);
            sides[5] = pointToLine(p2, p1);
        }
        else
        {
            sides[3] = pointToLine(p1, p2);
            sides[4] = pointToLine(p2, p3);
            sides[5] = pointToLine(p3, p1);
        }
        polygon pg = halfPlaneIntersection(sides, 6);
        double a = area(pg);
        cout << "pair " << cs << ": " << (a > EPSILON ? "yes" : "no") << '\n';
    }

    return 0;
}
