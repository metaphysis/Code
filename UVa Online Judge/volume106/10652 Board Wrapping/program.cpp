// Board Wrapping
// UVa ID: 10652
// Verdict: Accepted
// Submission Date: 2017-12-20
// UVa Run Time: 0.010s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

const double EPSILON = 1e-7;
const double PI = 2.0 * acos(0.0);

struct point {
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
};

typedef vector<point> polygon;

double cross(point a, point b)
{
    return a.x * b.y - a.y * b.x;
}

point rotate(point p, double t)
{
    return point(p.x * cos(t) - p.y * sin(t), p.x * sin(t) + p.y * cos(t));
}

double area(polygon &pg)
{
    if (pg.size() < 3) return 0.0;
    double A = 0.0;
    int n = pg.size();
    for (int i = 0, j = (i + 1) % n; i < n; i++, j = (i + 1) % n)
        A += (pg[i].x * pg[j].y - pg[j].x * pg[i].y);
    return fabs(A / 2.0);
}

int cp(point &a, point &b, point &c)
{
	return cross(b - a, c - a);
}

bool ccwOrCollinear(point &a, point &b, point &c)
{
    int cp1 = cp(a, b, c);
	return cp1 > EPSILON || fabs(cp1) <= EPSILON;
}

polygon andrewConvexHull(polygon &pg)
{
	sort(pg.begin(), pg.end());

	polygon ch;

	for (int i = 0; i < pg.size(); i++)
	{
		while (ch.size() >= 2 &&
		    ccwOrCollinear(ch[ch.size() - 2], ch[ch.size() - 1], pg[i]))
			ch.pop_back();
		ch.push_back(pg[i]);
	}

	for (int i = pg.size() - 1, upper = ch.size() + 1; i >= 0; i--)
	{
		while (ch.size() >= upper &&
		    ccwOrCollinear(ch[ch.size() - 2], ch[ch.size() - 1], pg[i]))
			ch.pop_back();
		ch.push_back(pg[i]);
	}

    ch.pop_back();

	return ch;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        int n;
        polygon pg;
        double xi, yi, w, h, theta, area1 = 0;

        cin >> n;
        for (int i = 0; i < n; i++)
        {
            cin >> xi >> yi >> w >> h >> theta;

            point o(xi, yi);
            double t = atan(h / w);
            point u(sqrt(w * w + h * h) / 2.0, 0.0);
            theta = theta * PI / 180.0;

            pg.push_back(o + rotate(u, t - theta));
            pg.push_back(o + rotate(u, PI - t - theta));
            pg.push_back(o + rotate(u, PI + t - theta));
            pg.push_back(o + rotate(u, 2 * PI - t - theta));

            area1 += w * h;
        }

        polygon mould = andrewConvexHull(pg);
        double area2 = area(mould);

        cout << fixed << setprecision(1) << (area1 * 100.0 / area2) << " %\n";
    }

    return 0;
}
