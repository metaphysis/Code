// Where Can You Hide?
// UVa ID: 10011
// Verdict: Accepted
// Submission Date: 2019-02-03
// UVa Run Time: 0.050s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const double EPSILON = 1E-7;

struct point {
    double x, y;
    point (double x = 0, double y = 0): x(x), y(y) {}
    point operator + (point p) { return point(x + p.x, y + p.y); };
    point operator - (point p) { return point(x - p.x, y - p.y); };
    point operator * (double k) { return point(x * k, y * k); };
    point operator / (double k) { return point(x / k, y / k); };
};

struct line
{
    double a, b, c;
    line (double a = 0, double b = 0, double c = 0): a(a), b(b), c(c) {}
};

struct circle { point c; double r; };

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

double cp(point a, point b, point c)
{
    return cross(b - a, c - a);
}

bool cw(point a, point b, point c)
{
    return cp(a, b, c) < -EPSILON;
}

bool ccw(point a, point b, point c)
{
    return cp(a, b, c) > EPSILON;
}

bool collinear(point a, point b, point c)
{
    return fabs(cp(a, b, c)) <= EPSILON;
}

line getLine(double x1, double y1, double x2, double y2)
{
    return line(y2 - y1, x1 - x2, y1 * (x2 - x1) - x1 * (y2 - y1));
}

line getLine(point p, point q)
{
    return getLine(p.x, p.y, q.x, q.y);
}

double getDistPL(point p, line l)
{
	return fabs(l.a * p.x + l.b * p.y + l.c) / sqrt(l.a * l.a + l.b * l.b);
}

pair<point, point> getIntersection(point p, double r)
{
    double D = abs(p);
    double b = sqrt(norm(p) - r * r);
    double sinA = r / D, cosA = b / D;
    double k = b / D;
    point p1 = point(p.x * cosA + p.y * sinA, -p.x * sinA + p.y * cosA);
    point p2 = point(p.x * cosA - p.y * sinA, p.x * sinA + p.y * cosA);
    return make_pair(p1 * k, p2 * k);
}

bool unsafe(point H, point p1, point p2)
{
    point O = point(0, 0);
    if (cw(O, p1, H)) return true;
    if (collinear(O, p1, H)) return true;
    if (ccw(O, p2, H)) return true;
    if (collinear(O, p2, H)) return true;
    if (ccw(p1, p2, H)) return true;
    return false;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    circle T;
    point H;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> T.c.x >> T.c.y >> T.r >> H.x >> H.y;
        point O = point(0, 0);
        if (fabs(abs(T.c) - T.r) <= EPSILON)
        {
            point NP = point(-T.c.y, T.c.x);
            line L = getLine(O, NP);
            if (ccw(O, NP, H) || collinear(O, NP, H))
                cout << "0.000\n";
            else
            {
                double d1 = getDistPL(H, L);
                double d2 = abs(H - T.c) - T.r;
                cout << fixed << setprecision(3) << min(d1, d2) << '\n';
            }
        }
        else
        {
            pair<point, point> intersections = getIntersection(T.c, T.r);
            point p1 = intersections.first, p2 = intersections.second;
            if (unsafe(H, p1, p2))
                cout << "0.000\n";
            else
            {
                double d1 = getDistPL(H, getLine(O, p1));
                double d2 = getDistPL(H, getLine(O, p2));
                double d3 = abs(H - T.c) - T.r;
                cout << fixed << setprecision(3) << min(d3, min(d1, d2)) << '\n';
            }
        }
    }

    return 0;
}
