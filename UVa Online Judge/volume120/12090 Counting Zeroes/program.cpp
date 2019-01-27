// Counting Zeroes
// UVa ID: 12090
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

const int MAXN = 3300000;

using namespace std;

int primes[MAXN] = {}, cnt;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    for (int i = 2; i < MAXN; i++)
    {
        if (!primes[i]) primes[cnt++] = i;
        for (int j = 0; j < cnt && i * primes[j] < MAXN; j++)
        {
            primes[i * primes[j]] = 1;
            if (i % primes[j] == 0) break;
        }
    }
    
    long long n, nn;
    while (cin >> n, n > 0)
    {
        nn = n;
        int factors[32], counter[32] = {}, idx = 0;
        for (int i = 0; i < cnt; i++)
            if (n % primes[i] == 0)
            {
                factors[idx] = primes[i];
                while (n % primes[i] == 0)
                {
                    counter[idx]++;
                    n /= primes[i];
                }
                idx++;
            }
        if (n > 0)
        {
            factors[idx] = n;
            counter[idx]++;
            idx++;
        }
        
        int zeros = 0;
        for (int i = 0; i < (1 << idx); i++)
        {
            int exponent = 100;
            for (int k = 0; k < idx; k++)
                if (i & (1 << k))
                    exponent = min(exponent, counter[k]);
            zeros += exponent;
        }
        cout << nn << ' ' << zeros << '\n';
    }

    return 0;
}
