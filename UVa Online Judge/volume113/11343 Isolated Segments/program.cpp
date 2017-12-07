// Isolated Segments
// UVa ID: 11343
// Verdict: Wrong Answer
// Submission Date: 2017-12-07
// UVa Run Time: 0.000s
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

const double EPSILON = 1e-7;

struct point
{
    double x, y;
    point (double x = 0, double y = 0): x(x), y(y) {}
};

bool pointInBox(point a, point b, point p)
{
    return (p.x >= min(a.x, b.x)) && (p.x <= max(a.x, b.x)) &&
        (p.y >= min(a.y, b.y)) && (p.y <= max(a.y, b.y));
}

struct segment
{
    point p1, p2;
    bool contains(const point &p) { return pointInBox(p1, p2, p); }
}ss[110];

struct line
{
    double a, b, c;
    line (double a = 0, double b = 0, double c = 0): a(a), b(b), c(c) {}
};

line getLine(double x1, double y1, double x2, double y2)
{
    return line(y2 - y1, x1 - x2, y1 * (x2 - x1) - x1 * (y2 - y1));
}

line getLine(point p, point q)
{
    return getLine(p.x, p.y, q.x, q.y);
}

point getIntersection(line p, line q)
{
    point pi;
    pi.x = (p.b * q.c - p.c * q.b) / (p.a * q.b - p.b * q.a);  
    pi.y = (p.a * q.c - p.c * q.a) / (p.b * q.a - p.a * q.b);
    return pi; 
}

double cp(point a, point b, point c)
{
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

bool isIntersected(segment s1, segment s2)
{
    line p = getLine(s1.p1, s1.p2), q = getLine(s2.p1, s2.p2);

    if (fabs(p.a * q.b - q.a * p.b) < EPSILON)
    {
        if (fabs(cp(s1.p1, s1.p2, s2.p1)) < EPSILON)
            return s1.contains(s2.p1) || s1.contains(s2.p2);
        return false;
    }

	point pi = getIntersection(p, q);
	return s1.contains(pi) && s2.contains(pi);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, n, visited[110];
    cin >> cases;

    for (int c = 1; c <= cases; c++)
    {
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            cin >> ss[i].p1.x >> ss[i].p1.y;
            cin >> ss[i].p2.x >> ss[i].p2.y;
        }

        memset(visited, 0, sizeof(visited));

        int isolated = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (i == j) continue;
                if (isIntersected(ss[i], ss[j]))
                {
                    visited[i] = visited[j] = 1;
                    break;
                }
            }
            isolated += 1 - visited[i];
        }
        cout << isolated << '\n';
    }

    return 0;
}
