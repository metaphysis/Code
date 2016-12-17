// The Fortified Forest
// UVa ID: 811
// Verdict: Accepted
// Submission Date: 2016-12-15
// UVa Run Time: 0.080s
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

const int MAXV = 20;
const int EPSILON = 1E-6;

struct point
{
	int x, y, v, l;
	
	bool operator<(const point& another) const
	{
	    if (abs(x - another.x) > 0)
	        return x < another.x;
	    else
	        return y < another.y;
	}
	
	bool operator==(const point& another) const
	{
	    return abs(x - another.x) <= 0 && abs(y - another.y) <= 0;
	}
};

struct polygon
{
	int number;
	point vertex[MAXV];
	
	double distanceOfPoints(point a, point b)
	{
	    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
	}
	
	double circumference()
	{
	    double length = 0.0;
	    for (int i = 0; i < number; i++)
	        length += distanceOfPoints(vertex[i], vertex[(i + 1) % number]);
	    return length;
	}
};

point lowerLeftPoint, allPoints[20];
int n, minValue, cutted[20], best[20];
double extraWood;

// 叉积。
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
	return fabs(crossProduct(a, b, c)) <= 0;
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

    // 点数小于等于3个，认为所有的点均在凸包上。
	if (number <= 3)
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

point uncuttedTrees[20];
void dfs(int value, int length, int depth)
{
    if (value > minValue || depth >= n) return;
    
    for (int i = 0; i < n; i++)
    {
        if (!cutted[i])
        {
            cutted[i] = 1;
            
            int k = 0;
            for (int j = 0; j < n; j++)
                if (!cutted[j])
                    uncuttedTrees[k++] = allPoints[j];
                    
            polygon pg = grahamConvexHull(uncuttedTrees, k);
            
            if ((double)(length + allPoints[i].l) > pg.circumference() + EPSILON)
            {
                if (value + allPoints[i].v < minValue)
                {
                    minValue = value + allPoints[i].v;
                    extraWood = (double)(length + allPoints[i].l) - pg.circumference();
                    memcpy(best, cutted, sizeof(cutted));
                }   
            }
            
            dfs(value + allPoints[i].v, length + allPoints[i].l, depth + 1);
            cutted[i] = 0;
        }
    }
}

int main(int argc, char *argv[])
{
	cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases = 0;
    while (cin >> n, n > 0)
    {
        for (int i = 0; i < n; i++)
            cin >> allPoints[i].x >> allPoints[i].y >> allPoints[i].v >> allPoints[i].l;
        
        minValue = 10000000;
        memset(cutted, 0, sizeof(cutted));

        dfs(0, 0, 0);

        if (cases > 0) cout << '\n';
        cout << "Forest " << ++cases << '\n';
        cout << "Cut these trees:";
        for (int i = 0; i < n; i++)
            if (best[i])
                cout << ' ' << (i + 1);
        cout << '\n';
        cout << "Extra wood: " << fixed << setprecision(2) << extraWood << '\n';
    }
    
	return 0;
}
