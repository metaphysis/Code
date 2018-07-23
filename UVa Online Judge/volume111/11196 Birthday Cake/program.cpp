// Birthday Cake
// UVa ID: 11196
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int n, m, best;

void dfs(int depth, int volume, int surface, int r, int h, int lastr)
{
    if (volume > n) return;
    if (depth == m)
    {
        if (volume == n) best = min(best, surface - lastr * lastr);
        return;
    }
    for (int ri = r; ; ri++)
    {
        for (int hi = h; ; hi++)
        {
            int v = ri * ri * hi;
            if (volume + (m - depth) * v > n) break;
            int s = 2 * ri * ri + 2 * ri * hi;
            if (depth) s -= 2 * lastr * lastr;
            dfs(depth + 1, volume + v, surface + s, ri + 1, hi + 1, ri);
        }
        if (volume + (m - depth) * ri * ri * h > n) break;
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0;
    while (cin >> n)
    {
        if (n == 0) break;
        cin >> m;
        best = 0x3f3f3f3f;
        dfs(0, 0, 0, 1, 1, 0);
        if (best == 0x3f3f3f3f) best = 0;
        cout << "Case " << ++cases << ": " << best << '\n';
    }

    return 0;
}
