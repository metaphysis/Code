// Find Solutions
// UVa ID: 12005
// Verdict: Accepted
// Submission Date: 2018-03-15
// UVa Run Time: 1.770s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 20000010;

long long primes[MAXN] = {0};
int cnt = 0;

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
            
    long long n;
    while (cin >> n, n > 0)
    {
        cout << n << ' ';
        n = n * 4 - 3;
        int t = 1;
        for (int i = 0; i < cnt; i++)
        {
            if (primes[i] * primes[i] > n) break;
            if (n % primes[i] == 0)
            {
                int c = 1;
                n /= primes[i];
                while (n % primes[i] == 0)
                {
                    c++;
                    n /= primes[i];
                }
                t *= (c + 1);
            }
        }
        
        if (n > 1) t *= 2;
        cout << t << '\n';
    }

    return 0;
}
