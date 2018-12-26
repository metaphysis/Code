// Art Gallery
// UVa ID: 1304
// Verdict: Accepted
// Submission Date: 2018-12-26
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAX_VERTICES = 1600;
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
double cp(point p1, point p2, point p3)
{
    return (p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y);
}

// 顺时针转向。从点p1向点p2望去，点p3位于线段p1p2的右侧，返回true。
bool cw(point p1, point p2, point p3)
{
    return cp(p1, p2, p3) < -EPSILON;
}

// 将直线按照极角进行排序。若极角相同，选择位于极角逆时针方向的直线。
bool cmpHalfPlaneLine(line p, line q)
{
    if (fabs(p.angle - q.angle) <= EPSILON) return cw(p.a, p.b, q.a);
    return p.angle < q.angle;
}

// 比较两条直线的极角。
bool cmpAngle(line p, line q)
{
    return fabs(p.angle - q.angle) <= EPSILON;
}

// 两条直线是否平行。
bool paralleLine(line p, line q)
{
    return fabs((p.a.x - p.b.x) * (q.a.y - q.b.y) -
        (q.a.x - q.b.x) * (p.a.y - p.b.y)) <= EPSILON;
}

// 求两条直线的交点。
point getIntersection(line p, line q)
{
    point p1 = p.a;
    double scale = ((p.a.x - q.a.x) * (q.a.y - q.b.y) -
        (p.a.y - q.a.y) * (q.a.x - q.b.x)) /
        ((p.a.x - p.b.x) * (q.a.y - q.b.y) -
        (p.a.y - p.b.y) * (q.a.x - q.b.x));
    p1.x += (p.b.x - p.a.x) * scale;
    p1.y += (p.b.y - p.a.y) * scale;
    return p1;
}

// 由两点得到对应的直线方程。
void pointsToLine(point a, point b, line & l)
{
    l.a = a;
    l.b = b;
    l.angle = atan2(b.y - a.y, b.x - a.x);
}

// 给定一组直线，求直线的交点得到多边形的顶点。
polygon halfPlaneIntersection(line *edgeLine, int nLine)
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
                getIntersection(dequeLine[top], dequeLine[top - 1])))
            top--;

        while (bottom < top && cw(edgeLine[i].a, edgeLine[i].b,
                getIntersection(dequeLine[bottom], dequeLine[bottom + 1])))
            bottom++;

        dequeLine[++top] = edgeLine[i];
    }

    while (bottom < top && cw(dequeLine[bottom].a, dequeLine[bottom].b,
            getIntersection(dequeLine[top], dequeLine[top - 1])))
        top--;

    while (bottom < top && cw(dequeLine[top].a, dequeLine[top].b,
            getIntersection(dequeLine[bottom], dequeLine[bottom + 1])))
        bottom++;

    if (top <= (bottom + 1))
        return pg;

    // 求相邻两条凸包边的交点获取顶点坐标。
    for (int i = bottom; i < top; i++)
        pg.vertex[pg.numberOfVertex++] =
            getIntersection(dequeLine[i], dequeLine[i + 1]);

    // 首尾两条直线的交点也是顶点。
    if (bottom < (top + 1))
        pg.vertex[pg.numberOfVertex++] =
            getIntersection(dequeLine[bottom], dequeLine[top]);

    return pg;
}

double getArea(point vertex[], int n)
{
	double area = 0.0;
	if (n < 3) return area;
	for (int i = 0, j = 1; i < n; i++, j = (i + 1) % n)
		area += (vertex[i].x * vertex[j].y - vertex[j].x * vertex[i].y);
	return fabs(area / 2.0);
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int n, cases = 0;
    point vertices[MAX_VERTICES];
    line edgeLine[MAX_VERTICES];

    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> n;
        double x, y;
        for (int i = n - 1; i >= 0; i--)
        {
            cin >> x >> y;
            vertices[i] = (point){x, y};
        }

        for (int i = 0; i < n; i++)
        {
            int j = (i + 1) % n;
            pointsToLine(vertices[i], vertices[j], edgeLine[i]);
        }

        polygon pg = halfPlaneIntersection(edgeLine, n);

        cout << fixed << setprecision(2) << getArea(pg.vertex, pg.numberOfVertex) << '\n';
    }

    return 0;
}
