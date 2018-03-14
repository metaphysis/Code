// How Many Zero's and How Many Digits?
// UVa ID: 10061
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

double sumOfLog10[(1 << 20)] = {0.0};

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int primes[1000] = {0}, cnt = 0;
    for (int i = 2; i < 1000; i++)
        if (!primes[i])
        {
            primes[cnt++] = i;
            for (int j = i + i; j < 1000; j += i)
                primes[j] = 1;
        }

    // DO NOT USE Stirling formula! It have problem of epsilon.
    // sumOfLog10[N] = log10(sqrt(2.0 * PI * N)) + N * log10(N / EXP);

    for (int i = 1; i < (1 << 20); i++)
        sumOfLog10[i] = sumOfLog10[i - 1] + log10(i);

    int N, B;
    while (cin >> N >> B)
    {
        if (N <= 1)
        {
            cout << "0 1\n";
            continue;
        }

        int digits = floor(sumOfLog10[N] / log10(B) + 1e-7) + 1;

        int divisor = 0, exponent = 0;
        for (int i = cnt - 1; i >= 0; i--)
            if (B % primes[i] == 0)
            {
                divisor = primes[i];
                int x = B;
                while (x % primes[i] == 0)
                {
                    exponent++;
                    x /= primes[i];
                }
                break;
            }
        if (!divisor) 
        {
            exponent = 1;
            divisor = B;
        }

        int zeros = 0;
        for (int i = 1; i <= N; i++)
        {
            int x = i;
            while (x % divisor == 0)
            {
                zeros++;
                x /= divisor;
            }
        }

        cout << (zeros / exponent) << ' ' << digits << '\n';
    }

    return 0;
}
