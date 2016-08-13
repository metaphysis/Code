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

point lowerLeftPoint;

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
void grahamConvexHull(point vertex[], int numberOfVertex, polygon& pg)
{
    // 点数小于等于3个，所有的均在凸包上。
	if (numberOfVertex <= 3)
	{
		for (int i = 0; i < numberOfVertex; i++)
			pg.vertex[i] = vertex[i];
		pg.numberOfVertex = numberOfVertex;
		return;
	}

	// 按横坐标和纵坐标排序，移除重复点。
	sort(vertex, vertex + numberOfVertex);
    numberOfVertex = unique(vertex, vertex + numberOfVertex) - vertex;

    // 按极角排序。
    lowerLeftPoint = vertex[0];
    sort(vertex + 1, vertex + numberOfVertex, smallerAngle);

    // 将初始的两点放入凸包。
	pg.vertex[0] = vertex[0];
	pg.vertex[1] = vertex[1];
	
	// 设置哨兵元素，将最左最低点设置为最后一个元素以便扫描时能回到参考点。
	vertex[numberOfVertex] = lowerLeftPoint;
	
	int i = 2, top = 1;
	while (i <= numberOfVertex)
	{
	    if (cw(pg.vertex[top - 1], pg.vertex[top], vertex[i]))
	        top--;
	    else if (collinear(pg.vertex[top - 1], pg.vertex[top], vertex[i]))
            pg.vertex[top] = vertex[i++];
	    else
	        pg.vertex[++top] = vertex[i++];
	}
	
    pg.numberOfVertex = top;
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
		{
			cin >> tile[i].x;
			cin >> tile[i].y;
		}

		double used = area(tile, numberOfVertex);

		grahamConvexHull(tile, numberOfVertex, container);

		cout << "Tile #" << currentCase++ << endl;
		double all = area(container.vertex, container.numberOfVertex);
		double rate = (1.0 - used / all) * 100.0;
		cout << "Wasted Space = " << rate << " %" << endl;
		cout << endl;
	}

	return 0;
}
