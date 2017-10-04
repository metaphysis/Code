// The Art Gallery
// UVa ID: 10078
// Verdict: Accepted
// Submission Date: 2017-02-25
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <algorithm>
#include <iomanip>
#include <cmath>
#include <iostream>

using namespace std;

const int MAX_VERTICES = 105;

struct point
{
	int x, y;
	
	bool operator<(const point& another) const
	{
	    if (y == another.y)
	        return x < another.x;
	    else
	        return y < another.y;
	}
	
	bool operator==(const point& another) const
	{
	    return x == another.x && y == another.y;
	}
};

struct polygon
{
	int numberOfVertex;
	point vertex[MAX_VERTICES];
};

// 叉积，判断点a，b，c组成的两条线段的转折方向。当叉积大于0，则形成一个右拐，
// 否则共线（cp = 0）或左拐（cp < 0）。
int crossProduct(point a, point b, point c)
{
	return (c.x - a.x) * (b.y - a.y) - (b.x - a.x) * (c.y - a.y);
}

// 从点a向点b望去，点c位于线段ab的右侧，返回true。
bool cw(point a, point b, point c)
{
	return crossProduct(a, b, c) > 0;
}

// 从点a向点b望去，点c位于线段ab的左侧时，返回true。
bool ccw(point a, point b, point c)
{
	return crossProduct(a, b, c) < 0;
}

// 当三点共线时，返回true。
bool collinear(point a, point b, point c)
{
	return crossProduct(a, b, c) == 0;
}

double distanceOfPoint(point a, point b)
{
    return pow(a.x - b.x, 2) + pow(a.y - b.y, 2);
}

// Jarvis步进法求凸包。
polygon jarvisConvexHull(point vertex[], int numberOfVertex)
{
    polygon pg;

    // 点数小于等于3个，认为所有的点均在凸包上。
	if (numberOfVertex <= 3)
	{
		for (int i = 0; i < numberOfVertex; i++)
			pg.vertex[i] = vertex[i];
		pg.numberOfVertex = numberOfVertex;
		return pg;
	}
	
	// 排序得到位置处于最左且最下的点，当有共线情况存在时，取y坐标最小的点。
	// 去除重复点。 
    sort(vertex, vertex + numberOfVertex);
    numberOfVertex = unique(vertex, vertex + numberOfVertex) - vertex;

    int current = 0;
    pg.numberOfVertex = 0;

    do
    {
        // 测试点current，next，i是否构成一个右转，或者共线。
        // 当构成右转时，说明点i比点next相对于current有更小的极角，应该将当前的
        // 待选凸包点更新为点i。
        // 当共线时，选择距离当前凸包点current更远的点。
        int next = 0;
        for (int i = 1; i < numberOfVertex; i++)
            if (cw(vertex[current], vertex[next], vertex[i]) ||
                (collinear(vertex[current], vertex[next], vertex[i]) &&
                    (distanceOfPoint(vertex[current], vertex[i]) >
                        distanceOfPoint(vertex[current], vertex[next]))))
                next = i;
        
        // 将点next加入凸包。
        pg.vertex[pg.numberOfVertex++] = vertex[next];
        current = next;
    } while (current != 0);
    
    return pg;
}

int main(int ac, char *av[])
{
	point tile[MAX_VERTICES];
	int numberOfVertex;

	while (cin >> numberOfVertex, numberOfVertex)
	{
		for (int i = 0; i < numberOfVertex; i++)
			cin >> tile[i].x >> tile[i].y;

		polygon container = jarvisConvexHull(tile, numberOfVertex);

		if (container.numberOfVertex == numberOfVertex)
            cout << "No\n";
        else
            cout << "Yes\n";
	}

	return 0;
}
