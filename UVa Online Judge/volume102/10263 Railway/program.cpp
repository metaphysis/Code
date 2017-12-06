// Railway
// UVa ID: 10263
// Verdict: Accepted
// Submission Date: 2017-12-05
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

struct point {
    double x, y;
    point (double x = 0, double y = 0): x(x), y(y) {}
    point operator + (point p) { return point(x + p.x, y + p.y); };
    point operator - (point p) { return point(x - p.x, y - p.y); };
    point operator * (double a) { return point(a * x, a * y); };
    point operator / (double a) { return point(x / a, y / a); };
};

double dot(point a, point b) { return a.x * b.x + a.y * b.y; }
double cross(point a, point b) { return a.x * b.y - b.x * a.y; }
double norm(point p) { return p.x * p.x + p.y * p.y; };
double abs(point p) { return sqrt(norm(p)); };

point project(point p, point p1, point p2)
{
    point base = p2 - p1;
    double r = dot(p - p1, base) / norm(base);
    return p1 + base * r;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    double dist, temp;
    point pm, p1, p2, pr;

    int n;
    while (cin >> pm.x >> pm.y)
    {
        cin >> n;

        cin >> p1.x >> p1.y;

        dist = abs(pm - p1);
        pr = p1;

        for (int i = 1; i <= n; i++)
        {
            cin >> p2.x >> p2.y;
            
            if (dot(p2 - p1, pm - p1) < 0.0)
            {
                temp = abs(pm - p1);
                if (temp < dist)
                {
                    pr = p1;
                    dist = temp;
                }
            }
            else if (dot(p1 - p2, pm - p2) < 0.0)
            {
                temp = abs(pm - p2);
                if (temp < dist)
                {
                    pr = p2;
                    dist = temp;
                }
            }
            else
            {
                temp = abs(cross(p2 - p1, pm - p1) / abs(p2 - p1));
                if (temp < dist)
                {
                    pr = project(pm, p1, p2);
                    dist = temp;
                }
            }
            swap(p1, p2);
        }
        
        cout << fixed << setprecision(4) << pr.x << '\n';
        cout << fixed << setprecision(4) << pr.y << '\n';
    }

    return 0;
}
