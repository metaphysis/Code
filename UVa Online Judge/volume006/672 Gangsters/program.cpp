// Gangsters
// UVa ID: 672
// Verdict: Accepted
// Submission Date: 2018-09-23
// UVa Run Time: 0.080s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct gangster
{
    int ti, pi, si;
};

int dp[30001][101], V[30001][101];
int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int M, N, K, T;
    gangster G[101];

    cin >> M;
    for (int cs = 1; cs <= M; cs++)
    {
        cin >> N >> K >> T;

        for (int i = 0; i < N; i++) cin >> G[i].ti;
        for (int i = 0; i < N; i++) cin >> G[i].pi;
        for (int i = 0; i < N; i++) cin >> G[i].si;

        for (int i = 0; i <= T; i++)
            for (int j = 0; j <= K; j++)
            {
                dp[i][j] = -1;
                V[i][j] = 0;
            }
        for (int i = 0; i < N; i++)
            V[G[i].ti][G[i].si] += G[i].pi;

        dp[0][0] = 0;
        int P = 0;
        for (int i = 1; i <= T; i++)
            for (int j = 0; j <= K; j++)
                if (~dp[i - 1][j])
                {
                    dp[i][j] = max(dp[i][j], dp[i - 1][j] + V[i][j]);
                    if (j)
                        dp[i][j - 1] = max(dp[i][j - 1], dp[i - 1][j] + V[i][j - 1]);
                    if (j < K)
                        dp[i][j + 1] = max(dp[i][j + 1], dp[i - 1][j] + V[i][j + 1]);
                }
        if (cs > 1) cout << '\n';
        int maximum = 0;
        for (int i = 0; i <= K; i++)
            maximum = max(maximum, dp[T][i]);
        cout << maximum << '\n';
    }

    return 0;
}
