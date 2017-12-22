// Convex Hull Finding
// UVa ID: 681
// Verdict: Accepted
// Submission Date: 2016-08-27
// UVa Run Time: 0.020s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <algorithm>
#include <cmath>
#include <iostream>

using namespace std;

const int MAX_VERTICES = 520;
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

// 叉积。
int crossProduct(point a, point b, point c)
{
	return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
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

// Andrew 凸包扫描算法。
polygon andrewConvexHull(point vertex[], int numberOfVertex)
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
		
	return pg;
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
    
	point tile[MAX_VERTICES];
	int numberOfVertex;

    int k, delimiter;
    cin >> k;
    cout << k << '\n';

    for (int i = 1; i <= k; i++)
    {
        if (i > 1)
            cout << -1 << '\n';
            
	    cin >> numberOfVertex;

		for (int j = 0; j < numberOfVertex; j++)
			cin >> tile[j].x >> tile[j].y;
        cin >> delimiter;
        
		polygon container = andrewConvexHull(tile, numberOfVertex);

        int lowx = container.vertex[0].x, lowy = container.vertex[0].y, lowi = 0;
        for (int j = 1; j < container.numberOfVertex; j++)
            if (container.vertex[j].y < lowy ||
                (container.vertex[j].y == lowy && container.vertex[j].x < lowx))
                lowx = container.vertex[j].x, lowy = container.vertex[j].y, lowi = j;
		cout << container.numberOfVertex + 1 << '\n';
		for (int j = lowi; j > lowi - container.numberOfVertex; j--)
		{
		    cout << container.vertex[(j + container.numberOfVertex) % container.numberOfVertex].x;
		    cout << ' ' << container.vertex[(j + container.numberOfVertex) % container.numberOfVertex].y << '\n';
	    }
	    cout << container.vertex[lowi].x;
	    cout << ' ' << container.vertex[lowi].y << '\n';
	}

	return 0;
}
