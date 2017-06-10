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

const int MAX_VERTICES = 105;
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

// Melkman凸包算法。
polygon melkmanConvexHull(polygon &pg)
{
    // 点数小于3个，不构成凸包。
	if (pg.size() < 3) return pg;

    // 使用数组实现双端队列。
    point deque[2 * pg.size() + 1];
    int bottom = pg.size(), top = bottom - 1;

    bool isLeft = ccw(pg[0], pg[1], pg[2]);
    deque[++top] = isLeft ? pg[0] : pg[1], deque[++top] = isLeft ? pg[1] : pg[0];
    deque[++top] = pg[2], deque[--bottom] = pg[2];

    int candidate = 3;
    while (candidate < pg.size())
    {
        if (ccw(deque[top - 1], deque[top], pg[candidate]) &&
            ccw(deque[bottom], deque[bottom + 1], pg[candidate]))
        {
            candidate++;
            continue;
        }

        while (!ccw(deque[top - 1], deque[top], pg[candidate])) top--;
        deque[++top] = pg[candidate];

        while (!ccw(pg[candidate], deque[bottom], deque[bottom + 1])) bottom++;
        deque[--bottom] = pg[candidate];

        candidate++;
    }

    polygon ch;
	for (int i = bottom; i < top; i++) ch.push_back(deque[i]);

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
		double all = area(melkmanConvexHull(tile));
		cout << "Tile #" << cases++ << '\n';
		cout << "Wasted Space = " << (1.0 - used / all) * 100.0 << " %\n\n";
	}

	return 0;
}
