// Digital Roulette
// UVa ID: 12318
// Verdict: Accepted
// Submission Date: 2018-11-30
// UVa Run Time: 0.420s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

#define GET(x) (B[x >> 5] & (1 << (x & 0x1F)))
#define SET(x) (B[x >> 5] ^= (1 << (x & 0x1F)))

const int MAXB = 10000001;
int B[MAXB >> 5] = {};

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int M, K;
    long long N, ai[12];
    while (cin >> N >> M)
    {
        if (N == 0) break;
        N++;
        cin >> K;
        for (int i = 0; i <= K; i++) cin >> ai[i];
        int cnt = 0;
        memset(B, 0, sizeof(B));
        for (int i = 0; i <= M; i++)
        {
            long long mod = ai[0], r = 1;
            for (int j = 1; j <= K; j++)
            {
                r = (r * i) % N;
                mod += (ai[j] * r) % N;
                mod %= N;
            }
            if (!GET(mod))
            {
                cnt++;
                SET(mod);
            }
        }
        cout << cnt << '\n';
    }

    return 0;
}
