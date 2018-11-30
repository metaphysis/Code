// Divisor Game
// UVa ID: 11960
// Verdict: Accepted
// Submission Date: 2018-11-30
// UVa Run Time: 0.040s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1000001;

int primes[MAXN] = {}, factors[MAXN] = {0, 1}, most[MAXN] = {0, 1}, cnt = 0;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    for (int i = 2; i < MAXN; i++)
    {
        if (!primes[i]) primes[cnt++] = i, factors[i] = 2;
        else
        {
            for (int j = 0; j < cnt; j++)
            {
                if (i % primes[j] == 0)
                {
                    int r = 0, n = i;
                    while (n % primes[j] == 0)
                    {
                        r++;
                        n /= primes[j];
                    }
                    factors[i] = (r + 1) * factors[n];
                    break;
                }
            }
        }
        for (int j = 0; j < cnt && i * primes[j] < MAXN; j++)
        {
            primes[i * primes[j]] = 1;
            if (i % primes[j] == 0) break;
        }
        if (factors[i] >= factors[most[i - 1]]) most[i] = i;
        else most[i] = most[i - 1];
    }
    
    int T, N;
    cin >> T;
    for (int cs = 1; cs <= T; cs++)
    {
        cin >> N;
        cout << most[N] << '\n';
    }

    return 0;
}
