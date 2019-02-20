// {Sum+=i++} to Reach N
// UVa ID: 10290
// Verdict: Accepted
// Submission Date: 2019-02-20
// UVa Run Time: 1.310s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 43000001;

long long primes[MAXN] = {}, factors[32];
int cnt = 0, exponent[32], tot;

vector<long long> fs;

void dfs(int d, long long r)
{
    if (d == tot) fs.push_back(r);
    else
    {
        long long b = 1;
        for (int i = 0; i <= exponent[d]; i++)
        {
            dfs(d + 1, r * b);
            b *= factors[d];
        }
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
    while (cin >> n)
    {
        if (binary_search(primes, primes + cnt, n))
        {
            if (n == 2) cout << 1 << '\n';
            else cout << 2 << '\n';
            continue;
        }

        nn = n * 2LL;
        tot = 0;
        for (int i = 0; primes[i] * primes[i] <= nn; i++)
        {
            if (nn % primes[i] == 0)
            {
                factors[tot] = primes[i];
                exponent[tot] = 0;
                while (nn % primes[i] == 0)
                {
                    exponent[tot]++;
                    nn /= primes[i];
                }
                tot++;
            }
        }
        if (nn > 1)
        {
            factors[tot] = nn;
            exponent[tot] = 1;
            tot++;
        }
        
        fs.clear();
        dfs(0, 1LL);
        sort(fs.begin(), fs.end());
        int ways = 0;
        n *= 2LL;
        for (auto f : fs)
        {
            long long x = n / f - f + 1;
            if (x <= 0) break;
            if (x & 1) continue;
            ways++;
        }
        cout << ways << '\n';
    }

    return 0;
}
