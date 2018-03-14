// Largest Prime Divisor
// UVa ID: 11466
// Verdict: Accepted
// Submission Date: 2018-03-09
// UVa Run Time: 0.260s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 10000010;

long long primes[MAXN] = {0};

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cnt = 0;
    for (int i = 2; i * i < MAXN; i++)
        if (!primes[i])
            for (int j = i * i; j < MAXN; j += i)
                primes[j] = 1;
    for (int i = 2; i < MAXN; i++)
        if (!primes[i])
            primes[cnt++] = i;

    long long n;
    while (cin >> n)
    {
        if (n == 0) break;
        n = abs(n);
        map<long long, int> divisors;
        for (int i = 0; i < cnt; i++)
        {
            if (primes[i] > n) break;
            while (n % primes[i] == 0)
            {
                divisors[primes[i]]++;
                n /= primes[i];
            }
        }
        if (n > 1) divisors[n]++;
        if (divisors.size() <= 1) cout << "-1\n";
        else cout << (--divisors.end())->first << '\n';
    }
    
    return 0;
}
