// Division Game
// UVa ID: 11859
// Verdict: Accepted
// Submission Date: 2018-06-21
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int grundy[10001] = {}, primes[10001] = {}, cnt = 0;
    for (int i = 2; i <= 10000; i++)
        if (!primes[i])
        {
            primes[cnt++] = i;
            for (int j = i + i; j <= 10000; j += i)
                primes[j] = 1;
        }

    for (int i = 2; i <= 10000; i++)
    {
        int next = i;
        for (int j = 0; j < cnt && next > 1; j++)
            if (next % primes[j] == 0)
            {
                while (next % primes[j] == 0)
                {
                    grundy[i]++;
                    next /= primes[j];
                }
            }
        if (next > 1) grundy[i]++;
    }

    int cases, N, M, n;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> N >> M;
        int bit = 0;
        for (int i = 0; i < N; i++)
        {
            int k = 0;
            for (int j = 0; j < M; j++)
            {
                cin >> n;
                k += grundy[n];
            }
            bit ^= k;
        }
        cout << "Case #" << cs << ": ";
        if (bit == 0) cout << "NO\n";
        else cout << "YES\n";
    }

    return 0;
}
