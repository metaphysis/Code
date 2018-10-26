// Primed Subsequence
// UVa ID: 10871
// Verdict: Accepted
// Submission Date: 2018-10-26
// UVa Run Time: 0.670s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

#define GET(x) (B[x >> 5] & (1 << (x & 0x1F)))
#define SET(x) (B[x >> 5] ^= (1 << (x & 0x1F)))

const int MAXN = 100000001, MAXP = 6000010;

int primes[MAXP], cnt = 0;
int B[(MAXN >> 5) + 1] = {}, sum[10010], xi[10010];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    B[0] = 3;
    for (int i = 2; i < MAXN; i++)
    {
        if (!GET(i)) primes[cnt++] = i;
        for (int j = 0; j < cnt && i * primes[j] < MAXN; j++)
        {
            SET(i * primes[j]);
            if (i % primes[j] == 0) break;
        }
    }

    int cases, n;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        memset(sum, 0, sizeof(sum));
        cin >> n;
        for (int i = 1; i <= n; i++)
        {
            cin >> xi[i];
            sum[i] = xi[i] + sum[i - 1];
        }

        int flag = 0, L, S;
        for (L = 2; L <= n; L++)
            for (S = 1; S <= n; S++)
            {
                if (S + L - 1 > n) break;
                int diff = sum[S + L - 1] - sum[S - 1];
                if (!GET(diff))
                {
                    flag = 1;
                    goto print;
                }
            }

        print:
        if (flag)
        {
            cout << "Shortest primed subsequence is length " << L;
            cout << ':';
            for (int i = 0; i < L; i++)
                cout << ' ' << xi[S + i];
            cout << '\n';
        }
        else
        {
            cout << "This sequence is anti-primed.\n";
        }
    }

    return 0;
}
