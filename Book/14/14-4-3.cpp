// Useless Tile Packers （没用的瓷砖打包公司）
// PC/UVa IDs: 111405/10065, Popularity: C, Success rate: average Level: 3
// Verdict: Accepted
// Submission Date: 2017-06-10
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <algorithm>
#include <iomanip>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

const int EPSILON = 0;

struct point
{
	int x, y;
	
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

double area(polygon pg)
{
	double areaOfPolygon = 0.0;

    int n = pg.size();
	for (int i = 0; i < n; i++)
	{
		int j = (i + 1) % n;
		areaOfPolygon += (pg[i].x * pg[j].y - pg[j].x * pg[i].y);
	}

	return fabs(areaOfPolygon / 2.0);
}

// 叉积。
int crossProduct(point &a, point &b, point &c)
{
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

// 判断是否向左转或共线。
bool ccwOrCollinear(point &a, point &b, point &c)
{
    int cp = crossProduct(a, b, c);
	return cp > EPSILON || fabs(cp) <= EPSILON;
}

// Andrew 凸包扫描算法。
polygon andrewConvexHull(polygon &pg)
{
	sort(pg.begin(), pg.end());

	polygon ch;

	// 求上凸包。
	for (int i = 0; i < pg.size(); i++)
	{
		while (ch.size() >= 2 &&
		    ccwOrCollinear(ch[ch.size() - 2], ch[ch.size() - 1], pg[i]))
			ch.pop_back();
		ch.push_back(pg[i]);
	}

	// 求下凸包。
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
	cout.precision(2);
	cout.setf(ios::fixed | ios::showpoint);

	int number, cases = 1;
	while (cin >> number, number)
	{
	    polygon tile(number);
		for (int i = 0; i < number; i++)
			cin >> tile[i].x >> tile[i].y;
		double used = area(tile);
		double all = area(andrewConvexHull(tile));
		cout << "Tile #" << cases++ << '\n';
		cout << "Wasted Space = " << (1.0 - used / all) * 100.0 << " %\n\n";
	}

	return 0;
}
