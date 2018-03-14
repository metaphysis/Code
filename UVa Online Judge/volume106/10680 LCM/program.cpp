// LCM
// UVa ID: 10680
// Verdict: Accepted
// Submission Date: 2017-03-18
// UVa Run Time: 0.170s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

void sieve(int *primes, int n, int &counter)
{
    counter = 0;
    memset(primes, 1, n * sizeof(int));

    for (int i = 2; i < n; i++) {
        if (primes[i]) primes[counter++] = i;
        for (int j = 0; j < counter && i * primes[j] < n; j++) {
            primes[i * primes[j]] = 0;
            if (!(i % primes[j])) break;
        }
    }
}

int main(int argc, char *argv[])
{
    int primes[1000000], counter = 0;
    long long n;

    sieve(primes, 1000000, counter);

    while (cin >> n, n > 0)
    {
        int c2 = 0, c5 = 0, s2 = 2, s5 = 5, last = 1;

        while (s2 <= n) { c2++; s2 *= 2; }
        while (s5 <= n) { c5++; s5 *= 5; }

        c2 -= c5;
        for (int i = 1; i <= c2; i++) last *= 2, last %= 10;

        for (int i = 0; i < counter; i++)
        {
            if (primes[i] == 2 || primes[i] == 5) continue;
            if (primes[i] > n) break;

            long long p = primes[i];
            while (p <= n)
            {
                last *= primes[i], last %= 10;
                p *= primes[i];
            }
        }

        cout << last << '\n';
    }
    
    return 0;
}
