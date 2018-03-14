// Composite Prime
// UVa ID: 11086
// Verdict: Accepted
// Submission Date: 2018-03-11
// UVa Run Time: 0.130s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = (1 << 20) + 1;

int primes[MAXN] = {0}, compositePrimes[MAXN] = {0}, cnt = 0;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    for (int i = 2; i * i < MAXN; i++)
        if (!primes[i])
            for (int j = i * i; j < MAXN; j += i)
                primes[j] = 1;
    for (int i = 2; i < MAXN; i++)
        if (!primes[i])
            primes[cnt++] = i;
    
    for (int i = 0; i < cnt; i++)
    {
        if (primes[i] * primes[i] >= MAXN) break;
        for (int j = i; j < cnt; j++)
        {
            int c = primes[i] * primes[j];
            if (c >= MAXN) break;
            compositePrimes[c] = 1;
        }
    }
    
    int n, number;
    while (cin >> n)
    {
        int total = 0;
        for (int i = 0; i < n; i++)
        {
            cin >> number;
            total += compositePrimes[number];
        }
        cout << total << '\n';
    }

    return 0;
}
