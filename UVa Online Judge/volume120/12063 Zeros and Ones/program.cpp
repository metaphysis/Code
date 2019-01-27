// Zeros and Ones
// UVa ID: 12063
// Verdict: Accepted
// Submission Date: 2019-01-27
// UVa Run Time: 0.010s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int T, N, K;
    long long dp[70][70][110];

    cin >> T;
    for (int cs = 1; cs <= T; cs++)
    {
        cin >> N >> K;
        cout << "Case " << cs << ": ";
        if (N % 2 == 1 || K == 0)
        {
            cout << "0\n";
            continue;
        }
        
        for (int i = 0; i <= N; i++)
            for (int j = 0; j <= N; j++)
                for (int k = 0; k < K; k++)
                    dp[i][j][k] = 0;

        dp[1][0][1 % K] = 1;
        for (int n = 1; n < N; n++)
            for (int i = 1; i <= min(n, N / 2); i++)
                for (int k = 0; k < K; k++)
                {
                    dp[i + 1][n - i][(k * 2 + 1) % K] += dp[i][n - i][k];
                    dp[i][n - i + 1][(k * 2) % K] += dp[i][n - i][k];
                }

        cout << dp[N / 2][N / 2][0] << '\n';
    }

    return 0;
}
