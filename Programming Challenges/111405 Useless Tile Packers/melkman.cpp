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

// Melkman 凸包算法。
void melkmanConvexHull(point vertex[], int number, polygon& hull)
{
    // 使用数组实现双端队列。
    point deque[2 * number + 1];
    int bottom = number, top = bottom - 1;
    
    bool isLeft = ccw(vertex[0], vertex[1], vertex[2]);
    deque[++top] = isLeft ? vertex[0] : vertex[1];
    deque[++top] = isLeft ? vertex[1] : vertex[0];
    
    deque[++top] = vertex[2];
    deque[--bottom] = vertex[2];
    
    int i = 3;
    while (i < number)
    {
        if (ccw(deque[top - 1], deque[top], vertex[i]) &&
            ccw(deque[bottom], deque[bottom + 1], vertex[i]))
        {
            i++;
            continue;
        }
        
        while (!ccw(deque[top - 1], deque[top], vertex[i]))
            top--;
        deque[++top] = vertex[i];
            
        while (!ccw(vertex[i], deque[bottom], deque[bottom + 1]))
            bottom++;
        deque[--bottom] = vertex[i];
            
        i++;
    }
	
	hull.number = 0;
	for (int i = bottom; i < top; i++)
	   hull.vertex[hull.number++] = deque[i];
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

		melkmanConvexHull(tile, number, container);

		cout << "Tile #" << currentCase++ << endl;
		double all = area(container.vertex, container.number);
		double rate = (1.0 - used / all) * 100.0;
		cout << "Wasted Space = " << rate << " %" << endl;
		cout << endl;
	}

	return 0;
}
