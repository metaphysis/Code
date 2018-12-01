// Crossed Ladders
// UVa ID: 10566
// Verdict: Accepted
// Submission Date: 2018-12-01
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const double EPSILON = 1e-7;

struct point
{
    double x, y;
    point (double x = 0, double y = 0): x(x), y(y) {}
};

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

bool getIntersection(line p, line q, point &pi)
{
    if (fabs(p.a * q.b - q.a * p.b) < EPSILON) return false;  
    pi.x = (q.c * p.b - p.c * q.b) / (p.a * q.b - q.a * p.b);  
    pi.y = (q.c * p.a - p.c * q.a) / (p.b * q.a - q.b * p.a);  
    return true;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    double X, Y, C;
    while (cin >> X >> Y >> C)
    {
        int cnt = 0;
        double low = 0, high = min(X, Y), width, c;
        while (true)
        {
            width = (low + high) / 2;
            point p1 = point(0, sqrt(X * X - width * width)), p2 = point(width, 0);
            point p3 = point(0, 0), p4 = point(width, sqrt(Y * Y - width * width));
            line line1 = getLine(p1, p2), line2 = getLine(p3, p4);
            point pi;
            getIntersection(line1, line2, pi);
            if (fabs(pi.y - C) < EPSILON || cnt++ > 40) break;
            if (pi.y > C) low = width;
            else high = width;
        }
        cout << fixed << setprecision(3) << width << '\n';
    }

    return 0;
}
