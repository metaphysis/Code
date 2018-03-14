// Enumerating Rational Numbers
// UVa ID: 11327
// Verdict: Accepted
// Submission Date: 2018-03-12
// UVa Run Time: 0.030s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1 << 18;

long long sigma[MAXN] = {1, 2};
int primes[MAXN], phi[MAXN], cnt = 0;

void sieve(int n)
{
    iota(primes, primes + n, 0);

    for (int i = 2; i < n; i++)
    {
        if (primes[i] == i)
        {
            phi[i] = i - 1;
            primes[cnt++] = i;
            for (int j = i + i; j < n; j += i)
                if (primes[j] == j)
                    primes[j] = i;
        }
        else
        {
            int k = i / primes[i];
            if (k % primes[i] == 0) phi[i] = primes[i] * phi[k];
            else phi[i] = (primes[i] - 1) * phi[k];
        }
        sigma[i] = sigma[i - 1] + phi[i];
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    sieve(MAXN);

    long long k;
    while (cin >> k, k > 0)
    {
        if (k == 1)
        {
            cout << "0/1\n";
            continue;
        }

        if (k == 2)
        {
            cout << "1/1\n";
            continue;
        }

        int i = lower_bound(sigma, sigma + MAXN, k) - sigma;
        if (sigma[i] == k)
        {
            cout << (i - 1) << "/" << i << '\n';
            continue;
        }

        int diff = k - sigma[i - 1];
        if (binary_search(primes, primes + cnt, i))
        {
            cout << diff << '/' << i << '\n';
            continue;
        }
        
        for (int j = 1; j < i; j++)
            if (__gcd(j, i) == 1)
            {
                if (--diff == 0)
                {
                    cout << j << '/' << i << '\n';
                    break;
                }
            }
    }

    return 0;
}
