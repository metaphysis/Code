// Puzzles of Triangles
// UVa ID: 12137
// Verdict: Accepted
// Submission Date: 2019-01-31
// UVa Run Time: 0.290s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 10000000;

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

    int cases = 0;
    long long n, backup;
    while (cin >> n, n > 0)
    {
        cout << "Case " << ++cases << ": ";
        backup = n;
        long long high = 1;
        for (int i = 0; i < cnt && primes[i] * primes[i] <= n; i++)
        {
            if (n % primes[i] == 0)
            {
                long long base = 1;
                int exponent = 0;
                while (n % primes[i] == 0)
                {
                    n /= primes[i];
                    exponent++;
                    if (exponent == 2)
                    {
                        base *= primes[i];
                        exponent = 0;
                    }
                }
                if (exponent) base *= primes[i];
                high *= base;
            }
        }
        if (n > 1) high *= n;

        int ways = 8 * (backup / high - 1);
        if (ways == 0) cout << "Impossible";
        else cout << ways;
        cout << '\n';
    }

    return 0;
}
