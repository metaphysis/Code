// Philip J. Fry Problem
// UVa ID: 12324
// Verdict: Accepted
// Submission Date: 2018-09-12
// UVa Run Time: 0.020s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f;

int n, duration[110], spheres[110], cache[110][110];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> n, n > 0)
    {
        for (int i = 0; i < n; i++)
            cin >> duration[i] >> spheres[i];
        memset(cache, 0x3f, sizeof(cache));
        cache[0][spheres[0]] = duration[0];
        for (int i = 0; i < n - 1; i++)
            for (int j = 0; j <= n; j++)
            {
                if (cache[i][j] == INF) continue;
                // Don't use the sphere of dark matter for next trip
                int *tmp = &cache[i + 1][min(j + spheres[i + 1], n)];
                *tmp = min(*tmp, cache[i][j] + duration[i + 1]);
                // Use the sphere of dark matter for next trip
                if (j)
                {
                    // The redundant spheres is useless
                    tmp = &cache[i + 1][min(j - 1 + spheres[i + 1], n)];
                    *tmp = min(*tmp, cache[i][j] + duration[i + 1] / 2);
                }
            }
        int minimal = INF;
        for (int i = 0; i <= n; i++)
            minimal = min(minimal, cache[n - 1][i]);
        cout << minimal << '\n';
    }

    return 0;
}
