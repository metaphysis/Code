// Pick-up Sticks
// UVa ID: 10902
// Verdict: Accepted
// Submission Date: 2017-12-09
// UVa Run Time: 0.120s
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
    int idx;
    point p1, p2;
    bool contains(const point &p) { return pointInBox(p1, p2, p); }
};

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

    int n;
    vector<segment> sticks;
    
    while (cin >> n, n > 0)
    {
        sticks.clear();
        for (int i = 1; i <= n; i++)
        {
            segment s;
            s.idx = i;
            cin >> s.p1.x >> s.p1.y >> s.p2.x >> s.p2.y;
            for (int j = sticks.size() - 1; j >= 0; j--)
            {
                if (isIntersected(sticks[j], s))
                    sticks.erase(sticks.begin() + j);
            }
            sticks.push_back(s);
        }
        cout << "Top sticks: ";
        for (int i = 0; i < sticks.size(); i++)
        {
            if (i) cout << ", ";
            cout << sticks[i].idx;
        }
        cout << ".\n";
    }

    return 0;
}
