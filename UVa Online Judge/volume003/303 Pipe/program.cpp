// Pipe
// UVa IDs: 303
// Verdict: Accepted
// Submission Date: 2016-07-09
// UVa Run Time: 0.010s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

using namespace std;

const double EPSILON = 1E-7;

struct point
{
    double x, y;
};

struct line
{
    double a, b, c;
};

double crossProduct(point a, point b, point c)
{
	return (c.x - a.x) * (b.y - a.y) - (b.x - a.x) * (c.y - a.y);
}

bool cw(point a, point b, point c)
{
	return crossProduct(a, b, c) > EPSILON;
}

bool ccw(point a, point b, point c)
{
	return crossProduct(a, b, c) < -EPSILON;
}

line pointsToLine(point from, point to)
{
    line lr;

    if (fabs(from.x - to.x) <= EPSILON)
    {
        lr.a = 1.0;
        lr.b = 0.0;
        lr.c = -from.x;
    }
    else
    {
        lr.a = -(from.y - to.y) / (from.x - to.x);
        lr.b = 1.0;
        lr.c = -lr.a * from.x - from.y;
    }

    return lr;
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

bool pointInBox(point p, point a, point b)
{
    return ((p.x >= min(a.x, b.x)) && (p.x <= max(a.x, b.x)) && (p.y >= min(a.y, b.y)) && (p.y <= max(a.y, b.y)));
}

vector<point> upper, lower;

double getRightmostX(point from, point to)
{
    double rightmostX = upper.front().x;

    for (int rightmost = 0; rightmost < upper.size(); rightmost++)
        if (cw(from, to, upper[rightmost]) || ccw(from, to, lower[rightmost]))
        {
            if (rightmost == 0)
                return rightmostX;

            line line1 = pointsToLine(from, to);
            line line2 = pointsToLine(lower[rightmost - 1], lower[rightmost]);
            line line3 = pointsToLine(upper[rightmost - 1], upper[rightmost]);

            point point1 = getIntersection(line1, line2);
            if (pointInBox(point1, lower[rightmost - 1], lower[rightmost]))
                rightmostX = max(rightmostX, point1.x);
            
            point point2 = getIntersection(line1, line3);
            if (pointInBox(point2, upper[rightmost - 1], upper[rightmost]))
                rightmostX = max(rightmostX, point2.x);
                
            return rightmostX;
        }
    
    return upper.back().x + fabs(upper.back().x);
}

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    int n;
    while (cin >> n, n)
    {
        upper.resize(n), lower.resize(n);
        for (int i = 0; i < n; i++)
        {
            cin >> upper[i].x >> upper[i].y;
            lower[i].x = upper[i].x;
            lower[i].y = upper[i].y - 1.0;
        }
        
        double rightmostX = upper.front().x;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
            {
                rightmostX = max(rightmostX, getRightmostX(upper[i], lower[j]));
                rightmostX = max(rightmostX, getRightmostX(lower[i], upper[j]));
            }

        if (rightmostX >= upper.back().x)
            cout << "Through all the pipe." << endl;
        else
            cout << fixed << setprecision(2) << rightmostX << endl;
    }
    
	return 0;
}
