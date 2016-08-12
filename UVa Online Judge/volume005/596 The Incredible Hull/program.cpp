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
};

struct polygon
{
	int number;
	point vertex[MAX_VERTICES];
};

point lowerLeftPoint, vertex[MAX_VERTICES];
int number, counter = 0;

// 叉积。
int crossProduct(point a, point b, point c)
{
	return (c.x - a.x) * (b.y - a.y) - (b.x - a.x) * (c.y - a.y);
}

// 从点 a 向点 b 望去，点 c 位于线段 ab 的右侧，返回 true。
bool cw(point a, point b, point c)
{
	return crossProduct(a, b, c) > 0;
}
// 从点 a 向点 b 望去，点 c 位于线段 ab 的左侧时，返回 true。
bool ccw(point a, point b, point c)
{
	return crossProduct(a, b, c) < 0;
}

// 当三点共线时，返回true。
bool collinear(point a, point b, point c)
{
	return fabs(crossProduct(a, b, c)) <= 0;
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

// Graham 凸包扫描算法。
void grahamConvexHull()
{
    polygon hull;
    
	if (number <= 3)
	{
		for (int i = 0; i < counter; i++)
			hull.vertex[i] = vertex[i];
		hull.number = counter;
		return;
	}

	sort(vertex, vertex + counter, lowerLeft);

    lowerLeftPoint = vertex[0];
    
    sort(vertex + 1, vertex + counter, smallerAngle);

	int i = 2, top = 1;
	hull.vertex[0] = vertex[0];
	hull.vertex[1] = vertex[1];
	
	vertex[counter] = lowerLeftPoint;
	
	while (i <= counter)
	{
	    if (cw(hull.vertex[top - 1], hull.vertex[top], vertex[i]))
	        top--;
	    else
	        hull.vertex[++top] = vertex[i++];
	}
	
    hull.number = top;
    
    int selected = 0;
    for (int i = 0; i < hull.number; i++)
    {
        if (hull.vertex[i].x > hull.vertex[selected].x ||
            (hull.vertex[i].x == hull.vertex[selected].x && hull.vertex[i].y < hull.vertex[selected].y))
            selected = i;
    }
    
    for (int i = selected; i < hull.number + selected; i++)
        cout << " (" << hull.vertex[i % hull.number].x << ',' << hull.vertex[i % hull.number].y << ')';
    cout << '\n';
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    char start;
    while (cin >> start, start != 'E')
    {
        string dataset;
        getline(cin, dataset);
        if (dataset.front() == ' ')
            dataset.erase(dataset.begin());
        cout << dataset << " convex hull:\n";
        
        counter = 0;
        while (cin >> start, start == 'P')
        {
            cin >> number;
            point object[MAX_VERTICES];
            for (int i = 0; i < number; i++)
                cin >> object[i].x >> object[i].y;
            sort(object, object + number, lowerLeft);
            number = unique(object, object + number, cmpPoint) - object;
            for (int i = 0; i < number; i++)
                vertex[counter++] = object[i];
        }

        grahamConvexHull();

        cin.putback(start);
    }
    
	return 0;
}
