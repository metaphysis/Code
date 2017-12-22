// The Incredible Hull
// UVa ID: 596
// Verdict: Accepted
// Submission Date: 2016-08-13
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <vector>

using namespace std;

const int MAX_VERTICES = 500;

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
	int vertexNumber;
	point vertex[MAX_VERTICES];
};

point lowerLeftPoint, vertex[MAX_VERTICES];
int vertexPerObject, vertexOfTotal = 0;

// 叉积。
int cp(point a, point b, point c)
{
	return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
}

// 从点a向点b望去，点c位于线段ab的右侧，返回true。
bool cw(point a, point b, point c)
{
	return cp(a, b, c) < 0;
}
// 从点a向点b望去，点c位于线段ab的左侧时，返回true。
bool ccw(point a, point b, point c)
{
	return cp(a, b, c) > 0;
}

// 当三点共线时，返回true。
bool collinear(point a, point b, point c)
{
	return cp(a, b, c) == 0;
}

// 判断是否向左转或共线。
bool ccwOrCollinear(point a, point b, point c)
{
	return cp(a, b, c) >= 0;
}

// 两点距离的平方值。
int distanceToLowerLeftPoint(point p)
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
void grahamConvexHull()
{
    polygon pg;

	sort(vertex, vertex + vertexOfTotal);
	vertexOfTotal = unique(vertex, vertex + vertexOfTotal) - vertex;
    lowerLeftPoint = vertex[0];
    sort(vertex + 1, vertex + vertexOfTotal, smallerAngle);

	pg.vertex[0] = vertex[0];
	pg.vertex[1] = vertex[1];
	vertex[vertexOfTotal] = lowerLeftPoint;
	
	int i = 2, top = 1;
	while (i <= vertexOfTotal)
	{
	    if (cw(pg.vertex[top - 1], pg.vertex[top], vertex[i]))
	        top--;
	    else
	        pg.vertex[++top] = vertex[i++];
	}
	
    pg.vertexNumber = top;
    
    int selected = 0;
    for (int i = 0; i < pg.vertexNumber; i++)
        if (pg.vertex[i].x > pg.vertex[selected].x ||
            (pg.vertex[i].x == pg.vertex[selected].x && pg.vertex[i].y < pg.vertex[selected].y))
            selected = i;
    
    for (int i = selected; i < pg.vertexNumber + selected; i++)
        cout << " (" << pg.vertex[i % pg.vertexNumber].x << ',' << pg.vertex[i % pg.vertexNumber].y << ')';
    cout << '\n';
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    char start;
    while (cin >> start, start != 'E')
    {
        string description;
        getline(cin, description);
        if (description.front() == ' ')
            description.erase(description.begin());
        cout << description << " convex hull:\n";
        
        vertexOfTotal = 0;
        while (cin >> start, start == 'P')
        {
            cin >> vertexPerObject;
            for (int i = 0; i < vertexPerObject; i++)
            {
                cin >> vertex[vertexOfTotal].x >> vertex[vertexOfTotal].y;
                vertexOfTotal++;
            }
        }

        grahamConvexHull();

        cin.putback(start);
    }
    
	return 0;
}
