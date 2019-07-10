// Distant Galaxy
// UVa ID: 1382
// Verdict: Accepted
// Submission Date: 2019-07-10
// UVa Run Time: 0.010s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 110, INF = 0x3f3f3f3f;

struct point
{
    int x, y;
    bool operator<(const point &p) const
    {
        if (x != p.x) return x < p.x;
        return y < p.y;
    }
} ps[MAXN];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n, cases = 0;
    while (cin >> n, n > 0)
    {
        for (int i = 0; i < n; i++) cin >> ps[i].x >> ps[i].y;
        sort(ps, ps + n);
        int stars = 1;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
            {
                int min_y = min(ps[i].y, ps[j].y), max_y = max(ps[i].y, ps[j].y);
                int left_i = 0, on_i = 0, in_i = 0, pre_x = -INF, max_diff = 0;
                for (int k = 0; k < n; k++)
                {
                    if (ps[k].y < min_y || ps[k].y > max_y) continue;
                    if (ps[k].x != pre_x)
                    {
                        stars = max(stars, left_i + on_i + max_diff);
                        pre_x = ps[k].x;
                        max_diff = max(max_diff, -left_i + in_i);
                        left_i += on_i - in_i;
                        on_i = in_i = 0;
                    }
                    if (ps[k].x == pre_x)
                    {
                        on_i++;
                        if (ps[k].y > min_y && ps[k].y < max_y) in_i++;
                    }
                }
                stars = max(stars, left_i + on_i + max_diff);
            }
        cout << "Case " << ++cases << ": " << stars << '\n';
    }

    return 0;
}
