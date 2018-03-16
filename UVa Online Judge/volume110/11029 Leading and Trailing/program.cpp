// Leading and Trailing
// UVa ID: 11029
// Verdict: Accepted
// Submission Date: 2018-03-13
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

long long modPow(long long x, long long k, long long mod)
{
    if (k == 0) return 1;
    long long r = modPow(x * x % mod, k >> 1, mod);
    if (k & 1) r = r * x % mod;
    return r;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, n, k;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n >> k;
        // LLL
        double exponent = k * log10(n);
        exponent -= (int)exponent;
        int integer = pow(10, exponent) * 100.0;
        cout << setw(3) << left << integer;
        cout << "...";
        // TTT
        cout << setw(3) << right << setfill('0') << modPow(n, k, 1000) << '\n';
    }

    return 0;
}
