#include <bits/stdc++.h>

using namespace std;

struct point {
    double x, y;
    point (double x = 0, double y = 0): x(x), y(y) {}
    point operator-(point &p) { return point(x - p.x, y - p.y); }
};

double cross(const point &a, const point &b)
{
    return a.x * b.y - a.y * b.x;
}

typedef vector<point> polygon;

point getCentroid1(polygon &pg)
{
    double areaOfPolygon = 0, areaOfTriangle = 0, px = 0, py = 0;

    for (int i = 2; i < pg.size(); i++)
    {
        areaOfTriangle = cross(pg[i - 1] - pg[0], pg[i] - pg[0]);
        areaOfPolygon += areaOfTriangle;
        px += areaOfTriangle * (pg[0].x + pg[i - 1].x + pg[i].x);
        py += areaOfTriangle * (pg[0].y + pg[i - 1].y + pg[i].y);
    }

    return point(px / (3.0 * areaOfPolygon), py / (3.0 * areaOfPolygon));
}

point getCentroid2(polygon &pg)
{
    double areaOfPolygon = 0, areaOfTriangle = 0, px = 0, py = 0;

    int n = pg.size();
    for (int i = 0; i < n; i++)
    {
        areaOfTriangle = cross(pg[i], pg[(i + 1) % n]);
        areaOfPolygon += areaOfTriangle;
        px += areaOfTriangle * (pg[i].x + pg[(i + 1) % n].x);
        py += areaOfTriangle * (pg[i].y + pg[(i + 1) % n].y);
    }

    return point(px / (3.0 * areaOfPolygon), py / (3.0 * areaOfPolygon));
}
