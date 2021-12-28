// Common Area
// UVa ID: 12931
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2021，邱秋。metaphysis # yeah dot net

#include<bits/stdc++.h>
using namespace std;
#define maxn 510
const double eps = 1E-8;
int sig(double d)
{
    return (d > eps) - (d < -eps);
}

struct Point
{
    double x, y;
     Point()
    {
    }
    Point(double x, double y):x(x), y(y)
    {
    }
    bool operator==(const Point & p) const
    {
        return sig(x - p.x) == 0 && sig(y - p.y) == 0;
    }
};
double cross(Point o, Point a, Point b)
{
    return (a.x - o.x) * (b.y - o.y) - (b.x - o.x) * (a.y - o.y);
}

double area(Point * ps, int n)
{
    ps[n] = ps[0];
    double res = 0;
    for (int i = 0; i < n; i++)
    {
        res += ps[i].x * ps[i + 1].y - ps[i].y * ps[i + 1].x;
    }
    return res / 2.0;
}

int lineCross(Point a, Point b, Point c, Point d, Point & p)
{
    double s1, s2;
    s1 = cross(a, b, c);
    s2 = cross(a, b, d);
    if (sig(s1) == 0 && sig(s2) == 0)
        return 2;
    if (sig(s2 - s1) == 0)
        return 0;
    p.x = (c.x * s2 - d.x * s1) / (s2 - s1);
    p.y = (c.y * s2 - d.y * s1) / (s2 - s1);
    return 1;
}

void polygon_cut(Point * p, int &n, Point a, Point b)
{
    static Point pp[maxn];
    int m = 0;
    p[n] = p[0];
    for (int i = 0; i < n; i++)
    {
        if (sig(cross(a, b, p[i])) > 0)
            pp[m++] = p[i];
        if (sig(cross(a, b, p[i])) != sig(cross(a, b, p[i + 1])))
            lineCross(a, b, p[i], p[i + 1], pp[m++]);
    }
    n = 0;
    for (int i = 0; i < m; i++)
        if (!i || !(pp[i] == pp[i - 1]))
            p[n++] = pp[i];
    while (n > 1 && p[n - 1] == p[0])
        n--;
}

double intersectArea(Point a, Point b, Point c, Point d)
{
    Point o(0, 0);
    int s1 = sig(cross(o, a, b));
    int s2 = sig(cross(o, c, d));
    if (s1 == 0 || s2 == 0)
        return 0.0;
    if (s1 == -1)
        swap(a, b);
    if (s2 == -1)
        swap(c, d);
    Point p[10] = { o, a, b };
    int n = 3;
    polygon_cut(p, n, o, c);
    polygon_cut(p, n, c, d);
    polygon_cut(p, n, d, o);
    double res = fabs(area(p, n));
    if (s1 * s2 == -1)
        res = -res;
    return res;
}

double intersectArea(Point * ps1, int n1, Point * ps2, int n2)
{
    if (area(ps1, n1) < 0)
        reverse(ps1, ps1 + n1);
    if (area(ps2, n2) < 0)
        reverse(ps2, ps2 + n2);
    ps1[n1] = ps1[0];
    ps2[n2] = ps2[0];
    double res = 0;
    for (int i = 0; i < n1; i++)
    {
        for (int j = 0; j < n2; j++)
        {
            res += intersectArea(ps1[i], ps1[i + 1], ps2[j], ps2[j + 1]);
        }
    }
    return res;
}

Point ps1[maxn], ps2[maxn];
int cases = 0, n1, n2;
int main()
{
    while (scanf("%d", &n1) != EOF)
    {
        for (int i = 0; i < n1; i++)
            scanf("%lf%lf", &ps1[i].x, &ps1[i].y);
        scanf("%d", &n2);
        for (int i = 0; i < n2; i++)
            scanf("%lf%lf", &ps2[i].x, &ps2[i].y);
        double ans = intersectArea(ps1, n1, ps2, n2);
        printf("Case %d: %s\n", ++cases, fabs(ans) > 1e-6 ? "Yes" : "No");
    }
    return 0;
}
