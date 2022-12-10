// Stock Market
// UVa ID: 12951
// Verdict: Accepted
// Submission Date: 2022-12-09
// UVa Run Time: 0.060s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int f[200010], g[200010], n, c;
    while (cin >> n >> c) {
        // max profit of i-th day when have a stock in hand
        f[0] = -0x7f7f7f7f;
        // max profit of i-th day when have none stock in hand
        g[0] = 0;
        for (int i = 1, p; i <= n; i++) {
            cin >> p;
            f[i] = max(f[i - 1], g[i - 1] - p - c);
            g[i] = max(g[i - 1], f[i - 1] + p);
        }
        cout << max(f[n], g[n]) << '\n';
    }
    return 0;
}
