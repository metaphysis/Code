// Teletransport
// UVa ID: 12796
// Verdict: Accepted
// Submission Date: 2022-10-09
// UVa Run Time: 0.370s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int M[110][110], R[110][110], TMP[110][110], N, L, S, T, MOD = 10000;
    while (cin >> N >> L)
    {
        cin >> S >> T;
        memset(M, 0, sizeof M);
        for (int i = 1; i <= N; i++)
            for (int j = 1, p; j <= 4; j++)
            {
                cin >> p;
                M[i][p]++;
            }
        memset(R, 0, sizeof R);
        for (int i = 1; i <= N; i++) R[i][i] = 1;
        while (L)
        {
            if (L & 1)
            {
                memset(TMP, 0, sizeof TMP);
                for (int i = 1; i <= N; i++)
                    for (int j = 1; j <= N; j++)
                    {
                        for (int k = 1; k <= N; k++)
                            TMP[i][j] += R[i][k] * M[k][j] % MOD;
                        TMP[i][j] %= MOD;
                    }
                for (int i = 1; i <= N; i++)
                    for (int j = 1; j <= N; j++)
                        R[i][j] = TMP[i][j];
            }
            memset(TMP, 0, sizeof TMP);
            for (int i = 1; i <= N; i++)
                for (int j = 1; j <= N; j++)
                {
                    for (int k = 1; k <= N; k++)
                        TMP[i][j] += M[i][k] * M[k][j] % MOD;
                    TMP[i][j] %= MOD;
                }
            for (int i = 1; i <= N; i++)
                for (int j = 1; j <= N; j++)
                    M[i][j] = TMP[i][j];
            L >>= 1;
        }
        cout << R[S][T] << '\n';
    }
    return 0;
}
