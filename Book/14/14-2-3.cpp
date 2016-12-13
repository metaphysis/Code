#include <iostream>
#include <cmath>

using namespace std;

const double EPSILON = 1E-7;

struct point
{
    double x, y;
};

struct segment
{
    point start, end;
};

// 使用叉积来表示线段的相对方向。
double direction(point a, point b, point c)
{
    return (c.x - a.x) * (b.y - a.y) - (b.x - a.x) * (c.y - a.y);
}

// 包围盒测试。测试点p是否在线段 ab 上。
bool pointInBox(point p, point a, point b)
{
    return ((p.x >= min(a.x, b.x)) && (p.x <= max(a.x, b.x)) &&
        (p.y >= min(a.y, b.y)) && (p.y <= max(a.y, b.y)));
}

// 判断两条线段是否相交。
bool segmentsIntersect(segment a, segment b)
{
    double d1, d2, d3, d4;
    
    d1 = direction(a.start, a.end, b.start);
    d2 = direction(a.start, a.end, b.end);
    d3 = direction(b.start, b.end, a.start);
    d4 = direction(b.start, b.end, a.end);
    
    if ((d1 * d2 < 0) && (d3 * d4) < 0)
        return true;
    if (fabs(d1) <= EPSILON && pointInBox(b.start, a.start, a.end))
        return true;
    if (fabs(d2) <= EPSILON && pointInBox(b.end, a.start, a.end))
        return true;
    if (fabs(d3) <= EPSILON && pointInBox(a.start, b.start, b.end))
        return true;
    if (fabs(d4) <= EPSILON && pointInBox(a.end, b.start, b.end))
        return true;
        
    return false;
}


int main(int argc, char* argv[])
{
    int x, y;
    segment first, second;
    
    while (cin >> x >> y, x || y)
    {
        first.start = (point){x, y};
        cin >> x >> y;
        first.end = (point){x, y};
        cin >> x >> y;
        second.start = (point){x, y};
        cin >> x >> y;
        second.end = (point){x, y};
        
        cout << (segmentsIntersect(first, second) ? "true" : "false") << endl;
    }
    
    return 0;
}
