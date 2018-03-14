// Convex Hull
// UVa ID: 11626
// Verdict: Accepted
// Submission Date: 2017-12-21
// UVa Run Time: 0.150s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const double EPSILON = 1e-7;

struct point
{
	double x, y;

	bool operator<(const point &p) const
	{
	    if (fabs(x - p.x) > EPSILON) return x < p.x;
	    return y < p.y;
	}
};

typedef vector<point> polygon;

double cp(point a, point b, point c)
{
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

bool ccw(point a, point b, point c)
{
	return cp(a, b, c) > EPSILON;
}

polygon andrewConvexHull(polygon &pg)
{
	polygon ch;

    sort(pg.begin(), pg.end());
	for (int i = 0; i < pg.size(); i++)
	{
		while (ch.size() >= 2 && ccw(ch[ch.size() - 2], ch[ch.size() - 1], pg[i]))
			ch.pop_back();
		ch.push_back(pg[i]);
	}
	for (int i = pg.size() - 2, upper = ch.size() + 1; i >= 0; i--)
	{
		while (ch.size() >= upper && ccw(ch[ch.size() - 2], ch[ch.size() - 1], pg[i]))
			ch.pop_back();
		ch.push_back(pg[i]);
	}
    ch.pop_back();
    
	return ch;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    
    for (int cs = 1; cs <= cases; cs++)
    {
        polygon pg;
        
        char flag;
        int n, on = 0;
        double xi, yi;
        
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            cin >> xi >> yi >> flag;
            if (flag == 'Y')
            {
                pg.push_back(point{xi, yi});
                on++;
            }
        }
        
        polygon ch = andrewConvexHull(pg);

        cout << on << '\n';
        
        point leftLower = ch.front();
        int k = 0;
        for (int i = 1; i < ch.size(); i++)
            if (ch[i].x < leftLower.x || (ch[i].x == leftLower.x && ch[i].y < leftLower.y))
                k = i;
                
        int size = ch.size();
        for (int i = 0; i < size; i++)
        {
            int j = (k - i + size) % size;
            cout << (int)ch[j].x << ' ' << (int)ch[j].y << '\n';
        }
    }

    return 0;
}
