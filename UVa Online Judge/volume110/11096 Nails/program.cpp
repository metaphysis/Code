// Nails
// UVa ID: 11096
// Verdict: Accepted
// Submission Date: 2017-12-20
// UVa Run Time: 0.000s
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

struct point
{
	double x, y;

	bool operator<(const point &p) const
	{
	    if (abs(y - p.y) > 0) return y < p.y;
	    return x < p.x;
	}

	bool operator==(const point &p) const
	{
	    return abs(x - p.x) == 0 && abs(y - p.y) == 0;
	}

	double distTo(const point &p)
	{
	    return pow(x - p.x, 2) + pow(y - p.y, 2);
	}
};

typedef vector<point> polygon;

point pr;

// 叉积，判断点a，b，c组成的两条线段的转折方向。当叉积小于0，则形成一个右拐，
// 否则共线（cp = 0）或左拐（cp > 0）。
double cp(point a, point b, point c)
{
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

// 从点a向点b望去，点c位于线段ab的右侧，返回true。
bool cw(point a, point b, point c)
{
	return cp(a, b, c) < 0;
}
// 从点a向点b望去，点c位于线段ab的左侧时，返回true。
bool ccw(point a, point b, point c)
{
	return cp(a, b, c) > 0;
}

// 当三点共线时，返回true。
bool collinear(point a, point b, point c)
{
	return abs(cp(a, b, c)) == 0;
}

// 判断是否向左转或共线。
bool ccwOrCollinear(point a, point b, point c)
{
	return ccw(a, b, c) || collinear(a, b, c);
}

// 按相对于参考点的极角大小进行排序。
bool cmpAngle(point &a, point &b)
{
    if (collinear(pr, a, b)) return pr.distTo(a) <= pr.distTo(b);
    return ccw(pr, a, b);
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

polygon grahamConvexHull(polygon &pg)
{
    polygon ch(pg);

	sort(ch.begin(), ch.end());
    ch.erase(unique(ch.begin(), ch.end()), ch.end());
    if (ch.size() < 3) return ch;

    pr = ch.front();
    sort(ch.begin() + 1, ch.end(), cmpAngle);
	ch.push_back(pr);

	int top = 2, candidate = 2, total = ch.size() - 1;
	while (candidate <= total)
	{
	    if (cw(ch[top - 2], ch[top - 1], ch[candidate])) top--;
	    else ch[top++] = ch[candidate++];
	    //else 
	    //{
	    //    if (collinear(ch[top - 2], ch[top - 1], ch[candidate]))
	    //        ch[top - 1] = ch[candidate++];
	    //    else ch[top++] = ch[candidate++];
        //}
	}
	ch.erase(ch.begin() + top, ch.end());

	return ch;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        double ribbon, xi, yi;
        int n;
        
        polygon pg;
        cin >> ribbon >> n;
        for (int i = 0; i < n; i++)
        {
            cin >> xi >> yi;
            
            pg.push_back(point{xi, yi});
        }
        
        polygon ch = grahamConvexHull(pg);
        
        double length = 0;
        n = ch.size();
        for (int i = 0; i < n; i++)
        {
            int j = (i + 1) % n;
            length += sqrt(pow(ch[i].x - ch[j].x, 2) + pow(ch[i].y - ch[j].y, 2));
        }
        ribbon = max(ribbon, length);
        cout << fixed << setprecision(5) << ribbon << '\n';
    }

    return 0;
}
