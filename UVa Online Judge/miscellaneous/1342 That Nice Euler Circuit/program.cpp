// That Nice Euler Circuit
// UVa ID: 1342
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net
//
// 欧拉公式，对于连通平面图，有：v + f - e = 2。

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

const double EPSILON = 1E-7;

struct point
{
    double x, y;
    
    bool operator == (point p)
    {
        return fabs(x - p.x) < EPSILON && fabs(y - p.y) < EPSILON;
    }
};

// 叉积。
int crossProduct(point a, point b, point c)
{
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

// 从点a向点b望去，点c位于线段ab的右侧，返回true。
bool cw(point a, point b, point c)
{
	return crossProduct(a, b, c) < -EPSILON;
}
// 从点a向点b望去，点c位于线段ab的左侧时，返回true。
bool ccw(point a, point b, point c)
{
	return crossProduct(a, b, c) > EPSILON;
}

struct segment
{
    point p1, p2;

    bool contains(point p)
    {
        return p.x >= min(p1.x, p2.x) && p.x <= max(p1.x, p2.x) &&
            p.y >= min(p1.y, p2.y) && p.y <= max(p1.y, p2.y);
    }
};

bool intersected(segment s1, segment s2)
{
    double cp1, cp2, cp3, cp4;

    cp1 = crossProduct(s1.p1, s1.p2, s2.p1);
    cp2 = crossProduct(s1.p1, s1.p2, s2.p2);
    cp3 = crossProduct(s2.p1, s2.p2, s1.p1);
    cp4 = crossProduct(s2.p1, s2.p2, s1.p2);
    
    if ((cp1 * cp2 < 0) && (cp3 * cp4) < 0) return true;
    if (fabs(cp1) < EPSILON && s1.contains(s2.p1)) return true;
    if (fabs(cp2) < EPSILON && s1.contains(s2.p2)) return true;
    if (fabs(cp3) < EPSILON && s2.contains(s1.p1)) return true;
    if (fabs(cp4) < EPSILON && s2.contains(s1.p2)) return true;
        
    return false;
}

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

int main(int argc, char *argv[])
{
    //cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int N, cases = 0;

    while (cin >> N, N > 0)
    {
        vector<point> points;
        vector<segment> segments;
        
        double x1, y1, x2, y2, x3, y3;
        cin >> x1 >> y1 >> x2 >> y2;
        
        point p1 = point{x1, y1}, p2 = point{x2, y2};
        points.push_back(p1);
        points.push_back(p2);
        segments.push_back(segment{p1, p2});
        
        int edges = 1;

        for (int i = 3; i <= N; i++)
        {
            cin >> x3 >> y3;
            
            segment s2 = segment{point{x2, y2}, point{x3, y3}};

            for (int j = 0; j < segments.size() - 1; j++)
            {
                if (i == N && j == 0) continue;

                if (intersected(segments[j], s2))
                {
                    line line1 = pointsToLine(segments[j].p1, segments[j].p2);
                    line line2 = pointsToLine(s2.p1, s2.p2);
                    
                    point p3 = getIntersection(line1, line2);
                    
                    if (find(points.begin(), points.end(), p3) != points.end())
                        edges += 1;
                    else
                    {
                        edges += 2;
                        points.push_back(p3);
                    }
                }
            }
            
            edges += 1;
            
            if (i != N) points.push_back(point{x3, y3});
            segments.push_back(s2);

            x2 = x3, y2 = y3;
        }

        int f = edges + 2 - points.size();
        cout << "Case " << ++cases << ": There are " << f << " pieces.\n";
    }
    
    return 0;
}
