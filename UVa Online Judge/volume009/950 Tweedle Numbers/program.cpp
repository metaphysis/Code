// Tweedle Numbers
// UVa ID: 950
// Verdict: Accepted
// Submission Date: 2018-11-27
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int N, M, K;
int dp[40][40][2], blocks[40];

int dfs(int n, int k, int h)
{
    if (n == 0 || k == 0)
    {
        if (n == 0 && k == 0) return dp[n][k][h] = 1;
        return dp[n][k][h] = 0;
    }
    if (~dp[n][k][h]) return dp[n][k][h];
    int r = 0;
    for (int i = 1; i <= M; i++)
            if (n - i >= 0)
                r += dfs(n - i, k - 1, !h);
    return dp[n][k][h] = r;
}

int getIdx(int n, int k, int h)
{
    if (n == 0 || k == 0) return dp[n][k][h];
    int r = 0;
    if (h)
    {
        for (int i = 1; i <= M; i++)
            if (n - i >= 0 && blocks[K - k] > i)
                r += dp[n - i][k - 1][!h];
    }
    else
    {
        for (int i = M; i >= 1; i--)
            if (n - i >= 0 && blocks[K - k] < i)
                r += dp[n - i][k - 1][!h];
    }
    r += getIdx(n - blocks[K - k], k - 1, !h);
    return r;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0, T, I;
    string S;

    while (cin >> N >> K >> M)
    {
        if (cases++) cout << '\n';
        memset(dp, -1, sizeof(dp));
        dfs(N, K, 1);
        cin >> T;
        for (int i = 1; i <= T; i++)
        {
            cin >> S;
            S += '\n';
            I = blocks[0] = 0;
            char C = S[0];
            for (int j = 0; j < S.length(); j++)
            {
                if (S[j] == '\n') break;
                if (S[j] == C) blocks[I]++;
                else blocks[++I] = 1;
                C = S[j];
            }
            cout << getIdx(N, K, 1) << '\n';
        }
    }

    return 0;
}
