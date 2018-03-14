// Perfect P-th Power
// UVa ID: 10622
// Verdict: Accepted
// Submission Date: 2018-03-10
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int primes[1 << 16] = {0}, cnt = 0;
    for (int i = 2; i * i < (1 << 16); i++)
        if (!primes[i])
            for (int j = i * i; j < (1 << 16); j += i)
                primes[j] = 1;
    for (int i = 2; i < (1 << 16); i++)
        if (!primes[i])
            primes[cnt++] = i;
            
    long long n;
    while (cin >> n, n != 0)
    {
        map<long long, long long> divisor;
        long long x = abs(n);
        for (int i = 0; i < cnt; i++)
        {
            if (primes[i] > x) break;
            while (x % primes[i] == 0)
            {
                divisor[primes[i]]++;
                x /= primes[i];
            }
        }
        if (x > 1) divisor[x]++;
        long long p = (divisor.begin())->second;
        for (auto it = divisor.begin(); it != divisor.end(); it++)
        {
            p = __gcd(p, it->second);
            if (p == 1) break;
        }
        if (n > 0)
            cout << p << '\n';
        else
        {
            while (p % 2 == 0) p /= 2;
            cout << p << '\n';
        }
    }

    return 0;
}
