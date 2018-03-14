// An Easy Task
// UVa ID: 11068
// Verdict: Accepted
// Submission Date: 2017-12-07
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

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
    cout << fixed << setprecision(2);

    line p, q;
    while (true)
    {
        cin >> p.a >> p.b >> p.c;
        cin >> q.a >> q.b >> q.c;

        if (p.a == 0 && p.b == 0 && p.c == 0 && q.a == 0 && q.b == 0 && q.c == 0)
            break;

        p.c = -p.c, q.c = -q.c;

        point pi;
        if (!getIntersection(p, q, pi)) cout << "No fixed point exists.\n";
        else
        {
            cout << "The fixed point is at ";
            cout << pi.x << ' ';
            cout << pi.y << ".\n";
        }
    }

    return 0;
}
