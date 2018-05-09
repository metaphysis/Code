#include <bits/stdc++.h>

using namespace std;

const double EPSILON = 1e-9;

struct point
{
    double x, y;
    point(double x = 0, double y = 0): x(x), y(y) {}
    point operator+(point i) { return point(x + i.x, y + i.y); };
    point operator-(point i) { return point(x - i.x, y - i.y); };
    point operator*(double k) { return point(x * k, y * k); };
    point operator/(double k) { return point(x / k, y / k); };
    bool operator<(const point &p) const
	{
	    if (fabs(y - p.y) > EPSILON) return y < p.y;
	    return x < p.x;
	}
	bool operator==(const point &p) const
	{
	    return fabs(x - p.x) <= EPSILON && fabs(y - p.y) <= EPSILON;
	}
    double distTo(point i) { return sqrt(pow(x - i.x, 2) + pow(y - i.y, 2)); }
} pr;

typedef vector<point> polygon;

double cross(point a, point b) { return a.x * b.y - a.y * b.x; }
double dot(point a, point b) { return a.x * b.x + a.y * b.y; }
double norm(point a) { return dot(a, a); }
double abs(point a) { return sqrt(norm(a)); }
double cp(point a, point b, point c) { return cross(b - a, c - a);}

double rotatingCalipers1(polygon pg)
{
    double dist = 0.0;
    pg.push_back(pg.front());
    for (int i = 0, j = 1, n = pg.size() - 1; i < n; i++)
    {
        while (cross(pg[i + 1] - pg[i], pg[j + 1] - pg[j]) > EPSILON)
            j = (j + 1) % n;
        dist = max(dist, max(pg[i].distTo(pg[j]), pg[i + 1].distTo(pg[j + 1])));
    }
    return dist;
}

pair<double, double> rotatingCalipers(polygon pg)
{
    double minArea = 1e20, minLength = 1e20;
    pg.push_back(pg.front());
    for (int i = 0, j = 1, k, m, n = pg.size() - 1; i < n; i++)
    {
        while (dot(pg[i + 1] - pg[i], pg[j + 1] - pg[j]) > EPSILON)
            j = (j + 1) % n;
        if (!i) k = j;
        while (cross(pg[i + 1] - pg[i], pg[k + 1] - pg[k]) > EPSILON)
            k = (k + 1) % n;
        if (!i)  m = k;
        while (dot(pg[i + 1] - pg[i], pg[m + 1] - pg[m]) < -EPSILON)
            m = (m + 1) % n;
        double d = abs(pg[i + 1] - pg[i]);
        double height = fabs(cp(pg[i], pg[i + 1], pg[k])) / d;
        double width = dot(pg[i + 1] - pg[i], pg[j] - pg[m]) / d;
        minArea = min(minArea, width * height);
        minLength = min(minLength, (width + height) * 2);
    }
    return make_pair(minArea, minLength);
}
