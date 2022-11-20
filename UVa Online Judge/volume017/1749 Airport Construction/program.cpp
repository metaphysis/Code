// Airport Construction
// UVa ID: 1749
// Verdict: Wrong Answer
// Submission Date: 2020-07-01
// UVa Run Time: s
//
// 版权所有（C）2020，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const double EPSILON = 1e-6;

struct point
{
	double x, y;
    point (double x = 0, double y = 0): x(x), y(y) {}
    point operator + (point p) { return point(x + p.x, y + p.y); };
    point operator - (point p) { return point(x - p.x, y - p.y); };
    point operator * (double k) { return point(x * k, y * k); };
    point operator / (double k) { return point(x / k, y / k); };

	bool operator<(const point &p) const
	{
	    if (fabs(x - p.x) > EPSILON) return x < p.x;
	    return y < p.y;
	}
	
	double distTo(const point &p)
	{
	    return sqrt(pow(x - p.x, 2) + pow(y - p.y, 2));
	}
};

typedef vector<point> polygon;

int n;
polygon pg;

double dot(point a, point b) { return a.x * b.x + a.y * b.y; }
double cross(point a, point b) { return a.x * b.y - a.y * b.x; }

double cp(point a, point b, point c)
{
	return cross(b - a, c - a);
}

bool pointInBox(point a, point b, point p)
{
    double minx = min(a.x, b.x), maxx = max(a.x, b.x);
    double miny = min(a.y, b.y), maxy = max(a.y, b.y);
    return p.x >= minx && p.x <= maxx && p.y >= miny && p.y <= maxy;
}

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

const int OUT = 0, ON = 1, IN = 2;

int isPointInPolygon(point p)
{
    bool in = false;
    for (int i = 0; i < pg.size(); i++)
    {
        point a = pg[i] - p, b = pg[(i + 1) % pg.size()] - p;
        if (abs(cross(a, b)) < EPSILON && dot(a, b) < EPSILON) return ON;
        if (a.y > b.y) swap(a, b);
        if (a.y < EPSILON && EPSILON < b.y && cross(a, b) > EPSILON) in = !in;
    }
    return in ? IN : OUT;
}

double getDist(int i, int j)
{
    polygon pg1;
    for (int k1 = 0, k2 = 1; k1 < n; k1++, k2++)
    {
        if (k2 >= n) k2 %= n;
        double cp1 = cp(pg[i], pg[j], pg[k1]);
        double cp2 = cp(pg[i], pg[j], pg[k2]);
        if (cp1 * cp2 < -EPSILON)
        {
            point p1 = getIntersection(getLine(pg[i], pg[j]), getLine(pg[k1], pg[k2]));
            if (pointInBox(pg[i], pg[j], p1)) pg1.push_back(p1);
        }
        if (fabs(cp1) < EPSILON) pg1.push_back(pg[k1]);
    }
    sort(pg1.begin(), pg1.end());
    
    double d = 0, cd = 0;
    for (int i = 1; i < pg1.size(); i++)
    {
        point m = (pg1[i] + pg[i - 1]) / 2.0;
        if (isPointInPolygon(m) != OUT) cd += pg1[i].distTo(pg1[i - 1]);
        else
        {
            d = max(d, cd);
            cd = 0;
        }
    }

    return d;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    double x1, y1;
    while (cin >> n)
    {
        pg.clear();
        for (int i = 0; i < n; i++)
        {
            cin >> x1 >> y1;
            pg.push_back(point{x1, y1});
        }
        double longest = 0.0;
        for (int i = 0; i < n; i++)
        {
            longest = max(longest, pg[i].distTo(pg[(i + 1) % n]));
            for (int j = i + 2; j < n; j++)
            {
                if (fabs(pg[i].distTo(pg[j]) - longest) < EPSILON) continue;
                longest = max(longest, getDist(i, j));
            }
        }
        cout << fixed << setprecision(9) << longest << '\n';
    }
    
    return 0;
}
