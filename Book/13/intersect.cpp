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

struct line
{
    double a, b, c;
};

line pointsToLine(point start, point end)
{
    line lr;

    if (fabs(start.x - end.x) <= EPSILON)
    {
        lr.a = 1.0;
        lr.b = 0.0;
        lr.c = -start.x;
    }
    else
    {
        lr.a = -(start.y - end.y) / (start.x - end.x);
        lr.b = 1.0;
        lr.c = -lr.a * start.x - start.y;
    }

    return lr;
}

bool isParallelLine(line line1, line line2)
{
    return (fabs(line1.a - line2.a) <= EPSILON) && (fabs(line1.b - line2.b) <= EPSILON);
}

bool isSameLine(line line1, line line2)
{
    return isParallelLine(line1, line2) && (fabs(line1.c - line2.c) <= EPSILON);
}

point getIntersection(line line1, line line2)
{
    point pr;

    pr.x = (line2.b * line1.c - line1.b * line2.c) / (line2.a * line1.b - line1.a * line2.b);
    if (fabs(line1.b) > EPSILON)
        pr.y = -(line1.a * pr.x + line1.c) / line1.b;
    else
        pr.y = -(line2.a * pr.x + line2.c) / line2.b;

    return pr;
}

line pointAndSlopeToLine(point p, double slope)
{
    line lr;

    lr.a = -slope;
    lr.b = 1.0;
    lr.c = -(lr.a * p.x + lr.b * p.y);

    return lr;
}

point closestPoint(point p1, line lr)
{
    point p2;

    if (fabs(lr.a) <= EPSILON)
    {
        p2.x = p1.x;
        p2.y = -lr.c;
    }
    else if (fabs(lr.b) <= EPSILON)
    {
        p2.x = -lr.c;
        p2.y = p1.y;
    }
    else
    {
        line lp = pointAndSlopeToLine(p1, lr.b / lr.a);
        p2 = getIntersection(lr, lp);
    }

    return p2;
}

bool pointInBox(point p, point a, point b)
{
    return ((p.x >= min(a.x, b.x)) && (p.x <= max(a.x, b.x)) && (p.y >= min(a.y, b.y)) && (p.y <= max(a.y, b.y)));
}

bool segmentsIntersect(segment aSegment, segment bSegment)
{
    line first, second;

    first = pointsToLine(aSegment.start, aSegment.end);
    second = pointsToLine(bSegment.start, bSegment.end);

    if (isSameLine(first, second))
        return (pointInBox(aSegment.start, bSegment.start, bSegment.end) ||
            pointInBox(aSegment.end, bSegment.start, bSegment.end));

    if (isParallelLine(first, second))
        return false;

    point intersection = getIntersection(first, second);

    return (pointInBox(intersection, aSegment.start, aSegment.end) &&
        pointInBox(intersection, bSegment.start, bSegment.end));
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
