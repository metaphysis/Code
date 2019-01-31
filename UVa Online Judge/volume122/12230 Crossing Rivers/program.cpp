// Crossing Rivers
// UVa ID: 12230
// Verdict: Accepted
// Submission Date: 2019-01-31
// UVa Run Time: 0.000s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct river
{
    int p, L, v;
    bool operator<(const river &r) const { return p < r.p; }
} rivers[16];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0, n, D;
    while (cin >> n >> D)
    {
        if (D == 0) break;
        cout << "Case " << ++cases << ": ";
        for (int i = 0; i < n; i++)
            cin >> rivers[i].p >> rivers[i].L >> rivers[i].v;
        sort(rivers, rivers + n);
        double elapsed = 0;
        int W = 0;
        for (int i = 0; i < n; i++)
        {
            elapsed += 2.0 * rivers[i].L / rivers[i].v;
            W += rivers[i].L;
        }
        elapsed += 1.0 * (D - W);
        cout << fixed << setprecision(3) << elapsed << '\n';
        cout << '\n';
    }

    return 0;
}
