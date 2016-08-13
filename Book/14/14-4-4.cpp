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

// Melkman凸包算法。
void melkmanConvexHull(point vertex[], int numberOfVertex, polygon& pg)
{
    // 使用数组实现双端队列。
    point deque[2 * numberOfVertex + 1];
    int bottom = numberOfVertex, top = bottom - 1;
    
    bool isLeft = ccw(vertex[0], vertex[1], vertex[2]);
    deque[++top] = isLeft ? vertex[0] : vertex[1];
    deque[++top] = isLeft ? vertex[1] : vertex[0];
    
    deque[++top] = vertex[2];
    deque[--bottom] = vertex[2];
    
    int i = 3;
    while (i < numberOfVertex)
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
	
	pg.numberOfVertex = 0;
	for (int i = bottom; i < top; i++)
	   pg.vertex[pg.numberOfVertex++] = deque[i];
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

		melkmanConvexHull(tile, numberOfVertex, container);

		cout << "Tile #" << currentCase++ << endl;
		double all = area(container.vertex, container.numberOfVertex);
		double rate = (1.0 - used / all) * 100.0;
		cout << "Wasted Space = " << rate << " %" << endl;
		cout << endl;
	}

	return 0;
}
