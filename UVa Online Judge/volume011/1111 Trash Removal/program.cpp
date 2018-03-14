// Trash Removal
// UVa ID: 1111
// Verdict: Accepted
// Submission Date: 2017-12-23
// UVa Run Time: 0.120s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct point {
    double x, y;
    point (double x = 0, double y = 0): x(x), y(y) {}
    point operator + (point p) { return point(x + p.x, y + p.y); };
    point operator - (point p) { return point(x - p.x, y - p.y); };
    point operator * (double a) { return point(a * x, a * y); };
    point operator / (double a) { return point(x / a, y / a); };
}vertices[110];

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

double cross(point a, point b)
{
    return a.x * b.y - a.y * b.x;
}

double cp(point a, point b, point c)
{
    return cross(b - a, c - a);
}

bool cw(point a, point b, point c)
{
    return cp(a, b, c) < 0;
}

double getDistPL(point p, point p1, point p2)
{
	return fabs(cross(p2 - p1, p - p1) / abs(p2 - p1));
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n, cases = 0;
    
    while (cin >> n, n > 0)
    {
        for (int i = 0; i < n; i++)
        {
            cin >> vertices[i].x >> vertices[i].y;
        }
        
        double mostH = 1e9;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
            {
                double maxLeft = 0, maxRight = 0;
                for (int k = 0; k < n; k++)
                {
                    double h = getDistPL(vertices[k], vertices[i], vertices[j]);
                    if (cw(vertices[i], vertices[j], vertices[k]))
                        maxLeft = max(maxLeft, h);
                    else
                        maxRight = max(maxRight, h);
                    if (maxLeft + maxRight > mostH) break;
                }
                mostH = min(mostH, maxLeft + maxRight);
            }

        cout << "Case " << ++cases << ": " << fixed << setprecision(2) << mostH << '\n';
    }

    return 0;
}
