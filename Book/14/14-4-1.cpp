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

const int MAXV = 105;
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
	int number;
	point vertex[MAXV];
};

point lowerLeftPoint;

// 利用有向面积计算多边形的面积，注意最后结果取绝对值，因为顶点顺序可能并不是按
// 逆时针方向给出。
double area(point vertex[], int number)
{
	double areaOfPolygon = 0.0;

	for (int i = 0; i < number; i++)
	{
		int j = (i + 1) % number;
		areaOfPolygon += (vertex[i].x * vertex[j].y - vertex[j].x * vertex[i].y);
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
polygon grahamConvexHull(point vertex[], int number)
{
    polygon pg;

    // 点数小于3个，不构成凸包。
	if (number < 3)
	{
		for (int i = 0; i < number; i++)
			pg.vertex[i] = vertex[i];
		pg.number = number;
		return pg;
	}

	// 按横坐标和纵坐标排序，移除重复点。
	sort(vertex, vertex + number);
    number = unique(vertex, vertex + number) - vertex;

    // 按极角排序。
    lowerLeftPoint = vertex[0];
    sort(vertex + 1, vertex + number, smallerAngle);

    // 将初始的两点放入凸包。
	pg.vertex[0] = vertex[0];
	pg.vertex[1] = vertex[1];
	
	// 设置哨兵元素，将最左最低点设置为最后一个元素以便扫描时能回到参考点。
	vertex[number] = lowerLeftPoint;
	
	int i = 2, top = 1;
	while (i <= number)
	{
	    if (cw(pg.vertex[top - 1], pg.vertex[top], vertex[i]))
	        top--;
	    else if (collinear(pg.vertex[top - 1], pg.vertex[top], vertex[i]))
            pg.vertex[top] = vertex[i++];
	    else
	        pg.vertex[++top] = vertex[i++];
	}
	
    pg.number = top;
    
    return pg;
}

int main(int ac, char *av[])
{
	point tile[MAXV];
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

		polygon container = grahamConvexHull(tile, number);

		cout << "Tile #" << currentCase++ << endl;
		double all = area(container.vertex, container.number);
		double rate = (1.0 - used / all) * 100.0;
		cout << "Wasted Space = " << rate << " %" << endl;
		cout << endl;
	}

	return 0;
}
