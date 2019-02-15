// Prime Gap
// UVa ID: 1644
// Verdict: Accepted
// Submission Date: 2019-02-15
// UVa Run Time: 0.010s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1300000;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int primes[MAXN] = {}, cnt = 0;
    
    for (int i = 2; i < MAXN; i++)
    {
        if (!primes[i]) primes[cnt++] = i;
        for (int j = 0; j < cnt && i * primes[j] < MAXN; j++)
        {
            primes[i * primes[j]] = 1;
            if (!(i % primes[j])) break;
        }
    }

    int n;
    while (cin >> n, n)
    {
        if (binary_search(primes, primes + cnt, n)) cout << "0\n";
        else
        {
            int k = upper_bound(primes, primes + cnt, n) - primes;
            cout << (primes[k] - primes[k - 1]) << '\n';
        }
    }

    return 0;
}
