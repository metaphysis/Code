// Center of Masses
// UVa ID: 10002
// Verdict: 
// Submission Date: 
// UVa Run Time: s
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

struct point {
    double x, y;
    point (double x = 0, double y = 0): x(x), y(y) {}
    
    point operator-(point &p)
    {
        return point(x - p.x, y - p.y);
    }

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

double cp(point &a, point &b, point &c)
{
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

bool ccwOrCollinear(point &a, point &b, point &c)
{
    double cp1 = cp(a, b, c);
	return cp1 > EPSILON || fabs(cp1) <= EPSILON;
}

polygon andrewConvexHull(polygon &pg)
{
	sort(pg.begin(), pg.end());

	polygon ch;

	for (int i = 0; i < pg.size(); i++)
	{
		while (ch.size() >= 2 && ccwOrCollinear(ch[ch.size() - 2], ch[ch.size() - 1], pg[i]))
			ch.pop_back();
		ch.push_back(pg[i]);
	}

	for (int i = pg.size() - 1, upper = ch.size() + 1; i >= 0; i--)
	{
		while (ch.size() >= upper && ccwOrCollinear(ch[ch.size() - 2], ch[ch.size() - 1], pg[i]))
			ch.pop_back();
		ch.push_back(pg[i]);
	}

    ch.pop_back();
    
	return ch;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n;
    double x, y;
    vector<point> pg;

    while (cin >> n)
    {
        if (n < 3) break;

        pg.clear();
        for (int i = 0; i < n; i++)
        {
            cin >> x >> y;
            pg.push_back(point(x, y));
        }

        polygon ch = andrewConvexHull(pg);
        point pc = getCentroid1(ch);
        //point pc = getCentroid2(ch);
        
        cout << fixed << setprecision(3) << (pc.x + 1e-9);
        cout << ' ';
        cout << fixed << setprecision(3) << (pc.y + 1e-9) << '\n';
    }

    return 0;
}
