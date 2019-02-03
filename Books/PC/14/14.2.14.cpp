#include <bits/stdc++.h>

using namespace std;

struct point {
    double x, y;
    point (double x = 0, double y = 0): x(x), y(y) {}
    point operator + (point p) { return point(x + p.x, y + p.y); };
    point operator - (point p) { return point(x - p.x, y - p.y); };
    point operator * (double k) { return point(x * k, y * k); };
    point operator / (double k) { return point(x / k, y / k); };
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

struct circle { point c; double r; };
double atan2(point p) { return atan2(p.y, p.x); }
point polar(double d, double t) { return point(d * cos(t), d * sin(t)); }

pair<point, point> getIntersection1(point p, circle cc)
{
    double D = abs(cc.c - p);
    double a = asin(cc.r / D);
    double t = atan2(cc.c - p);
    double b = sqrt(D * D - cc.r * cc.r);
    return make_pair(p + polar(b, t + a), p + polar(b, t - a));
}

pair<point, point> getIntersection2(point p, circle cc)
{
    point pv = cc.c - p;
    double D = abs(pv);
    double b = sqrt(norm(pv) - cc.r * cc.r);
    double sina = cc.r / D, cosa = b / D;
    double k = b / D;
    point p1 = point(pv.x * cosa - pv.y * sina, pv.x * sina + pv.y * cosa);
    point p2 = point(pv.x * cosa + pv.y * sina, -pv.x * sina + pv.y * cosa);
    return make_pair(p + p1 * k, p + p2 * k);
}

int main(int argc, char *argv[])
{
    point p;
    circle cc;
    
    while (cin >> p.x >> p.y)
    {
        cin >> cc.c.x >> cc.c.y >> cc.r;
        pair<point, point> pair1 = getIntersection1(p, cc);
        pair<point, point> pair2 = getIntersection2(p, cc);
        cout << pair1.first.x << ' ' << pair1.first.y << ' ' << pair1.second.x << ' ' << pair1.second.y << '\n';
        cout << pair2.first.x << ' ' << pair2.first.y << ' ' << pair2.second.x << ' ' << pair2.second.y << '\n';
    }

    return 0;
}
