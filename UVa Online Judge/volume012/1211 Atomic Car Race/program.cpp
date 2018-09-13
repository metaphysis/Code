// Atomic Car Race
// UVa ID: 1211
// Verdict: Accepted
// Submission Date: 2018-09-14
// UVa Run Time: 0.550s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int n;
int ai[110] = {}, r;
double b, v, e, f;
double dist[110][110], cache[110];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0;
    while (cin >> n, n > 0)
    {
        for (int i = 1; i <= n; i++)
            cin >> ai[i];
        cin >> b >> r >> v >> e >> f;

        ai[0] = 0;
        for (int i = 0; i <= n; i++)
            for (int j = i + 1; j <= n; j++)
            {
                dist[i][j] = 0;
                for (int x = 0; x < (ai[j] - ai[i]); x++)
                {
                    if (x < r) dist[i][j] += 1.0 / (v - f * (r - x));
                    else dist[i][j] += 1.0 / (v - e * (x - r));
                }
                dist[j][i] = dist[i][j];
            }

        cache[0] = 0;
        for (int i = 1; i <= n; i++)
        {
            cache[i] = 1e10;
            for (int j = 0; j < i; j++)
                cache[i] = min(cache[i], cache[j] + (j ? b : 0) + dist[j][i]);
        }
        cout << fixed << setprecision(4) << cache[n] << endl;
    }

    return 0;
}
