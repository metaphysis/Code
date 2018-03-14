// Factoring Large Numbers
// UVa ID: 10392
// Verdict: Accepted
// Submission Date: 2018-03-09
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 10000010;

int primes[MAXN] = {0};

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cnt = 0;
    for (int i = 2; i * i < MAXN; i++)
        if (!primes[i])
            for (int j = i * i; j < MAXN; j += i)
                primes[j] = 1;
    for (int i = 2; i < MAXN; i++)
        if (!primes[i])
            primes[cnt++] = i;

    long long n;
    while (cin >> n, n >= 0)
    {
        if (n <= 1)
        {
            cout << "    " << n << '\n';
        }
        else
        {
            for (int i = 0; i < cnt && n > 1; i++)
            {
                if (primes[i] > n) break;
                while (n % primes[i] == 0)
                {
                    cout << "    " << primes[i] << '\n';
                    n /= primes[i];
                }
            }
            if (n > 1) cout << "    " << n << '\n';
        }
        cout << '\n';
    }

    return 0;
}
