// Reverse Prime
// UVa ID: 11610
// Verdict: Accepted
// Submission Date: 2019-01-03
// UVa Run Time: 0.030s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

#define GET(x) (B[x >> 5] & (1 << (x & 0x1F)))
#define SET(x) (B[x >> 5] ^= (1 << (x & 0x1F)))

const int MAXN = 1000000, MAXB = 80000;

struct rp
{
    int p, f;
    rp (int p = 0, int f = 0): p(p), f(f) {}
    bool operator<(const rp &r) const
    {
        return p < r.p;
    }
    bool operator==(const int x) const
    {
        return p == x;
    }
} rps[MAXB];

int B[MAXN >> 5] = {}, primes[MAXB], factors[MAXN] = {}, cnt = 0, idx = 0;
int SF[MAXB] = {}, SD[MAXB] = {};

inline int reverse(int x)
{
    int n = 0;
    while (x)
    {
        n = n * 10 + x % 10;
        x /= 10;
    }
    return n;
}

inline int lowbit(int x) { return x & (-x); }

void add(int *fenwick, int x, int delta)
{
    for (int i = x; i < MAXB; i += lowbit(i))
        fenwick[i] += delta;
}

int get(int *fenwick, int x)
{
    int sum = 0;
    for (int i = x; i; i -= lowbit(i))
        sum += fenwick[i];
    return sum;
}

int sum(int *fenwick, int L, int R)
{
    return get(fenwick, R) - get(fenwick, L - 1);
}

int getFactors(int x)
{
    if (x < MAXN && factors[x]) return factors[x];
    for (int i = 0; primes[i] * primes[i] <= x; i++)
        if (x % primes[i] == 0)
            return 1 + getFactors(x / primes[i]);
    return 1;
}

void prepare()
{
    for (int i = 2; i < MAXN; i++)
    {
        if (!GET(i)) primes[cnt++] = i;
        for (int j = 0; j < cnt && i * primes[j] < MAXN; j++)
        {
            SET(i * primes[j]);
            if (i % primes[j] == 0) break;
        }
        if (!GET(i)) factors[i] = 1;
        else
        {
            for (int j = 0; j < cnt; j++)
                if (i % primes[j] == 0)
                {
                    factors[i] = factors[i / primes[j]] + 1;
                    break;
                }
        }
    }
    for (int i = 0; i < cnt; i++)
    {
        if (primes[i] >= 1000000) break;
        int x = reverse(primes[i]);
        while (x < 1000000) x *= 10;
        rps[idx++] = rp(x, getFactors(x));
    }
    sort(rps, rps + idx);
    
    for (int i = 0; i < idx; i++)
        add(SF, i + 1, rps[i].f);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    prepare();

    char command;
    int i;
    
    while (cin >> command)
    {
        cin >> i;
        if (command == 'q')
        {
            int low = 1, high = MAXB, middle;
            while (true)
            {
                middle = (low + high) >> 1;
                int C = middle - sum(SD, 1, middle);
                if (C == (i + 1)) break;
                if (C < (i + 1))
                    low = middle;
                else
                    high = middle;
            }
            cout << sum(SF, 1, middle) << '\n';
        }
        else
        {
            int k = lower_bound(rps, rps + idx, i) - rps;
            add(SF, k + 1, -rps[k].f);
            add(SD, k + 1, 1);
        }
    }

    return 0;
}
