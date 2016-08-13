// Useless Tile Packers （没用的瓷砖打包公司）
// PC/UVa IDs: 111405/10065, Popularity: C, Success rate: average Level: 3
// Verdict: Accepted
// Submission Date: 2016-08-13
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <algorithm>
#include <iomanip>
#include <cmath>
#include <iostream>

using namespace std;

const int MAX_VERTICES = 105;
const int EPSILON = 0;

struct point
{
	int x, y;
	
	bool operator<(const point& another) const
	{
	    if (fabs(x - another.x) > EPSILON)
	        return x < another.x;
	    else
	        return y < another.y;
	}
	
	bool operator==(const point& another) const
	{
	    return fabs(x - another.x) <= EPSILON && fabs(y - another.y) <= EPSILON;
	}
};

struct polygon
{
	int numberOfVertex;
	point vertex[MAX_VERTICES];
};

// 利用有向面积计算多边形的面积，注意最后结果取绝对值，因为顶点顺序可能并不是按
// 逆时针方向给出。
double area(point vertex[], int numberOfVertex)
{
	double areaOfPolygon = 0.0;

	for (int i = 0; i < numberOfVertex; i++)
	{
		int j = (i + 1) % numberOfVertex;
		areaOfPolygon += (vertex[i].x * vertex[j].y - vertex[j].x * vertex[i].y);
	}

	return fabs(areaOfPolygon / 2.0);
}

// 叉积。
int crossProduct(point a, point b, point c)
{
	return (c.x - a.x) * (b.y - a.y) - (b.x - a.x) * (c.y - a.y);
}

// 从点a向点b望去，点c位于线段ab的右侧，返回true。
bool cw(point a, point b, point c)
{
	return crossProduct(a, b, c) > EPSILON;
}
// 从点a向点b望去，点c位于线段ab的左侧时，返回true。
bool ccw(point a, point b, point c)
{
	return crossProduct(a, b, c) < -EPSILON;
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

// Andrew 凸包扫描算法。
void andrewConvexHull(point vertex[], int numberOfVertex, polygon& pg)
{
	// 排序并去除重复点。
	sort(vertex, vertex + numberOfVertex);
    numberOfVertex = unique(vertex, vertex + numberOfVertex) - vertex;

	point upper[MAX_VERTICES], lower[MAX_VERTICES];
	int top;

	// 求上凸包。
	upper[0] = vertex[0];
	upper[1] = vertex[1];
	top = 2;
	for (int i = 2; i < numberOfVertex; i++)
	{
		upper[top] = vertex[i];
		while (top >= 2 && ccwOrCollinear(upper[top - 2], upper[top - 1], upper[top]))
		{
			upper[top - 1] = upper[top];
			top--;
		}
		top++;
	}

	pg.numberOfVertex = 0;
	for (int i = 0; i < top; i++)
		pg.vertex[pg.numberOfVertex++] = upper[i];

	// 求下凸包。
	lower[0] = vertex[numberOfVertex - 1];
	lower[1] = vertex[numberOfVertex - 2];
	top = 2;
	for (int i = numberOfVertex - 3; i >= 0; i--)
	{
		lower[top] = vertex[i];
		while (top >= 2 && ccwOrCollinear(lower[top - 2], lower[top - 1], lower[top]))
		{
			lower[top - 1] = lower[top];
			top--;
		}
		top++;
	}

	// 合并下凸包。
	for (int i = 1; i < top - 1; i++)
		pg.vertex[pg.numberOfVertex++] = lower[i];
}

int main(int ac, char *av[])
{
	point tile[MAX_VERTICES];
	polygon container;
	int numberOfVertex, currentCase = 1;

	cout.precision(2);
	cout.setf(ios::fixed | ios::showpoint);

	while (cin >> numberOfVertex, numberOfVertex)
	{
		for (int i = 0; i < numberOfVertex; i++)
			cin >> tile[i].x >> tile[i].y;

		double used = area(tile, numberOfVertex);

		andrewConvexHull(tile, numberOfVertex, container);

		cout << "Tile #" << currentCase++ << endl;
		double all = area(container.vertex, container.numberOfVertex);
		double rate = (1.0 - used / all) * 100.0;
		cout << "Wasted Space = " << rate << " %" << endl;
		cout << endl;
	}

	return 0;
}
