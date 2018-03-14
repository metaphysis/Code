// Ferry Loading II
// UVa ID: 10440
// Verdict: Accepted
// Submission Date: 2018-01-27
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, n, t, m, arrived[1500];

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n >> t >> m;
        for (int i = 1; i <= m; i++) cin >> arrived[i];

        // More less trips more better.
        int times = 0;
        int trips = (m / n) + (m % n != 0);
        if (m % n != 0)
        {
            times = arrived[(m % n)] + 2 * t;
        }
        if (m >= n)
        {
            for (int i = (m % n) + n; i <= m; i += n)
                times = max(times, arrived[i]) + 2 * t;
        }
        // Last trip needs not return.
        times -= t;
        
        cout << times << ' ' << trips << '\n';
    }

    return 0;
}
