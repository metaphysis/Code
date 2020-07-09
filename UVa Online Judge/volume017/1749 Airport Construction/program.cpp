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

double cross(point a, point b) { return a.x * b.y - a.y * b.x; }

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
    return fabs(cp(a, b, c)) < EPSILON;
}

bool cwOrCollinear(point a, point b, point c)
{
    return cw(a, b, c) || collinear(a, b, c);
}

bool ccwOrCollinear(point a, point b, point c)
{
    return ccw(a, b, c) || collinear(a, b, c);
}

bool pointInBox(point a, point b, point p)
{
    double minx = min(a.x, b.x), maxx = max(a.x, b.x);
    double miny = min(a.y, b.y), maxy = max(a.y, b.y);
    return p.x >= minx && p.x <= maxx && p.y >= miny && p.y <= maxy;
}

struct segment
{
    point p1, p2;
    bool contains(const point &p) { return pointInBox(p1, p2, p); }
};

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

// 检测从点i到点j的连线是否被其他线段所阻挡。
bool isBlocked(int i, int j)
{
    if (j == i + 1) return false;
    for (int k1 = 0, k2 = 1; k1 < n; k1++, k2++)
    {
        if (k2 >= n) k2 %= n;
        double cp1 = cp(pg[i], pg[j], pg[k1]);
        double cp2 = cp(pg[i], pg[j], pg[k2]);
        if (cp1 * cp2 < EPSILON)
        {
            point p1 = getIntersection(getLine(pg[i], pg[j]), getLine(pg[k1], pg[k2]));
            if (pointInBox(pg[i], pg[j], p1))
                return true;
        }
    }
    return false;
}

// 检查与线段ij两端相交的线段，获得的端点即为跑道的最长的长度。
double getDist(int i, int j)
{
    // 从i到j的方向与简单多边形的交点。
    point p1 = pg[j], p2 = pg[i];
    for (int k = j + 1; k < n; k++)
        if (ccw(pg[i], pg[j], pg[k]))
        {
            p1 = getIntersection(getLine(pg[i], pg[j]), getLine(pg[k - 1], pg[k]));
            break;
        }
    // 从j到i的方向与简单多边形的交点。
    for (int k = i - 1; k >= 0; k--)
        if (ccw(pg[i], pg[j], pg[k]))
        {
            p2 = getIntersection(getLine(pg[i], pg[j]), getLine(pg[k], pg[k + 1]));
            break;
        }
    return p1.distTo(p2);
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
                if (isBlocked(i, j)) continue;
                longest = max(longest, getDist(i, j));
            }
        cout << fixed << setprecision(9) << longest << '\n';
    }
    
    return 0;
}
