#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cmath>

using namespace std;

#define MAX_VERTICES 105
#define EPSILON 1E-10

struct point
{
	int x;
	int y;
};

struct polygon
{
	int number;
	point vertex[MAX_VERTICES];
};

// 利用有向面积计算多边形的面积，注意最后结果取绝对值，因为顶点顺序可能并不是按逆时针方向给出。
double area(point vertex[], int number)
{
	double total = 0.0;

	for (int i = 0; i < number; i++)
	{
		int j = (i + 1) % number;
		total += (vertex[i].x * vertex[j].y - vertex[j].x * vertex[i].y);
	}

	return fabs(total / 2.0);
}

// 叉积。
int crossProduct(point a, point b, point c)
{
	return (c.x - a.x) * (b.y - a.y) - (b.x - a.x) * (c.y - a.y);
}

// 从点 a 向点 b 望去，点 c 位于线段 ab 的右侧，返回 true。
bool cw(point a, point b, point c)
{
	return crossProduct(a, b, c) > EPSILON;
}
// 从点 a 向点 b 望去，点 c 位于线段 ab 的左侧时，返回 true。
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

// Andrew 凸包扫描算法的预排序，按 y 坐标排序。
bool lowerLeft(point a, point b)
{
	return (a.y == b.y) ? (a.x < b.x) : (a.y < b.y);
}

// Andrew 凸包扫描算法。
void andrewConvexHull(point vertex[], int number, polygon& hull)
{
	// 排序。
	sort(vertex, vertex + number, lowerLeft);

	point upper[MAX_VERTICES], lower[MAX_VERTICES];
	int top;

	// 求上凸包。
	upper[0] = vertex[0];
	upper[1] = vertex[1];
	top = 2;
	for (int i = 2; i < number; i++)
	{
		upper[top] = vertex[i];
		while (top >= 2 && ccwOrCollinear(upper[top - 2], upper[top - 1], upper[top]))
		{
			upper[top - 1] = upper[top];
			top--;
		}
		top++;
	}

	hull.number = 0;
	for (int i = 0; i < top; i++)
		hull.vertex[hull.number++] = upper[i];

	// 求下凸包。
	lower[0] = vertex[number - 1];
	lower[1] = vertex[number - 2];
	top = 2;
	for (int i = number - 3; i >= 0; i--)
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
		hull.vertex[hull.number++] = lower[i];
}

int main(int ac, char *av[])
{
	point tile[MAX_VERTICES];
	polygon container;
	int number, currentCase = 1;

	cout.precision(2);
	cout.setf(ios::fixed | ios::showpoint);

	while (cin >> number, number)
	{
		for (int i = 0; i < number; i++)
		{
			cin >> tile[i].x;
			cin >> tile[i].y;
		}

		double used = area(tile, number);

		andrewConvexHull(tile, number, container);

		cout << "Tile #" << currentCase++ << endl;
		double all = area(container.vertex, container.number);
		double rate = (1.0 - used / all) * 100.0;
		cout << "Wasted Space = " << rate << " %" << endl;
		cout << endl;
	}

	return 0;
}
