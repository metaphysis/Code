// Recover Factorial
// UVa ID: 10856
// Verdict: Accepted
// Submission Date: 2018-12-01
// UVa Run Time: 0.090s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2750001;

int primes[MAXN] = {}, factors[MAXN] = {}, sum[MAXN] = {}, cnt = 0;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    for (int i = 2; i < MAXN; i++)
    {
        if (!primes[i]) primes[cnt++] = i, factors[i] = 1;
        else
        {
            for (int j = 0; j < cnt; j++)
                if (i % primes[j] == 0)
                {
                    factors[i] = factors[i / primes[j]] + 1;
                    break;
                }
        }
        for (int j = 0; j < cnt && i * primes[j] < MAXN; j++)
        {
            primes[i * primes[j]] = 1;
            if (i % primes[j] == 0) break;
        }
        sum[i] = sum[i - 1] + factors[i];
    }
        
    int T = 0, N;
    while (cin >> N)
    {
        if (N < 0) break;
        cout << "Case " << ++T << ": ";
        int n = lower_bound(sum, sum + MAXN, N) - sum;
        if (sum[n] == N) cout << n << "!\n";
        else cout << "Not possible.\n";
    }

    return 0;
}
