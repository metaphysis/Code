// Fantasy of a Summation
// UVa ID: 11718
// Verdict: Accepted
// Submission Date: 2018-03-04
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int modPow(int x, int k, int mod)
{
    if (k == 0) return 1;
    int r = modPow(x * x % mod, k >> 1, mod);
    if (k & 1) r = r * x % mod;
    return r;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, Ai[1010], n, K, MOD;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cout << "Case " << c << ": ";
        cin >> n >> K >> MOD;
        
        int l = 0;
        for (int i = 0; i < n; i++)
        {
            cin >> Ai[i];
            l += Ai[i] % MOD;
            l %= MOD;
        }
        
        int r = ((K % MOD) * modPow(n, K - 1, MOD)) % MOD;
        
        cout << (l * r) % MOD << '\n';
    }

    return 0;
}
