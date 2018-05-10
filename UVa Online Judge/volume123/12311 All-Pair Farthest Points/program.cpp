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
    point operator+(point p) { return point(x + p.x, y + p.y); };
    point operator-(point p) { return point(x - p.x, y - p.y); };
    point operator*(double k) { return point(x * k, y * k); };
    point operator/(double k) { return point(x / k, y / k); };
    double distTo(point p) { return pow(x - p.x, 2) + pow(y - p.y, 2); }
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
    for (int i = 0, j = 1, n = pg.size() - 1; i < n; i++)
    {
        while (cross(pg[i + 1] - pg[i], pg[j + 1] - pg[j]) > 0)
            j = (j + 1) % n;
        double dist1 = pg[i].distTo(pg[j - 1]);
        double dist2 = pg[i].distTo(pg[j]);
        double dist3 = pg[i].distTo(pg[j + 1]);
        int r1 = j + 1, r2 = j + 2;
        cout << (j - 1) << '=' << dist1 << ' ' << j << '=' << dist2 << ' ' << (j + 1) << '=' << dist3 << '\n';
        if (r1 >= n) r1 = 1;
        if (r2 >= n) r2 = 1;
        if (dist2 > dist3) cout << r1 << '\n';
        else if (dist3 > dist2) cout << r2 << '\n';
        else cout << min(r1, r2) << '\n';
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
        }
        rotatingCalipers(pg);
    }

    return 0;
}
