// That Nice Euler Circuit
// UVa ID: 1342
// Verdict: Accepted
// Submission Date: 2017-08-09
// UVa Run Time: 0.020s
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

const double epsilon = 1e-7;

int dcmp(double x)
{
    if (fabs(x) < epsilon) return 0;
    return x < 0 ? -1 : 1;
}

struct point
{
    double x, y;

    point() { }
    point(double x, double y):x(x), y(y) { }

    bool operator<(point p) const
    {
        if (fabs(x - p.x) < epsilon)
            return y < p.y;
        else
            return x < p.x;
    }

    bool operator==(point p) const
    {
        return fabs(x - p.x) < epsilon && fabs(y - p.y) < epsilon;
    }
};

struct segment
{
    point p1, p2;
};

point operator+(point p1, point p2)
{
    return point(p1.x + p2.x, p1.y + p2.y);
}

point operator-(point p1, point p2)
{
    return point(p1.x - p2.x, p1.y - p2.y);
}

point operator*(point p1, double p)
{
    return point(p1.x * p, p1.y * p);
}

point operator/(point p1, double p)
{
    return point(p1.x / p, p1.y / p);
}

double dot(point p1, point p2)
{
    return p1.x * p2.x + p1.y * p2.y;
}

double cross(point p1, point p2)
{
    return p1.x * p2.y - p1.y * p2.x;
}

bool intersected(segment s1, segment s2)
{
    double c1 = cross(s1.p2 - s1.p1, s2.p1 - s1.p1);
    double c2 = cross(s1.p2 - s1.p1, s2.p2 - s1.p1);
    double c3 = cross(s2.p2 - s2.p1, s1.p1 - s2.p1);
    double c4 = cross(s2.p2 - s2.p1, s1.p2 - s2.p1);
    return dcmp(c1) * dcmp(c2) < 0 && dcmp(c3) * dcmp(c4) < 0;
}

point getIntersection(segment s1, segment s2)
{
    point p = s1.p1, v = s1.p2 - s1.p1, q = s2.p1, w = s2.p2 - s2.p1;
    point u = p - q;
    double t = cross(w, u) / cross(v, w);
    return p + v * t;
}

bool onSegment(point p, point p1, point p2)
{
    return dcmp(cross(p1 - p, p2 - p)) == 0 && dcmp(dot(p1 - p, p2 - p)) < 0;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int N, cases = 0;

    while (cin >> N, N > 0)
    {
        vector<point> points;
        vector<segment> segments;

        double x1, y1;
        for (int i = 1; i <= N; i++)
        {
            cin >> x1 >> y1;
            points.push_back(point
                {
                x1, y1});
        }

        for (int i = 1; i < points.size(); i++)
            segments.push_back(segment{points[i - 1], points[i]});

        for (int i = 0; i < segments.size(); i++)
            for (int j = 0; j < i; j++)
                if (intersected(segments[i], segments[j]))
                    points.push_back(getIntersection(segments[i], segments[j]));

        sort(points.begin(), points.end());
        points.erase(unique(points.begin(), points.end()), points.end());

        int edges = N - 1;
        for (int i = 0; i < segments.size(); i++)
            for (int j = 0; j < points.size(); j++)
                if (onSegment(points[j], segments[i].p1, segments[i].p2))
                    edges++;

        int vertices = points.size();
        int face = edges + 2 - vertices;
        cout << "Case " << ++cases << ": There are " << face << " pieces.\n";
    }

    return 0;
}
