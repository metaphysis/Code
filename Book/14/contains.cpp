#include <iostream>
#include <cmath>

using namespace std;

#define MAXPOLY 100
#define EPSILON 1E-10

struct point
{
    double x, y;
};

struct segment
{
    point start, end;
};

struct polygon
{
    int vertexNumber;
    point vertex[MAXPOLY];
};

// 使用叉积来表示线段的相对方向。
double direction(point a, point b, point c)
{
    return (c.x - a.x) * (b.y - a.y) - (b.x - a.x) * (c.y - a.y);
}

// 判断多边形的边是否在射线上方。
bool isSideAboveRay(segment ray, segment side)
{
    return side.start.y >= ray.start.y && side.end.y >= ray.start.y;
}

// 根据设定的交点数规则判断射线与多边形的边是否相交。
bool segmentsIntersect(segment ray, segment side)
{
    double d1, d2, d3, d4;
    
    d1 = direction(ray.start, ray.end, side.start);
    d2 = direction(ray.start, ray.end, side.end);
    d3 = direction(side.start, side.end, ray.start);
    d4 = direction(side.start, side.end, ray.end);
    
    // 不相交。
    if ((d1 * d2 > 0) || (d3 * d4 > 0))
        return false;
    // 跨越式相交。
    if ((d1 * d2 < 0) && (d3 * d4 < 0))
        return true;
	// 共线，不论是否重合，均判断为不相交。
    if ((fabs(d1) <= EPSILON && fabs(d2) <= EPSILON) ||
        (fabs(d3) <= EPSILON && fabs(d4) <= EPSILON))
        return false;
	// 相交于顶点，判断是否在射线上方。
    if (fabs(d1) <= EPSILON || fabs(d2) <= EPSILON ||
        fabs(d3) <= EPSILON || fabs(d4) <= EPSILON)
        return isSideAboveRay (ray, side);

    return false;
}

bool isPointInPolygon(point p, polygon hull)
{
    // 找到多边形顶点中位于最右边的点的横坐标。
    double rightX = hull.vertex[0].x;
    for (int i = 0; i < hull.vertexNumber; i++)
    {
        if (hull.vertex[i].x > rightX)
            rightX = hull.vertex[i].x;
    }
    
    
    int numberOfIntersection = 0;
    segment ray = (segment){ p, (point){ rightX, p.y }};
    for (int i = 0; i < hull.vertexNumber; i++)
    {
        segment side = (segment){ hull.vertex[i], hull.vertex[(i + 1) % hull.vertexNumber] };
        if (segmentsIntersect(ray, side))
            numberOfIntersection++;
    }
    
    // 测试交点个数奇偶性。
    return ((numberOfIntersection & 1) == 1);
}


int main(int argc, char* argv[])
{
    point p;
    polygon hull;
    
    cin >> hull.vertexNumber;
    for (int i = 0; i < hull.vertexNumber; i++)
        cin >> hull.vertex[i].x >> hull.vertex[i].y;
    
    while (cin >> p.x >> p.y, p.x || p.y)
    {
        cout << p.x << " " << p.y << " " << (isPointInPolygon(p, hull) ? "true" : "false") << endl;
    }
    
    return 0;
}
