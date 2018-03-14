// Isolated Segments
// UVa ID: 11343
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

double cp(point a, point b, point c)
{
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

bool pointInBox(point a, point b, point p)
{
    double minx = min(a.x, b.x), maxx = max(a.x, b.x);
    double miny = min(a.y, b.y), maxy = max(a.y, b.y);
    return p.x >= minx && p.x <= maxx && p.y >= miny && p.y <= maxy;
}

struct segment
{
    point p1, p2;
    bool contains(const point &p) { return pointInBox(p1, p2, p); }
}ss[110];

bool isIntersected(segment &s1, segment &s2)
{
    double cp1 = cp(s1.p1, s1.p2, s2.p1), cp2 = cp(s1.p1, s1.p2, s2.p2);
    double cp3 = cp(s2.p1, s2.p2, s1.p1), cp4 = cp(s2.p1, s2.p2, s1.p2);

    if ((cp1 * cp2 < 0) && (cp3 * cp4) < 0) return true;
    if (fabs(cp1) <= EPSILON && s1.contains(s2.p1)) return true;
    if (fabs(cp2) <= EPSILON && s1.contains(s2.p2)) return true;
    if (fabs(cp3) <= EPSILON && s2.contains(s1.p1)) return true;
    if (fabs(cp4) <= EPSILON && s2.contains(s1.p2)) return true;

    return false;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, n, visited[110];
    cin >> cases;

    for (int c = 1; c <= cases; c++)
    {
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            cin >> ss[i].p1.x >> ss[i].p1.y;
            cin >> ss[i].p2.x >> ss[i].p2.y;
        }

        memset(visited, 0, sizeof(visited));

        int isolated = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (i == j) continue;
                if (isIntersected(ss[i], ss[j]))
                {
                    visited[i] = visited[j] = 1;
                    break;
                }
            }
            isolated += 1 - visited[i];
        }
        cout << isolated << '\n';
    }

    return 0;
}
