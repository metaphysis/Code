// The partition of a cake
// UVa ID: 527
// Verdict: Accepted
// Submission Date: 2017-05-08
// UVa Run Time: 0.330s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

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
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

const int MAXN = 1100;
const double EPSILON = 1e-7;
bool debug = false;

// 点。
struct point
{
    double x, y;
    
	bool operator<(const point& p) const
	{
	    if (fabs(x - p.x) > EPSILON)
	        return x < p.x;
	    else
	        return y < p.y;
	}
	
	bool operator==(const point& p) const
	{
	    return fabs(x - p.x) <= EPSILON && fabs(y - p.y) <= EPSILON;
	}
};

point lowerLeftPoint;

// 使用直线的极角和直线上的两个点来表示直线。
struct line
{
    point a, b;
    double angle;
};

// 多边形。
struct polygon
{
    int number;
    point vertex[MAXN];
};

// 叉积。
double crossProduct(point p1, point p2, point p3)
{
    return (p3.x - p1.x) * (p2.y - p1.y) - (p2.x - p1.x) * (p3.y - p1.y);
}

// 顺时针转向。从点p1向点p2望去，点p3位于线段p1p2的右侧，返回true。
bool cw(point p1, point p2, point p3)
{
    return crossProduct(p1, p2, p3) > EPSILON;
}

// 将直线按照极角进行排序。若极角相同，选择位于极角逆时针方向的直线。
bool cmpLine(line line1, line line2)
{
    if (fabs(line1.angle - line2.angle) <= EPSILON)
        return crossProduct(line2.a, line2.b, line1.a) < EPSILON;
    return line1.angle < line2.angle;
}

// 比较两条直线的极角。
bool cmpAngle(line line1, line line2)
{
    return fabs(line1.angle - line2.angle) <= EPSILON;
}

// 两条直线是否平行。
bool paralle(line line1, line line2)
{
    return fabs((line1.a.x - line1.b.x) * (line2.a.y - line2.b.y) -
        (line2.a.x - line2.b.x) * (line1.a.y - line1.b.y)) <= EPSILON;
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
polygon grahamConvexHull(point vertex[], int number)
{
    polygon pg;
    pg.number = 0;

    // 点数小于等于3个，认为所有的点均在凸包上。
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

// 求两条直线的交点。
point intersection(line line1, line line2)
{
    point p = line1.a;
    double scale = ((line1.a.x - line2.a.x) * (line2.a.y - line2.b.y) -
        (line1.a.y - line2.a.y) * (line2.a.x - line2.b.x)) /
        ((line1.a.x - line1.b.x) * (line2.a.y - line2.b.y) -
        (line1.a.y - line1.b.y) * (line2.a.x - line2.b.x));
    p.x += (line1.b.x - line1.a.x) * scale;
    p.y += (line1.b.y - line1.a.y) * scale;
    return p;
}

// 由两点得到对应的直线方程。
line pointsToLine(point a, point b)
{
    line l;
    l.a = a;
    l.b = b;
    l.angle = atan2(b.y - a.y, b.x - a.x);
    return l;
}

// 给定一组直线，求直线的交点得到多边形的顶点。直线按逆时针顺序排列。
polygon halfPlaneIntersection(line *edges, int n)
{
    polygon pg;
    line deques[MAXN];

    pg.number = 0;

    sort(edges, edges + n, cmpLine);
    n = unique(edges, edges + n, cmpAngle) - edges;

    int bottom = 0, top = 1;
    deques[0] = edges[0], deques[1] = edges[1];

    for (int i = 2; i < n; i++)
    {
        if (paralle(deques[top], deques[top - 1])
            || paralle(deques[bottom], deques[bottom + 1]))
            return pg;

        while (bottom < top && cw(edges[i].a, edges[i].b,
                intersection(deques[top], deques[top - 1])))
            top--;

        while (bottom < top && cw(edges[i].a, edges[i].b,
                intersection(deques[bottom], deques[bottom + 1])))
            bottom++;

        deques[++top] = edges[i];
    }

    while (bottom < top && cw(deques[bottom].a, deques[bottom].b,
            intersection(deques[top], deques[top - 1])))
        top--;

    while (bottom < top && cw(deques[top].a, deques[top].b,
            intersection(deques[bottom], deques[bottom + 1])))
        bottom++;

    if (top <= (bottom + 1)) return pg;

    // 求相邻两条凸包边的交点获取顶点坐标。
    for (int i = bottom; i < top; i++)
        pg.vertex[pg.number++] = intersection(deques[i], deques[i + 1]);

    // 首尾两条直线的交点也是顶点。
    if (bottom < (top + 1))
        pg.vertex[pg.number++] = intersection(deques[bottom], deques[top]);

    return pg;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0;
    cin >> cases;
    
    for (int c = 1; c <= cases; c++)
    {
        if (c > 1) cout << '\n';
        
        int cuts;
        cin >> cuts;
        
        vector<polygon> pgs, next;

        polygon pg;
        pg.number = 4;
        pg.vertex[0] = point{0, 0};
        pg.vertex[1] = point{1000, 0};
        pg.vertex[2] = point{1000, 1000};
        pg.vertex[3] = point{0, 1000};
        pgs.push_back(pg);

        line edges1[MAXN], edges2[MAXN];
        
        double x1, y1, x2, y2;
        for (int i = 1; i <= cuts; i++)
        {
            cin >> x1 >> y1 >> x2 >> y2;

            point cutpoint1 = point{x1, y1}, cutpoint2 = point{x2, y2};
            
            for (int j = 0; j < pgs.size(); j++)
            {
                polygon somePg = pgs[j];

                int lines = 0;
                for (int k = 0; k < somePg.number; k++)
                {
                    point start = somePg.vertex[k];
                    point end = somePg.vertex[(k + 1) % somePg.number];

                    edges1[lines] = pointsToLine(start, end);
                    edges2[lines] = pointsToLine(start, end);

                    lines++;
                }

                edges1[lines] = pointsToLine(cutpoint1, cutpoint2);
                polygon pg1 = halfPlaneIntersection(edges1, lines + 1);
                
                edges2[lines] = pointsToLine(cutpoint2, cutpoint1);
                polygon pg2 = halfPlaneIntersection(edges2, lines + 1);
                
                polygon pg3 = grahamConvexHull(pg1.vertex, pg1.number);
                polygon pg4 = grahamConvexHull(pg2.vertex, pg2.number);

                if (pg3.number < 3 || pg4.number < 3) next.push_back(somePg);
                else next.push_back(pg3), next.push_back(pg4);
            }
            
            pgs.swap(next);
            next.clear();
        }

        cout << pgs.size() << '\n';
    }

    return 0;
}
