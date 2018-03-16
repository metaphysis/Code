// Find the Ways!
// UVa ID: 10219
// Verdict: Accepted
// Submission Date: 2018-03-16
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net
//
// C(m, n + 1) = C(m, n) * (m - n) / (n + 1).

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int m, n;
    while (cin >> m >> n)
    {
        // It seems that you must use long double to get AC.
        long double e = 0;
        for (int up = m, down = 1; down <= n; up--, down++)
            e += log10(up) - log10(down);
        cout << int(floor(e)) + 1 << '\n';
    }

    return 0;
}
