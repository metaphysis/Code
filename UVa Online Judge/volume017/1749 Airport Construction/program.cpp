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
	
	bool operator==(const point &p) const
	{
	    return fabs(x - p.x) <= EPSILON && fabs(y - p.y) <= EPSILON;
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

bool pointInBox(point a, point b, point p, bool includeEndPoint)
{
    double minx = min(a.x, b.x), maxx = max(a.x, b.x);
    double miny = min(a.y, b.y), maxy = max(a.y, b.y);
    if (includeEndPoint) return p.x >= minx && p.x <= maxx && p.y >= miny && p.y <= maxy;
    else return p.x > minx && p.x < maxx && p.y > miny && p.y < maxy;
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

int isPointInPolygon(point p, polygon &pg)
{
    bool in = false;
    for (int i = 0; i < pg.size(); i++)
    {
        point a = pg[i] - p, b = pg[(i + 1) % pg.size()] - p;
        if (fabs(cross(a, b)) < EPSILON && dot(a, b) < EPSILON) return ON;
        if (a.y > b.y) swap(a, b);
        if (a.y < EPSILON && EPSILON < b.y && cross(a, b) > EPSILON) in = !in;
    }
    return in ? IN : OUT;
}

bool isInPolygon(int i, int j)
{
    if (j == i + 1) return true;
    polygon pg1;
    for (int k1 = 0, k2 = 1; k1 < n; k1++, k2++)
    {
        if (k2 >= n) k2 %= n;
        double cp1 = cp(pg[i], pg[j], pg[k1]);
        double cp2 = cp(pg[i], pg[j], pg[k2]);
        if (cp1 * cp2 < -EPSILON)
        {
            point p1 = getIntersection(getLine(pg[i], pg[j]), getLine(pg[k1], pg[k2]));
            if (pointInBox(pg[i], pg[j], p1, false))
                return false;
        }
        if (fabs(cp1) < EPSILON && pointInBox(pg[i], pg[j], pg[k1], true)) pg1.push_back(pg[k1]);
        if (fabs(cp2) < EPSILON && pointInBox(pg[i], pg[j], pg[k2], true)) pg1.push_back(pg[k2]);
    }
    sort(pg1.begin(), pg1.end());
    for (int k = 0; k < pg1.size() - 1; k++)
        if (isPointInPolygon((pg1[k] + pg1[k + 1]) / 2.0, pg) == OUT)
            return false;
    return true;
}

double getDist(int i, int j)
{
    if (pg[i].x > pg[j].x) swap(i, j);
    polygon pg1;
    for (int k1 = 0, k2 = 1; k1 < n; k1++, k2++)
    {
        if (k2 >= n) k2 %= n;
        double cp1 = cp(pg[i], pg[j], pg[k1]);
        double cp2 = cp(pg[i], pg[j], pg[k2]);
        if (cp1 * cp2 < -EPSILON)
        {
            point p1 = getIntersection(getLine(pg[i], pg[j]), getLine(pg[k1], pg[k2]));
            if (pointInBox(pg[i], pg[j], p1, true))
                pg1.push_back(p1);
        }
        if (fabs(cp1) < EPSILON && pointInBox(pg[i], pg[j], pg[k1], true)) pg1.push_back(pg[k1]);
        if (fabs(cp2) < EPSILON && pointInBox(pg[i], pg[j], pg[k2], true)) pg1.push_back(pg[k2]);
    }
    sort(pg1.begin(), pg1.end());
    int s = -1, e = -1;
    for (int k = 0; k < pg1.size(); k++)
        if (pg[i] == pg1[k])
        {
            s = k;
            break;
        }
    for (int k = 0; k < pg1.size(); k++)
        if (pg[j] == pg1[k])
        {
            e = k;
            break;
        }
    while (true)
    {
        if (!s || isPointInPolygon((pg1[s] + pg1[s - 1]) / 2, pg) == OUT) break;
        s--;
    }
    while (true)
    {
        if (e + 1 == pg1.size() || isPointInPolygon((pg1[e] + pg1[e + 1]) / 2, pg) == OUT) break;
        e++;
    }
    return pg1[s].distTo(pg1[e]);
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
            for (int j = i + 1; j < n; j++)
            {
                if (fabs(pg[i].distTo(pg[j]) - longest) < EPSILON) continue;
                if (isInPolygon(i, j)) longest = max(longest, getDist(i, j));
            }
        cout << fixed << setprecision(9) << longest << '\n';
    }
    
    return 0;
}
