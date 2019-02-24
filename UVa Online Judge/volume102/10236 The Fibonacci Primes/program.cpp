// The Fibonacci Primes
// UVa ID: 10236
// Verdict: Accepted
// Submission Date: 2019-02-24
// UVa Run Time: 0.000s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 250000;

int primes[MAXN] = {}, cnt = 0;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    for (int i = 2; i < MAXN; i++)
    {
        if (!primes[i]) primes[cnt++] = i;
        for (int j = 0; j < cnt && i * primes[j] < MAXN; j++)
        {
            primes[i * primes[j]] = 1;
            if (!(i % primes[j])) break;
        }
    }

    double fib[22010] = {2, 3};
    double f0 = 2, f1 = 3, f2;
    
    int fIdx = 5, pIdx = 2;
    while (pIdx <= 22000)
    {
        f2 = f0 + f1;
        if (f2 >= 1e9) f1 /= 10, f2 /= 10;
        if (fIdx == primes[pIdx])
        {
            fib[pIdx] = f2;
            pIdx++;
        }
        fIdx++;
        f0 = f1, f1 = f2;
    }

    int n;
    while (cin >> n) cout << (int)fib[n - 1] << '\n';

    return 0;
}
