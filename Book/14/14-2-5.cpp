#include <iostream>
#include <cmath>

using namespace std;

const int MAX_VERTICES = 100;
const double EPSILON = 1E-7;

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
    point vertex[MAX_VERTICES];
};

// 使用叉积来表示线段的相对方向。
double crossProduct(point a, point b, point c)
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
    double cp1, cp2, cp3, cp4;
    
    cp1 = crossProduct(ray.start, ray.end, side.start);
    cp2 = crossProduct(ray.start, ray.end, side.end);
    cp3 = crossProduct(side.start, side.end, ray.start);
    cp4 = crossProduct(side.start, side.end, ray.end);
    
    // 跨越式相交。
    if ((cp1 * cp2 < 0) && (cp3 * cp4 < 0)) return true;
        
    // 不相交。
    if ((cp1 * cp2 > 0) || (cp3 * cp4 > 0)) return false;   
        
	// 共线，不论是否重合，均判断为不相交。
    if ((fabs(cp1) <= EPSILON && fabs(cp2) <= EPSILON) ||
        (fabs(cp3) <= EPSILON && fabs(cp4) <= EPSILON))
        return false;
        
	// 相交于顶点，判断是否在射线上方。
    if (fabs(cp1) <= EPSILON || fabs(cp2) <= EPSILON ||
        fabs(cp3) <= EPSILON || fabs(cp4) <= EPSILON)
        return isSideAboveRay (ray, side);

    return false;
}

bool isPointInPolygon(point p, polygon pg)
{
    // 找到多边形顶点中位于最右边的点的横坐标。
    double rightX = pg.vertex[0].x;
    for (int i = 0; i < pg.vertexNumber; i++)
    {
        if (pg.vertex[i].x > rightX)
            rightX = pg.vertex[i].x;
    }
    
    int numberOfIntersection = 0;
    segment ray = (segment){ p, (point){ 2 * rightX, p.y }};
    for (int i = 0; i < pg.vertexNumber; i++)
    {
        segment side = (segment){ pg.vertex[i], pg.vertex[(i + 1) % pg.vertexNumber] };
        if (segmentsIntersect(ray, side))
            numberOfIntersection++;
    }

    // 测试交点个数奇偶性。
    return ((numberOfIntersection & 1) == 1);
}


int main(int argc, char* argv[])
{
    point p;
    polygon pg;
    
    cin >> pg.vertexNumber;
    for (int i = 0; i < pg.vertexNumber; i++)
        cin >> pg.vertex[i].x >> pg.vertex[i].y;
    
    while (cin >> p.x >> p.y, p.x || p.y)
    {
        cout << p.x << " " << p.y << " " << (isPointInPolygon(p, pg) ? "true" : "false") << '\n';
    }
    
    return 0;
}
