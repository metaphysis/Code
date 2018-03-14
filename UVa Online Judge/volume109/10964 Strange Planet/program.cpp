// Strange Planet
// UVa ID: 10964
// Verdict: Accepted
// Submission Date: 2018-03-14
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net
//
// From center to left: 0, 4, 12, 24, 40, 60, 84, ... => 2 * (n - 1) * n, n >= 1.

#include <bits/stdc++.h>

using namespace std;

struct point
{
    int x, y;
    point (int x = 0, int y = 0): x(x), y(y) {}
    double distTo(point &a)
    {
        return sqrt(pow(x - a.x, 2) + pow(y - a.y, 2));
    }
};

const int MAXN = 23000;

int anchor[MAXN], offset[4][2] = {{1, -1}, {1, 1}, {-1, 1}, {-1, -1}};

point translate(int n)
{
    int k = lower_bound(anchor, anchor + MAXN, n) - anchor;
    int top = anchor[k];
    point p = point(-k, 0);
    for (int i = 0; i < 4; i++)
    {
        if (n >= top - k)
        {
            int diff = top - n;
            p.x += diff * offset[i][0], p.y += diff * offset[i][1];
            break;
        }
        p.x += k * offset[i][0], p.y += k * offset[i][1];
        top -= k;
    }
    return p;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    for (int i = 1; i < 23000; i++)
        anchor[i - 1] = 2 * (i - 1) * i;

    int a, b;
    while (cin >> a >> b)
    {
        if (a == -1 && b == -1) break;
        point p1 = translate(a), p2 = translate(b);
        cout << fixed << setprecision(2) << p1.distTo(p2) << '\n';
    }

    return 0;
}
