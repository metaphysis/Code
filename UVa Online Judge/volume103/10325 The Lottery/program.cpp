// The Lottery
// UVa ID: 10325
// Verdict: Accepted
// Submission Date: 2018-11-28
// UVa Run Time: 0.070s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    long long N, M, numbers[16];
    while (cin >> N >> M)
    {
        for (int i = 0; i < M; i++) cin >> numbers[i];
        long long cnt = 0;
        for (int i = 1; i < (1 << M); i++)
        {
            long long p = 1;
            for (int j = 0; j < M; j++)
                if (i & (1 << j))
                {
                    p = p / __gcd(p, numbers[j]) * numbers[j];
                    if (p > N) break;
                }
            cnt += (N / p) * ((__builtin_popcount(i) % 2) ? 1 : (-1));
        }
        cout << (N - cnt) << '\n';
    }

    return 0;
}
