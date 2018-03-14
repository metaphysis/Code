// Chinese Shuffle
// UVa ID: 10710
// Verdict: Accepted
// Submission Date: 2018-03-14
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net
//
// Find formula: 2^(N - 1) = 1 (mod N)

#include <bits/stdc++.h>

using namespace std;

long long powMod(long long x, long long k, long long mod)
{
    if (k == 0) return 1;
    long long r = powMod(x * x % mod, k >> 1, mod);
    if (k & 1) r = r * x % mod;
    return r;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n;
    while (cin >> n, n > 0)
    {
        cout << n;
        if (powMod(2, n - 1, n) == 1) cout << " is a Jimmy-number\n";
        else cout << " is not a Jimmy-number\n";
    }

    return 0;
}
