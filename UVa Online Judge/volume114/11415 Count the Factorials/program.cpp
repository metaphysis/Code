// Count the Factorials
// UVa ID: 11415
// Verdict: Accepted
// Submission Date: 2018-11-30
// UVa Run Time: 0.090s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 3000000;

int primes[MAXN] = {}, factors[MAXN] = {}, sum[MAXN] = {0};

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cnt = 0;
    for (int i = 2; i < MAXN; i++)
    {
        if (!primes[i]) primes[cnt++] = i;
        if (!primes[i]) sum[i] = sum[i - 1] + 1, factors[i] = 1;
        else
        {
            for (int j = 0; j < cnt; j++)
                if (i % primes[j] == 0)
                {
                    factors[i] = factors[i / primes[j]] + 1;
                    break;
                }
            sum[i] = sum[i - 1] + factors[i];
        }
        for (int j = 0; j < cnt && i * primes[j] < MAXN; j++)
        {
            primes[i * primes[j]] = 1;
            if (i % primes[j] == 0) break;
        }
    }
    
    int t, n;
    cin >> t;
    for (int cs = 1; cs <= t; cs++)
    {
        cin >> n;
        int k = upper_bound(sum, sum + MAXN, n) - sum;
        cout << k << '\n';
    }

    return 0;
}
