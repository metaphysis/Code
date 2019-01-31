// Counting Zeroes
// UVa ID: 12090
// Verdict: Accepted
// Submission Date: 2019-01-28
// UVa Run Time: 0.470s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

const int MAXN = 3300000;

using namespace std;

vector<long long> divisors;
int primes[MAXN] = {}, cnt, exponent[32], tot;
long long factors[32];

void dfs(int depth, long long divisor)
{
    if (depth == tot)
    {
        divisors.push_back(divisor);
        return;
    }

    for (int i = 0; i <= exponent[depth]; i++)
    {
        dfs(depth + 1, divisor);
        divisor *= factors[depth];
    }
}

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

    long long n, nn;
    while (cin >> n, n > 0)
    {
        nn = n;
        tot = 0;
        for (int i = 0; i < cnt && n > 1; i++)
            if (n % primes[i] == 0)
            {
                factors[tot] = primes[i];
                exponent[tot] = 0;
                while (n % primes[i] == 0)
                {
                    exponent[tot]++;
                    n /= primes[i];
                }
                tot++;
            }
        if (n > 1)
        {
            factors[tot] = n;
            exponent[tot] = 1;
            tot++;
        }

        divisors.clear();
        dfs(0, 1);

        int zeros = 0;
        for (int i = 0; i < divisors.size(); i++)
        {
            if (divisors[i] == 1) continue;
            n = nn;
            while (n % divisors[i] == 0)
            {
                zeros++;
                n /= divisors[i];
            }
        }
        cout << nn << ' ' << zeros << '\n';
    }

    return 0;
}
