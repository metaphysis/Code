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
} ps[1024];

typedef vector<point> polygon;

double cp(point &a, point &b, point &c)
{
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

bool ccw(point &a, point &b, point &c)
{
    return cp(a, b, c) > EPSILON;
}

bool ccwOrCollinear(point &a, point &b, point &c)
{
    double cp1 = cp(a, b, c);
	return cp1 > EPSILON || fabs(cp1) <= EPSILON;
}

// Any three vertex not collinear.
polygon andrewConvexHull(polygon &pg)
{
	polygon ch;

    sort(pg.begin(), pg.end());
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

    srand(time(NULL));

    int cases = 100;
    cout << cases << '\n';
    for (int cs = 1; cs <= cases; )
    {
        cout << '\n';
        int n = rand() % 400 + 100;
        int m = rand() % 400 + 100;
        cout << n << ' ' << m << '\n';
        int p = rand() % 6 + 3;
        polygon pg;
        for (int i = 0; i < 1000; i++)
        {
            int x = rand() % (n - 1) + 1;
            int y = rand() % (m - 1) + 1;
            pg.push_back(point(x, y));
        }
        polygon ch = andrewConvexHull(pg);
        if (ch.size() < p) continue;
        cout << p << '\n';
        for (int j = 0; j < p && j < ch.size(); j++)
            cout << ch[j].x << ' ' << ch[j].y << '\n';
        cs++;
    }

    return 0;
}
