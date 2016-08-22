// Video Surveillance
// UVa ID: 588
// Verdict: Accepted
// Submission Date: 2016-08-22
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <algorithm>
#include <cmath>
#include <iostream>

using namespace std;

const int MAX_VERTICES = 1100;
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
    int numberOfVertex;
    point vertex[MAX_VERTICES];
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
bool cmpHalfPlaneLine(line line1, line line2)
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

// 重复点比较函数。
bool cmpPoint(point p1, point p2)
{
    return fabs(p1.x - p2.x) <= EPSILON && fabs(p1.y - p2.y) <= EPSILON;
}

// 两条直线是否平行。
bool paralleLine(line line1, line line2)
{
    return fabs((line1.a.x - line1.b.x) * (line2.a.y - line2.b.y) -
        (line2.a.x - line2.b.x) * (line1.a.y - line1.b.y)) <= EPSILON;
}

// 求两条直线的交点。
point intersectionPoint(line line1, line line2)
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
void pointsToLine(point a, point b, line & l)
{
    l.a = a;
    l.b = b;
    l.angle = atan2(b.y - a.y, b.x - a.x);
}

// 给定一组直线，求直线的交点得到多边形的顶点。
polygon halfPlaneIntersection(line * edgeLine, int nLine)
{
    polygon pg;
    line dequeLine[MAX_VERTICES];

    pg.numberOfVertex = 0;
    sort(edgeLine, edgeLine + nLine, cmpHalfPlaneLine);
    nLine = unique(edgeLine, edgeLine + nLine, cmpAngle) - edgeLine;

    int bottom = 0, top = 1;
    dequeLine[0] = edgeLine[0];
    dequeLine[1] = edgeLine[1];

    for (int i = 2; i < nLine; i++)
    {
        if (paralleLine(dequeLine[top], dequeLine[top - 1])
            || paralleLine(dequeLine[bottom], dequeLine[bottom + 1]))
            return pg;

        while (bottom < top && cw(edgeLine[i].a, edgeLine[i].b,
                intersectionPoint(dequeLine[top], dequeLine[top - 1])))
            top--;

        while (bottom < top && cw(edgeLine[i].a, edgeLine[i].b,
                intersectionPoint(dequeLine[bottom], dequeLine[bottom + 1])))
            bottom++;

        dequeLine[++top] = edgeLine[i];
    }

    while (bottom < top && cw(dequeLine[bottom].a, dequeLine[bottom].b,
            intersectionPoint(dequeLine[top], dequeLine[top - 1])))
        top--;

    while (bottom < top && cw(dequeLine[top].a, dequeLine[top].b,
            intersectionPoint(dequeLine[bottom], dequeLine[bottom + 1])))
        bottom++;

    if (top <= (bottom + 1))
        return pg;

    // 求相邻两条凸包边的交点获取顶点坐标。
    for (int i = bottom; i < top; i++)
        pg.vertex[pg.numberOfVertex++] =
            intersectionPoint(dequeLine[i], dequeLine[i + 1]);

    // 首尾两条直线的交点也是顶点。
    if (bottom < (top + 1))
        pg.vertex[pg.numberOfVertex++] =
            intersectionPoint(dequeLine[bottom], dequeLine[top]);

    // 去除重复的顶点。
    pg.numberOfVertex =
        unique(pg.vertex, pg.vertex + pg.numberOfVertex, cmpPoint) - pg.vertex;

    return pg;
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int n, cases = 0;
    point vertices[MAX_VERTICES];
    line edgeLine[MAX_VERTICES];

    while (cin >> n, n)
    {
        double x, y;
        for (int i = n - 1; i >= 0; i--)
        {
            cin >> x >> y;
            vertices[i] = (point)
            {
            x, y};
        }

        for (int i = 0; i < n; i++)
        {
            int j = (i + 1) % n;
            pointsToLine(vertices[i], vertices[j], edgeLine[i]);
        }

        polygon pg = halfPlaneIntersection(edgeLine, n);

        cout << "Floor #" << ++cases << '\n';
        if (pg.numberOfVertex > 0)
            cout << "Surveillance is possible.\n\n";
        else
            cout << "Surveillance is impossible.\n\n";
    }

    return 0;
}
