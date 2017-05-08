// Useless Tile Packers （没用的瓷砖打包公司）
// PC/UVa IDs: 111405/10065, Popularity: C, Success rate: average Level: 3
// Verdict: Accepted
// Submission Date: 2011-11-06
// UVa Run Time: 0.020s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net

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

point lowerLeftPoint;

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

// 凸包扫描算法的预排序，按 y 坐标排序。
bool lowerLeft(point a, point b)
{
	return (a.y == b.y) ? (a.x < b.x) : (a.y < b.y);
}

// 比较两点是否相同。
bool cmpPoint(point first, point second)
{
    return first.x == second.x && first.y == second.y;
}

// 两点距离的平方值。
double distanceToLowerLeftPoint(point p)
{
    return pow(lowerLeftPoint.x - p.x, 2) + pow(lowerLeftPoint.y - p.y, 2);
}

// 按相对于参考点的极角大小进行排序。
bool smallerAngle(point first, point second)
{
    if (collinear(lowerLeftPoint, first, second))
        return distanceToLowerLeftPoint(first) <= distanceToLowerLeftPoint(second);
    return ccw(lowerLeftPoint, first, second);
}

// Graham凸包扫描算法。
void grahamConvexHull(point vertex[], int number, polygon& hull)
{
    // 点数小于3个，不构成凸包。
	if (number < 3)
	{
		for (int i = 0; i < number; i++)
			hull.vertex[i] = vertex[i];
		hull.number = number;
		return;
	}

	// 按横坐标和纵坐标排序。
	sort(vertex, vertex + number, lowerLeft);

    // 移除重复点。
    number = unique(vertex, vertex + number, cmpPoint) - vertex;

    // 按极角排序。
    lowerLeftPoint = vertex[0];
    
    sort(vertex + 1, vertex + number, smallerAngle);

    // 将初始的两点放入凸包。
	int i = 2, top = 1;
	hull.vertex[0] = vertex[0];
	hull.vertex[1] = vertex[1];
	
	// 设置哨兵元素，将最左最低点设置为最后一个元素以便扫描时能回到参考点。
	vertex[number] = lowerLeftPoint;
	
	while (i <= number)
	{
	    if (cw(hull.vertex[top - 1], hull.vertex[top], vertex[i]))
	        top--;
	    else if (collinear(hull.vertex[top - 1], hull.vertex[top], vertex[i]))
            hull.vertex[top] = vertex[i++];
	    else
	        hull.vertex[++top] = vertex[i++];
	}
	
    hull.number = top;
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

		grahamConvexHull(tile, number, container);

		cout << "Tile #" << currentCase++ << endl;
		double all = area(container.vertex, container.number);
		double rate = (1.0 - used / all) * 100.0;
		cout << "Wasted Space = " << rate << " %" << endl;
		cout << endl;
	}

	return 0;
}
