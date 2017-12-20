// Polygons
// UVa ID: 137
// Verdict: Accepted
// Submission Date: 2017-05-08
// UVa Run Time: 0.000s
//
// 版权所有（C）2016 - 2017，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cmath>

using namespace std;

#define MAXV 1100
#define EPSILON 1E-7

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
    point vertices[MAXV];
};

double cp(point a, point b, point c)
{
    return (c.x - a.x) * (b.y - a.y) - (b.x - a.x) * (c.y - a.y);
}

// 从点 a 向点 b 望去，点 c 位于线段 ab 的右侧，返回 true。
bool cw(point a, point b, point c)
{
    return cp(a, b, c) > EPSILON;
}

line pointsToLine(point a, point b)
{
    line lr;
    lr.a = a;
    lr.b = b;
    lr.angle = atan2(a.y - b.y, a.x - b.x);
    return lr;
}

// 角度排序函数。
bool cmpAngle(line a, line b)
{
    return fabs(a.angle - b.angle) <= EPSILON;
}

// 半平面比较函数。
bool cmpLine(line f, line s)
{
    if (fabs(f.angle - s.angle) <= EPSILON)
        return cp(s.a, s.b, f.a) < EPSILON;
    return f.angle < s.angle;
}

// 两条直线是否平行。
bool parallel(line p, line q)
{
    return fabs((p.a.x - p.b.x) * (q.a.y - q.b.y) -
        (q.a.x - q.b.x) * (p.a.y - p.b.y)) <= EPSILON;
}

point getIntersection(line p, line q)
{
    point p1 = p.a;
    double scale =
        ((p.a.x - q.a.x) * (q.a.y - q.b.y) - (p.a.y - q.a.y) * (q.a.x - q.b.x)) /
        ((p.a.x - p.b.x) * (q.a.y - q.b.y) - (p.a.y - p.b.y) * (q.a.x - q.b.x));
    p1.x += (p.b.x - p.a.x) * scale;
    p1.y += (p.b.y - p.a.y) * scale;
    return p1;
}

// 给定一组直线，求直线的交点得到多边形的顶点。
polygon halfPlaneIntersection(line * sides, int nLine)
{
    polygon pg;
    line deque[MAXV];

    pg.number = 0;
    sort(sides, sides + nLine, cmpLine);
    nLine = unique(sides, sides + nLine, cmpAngle) - sides;

    int bottom = 0, top = 1;
    deque[0] = sides[0];
    deque[1] = sides[1];

    for (int i = 2; i < nLine; i++)
    {
        if (parallel(deque[top], deque[top - 1])
            || parallel(deque[bottom], deque[bottom + 1]))
            return pg;

        while (bottom < top && cw(sides[i].a, sides[i].b,
                getIntersection(deque[top], deque[top - 1])))
            top--;

        while (bottom < top && cw(sides[i].a, sides[i].b,
                getIntersection(deque[bottom], deque[bottom + 1])))
            bottom++;

        deque[++top] = sides[i];
    }

    while (bottom < top && cw(deque[bottom].a, deque[bottom].b,
            getIntersection(deque[top], deque[top - 1])))
        top--;

    while (bottom < top && cw(deque[top].a, deque[top].b,
            getIntersection(deque[bottom], deque[bottom + 1])))
        bottom++;

    if (top <= (bottom + 1))
        return pg;

    // 求相邻两条凸包边的交点获取顶点坐标。
    for (int i = bottom; i < top; i++)
        pg.vertices[pg.number++] = getIntersection(deque[i], deque[i + 1]);

    // 首尾两条直线的交点也是顶点。
    if (bottom < (top + 1))
        pg.vertices[pg.number++] = getIntersection(deque[bottom], deque[top]);

    return pg;
}

// 利用有向面积计算多边形的面积，注意最后结果取绝对值，因为顶点顺序可能
// 并不是按逆时针方向给出。
double area(polygon pg)
{
    if (pg.number < 3) return 0.0;

    double A = 0.0;
    for (int i = 0, j; j = (i + 1) % pg.number, i < pg.number; i++)
        A += (pg.vertices[i].x * pg.vertices[j].y - pg.vertices[j].x * pg.vertices[i].y);
    return fabs(A / 2.0);
}

void exclusiveOr(polygon a, polygon b)
{
    double areaA = area(a);
    double areaB = area(b);

    line sides[MAXV];
    int nLine = 0;

    for (int i = 0; i < a.number - 1; i++)
        sides[nLine++] = pointsToLine(a.vertices[i + 1], a.vertices[i]);
    sides[nLine++] = pointsToLine(a.vertices[0], a.vertices[a.number - 1]);

    for (int i = 0; i < b.number - 1; i++)
        sides[nLine++] = pointsToLine(b.vertices[i + 1], b.vertices[i]);
    sides[nLine++] = pointsToLine(b.vertices[0], b.vertices[b.number - 1]);

    polygon c = halfPlaneIntersection(sides, nLine);

    double areaAnd = area(c);
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
            a.vertices[a.number++] = (point){x, y};
        }

        cin >> number;
        b.number = 0;
        for (int i = 1; i <= number; i++)
        {
            cin >> x >> y;
            b.vertices[b.number++] = (point){x, y};
        }

        exclusiveOr(a, b);
    }

    cout << endl;

    return 0;
}
