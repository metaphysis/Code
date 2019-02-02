// Where Can You Hide?
// UVa ID: 10011
// Verdict: Wrong Answer
// Submission Date: 2019-02-02
// UVa Run Time: 0.060s
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
    point p1, p2;
    line (point p1 = point(0, 0), point p2 = point(0, 0)): p1(p1), p2(p2) {}
};

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

struct circle { point c; double r; };
double atan2(point p) { return atan2(p.y, p.x); }
point polar(double d, double t) { return point(d * cos(t), d * sin(t)); }

pair<point, point> getIntersection(point p, circle c1)
{
    double d = abs(c1.c - p);
    double a = asin(c1.r / d);
    double t = atan2(c1.c - p);
    double b = sqrt(d * d - c1.r * c1.r);
    return make_pair(p + polar(b, t + a), p + polar(b, t - a));
}

double getDistPL(point p, line l)
{
	return fabs(cross(l.p2 - l.p1, p - l.p1) / abs(l.p2 - l.p1));
}

bool unsafe(point home, point p1, point p2)
{
    point source = point(0, 0);
    if (cw(source, p2, home)) return true;
    if (collinear(source, p2, home)) return true;
    if (ccw(source, p1, home)) return true;
    if (collinear(source, p1, home)) return true;
    if (ccw(p2, p1, home)) return true;
    return false;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    circle tree;
    point home;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> tree.c.x >> tree.c.y >> tree.r >> home.x >> home.y;
        point source = point(0, 0);
        if (fabs(abs(source - tree.c) - tree.r) <= EPSILON)
        {
            double a = atan2(tree.c.y, tree.c.x);
            a -= acos(0);
            double d = abs(tree.c - source);
            point p = point(d * cos(a), d * sin(a));
            if (cw(source, p, home) || collinear(source, p, home))
                cout << "0.000\n";
            else
            {
                double d1 = abs(home - tree.c) - tree.r;
                double d2 = getDistPL(home, line(source, p));
                cout << fixed << setprecision(3) << min(d1, d2) << '\n';
            }
        }
        else
        {
            pair<point, point> intersections = getIntersection(point(0, 0), tree);
            point p1 = intersections.first, p2 = intersections.second;
            if (unsafe(home, p1, p2))
                cout << "0.000\n";
            else
            {
                double d1 = getDistPL(home, line(source, p1));
                double d2 = getDistPL(home, line(source, p2));
                double d3 = abs(home - tree.c) - tree.r;
                cout << fixed << setprecision(3) << min(d3, min(d1, d2)) << '\n';
            }
        }
    }

    return 0;
}
