#include <bits/stdc++.h>

using namespace std;

struct point {
    double x, y;

    point (double x = 0, double y = 0): x(x), y(y) {}

    point operator + (point p) { return point(x + p.x, y + p.y); };
    point operator - (point p) { return point(x - p.x, y - p.y); };
    point operator * (double k) { return point(x * k, y * k); };
    point operator / (double k) { return point(x / k, y / k); };
    
    double distTo(point p)
    {
        return sqrt(pow(x - p.x, 2) + pow(y - p.y, 2));
    }
};

typedef vector<point> polygon;

double cross(point a, point b)
{
    return a.x * b.y - a.y * b.x;
}

double cp(point a, point b, point c)
{
    return cross(b - a, c - a);
}

double rotatingCalipers(polygon pg)
{
    double dist = 0.0;
    pg.push_back(pg.front());
    for (int i = 0, q = 1, n = pg.size() - 1; i < n; i++)
    {
        while (cp(pg[i], pg[i + 1], pg[q + 1]) > cp(pg[i], pg[i + 1], pg[q]))
            q = (q + 1) % pg.size();
        dist = max(dist, max(pg[i].distTo(pg[q]), pg[i + 1].distTo(pg[q + 1])));
    }
    return dist;
}

int main(int argc, char *argv[])
{
    return 0;
}
