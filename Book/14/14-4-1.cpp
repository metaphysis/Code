// Useless Tile Packers （没用的瓷砖打包公司）
// PC/UVa IDs: 111405/10065, Popularity: C, Success rate: average Level: 3
// Verdict: Accepted
// Submission Date: 2017-06-09
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

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

point lowerLeftPoint;

// 利用有向面积计算多边形的面积，注意最后结果取绝对值，因为顶点顺序可能并不是按
// 逆时针方向给出。
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

// 从点a向点b望去，点c位于线段ab的右侧，返回true。
bool cw(point a, point b, point c)
{
	return crossProduct(a, b, c) < -EPSILON;
}

// 从点a向点b望去，点c位于线段ab的左侧时，返回true。
bool ccw(point a, point b, point c)
{
	return crossProduct(a, b, c) > EPSILON;
}

// 当三点共线时，返回true。
bool collinear(point a, point b, point c)
{
	return fabs(crossProduct(a, b, c)) <= EPSILON;
}

// 判断是否向左转或共线。
bool ccwOrCollinear(point a, point b, point c)
{
	return ccw(a, b, c) || collinear(a, b, c);
}

// 两点距离的平方值。
double distanceToLowerLeftPoint(point &p)
{
    return pow(lowerLeftPoint.x - p.x, 2) + pow(lowerLeftPoint.y - p.y, 2);
}

// 按相对于参考点的极角大小进行排序。
bool smallerAngle(point &p1, point &p2)
{
    if (collinear(lowerLeftPoint, p1, p2))
        return distanceToLowerLeftPoint(p1) <= distanceToLowerLeftPoint(p2);
    return ccw(lowerLeftPoint, p1, p2);
}

// Graham凸包扫描算法。
polygon grahamConvexHull(polygon &vertices)
{
    polygon ch(vertices);

	sort(ch.begin(), ch.end());
    ch.erase(unique(ch.begin(), ch.end()), ch.end());

    lowerLeftPoint = ch.front();
    sort(ch.begin() + 1, ch.end(), smallerAngle);

	ch.push_back(lowerLeftPoint);

	int top = 2, candidate = 2, total = ch.size() - 1;
	while (candidate <= total)
	{
	    if (cw(ch[top - 2], ch[top - 1], ch[candidate]))
	        top--;
	    else 
	    {
	        if (collinear(ch[top - 2], ch[top - 1], ch[candidate]))
	            ch[top - 1] = ch[candidate++];
	        else
	            ch[top++] = ch[candidate++];
        }
	}
	ch.erase(ch.begin() + top, ch.end());

	return ch;
}

int main(int ac, char *av[])
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
