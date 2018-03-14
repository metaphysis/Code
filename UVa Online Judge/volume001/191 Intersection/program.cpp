// Intersection
// UVa ID: 191
// Verdict: Accepted
// Submission Date: 2016-03-14
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct point
{
    int x, y;
};

struct segment
{
    point start, end;
};

// 包围盒测试。测试点p是否在线段ab上。
bool pointInBox(point p, point a, point b)
{
    return ((p.x >= min(a.x, b.x)) && (p.x <= max(a.x, b.x))
        && (p.y >= min(a.y, b.y)) && (p.y <= max(a.y, b.y)));
}

double direction(point a, point b, point c)
{
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

// 判断两条线段是否相交。
bool segmentsIntersect(segment a, segment b)
{
    double d1, d2, d3, d4;
    
    d1 = direction(a.start, a.end, b.start);
    d2 = direction(a.start, a.end, b.end);
    d3 = direction(b.start, b.end, a.start);
    d4 = direction(b.start, b.end, a.end);
    
    if ((d1 * d2 < 0) && (d3 * d4 < 0))
        return true;

    if (d1 == 0 && pointInBox(b.start, a.start, a.end))
        return true;

    if (d2 == 0 && pointInBox(b.end, a.start, a.end))
        return true;

    if (d3 == 0 && pointInBox(a.start, b.start, b.end))
        return true;

    if (d4 == 0 && pointInBox(a.end, b.start, b.end))
        return true;
        
    return false;
}

int main(int argc, char *argv[])
{
    int n, xstart, ystart, xend, yend, xleft, ytop, xright, ybottom;
    cin >> n;
    while (n > 0)
    {
        cin >> xstart >> ystart >> xend >> yend >> xleft >> ytop >> xright >> ybottom;
        segment line = (segment){(point){xstart, ystart}, (point){xend, yend}};

        point leftTop = (point){xleft, ytop};
        point rightTop = (point){xright, ytop};
        point leftBottom = (point){xleft, ybottom};
        point rightBottom = (point){xright, ybottom};
        
        bool intersected = false;
        
        if (segmentsIntersect(line, (segment){leftTop, rightTop}))
            intersected = true;
        if (segmentsIntersect(line, (segment){leftBottom, rightBottom}))
            intersected = true;
        if (segmentsIntersect(line, (segment){leftTop, leftBottom}))
            intersected = true;
        if (segmentsIntersect(line, (segment){rightTop, rightBottom}))
            intersected = true;
        if (min(xleft, xright) <= xstart && xstart <= max(xleft, xright) &&
            min(ytop, ybottom) <= ystart && ystart <= max(ytop, ybottom))
            intersected = true;
        cout << (intersected ? "T\n" : "F\n");
        
        n--;
    }
    
	return 0;
}
