// Teams
// UVa ID: 11609
// Verdict: Accepted
// Submission Date: 2018-06-01
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

long long modPow(long long n, long long k, long long mod)
{
    if (k == 0) return 1;
    long long r = modPow(n * n % mod, k >> 1, mod);
    if (k & 1) r = r * n % mod;
    return r;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int T, N, MOD = 1000000007;
    cin >> T;
    for (int i = 1; i <= T; i++)
    {
        cin >> N;
        cout << "Case #" << i << ": " << (N * modPow(2, N - 1, MOD)) % MOD << '\n';
    }

    return 0;
}
