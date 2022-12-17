// Growing Trees
// UVa ID: 13141
// Verdict: Accepted
// Submission Date: 2022-12-07
// UVa Run Time: 0.000s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    long long dp[90] = {0, 1, 1, 2};
    long long x = 2, y = 0, xx, yy;
    for (int i = 4; i <= 85; i++) {
        xx = x + 2 * y, yy = x / 2;
        dp[i] = xx + yy;
        x = xx, y = yy;
    }
    int n;
    while (cin >> n, n) cout << dp[n] << '\n';
    return 0;
}
