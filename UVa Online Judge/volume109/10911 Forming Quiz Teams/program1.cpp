// Forming Quiz Teams
// UVa ID: 10911
// Verdict: Accepted
// Submission Date: 2018-09-12
// UVa Run Time: 1.070s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int n;
double dist[16][16], cache[1 << 16];

double dp(int x)
{
    if (cache[x] > -1) return cache[x];
    double minimal = 1e10;
    int mask = (1 << (n - 1)), i = n - 1, j;
    while (mask && !(x & mask))
        mask >>= 1, i--;
    if (mask)
    {
        x ^= mask, j = i;
        while (mask)
        {
            mask >>= 1, j--;
            if (x & mask)
                minimal = min(minimal, dp(x ^ mask) + dist[i][j]);
        }
    }
    return cache[x] = minimal;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0, xs[16], ys[16];
    string name;

    while (cin >> n, n > 0)
    {
        n *= 2;
        for (int i = 0; i < n; i++)
            cin >> name >> xs[i] >> ys[i];

        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                dist[i][j] = dist[j][i] = hypot(xs[i] - xs[j], ys[i] - ys[j]);

        cout << "Case " << ++cases << ": ";
        for (int i = 0; i < (1 << n); i++)
            cache[i] = -1;
        cache[0] = 0;
        cout << fixed << setprecision(2) << dp((1 << n) - 1) << '\n';
    }

    return 0;
}
