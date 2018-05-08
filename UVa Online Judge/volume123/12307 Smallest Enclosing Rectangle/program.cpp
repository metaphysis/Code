// Smallest Enclosing Rectangle
// UVa ID: 12307
// Verdict: Accepted
// Submission Date: 2018-05-08
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const double EPSILON = 1e-7;

struct point
{
	double x, y;

    point (double x = 0, double y = 0): x(x), y(y) {}
	bool operator<(const point &p) const
	{
	    if (fabs(y - p.y) > EPSILON) return y < p.y;
	    return x < p.x;
	}

	bool operator==(const point &p) const
	{
	    return fabs(x - p.x) <= EPSILON && fabs(y - p.y) <= EPSILON;
	}

	double distTo(const point &p)
	{
	    return pow(x - p.x, 2) + pow(y - p.y, 2);
	}
	
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

typedef vector<point> polygon;

point pr;

double cp(point a, point b, point c)
{
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
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

bool ccwOrCollinear(point a, point b, point c)
{
	return ccw(a, b, c) || collinear(a, b, c);
}

bool cmpAngle(point &a, point &b)
{
    if (collinear(pr, a, b)) return pr.distTo(a) <= pr.distTo(b);
    return ccw(pr, a, b);
}

polygon grahamConvexHull(polygon &pg)
{
    polygon ch(pg);

	sort(ch.begin(), ch.end());
    ch.erase(unique(ch.begin(), ch.end()), ch.end());
    if (ch.size() < 3) return ch;

    pr = ch.front();
    sort(ch.begin() + 1, ch.end(), cmpAngle);
	ch.push_back(pr);

	int top = 2, next = 2, total = ch.size() - 1;
	while (next <= total)
	{
	    if (cw(ch[top - 2], ch[top - 1], ch[next])) top--;
	    else 
	    {
	        if (collinear(ch[top - 2], ch[top - 1], ch[next]))
	            ch[top - 1] = ch[next++];
	        else
	            ch[top++] = ch[next++];
        }
	}
	ch.erase(ch.begin() + top, ch.end());

	return ch;
}

double area(point p1, point p2, point p3)
{
    double r = 0;
    r += p1.x * p2.y - p1.y * p2.x;
    r += p2.x * p3.y - p2.y * p3.x;
    r += p3.x * p1.y - p3.y * p1.x;
    return fabs(r) / 2.0;
}

double getDistPL(point p, point p1, point p2)
{
	return fabs(cross(p2 - p1, p - p1) / abs(p2 - p1));
}

point project(point p, point p1, point p2)
{
    point base = p2 - p1;
    double r = dot(p - p1, base) / norm(base);
    return p1 + base * r;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n;
    while (cin >> n, n > 0)
    {
        polygon pg;
        double x, y;
        for (int i = 0; i < n; i++)
        {
            cin >> x >> y;
            pg.push_back(point(x, y));
        }

        polygon hull = grahamConvexHull(pg);

        // O(n^2).
        double minArea = 1e20, minLength = 1e20;
        for (int i = 0; i < hull.size(); i++)
        {
            point p1 = hull[i], p2 = hull[(i + 1) % hull.size()];

            int maxIdx = 0;
            double maxArea = 0;
            for (int j = 0; j < hull.size(); j++)
            {
                double r = area(p1, p2, hull[j]);
                if (r > maxArea)
                {
                    maxArea = r;
                    maxIdx = j;
                }
            }

            point pt = hull[maxIdx];
            point ps = project(hull[maxIdx], p1, p2);
            double maxLeftDist = 0, maxRightDist = 0;
            for (int j = 0; j < hull.size(); j++)
            {
                double dist = getDistPL(hull[j], ps, pt);
                if (ccwOrCollinear(ps, pt, hull[j]))
                    maxLeftDist = max(maxLeftDist, dist);
                else
                    maxRightDist = max(maxRightDist, dist);
            }
            double height = getDistPL(pt, p1, p2);
            double currentArea = (maxLeftDist + maxRightDist) * height;
            minArea = min(minArea, currentArea);
            minLength = min(minLength, 2 * (height + maxLeftDist + maxRightDist));
        }

        cout << fixed << setprecision(2) << minArea << ' ';
        cout << fixed << setprecision(2) << minLength << '\n';
    }

    return 0;
}
