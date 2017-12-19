// Offset Polygons
// UVa ID: 877
// Verdict: Accepted
// Submission Date: 2017-12-19
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

struct point {
    double x, y;
    point (double x = 0, double y = 0): x(x), y(y) {}
    point operator + (point p) { return point(x + p.x, y + p.y); };
    point operator - (point p) { return point(x - p.x, y - p.y); };
    point operator * (double k) { return point(x * k, y * k); };
    point operator / (double k) { return point(x / k, y / k); };
};

typedef vector<point> polygon;

double norm(point a)
{
    return a.x * a.x + a.y * a.y;
}

double abs(point a)
{
    return sqrt(norm(a));
}

double dot(point a, point b)
{
    return a.x * b.x + a.y * b.y;
}

point rotate(point p, double t)
{
    return point(p.x * cos(t) - p.y * sin(t), p.x * sin(t) + p.y * cos(t));
}

point getShiftPoint(point a, point b, point c, double d)
{
    point u = a - b, v = c - b;
    double t = acos(dot(u, v) / (abs(u) * abs(v)));
    point uu = u * (d / (sin(t / 2) * abs(u)));
    return b - rotate(uu, t / 2);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, n;
    double d;
    point vertices[20];
    
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> d >> n;

        if (c > 1) cout << '\n';
        cout << n << '\n';

        for (int i = 0; i < n; i++)
            cin >> vertices[i].x >> vertices[i].y;

        for (int i = 0; i < n; i++)
        {
            int pre = (i - 1 + n) % n, next = (i + 1) % n;
            point pr = getShiftPoint(vertices[pre], vertices[i], vertices[next], d);
            cout << fixed << setprecision(3) << pr.x << ' ' << pr.y << '\n';
        }
    }

    return 0;
}
