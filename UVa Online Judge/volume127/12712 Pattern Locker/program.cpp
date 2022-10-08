// Pattern Locker
// UVa ID: 12712
// Verdict: Accepted
// Submission Date: 2022-10-08
// UVa Run Time: 0.080s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int T;
    cin >> T;
    for (int cs = 1; cs <= T; cs++)
    {
        int L, M, N;
        cin >> L >> M >> N;
        long long r = 1LL, MOD = 10000000000007LL;
        L *= L;
        for (int i = 1; i <= M; i++)
        {
            r = r * L % MOD;
            L--;
        }
        long long rr = r;
        for (int i = M + 1; i <= N; i++)
        {
            r = r * L % MOD;
            rr += r;
            rr %= MOD;
            L--;
        }
        cout << "Case " << cs << ": " << rr << '\n';
    }

    return 0;
}
