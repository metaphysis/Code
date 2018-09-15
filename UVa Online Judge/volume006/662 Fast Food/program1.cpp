// Fast Food
// UVa ID: 662
// Verdict: Accepted
// Submission Date: 2018-09-15
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int dist[201], path[31][201], dp[31][201];
int cost[201][201] = { 0 };

void dfs(int k, int n)
{
    if (k)
    {
        int up = path[k][n] + 1, middle = (up + n) / 2;
        dfs(k - 1, path[k][n]);
        if (up == n)
        {
            cout << "Depot " << k << " at restaurant " << middle;
            cout << " serves restaurant " << n << '\n';
        }
        else
        {
            cout << "Depot " << k << " at restaurant " << middle;
            cout << " serves restaurants " << up << " to " << n << '\n';
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0, N, K;
    while (cin >> N >> K)
    {
        if (N == 0) break;
        for (int i = 1; i <= N; ++i)
            cin >> dist[i];

        for (int i = 1; i <= N; ++i)
            for (int j = i; j <= N; ++j)
            {
                cost[i][j] = 0;
                int middle = (j + i) >> 1;
                for (int k = i; k <= j; ++k)
                    cost[i][j] += abs(dist[k] - dist[middle]);
            }
        for (int i = 1; i <= N; ++i)
            dp[1][i] = cost[1][i];

        for (int i = 2; i <= K; ++i)
            for (int j = i; j <= N; ++j)
            {
                dp[i][j] = 0x3f3f3f3f;
                for (int k = i - 1; k < j; ++k)
                {
                    if (dp[i][j] > dp[i - 1][k] + cost[k + 1][j])
                    {
                        dp[i][j] = dp[i - 1][k] + cost[k + 1][j];
                        path[i][j] = k;
                    }
                }
            }

        cout << "Chain " << ++cases << '\n';
        dfs(K, N);
        cout << "Total distance sum = " << dp[K][N] << "\n\n";
    }

    return 0;
}
