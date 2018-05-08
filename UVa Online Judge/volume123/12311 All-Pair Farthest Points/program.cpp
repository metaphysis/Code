// All-Pair Farthest Points
// UVa ID: 12311
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct point {
    double x, y;

    point (double x = 0, double y = 0): x(x), y(y) {}

    point operator + (point p) { return point(x + p.x, y + p.y); };
    point operator - (point p) { return point(x - p.x, y - p.y); };
    point operator * (double k) { return point(x * k, y * k); };
    point operator / (double k) { return point(x / k, y / k); };
    
    double distTo(point p)
    {
        return sqrt(pow(x - p.x, 2) + pow(y - p.y, 2));
    }
};

typedef vector<point> polygon;

double cross(point a, point b)
{
    return a.x * b.y - a.y * b.x;
}

double cp(point a, point b, point c)
{
    return cross(b - a, c - a);
}

void rotatingCalipers(polygon pg)
{
    pg.push_back(pg.front());
    for (int i = 0, q = 1, n = pg.size() - 1; i < n; i++)
    {
        while (cp(pg[i], pg[i + 1], pg[q + 1]) > cp(pg[i], pg[i + 1], pg[q]))
            q = (q + 1) % pg.size();
        if (q == 0) cout << 1 << '\n';
        else cout << (q + 1) << '\n';
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n;
    while (cin >> n, n > 0)
    {
        polygon pg;
        double x, y;
        for (int i = 0; i < n; i++)
        {
            cin >> x >> y;
            pg.push_back(point(x, y));
            rotatingCalipers(pg);
        }
    }

    return 0;
}
