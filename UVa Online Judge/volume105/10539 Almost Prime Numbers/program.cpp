// Almost Prime Numbers
// UVa ID: 10539
// Verdict: Accepted
// Submission Date: 2018-04-15
// UVa Run Time: 0.010s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

long long primes[1000001] = {0}, almost[1000001];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    for (long long i = 2; i * i < 1000001; i++)
        if (!primes[i])
        {
            for (int j = i * i; j < 1000001; j += i)
                primes[j] = 1;
        }
        
    int cnt = 0;
    for (long long i = 2; i < 1000001; i++)
        if (!primes[i])
        {
            long long n = i * i;
            while (n < 1e12)
            {
                almost[cnt++] = n;
                n *= i;
            }
        }

    sort(almost, almost + cnt);
    
    int cases;
    long long low, high;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> low >> high;
        int k1 = lower_bound(almost, almost + cnt, low) - almost;
        if (k1 >= cnt)
        {
            cout << 0 << '\n';
            continue;
        }
        
        int k2 = lower_bound(almost, almost + cnt, high) - almost;
        if (k2 >= cnt || almost[k2] != high) k2--;

        cout << (k2 - k1 + 1) << '\n';
    }

    return 0;
}
