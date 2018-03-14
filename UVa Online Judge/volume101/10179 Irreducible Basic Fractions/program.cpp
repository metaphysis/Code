// Irreducible Basic Fractions
// UVa ID: 10179
// Verdict: Accepted
// Submission Date: 2017-07-23
// UVa Run Time: 0.030s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 32000;
    
void sieve(int *primes, int n, int &counterOfPrimes)
{
    // 初始时假定所有数为素数，从最小的素数开始筛除。
    counterOfPrimes = 0;
    memset(primes, 1, n * sizeof(int));

    for (int i = 2; i < n; i++)
        if (primes[i])
        {
            // 记录筛选得到的素数。
            primes[counterOfPrimes++] = i;

            // 如果i为素数则将其倍数标记为非素数。
            for (int j = i + i; j < n; j += i) primes[j] = 0;
        }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int primes[MAXN], counterOfPrimes = 0;

    sieve(primes, MAXN, counterOfPrimes);
    
    int n;
    while (cin >> n, n > 0)
    {
        int t = n;
        for (int i = 0; i < counterOfPrimes; i++)
        {
            if (primes[i] > n) break;
            if (n % primes[i] == 0)
            {
                while (n % primes[i] == 0) n /= primes[i];
                t -= t / primes[i];
            }
        }
        if (n > 1) t -= t / n;
        
        cout << t << '\n';
    }
    
    return 0;
}
