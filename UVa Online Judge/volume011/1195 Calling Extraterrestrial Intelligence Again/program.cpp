// Calling Extraterrestrial Intelligence Again
// UVa ID: 1195
// Verdict: Accepted
// Submission Date: 2018-11-30
// UVa Run Time: 0.040s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100000;

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
            if (i % primes[j] == 0) break;
        }
    }

    long long m, a, b;
    while (cin >> m >> a >> b)
    {
        if (m == 0) break;
        long long most = 0, p, q, pp, qq;
        for (int i = 0; i < cnt; i++)
        {
            p = primes[i];
            for (int j = i; j < cnt; j++)
            {
                q = primes[j];
                if (p * q > m) break;
                if (a * q <= b * p && p * q > most)
                {
                    most = p * q;
                    pp = p, qq = q;
                }
            }
        }
        cout << pp << ' ' << qq << '\n';
    }

    return 0;
}
