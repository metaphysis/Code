// How Many Solutions?
// UVa ID: 10958
// Verdict: Accepted
// Submission Date: 2018-03-15
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

long long primes[1 << 20] = {0};
int cnt = 0;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    for (int i = 2; i * i < (1 << 20); i++)
        if (!primes[i])
            for (int j = i * i; j < (1 << 20); j += i)
                primes[j] = 1;
    for (int i = 2; i < (1 << 20); i++)
        if (!primes[i])
            primes[cnt++] = i;

    int cases = 0;
    long long m, n, p;
    while (cin >> m >> n >> p)
    {
        if (m == 0 && n == 0 && p == 0) break;
        long long total = 1, x = abs(m * n * p * p);
        for (int i = 0; i < cnt && x > 1; i++)
        {
            if (x % primes[i] == 0)
            {
                int c = 0;
                while (x % primes[i] == 0)
                {
                    c++;
                    x /= primes[i];
                }
                total *= (c + 1);
            }
        }
        if (x > 1) total *= 2;
        cout << "Case " << ++cases << ": " << (2 * total - 1) << '\n';
    }

    return 0;
}
