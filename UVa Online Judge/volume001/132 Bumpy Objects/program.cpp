// Bumpy Objects
// UVa ID: 132
// Verdict: Accepted
// Submission Date: 2015-12-11
// UVa Run Time: 0.000s
//
// 版权所有（C）2015，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

#define MAX_VERTICES 105
#define EPSILON 1E-10

struct point
{
    int x;
    int y;
    int index;
};

struct polygon
{
    int number;
    point vertex[MAX_VERTICES];
};

int crossProduct(point a, point b, point c)
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

bool ccwOrCollinear(point a, point b, point c)
{
    return ccw(a, b, c) || collinear(a, b, c);
}

bool lowerLeft(point a, point b)
{
    return (a.y == b.y) ? (a.x < b.x) : (a.y < b.y);
}

void andrewConvexHull(point vertex[], int number, polygon & hull)
{
    sort(vertex, vertex + number, lowerLeft);

    point upper[MAX_VERTICES], lower[MAX_VERTICES];
    int top;

    upper[0] = vertex[0];
    upper[1] = vertex[1];
    top = 2;
    for (int i = 2; i < number; i++)
    {
        upper[top] = vertex[i];
        while (top >= 2 && ccwOrCollinear(upper[top - 2], upper[top - 1], upper[top]))
        {
            upper[top - 1] = upper[top];
            top--;
        }
        top++;
    }

    hull.number = 0;
    for (int i = 0; i < top; i++)
        hull.vertex[hull.number++] = upper[i];

    lower[0] = vertex[number - 1];
    lower[1] = vertex[number - 2];
    top = 2;
    for (int i = number - 3; i >= 0; i--)
    {
        lower[top] = vertex[i];
        while (top >= 2 && ccwOrCollinear(lower[top - 2], lower[top - 1], lower[top]))
        {
            lower[top - 1] = lower[top];
            top--;
        }
        top++;
    }

    for (int i = 1; i < top - 1; i++)
        hull.vertex[hull.number++] = lower[i];
}

double distances(point a, point b)
{
    return pow(a.x - b.x, 2) + pow(a.y - b.y, 2);
}

// 根据余弦定理判断角 abc 是否为锐角。
bool isAcuteAngle(point a, point b, point c)
{
    double A = distances(b, c), B = distances(a, c), C = distances(a, b);
    return (A + C - B) > 0;
}

int lowestNumber(polygon pg, point center, int number)
{
    for (int i = 0; i < pg.number; i++)
        if (cw(pg.vertex[i], pg.vertex[(i + 1) % pg.number], center) &&
            isAcuteAngle(pg.vertex[i], pg.vertex[(i + 1) % pg.number], center) &&
            isAcuteAngle(pg.vertex[(i + 1) % pg.number], pg.vertex[i], center))
            number = min(number, max(pg.vertex[i].index, pg.vertex[(i + 1) % pg.number].index));

    return number;
}

int main(int argc, char *argv[])
{
    point tile[MAX_VERTICES], centerOfMass;
    polygon container;
    string name;

    while (cin >> name, name != "#")
    {
        cout << name;
        cin >> centerOfMass.x >> centerOfMass.y;

        int x, y, number = 0;
        while (cin >> x >> y, x || y)
        {
            tile[number] = (point)
            {
            x, y, number + 1};
            number++;
        }

        andrewConvexHull(tile, number, container);
        cout << " " << lowestNumber(container, centerOfMass, number) << endl;
    }

    return 0;
}
