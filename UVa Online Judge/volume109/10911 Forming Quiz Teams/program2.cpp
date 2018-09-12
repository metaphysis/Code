// Forming Quiz Teams
// UVa ID: 10911
// Verdict: Accepted
// Submission Date: 2018-09-12
// UVa Run Time: 0.060s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n;
    string name;
    int cases = 0, xs[16], ys[16];
    double dist[16][16], cache[1 << 16];

    while (cin >> n, n > 0)
    {
        n *= 2;
        for (int i = 0; i < n; i++)
            cin >> name >> xs[i] >> ys[i];

        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                dist[i][j] = dist[j][i] = hypot(xs[i] - xs[j], ys[i] - ys[j]);

        cout << "Case " << ++cases << ": ";

        cache[0] = 0;
        for (int k = 1; k < (1 << n); k++)
        {
            cache[k] = 1e10;
            for (int i = 0; i < n; i++)
                if (k & (1 << i))
                {
                    for (int j = i + 1; j < n; j++)
                        if (k & (1 << j))
                            cache[k] = min(cache[k], cache[k ^ (1 << i) ^ (1 << j)] + dist[i][j]);
                    break;
                }
        }
        cout << fixed << setprecision(2) << cache[(1 << n) - 1] << '\n';
    }

    return 0;
}
