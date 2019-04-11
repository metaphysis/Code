// Laser Mirrors
// UVa ID: 13132
// Verdict: Accepted
// Submission Date: 2019-04-12
// UVa Run Time: 0.010s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100010;

int primes[MAXN], phi[MAXN] = {0, 1}, cnt = 0;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    iota(primes, primes + MAXN, 0);
    for (int i = 2; i < MAXN; i++)
    {
        if (primes[i] == i)
        {
            phi[i] = i - 1;
            primes[cnt++] = i;
            for (int j = i + i; j < MAXN; j += i)
                if (primes[j] == j)
                    primes[j] = i;
        }
        else
        {
            int k = i / primes[i];
            if (k % primes[i] == 0) phi[i] = primes[i] * phi[k];
            else phi[i] = (primes[i] - 1) * phi[k];
        }
    }
    
    int cases, n;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> n;
        cout << phi[n] << '\n';
    }

    return 0;
}
