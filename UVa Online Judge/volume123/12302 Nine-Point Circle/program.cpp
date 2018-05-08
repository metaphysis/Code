// Nine-Point Circle
// UVa ID: 12302
// Verdict: Accepted
// Submission Date: 2018-05-08
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct point {
    double x, y;
    point (double x = 0, double y = 0): x(x), y(y) {}
};

struct circle {
    double x, y, r;
    double distTo(point a) { return sqrt(pow(x - a.x, 2) + pow(y - a.y, 2)); }
};

circle getCircleFromTriangle(point &a, point &b, point &c)
{
    double A1 = a.x - b.x, B1 = a.y - b.y;
    double A2 = c.x - b.x, B2 = c.y - b.y;
    double C1 = (a.x * a.x - b.x * b.x + a.y * a.y - b.y * b.y) / 2;
    double C2 = (c.x * c.x - b.x * b.x + c.y * c.y - b.y * b.y) / 2;

    circle cc;
    cc.x = (C1 * B2 - C2 * B1) / (A1 * B2 - A2 * B1);
    cc.y = (A1 * C2 - A2 * C1) / (A1 * B2 - A2 * B1);
    cc.r = cc.distTo(a);

    return cc;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    cout.setf(ios::fixed);
    cout.precision(6);

    int x1, y1, x2, y2, x3, y3;
    
    while (cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3)
    {
        if (x1 == -1) break;
        point p1 = point((x1 + x2) / 2.0, (y1 + y2) / 2.0);
        point p2 = point((x2 + x3) / 2.0, (y2 + y3) / 2.0);
        point p3 = point((x3 + x1) / 2.0, (y3 + y1) / 2.0);
        circle cc = getCircleFromTriangle(p1, p2, p3);
        cout << cc.x << ' ' << cc.y << ' ' << cc.r << '\n';
    }

    return 0;
}
