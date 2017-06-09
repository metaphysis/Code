// Useless Tile Packers （没用的瓷砖打包公司）
// PC/UVa IDs: 111405/10065, Popularity: C, Success rate: average Level: 3
// Verdict: Accepted
// Submission Date: 2017-06-09
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
	
	int distTo(const point &p)
	{
	    return pow(x - p.x, 2) + pow(y - p.y, 2);
	}
};

typedef vector<point> polygon;

point lowerLeftPoint;

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
int crossProduct(point a, point b, point c)
{
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

// 按相对于参考点的极角大小进行排序。
bool smallerAngle(point &p1, point &p2)
{
    int cp = crossProduct(lowerLeftPoint, p1, p2);
    if (fabs(cp) <= EPSILON)
        return lowerLeftPoint.distTo(p1) <= lowerLeftPoint.distTo(p2);
    return cp > EPSILON;
}

// Graham凸包扫描算法。
polygon grahamConvexHull(polygon &pg)
{
    polygon ch(pg);

	sort(ch.begin(), ch.end());
    ch.erase(unique(ch.begin(), ch.end()), ch.end());

    lowerLeftPoint = ch.front();
    sort(ch.begin() + 1, ch.end(), smallerAngle);

	ch.push_back(lowerLeftPoint);

	int top = 2, candidate = 2, total = ch.size() - 1;
	while (candidate <= total)
	{
	    int cp = crossProduct(ch[top - 2], ch[top - 1], ch[candidate]);
	    if (cp < -EPSILON) top--;
	    else 
	    {
	        if (fabs(cp) <= EPSILON) ch[top - 1] = ch[candidate++];
	        else ch[top++] = ch[candidate++];
        }
	}
	ch.erase(ch.begin() + top, ch.end());

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
		double all = area(grahamConvexHull(tile));
		cout << "Tile #" << cases++ << '\n';
		cout << "Wasted Space = " << (1.0 - used / all) * 100.0 << " %\n\n";
	}

	return 0;
}
