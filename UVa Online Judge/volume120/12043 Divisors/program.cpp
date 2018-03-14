// Divisors
// UVa ID: 12043
// Verdict: Accepted
// Submission Date: 2018-03-12
// UVa Run Time: 0.030s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int primes[320] = {0}, cnt = 0;
    for (int i = 2; i * i < 320; i++)
        if (!primes[i])
            for (int j = i * i; j < 320; j += i)
                primes[j] = 1;
    for (int i = 2; i < 320; i++)
        if (!primes[i])
            primes[cnt++] = i;
            
    int divisors[100010], sigma[100010];
    for (int i = 1; i <= 100000; i++)
    {
        int x = i, d = 1, s = 1;
        for (int j = 0; j < cnt && x > 1; j++)
        {
            if (x % primes[j] == 0)
            {
                int c = 0;
                while (x % primes[j] == 0)
                {
                    c++;
                    x /= primes[j];
                }
                d *= (c + 1);
                s *= ((int)pow(primes[j], c + 1) - 1) / (primes[j] - 1);
            }
        }
        if (x > 1)
        {
            d *= 2;
            s *= (x + 1);
        }
        divisors[i] = d, sigma[i] = s;
    }


    int cases, a, b, k;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> a >> b >> k;
        long long d = 0, s = 0;
        for (int i = a; i <= b; i++)
            if (i % k == 0)
            {
                d += divisors[i];
                s += sigma[i];
            }
        cout << d << ' ' << s << '\n';
    }

    return 0;
}
