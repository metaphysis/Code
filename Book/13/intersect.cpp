#include <iostream>
#include <cmath>

using namespace std;

#define EPSILON 1E-10

struct point
{
    double x, y;
    
    // 标记是否为有效交点
    bool is_valid;     
};

struct segment
{
    point start, end;
};

struct line
{
    // 使用一般形式 ax + by + c = 0 来表示直线。
    double a, b, c;
};

// 将两点表示的直线转换为一般形式表示。
line pointsToLine(point start, point end)
{
    line lr;

    // 判断两点 x 坐标是否相同，是表明直线为垂直 X 轴的直线，系数 a 规定为 1。
    if (fabs(start.x - end.x) <= EPSILON)
    {
        lr.a = 1.0;
        lr.b = 0.0;
        lr.c = -start.x;
    }
    // 直线与 X 轴不垂直，系数 b 规定为 1。
    else
    {
        lr.a = -(start.y - end.y) / (start.x - end.x);
        lr.b = 1.0;
        lr.c = -lr.a * start.x - start.y;
    }

    return lr;
}

// 判断两条直线是否平行。
bool isParallelLine(line line1, line line2)
{
    return (fabs(line1.a - line2.a) <= EPSILON) && (fabs(line1.b - line2.b) <= EPSILON);
}

// 判断两条直线是否为同一条直线。
bool isSameLine(line line1, line line2)
{
    return isParallelLine(line1, line2) && (fabs(line1.c - line2.c) <= EPSILON);
}

// 求两条直线的交点，如果存在交点则返回 true，否则返回 false。
point intersect(line line1, line line2)
{
    point pr;

    // 当两条直线平行时，认为其无交点。
    if (isParallelLine(line1, line2))
    {
        return (point){0.0, 0.0, false};
    }

    pr.is_valid = true;
    
    // 当两条直线重合时，任意取直线上一点作为交点。
    if (isSameLine(line1, line2))
    {
        // 系数 a 不为 0，取 y = 0。
        if (fabs(line1.a) > EPSILON)
        {
            pr.x = -line1.c / line1.a;
            pr.y = 0.0;
        }
        // 系数 b 不为 0，取 x = 0。
        else
        {
            pr.x = 0.0;
            pr.y = -line1.c / line1.b;
        }

        return pr;
    }

    // 两条直线相交，求出交点。
    pr.x = (line2.b * line1.c - line1.b * line2.c) / (line2.a * line1.b - line1.a * line2.b);
    if (fabs(line1.b) > EPSILON)
        pr.y = -(line1.a * pr.x + line1.c) / line1.b;
    else
        pr.y = -(line2.a * pr.x + line2.c) / line2.b;

    return pr;
}

// 将使用斜率与直线上一点的表示方式转换为标准形式。
line pointAndSlopeToLine(point p, double slope)
{
    line lr;

    // 直线与 X 轴不垂直，系数 b 规定为 1。
    lr.a = -slope;
    lr.b = 1.0;
    lr.c = -(lr.a * p.x + lr.b * p.y);

    return lr;
}

// 求经过点 pOutside 与直线 lr 垂直的直线 lp 与 lr 的交点。
point closestPoint(point p1, line lr)
{
    point p2;

    // 先判断特殊情形。
    // 若为平行于 X 轴的直线。
    if (fabs(lr.a) <= EPSILON)
    {
        p2.x = p1.x;
        p2.y = -lr.c;
    }
    // 若为垂直于 X 轴的直线。
    else if (fabs(lr.b) <= EPSILON)
    {
        p2.x = -lr.c;
        p2.y = p1.y;
    }
    else
    {
        line lp = pointAndSlopeToLine(p1, lr.b / lr.a);
        p2 = intersect(lr, lp);
    }

    return p2;
}

// 包围盒测试。
bool pointInBox(point p, point a, point b)
{
    return ((p.x >= min(a.x, b.x)) && (p.x <= max(a.x, b.x))
        && (p.y >= min(a.y, b.y)) && (p.y <= max(a.y, b.y)));
}

// 判断两条线段是否相交。
bool segmentsIntersect(segment aSegment, segment bSegment)
{
    line aLine, bLine;
    point p;

    aLine = pointsToLine(aSegment.start, aSegment.end);
    bLine = pointsToLine(bSegment.start, bSegment.end);

    if (isSameLine(aLine, bLine))
        return (pointInBox(aSegment.start, bSegment.start, bSegment.end)
            || pointInBox(aSegment.end, bSegment.start, bSegment.end));

    if (isParallelLine(aLine, bLine))
        return false;

    p = intersect(aLine, bLine);
    if (p.is_valid == false)
        return false;

    return (pointInBox(p, aSegment.start, aSegment.end) &&
        pointInBox(p, bSegment.start, bSegment.end));
}


int main(int argc, char *argv[])
{
    line lr;
    lr.a = 2.0;
    lr.b = -1.0;
    lr.c = 0.0;

    point p;
    p.x = 3.0;
    p.y = 4.0;

    point pOnLine = closestPoint(p, lr);

    cout << pOnLine.x << " " << pOnLine.y << endl;

    return 0;
}
