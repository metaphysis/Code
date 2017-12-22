// Polygon
// UVa ID: 634
// Verdict: Accepted
// Submission Date: 2016-08-29
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <cmath>

using namespace std;

const int MAX_VERTICES = 1100;
const int EPSILON = 0;

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
double direction(point a, point b, point c)
{
    return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
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
    
    // 跨越式相交。
    if ((d1 * d2 < 0) && (d3 * d4 < 0))
        return true;
        
    // 不相交。
    if ((d1 * d2 > 0) || (d3 * d4 > 0))
        return false;   
        
	// 共线，不论线段是否重合，均规定为不相交。
    if ((fabs(d1) <= EPSILON && fabs(d2) <= EPSILON) || (fabs(d3) <= EPSILON && fabs(d4) <= EPSILON))
        return false;
        
	// 相交于顶点，判断是否在射线上方。
    if (fabs(d1) <= EPSILON || fabs(d2) <= EPSILON || fabs(d3) <= EPSILON || fabs(d4) <= EPSILON)
        return isSideAboveRay (ray, side);

    return false;
}

bool isPointInPolygon(point &p, polygon &pg)
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
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
    
    point p;
    polygon pg;
    
    while (cin >> pg.vertexNumber, pg.vertexNumber)
    {
        for (int i = 0; i < pg.vertexNumber; i++)
            cin >> pg.vertex[i].x >> pg.vertex[i].y;
        
        cin >> p.x >> p.y;
        cout <<  (isPointInPolygon(p, pg) ? 'T' : 'F') << '\n';
    }
    
    return 0;
}
