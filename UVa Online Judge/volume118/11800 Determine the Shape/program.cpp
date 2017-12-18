// Determine the Shape
// UVa ID: 11800
// Verdict: Accepted
// Submission Date: 2017-12-18
// UVa Run Time: 0.060s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

struct point {
    int x, y;
    point (int x = 0, int y = 0): x(x), y(y) {}
    point operator + (point p) { return point(x + p.x, y + p.y); };
    point operator - (point p) { return point(x - p.x, y - p.y); };
};

int norm(point a)
{
	return a.x * a.x + a.y * a.y;
}

int dot(point a, point b)
{
    return a.x * b.x + a.y * b.y;
}

int cross(point a, point b)
{
    return a.x * b.y - a.y * b.x;
}

point pr;

bool cmp(point &p1, point &p2)
{
    double a1 = atan2(p1.y - pr.y, p1.x - pr.x);
    double a2 = atan2(p2.y - pr.y, p2.x - pr.x);
    if (a1 != a2) return a1 < a2;
    return norm(p1 - pr) < norm(p2 - pr);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    point ps[4];
    int sides[4], cases;
    
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cout << "Case " << c << ": ";

        cin >> ps[0].x >> ps[0].y;
        pr.x = ps[0].x, pr.y = ps[0].y;
        for (int i = 1; i <= 3; i++)
        {
            cin >> ps[i].x >> ps[i].y;
            if (ps[i].y < pr.y || ps[i].y == pr.y && ps[i].x < pr.x)
                pr.x = ps[i].x, pr.y = ps[i].y;
        }
        sort(ps, ps + 4, cmp);

        for (int i = 0; i < 4; i++)
            sides[i] = norm(ps[i] - ps[(i + 1) % 4]);
        
        if (sides[0] == sides[1] && sides[1] == sides[2] && sides[2] == sides[3])
        {
            if (dot(ps[0] - ps[1], ps[2] - ps[1]) == 0)
            {
                cout << "Square\n";
                continue;
            }
        }
        
        if (sides[0] == sides[2] && sides[1] == sides[3])
        {
            if (dot(ps[0] - ps[1], ps[2] - ps[1]) == 0)
            {
                cout << "Rectangle\n";
                continue;
            }
        }
        
        if (sides[0] == sides[1] && sides[1] == sides[2] && sides[2] == sides[3])
        {
            cout << "Rhombus\n";
            continue;
        }
        
        if (sides[0] == sides[2] && sides[1] == sides[3])
        {
            cout << "Parallelogram\n";
            continue;
        }

        if (cross(ps[1] - ps[0], ps[2] - ps[3]) == 0 || cross(ps[2] - ps[1], ps[3] - ps[0]) == 0)
        {
            cout << "Trapezium\n";
            continue;
        }

        cout << "Ordinary Quadrilateral\n";
    }

    return 0;
}
