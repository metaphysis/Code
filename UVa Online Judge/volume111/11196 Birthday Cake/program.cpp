// Birthday Cake
// UVa ID: 11196
// Verdict: Accepted
// Submission Date: 2019-07-10
// UVa Run Time: 0.170s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int n, m, best;

void dfs(int depth, int volume, int surface, int r, int h)
{
    if (volume > n || surface >= best) return;
    if (depth == m) {
        if (volume == n) best = min(best, surface);
        return;
    }
    if (depth) {
        int least = (n - volume) * 2 / r;
        if (surface + least >= best) return;
    }
    int maxr = sqrt(1.0 * (n - volume) / (m - depth));
    for (int ri = min(maxr, r); ri >= (m - depth); ri--) {
        if (volume + ri * ri * (m - depth) > n) break;
        int maxh = (n - volume) / (ri * ri);
        for (int hi = min(maxh, h); hi >= (m - depth); hi--) {
            if (volume + (m - depth) * (m - depth) * hi > n) break;
            int volumeDiff = ri * ri * hi, areaDiff = 2 * ri * hi;
            if (!depth) areaDiff += ri * ri;
            int least = (n - volume - volumeDiff) * 2 / ri;
            if (surface + least >= best) break;
            dfs(depth + 1, volume + volumeDiff, surface + areaDiff, ri - 1, hi - 1);
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0;
    while (cin >> n) {
        if (n == 0) break;
        cin >> m;
        best = 4 * n;
        dfs(0, 0, 0, sqrt(n), n);
        if (best == (4 * n)) best = 0;
        cout << "Case " << ++cases << ": " << best << '\n';
    }

    return 0;
}
