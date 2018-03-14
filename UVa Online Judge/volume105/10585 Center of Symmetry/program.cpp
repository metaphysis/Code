// Center of Symmetry
// UVa ID: 10585
// Verdict: Accepted
// Submission Date: 2017-12-06
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct point
{
    int x, y;
    point (int x = 0, int y = 0): x(x), y(y) {}
    
    bool operator<(const point &p) const
    {
        if (x != p.x) return x < p.x;
        return y < p.y;
    }
    
    bool operator==(const point &p) const
    {
        return x == p.x && y == p.y;
    }
} points[10001];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        int n;
        cin >> n;
        
        int minx = 100000000, maxx = -100000000, miny = 100000000, maxy = -100000000;
        for (int i = 0; i < n; i++)
        {
            cin >> points[i].x >> points[i].y;
            points[i].x *= 2, points[i].y *= 2;
            minx = min(minx, points[i].x), maxx = max(maxx, points[i].x);
            miny = min(miny, points[i].y), maxy = max(maxy, points[i].y);
        }
        
        point center;
        center.x = (minx + maxx) / 2, center.y = (miny + maxy) / 2;
        
        sort(points, points + n);
        
        bool yes = 1;
        for (int i = 0; i < n; i++)
        {
            point brother(2 * center.x - points[i].x, 2 * center.y - points[i].y);
            if (!binary_search(points, points + n, brother))
            {
                yes = 0;
                break;
            }
        }
        cout << (yes ? "yes" : "no") << '\n';
    }

    return 0;
}
