// Orchard Trees
// UVa ID: 143
// Verdict: Accepted
// Submission Date: 2016-01-21
// UVa Run Time: 0.099s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

const double EPSILON = 1E-9;

struct point
{
    double x, y;
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

bool collinear(point a, point b, point c)
{
    return fabs(crossProduct(a, b, c)) <= EPSILON;
}

// 包围盒测试。
bool pointInBox(point p, point a, point b)
{
    return ((p.x >= min(a.x, b.x)) && (p.x <= max(a.x, b.x))
        && (p.y >= min(a.y, b.y)) && (p.y <= max(a.y, b.y)));
}

int main(int argc, char *argv[])
{
    point a, b, c;
    while (true)
    {
        cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y;

        if (a.x == 0 && a.y == 0 && b.x == 0 && b.y == 0 & c.x == 0 && c.y == 0)
            break;

        int counter = 0;
        int minX, maxX, minY, maxY;
        
        minX = min(ceil(a.x), min(ceil(b.x), ceil(c.x)));
        maxX = max(floor(a.x), max(floor(b.x), floor(c.x)));
        minY = min(ceil(a.y), min(ceil(b.y), ceil(c.y)));
        maxY = max(floor(a.y), max(floor(b.y), floor(c.y)));

        for (int i = max(minX, 1); i <= min(maxX, 99); i++)
            for (int j = max(minY, 1); j <= min(maxY, 99); j++)
            {
                point tree = (point) { i, j };
                if ((collinear(a, b, tree) && pointInBox(tree, a, b)) ||
                    (collinear(b, c, tree) && pointInBox(tree, b, c)) ||
                    (collinear(c, a, tree) && pointInBox(tree, c, a)))
                    counter++;
                else
                {
                    if ((cw(a, b, tree) && cw(b, c, tree) && cw(c, a, tree)) ||
                        (ccw(a, b, tree) && ccw(b, c, tree) && ccw(c, a, tree)))
                            counter++;
                }
            }

        cout << setw(4) << right << counter << "\n";
    }

    return 0;
}
