// Symmetry
// UVa ID: 1595
// Verdict: Accepted
// Submission Date: 2020-04-11
// UVa Run Time: 0.010s
//
// 版权所有（C）2020，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1010;

struct point {
    int x, y;
    bool operator<(const point& p) const
    {
        if (x != p.x) return x < p.x;
        return y < p.y;
    }
} ps[1010];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, n;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> n;
        for (int i = 0; i < n; i++) cin >> ps[i].x >> ps[i].y;
        sort(ps, ps + n);
        int axis = ps[0].x + ps[n - 1].x;
        bool flag = true;
        for (int i = 0; i < n; i++)
            if (!binary_search(ps, ps + n, point{axis - ps[i].x, ps[i].y}))
            {
                flag = false;
                break;
            }
        cout << (flag ? "YES" : "NO") << '\n';
    }
    return 0;
}
