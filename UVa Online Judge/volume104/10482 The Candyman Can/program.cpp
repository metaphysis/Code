// The Candyman Can
// UVa ID: 10482
// Verdict: Accepted
// Submission Date: 2018-10-14
// UVa Run Time: 0.040s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    int N, S, T, ai[36], dp[36][230][230];

    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> N;
        S = 0;
        for (int i = 0; i < N; i++)
        {
            cin >> ai[i];
            S += ai[i];
        }
        sort(ai, ai + N, greater<int>());
        T = 0;
        for (int i = 0; i < (N / 3 + 1); i++)
            T += ai[i];
        for (int i = 0; i <= N; i++)
            for (int j = 0; j <= T; j++)
                for (int k = 0; k <= T; k++)
                    dp[i][j][k] = 0;
        dp[0][0][0] = 1;
        for (int i = 0; i < N; i++)
            for (int j = 0; j <= T; j++)
                for (int k = 0; k <= T; k++)
                    if (dp[i][j][k])
                    {
                        dp[i + 1][j][k] = 1;
                        if (j + ai[i] <= T) dp[i + 1][j + ai[i]][k] = 1;
                        if (k + ai[i] <= T) dp[i + 1][j][k + ai[i]] = 1;
                    }
        int M = 0x3f3f3f3f;
        for (int i = 0; i <= T; i++)
            for (int j = 0; j <= T; j++)
                if (dp[N][i][j])
                    M = min(M, max(i, max(j, S - (i + j))) - min(i, min(j, S - (i + j))));
        cout << "Case " << cs << ": " << M << '\n';
    }

    return 0;
}
