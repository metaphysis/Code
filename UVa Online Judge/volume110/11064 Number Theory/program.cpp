// Number Theory
// UVa ID: 11064
// Verdict: Accepted
// Submission Date: 2018-03-10
// UVa Run Time: 0.020s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

long long primes[1 << 16] = {0}, cnt = 0;

long long getCnt(long long m)
{
    long long total = m, phi = m, divisor = 1;
    for (int i = 0; i < cnt; i++) {
        if (primes[i] > m) break;
        if (m % primes[i] == 0)
        {
            long long c = 0;
            while (m % primes[i] == 0)
            {
                m /= primes[i];
                c++;
            }
            divisor *= (c + 1);
            phi -= phi / primes[i];
        }
    }
    if (m > 1) 
    {
        phi -= phi / m;
        divisor *= 2;
    }
    return total - phi - divisor + 1;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    for (int i = 2; i * i < (1 << 16); i++)
        if (!primes[i])
            for (int j = i * i; j < (1 << 16); j += i)
                primes[j] = 1;
    for (int i = 2; i < (1 << 16); i++)
        if (!primes[i])
            primes[cnt++] = i;
            
    long long n;
    while (cin >> n) cout << getCnt(n) << '\n';

    return 0;
}
