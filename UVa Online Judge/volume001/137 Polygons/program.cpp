// Polygons
// UVa IDs: 137
// Verdict: Accepted
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cmath>

using namespace std;

#define MAX_VERTICES 1100
#define EPSILON 1E-6

struct point
{
    double x, y;
};

// 使用直线和 X 轴所成的角度和直线经过的两个点的坐标来表示该条直线。
struct line
{
    point a, b;
    double angle;
};

struct polygon
{
    int number;
    point vertex[MAX_VERTICES];
};

double crossProduct(point a, point b, point c)
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

line pointsToLine(point a, point b)
{
    line l;

    l.a = a;
    l.b = b;
    l.angle = atan2(a.y - b.y, a.x - b.x);

    return l;
}

// 角度排序函数。
bool cmpAngle(line a, line b)
{
    return fabs(a.angle - b.angle) <= EPSILON;
}

// 半平面比较函数。
bool cmpHalfPlane(line f, line s)
{
    if (fabs(f.angle - s.angle) <= EPSILON)
        return crossProduct(s.a, s.b, f.a) < 0.0;
    return f.angle < s.angle;
}

// 点比较函数。
bool cmpPoint(point a, point b)
{
    return fabs(a.x - b.x) <= EPSILON && fabs(a.y - b.y) <= EPSILON;
}

// 两条直线是否平行。
bool paralleLine(line f, line s)
{
    return fabs((f.a.x - f.b.x) * (s.a.y - s.b.y) -
        (s.a.x - s.b.x) * (f.a.y - f.b.y)) <= EPSILON;
}

// 计算两点间距离。
double calDistance(point a, point b)
{
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

point intersectionPoint(line f, line s)
{
    point p = f.a;
    double tmp =
        ((f.a.x - s.a.x) * (s.a.y - s.b.y) - (f.a.y -
            s.a.y) * (s.a.x - s.b.x)) / ((f.a.x -
            f.b.x) * (s.a.y - s.b.y) - (f.a.y - f.b.y) * (s.a.x - s.b.x));
    p.x += (f.b.x - f.a.x) * tmp;
    p.y += (f.b.y - f.a.y) * tmp;
    return p;
}

// 给定一组直线，求直线的交点得到多边形的顶点。
polygon halfPlaneIntersection(line * edgeLine, int nLine)
{
    polygon pg;
    line deque[MAX_VERTICES];

    pg.number = 0;
    sort(edgeLine, edgeLine + nLine, cmpHalfPlane);
    nLine = unique(edgeLine, edgeLine + nLine, cmpAngle) - edgeLine;

    int bottom = 0, top = 1;
    deque[0] = edgeLine[0];
    deque[1] = edgeLine[1];

    for (int i = 2; i < nLine; i++)
    {
        if (paralleLine(deque[top], deque[top - 1])
            || paralleLine(deque[bottom], deque[bottom + 1]))
            return pg;

        while (bottom < top && cw(edgeLine[i].a, edgeLine[i].b,
                intersectionPoint(deque[top], deque[top - 1])))
            top--;

        while (bottom < top && cw(edgeLine[i].a, edgeLine[i].b,
                intersectionPoint(deque[bottom], deque[bottom + 1])))
            bottom++;

        deque[++top] = edgeLine[i];
    }

    while (bottom < top && cw(deque[bottom].a, deque[bottom].b,
            intersectionPoint(deque[top], deque[top - 1])))
        top--;

    while (bottom < top && cw(deque[top].a, deque[top].b,
            intersectionPoint(deque[bottom], deque[bottom + 1])))
        bottom++;

    if (top <= (bottom + 1))
        return pg;

    // 求相邻两条凸包边的交点获取顶点坐标。
    for (int i = bottom; i < top; i++)
        pg.vertex[pg.number++] = intersectionPoint(deque[i], deque[i + 1]);

    // 首尾两条直线的交点也是顶点。
    if (bottom < (top + 1))
        pg.vertex[pg.number++] = intersectionPoint(deque[bottom], deque[top]);

    // 去除重复的顶点。
    pg.number = unique(pg.vertex, pg.vertex + pg.number, cmpPoint) - pg.vertex;

    return pg;
}

// 利用有向面积计算多边形的面积，注意最后结果取绝对值，因为顶点顺序可能
// 并不是按逆时针方向给出。
double area(polygon pg)
{
    if (pg.number < 3)
        return 0.0;
        
    double total = 0.0;
    for (int i = 0, j; j = (i + 1) % pg.number, i < pg.number; i++)
        total +=
            (pg.vertex[i].x * pg.vertex[j].y - pg.vertex[j].x * pg.vertex[i].y);
    return fabs(total / 2.0);
}

void exclusiveOr(polygon a, polygon b)
{
    double areaA = area(a);
    double areaB = area(b);

    line edgeLine[MAX_VERTICES];
    int nLine = 0;

    for (int i = 0; i < a.number - 1; i++)
        edgeLine[nLine++] = pointsToLine(a.vertex[i + 1], a.vertex[i]);
    edgeLine[nLine++] = pointsToLine(a.vertex[0], a.vertex[a.number - 1]);

    for (int i = 0; i < b.number - 1; i++)
        edgeLine[nLine++] = pointsToLine(b.vertex[i + 1], b.vertex[i]);
    edgeLine[nLine++] = pointsToLine(b.vertex[0], b.vertex[b.number - 1]);

    polygon andPolygon = halfPlaneIntersection(edgeLine, nLine);

    double areaAnd = area(andPolygon);
    double areaExclusiveOr = areaA + areaB - 2 * areaAnd;
    cout << fixed << setw(8) << setfill(' ') << setprecision(2);
    cout << areaExclusiveOr;
}

int main(int argc, char *argv[])
{
    int number;
    polygon a, b;
    double x, y;

    while (cin >> number, number != 0)
    {
        a.number = 0;
        for (int i = 1; i <= number; i++)
        {
            cin >> x >> y;
            a.vertex[a.number++] = (point)
            {
            x, y};
        }

        cin >> number;
        b.number = 0;
        for (int i = 1; i <= number; i++)
        {
            cin >> x >> y;
            b.vertex[b.number++] = (point)
            {
            x, y};
        }

        exclusiveOr(a, b);
    }

    cout << endl;

    return 0;
}
