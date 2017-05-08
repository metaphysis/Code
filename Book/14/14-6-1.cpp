#include <algorithm>
#include <cmath>
#include <iostream>

using namespace std;

const int MAXV = 1100;
const double EPSILON = 1E-7;

// 点。
struct point
{
    double x, y;
};

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
    point vertex[MAXV];
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
polygon halfPlaneIntersection(line * edges, int n)
{
    polygon pg;
    line deques[MAXV];
    
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
