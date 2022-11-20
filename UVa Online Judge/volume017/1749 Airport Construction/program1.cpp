#include<bits/stdc++.h>
#define maxn 205
using namespace std;
const double eps = 1e-9;
int n;
double ans;
int sgn(double x)
{
    return x > eps ? 1 : x < -eps ? -1 : 0;
}

struct Point
{
    double x, y;
   Point(double x = 0, double y = 0):x(x), y(y)
    {
    }
    Point operator -(const Point & p)
    {
        return Point(x - p.x, y - p.y);
    }
    Point operator +(const Point & p)
    {
        return Point(x + p.x, y + p.y);
    }
    double operator *(const Point & p)
    {
        return x * p.y - y * p.x;
    }
    double len()
    {
        return sqrt(x * x + y * y);
    }
}

a[maxn];
struct Line
{
    Point p, v;
     Line(Point p, Point v):p(p), v(v)
    {
    }
};
double Length(Line a, Line b)
{
    return b.v * (a.p - b.p) / (a.v * b.v) * a.v.len();
}

pair<double, int> P[maxn];
void solve(Line L)
{
    int cnt = 0;
    for (int i = 1; i <= n; i++)
    {
        int d1 = sgn(L.v * (a[i] - L.p)), d2 = sgn(L.v * (a[i + 1] - L.p));
        if (d1 == d2)
            continue;
        P[++cnt] = make_pair(Length(L, Line(a[i], a[i + 1] - a[i])), (d1 > d2 ? 1 : -1) * (d1
                && d2 ? 2 : 1));
    }
    sort(P + 1, P + 1 + cnt);
    int flg = 0;
    double len = 0;
    for (int i = 1; i <= cnt; i++)
    {
        if (flg)
            len += P[i].first - P[i - 1].first;
        else
            ans = max(ans, len), len = 0;
        flg += P[i].second;
    }
    ans = max(ans, len);
}

int main()
{
    while (cin >> n)
    {
        ans = 0;
        for (int i = 1; i <= n; i++) cin >> a[i].x >> a[i].y;
        a[n + 1] = a[1];
        for (int i = 1; i <= n; i++)
            for (int j = i + 1; j <= n; j++)
                solve(Line(a[i], a[j] - a[i]));
        cout << fixed << setprecision(9) << ans << '\n';
    }
}
