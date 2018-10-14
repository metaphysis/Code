// Beautiful Numbers
// UVa ID: 11472
// Verdict: Accepted
// Submission Date: 2018-10-14
// UVa Run Time: 0.030s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;


int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, N, M;
    long long dp[101][10][1024], MOD = 1000000007;

    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> N >> M;
        for (int i = 0; i <= M; i++)
            for (int j = 0; j < N; j++)
                for (int k = 0; k < (1 << N); k++)
                    dp[i][j][k] = 0;
        for (int i = 1; i < N; i++)
            dp[1][i][1 << i] = 1LL;
        for (int i = 1; i < M; i++)
            for (int j = 0; j < N; j++)
                for (int k = 0; k < (1 << N); k++)
                {
                    if (j >= 1)
                    {
                        dp[i + 1][j - 1][k | (1 << (j - 1))] += dp[i][j][k];
                        dp[i + 1][j - 1][k | (1 << (j - 1))] %= MOD;
                    }
                    if (j <= N - 2)
                    {
                        dp[i + 1][j + 1][k | (1 << (j + 1))] += dp[i][j][k];
                        dp[i + 1][j + 1][k | (1 << (j + 1))] %= MOD;
                    }
                }
        long long T = 0;
        for (int i = N; i <= M; i++)
            for (int j = 0; j < N; j++)
                T = (T + dp[i][j][(1 << N) - 1]) % MOD;
        cout << T << '\n';
    }

    return 0;
}
