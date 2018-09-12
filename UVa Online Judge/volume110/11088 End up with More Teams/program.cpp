// End up with More Teams
// UVa ID: 11088
// Verdict: Accepted
// Submission Date: 2018-09-12
// UVa Run Time: 0.010s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n, cases = 0, ability[16], cache[1 << 15];
    while (cin >> n, n > 0)
    {
        for (int i = 0; i < n; i++)
            cin >> ability[i];
        sort(ability, ability + n, greater<int>());
        n -= (n % 3);
        memset(cache, 0, sizeof(cache));
        for (int i = 1, j, k, l, bit; i < (1 << n); i++)
        {
            if ((bit = __builtin_popcount(i)) % 3 != 0) continue;
            bit /= 3;
            for (j = 0; j < n; j++) if (i & (1 << j)) break;
            for (k = j + 1; k < n; k++)
            {
                if (cache[i] == bit) break;
                if (i & (1 << k))
                {
                    for (l = k + 1; l < n; l++)
                    {
                        if (i & (1 << l))
                        {
                            if (ability[j] + ability[k] + ability[l] < 20) continue;
                            cache[i] = max(cache[i], cache[i ^ (1 << j) ^ (1 << k) ^ (1 << l)] + 1);
                        }
                    }
                }
            }
        }
        cout << "Case " << ++cases << ": " << cache[(1 << n) - 1] << '\n';
    }

    return 0;
}
