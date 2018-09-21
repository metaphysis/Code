// Optimal Binary Search Tree
// UVa ID: 10304
// Verdict: Accepted
// Submission Date: 2018-09-21
// UVa Run Time: 0.610s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int INF = 0x7f7f7f7f;

int n, e[256], dp[256][256], sum[256];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> n)
    {
        sum[0] = 0;
        for (int i = 1; i <= n; i++)
        {
            cin >> e[i];
            sum[i] = e[i] + sum[i - 1];
        }

        memset(dp, 0, sizeof(dp));
        for (int L = 2; L <= n; L++)
            for (int i = 1, j = L; j <= n; i++, j++)
            {
                dp[i][j] = INF;
                for (int k = i; k <= j; k++)
                {
                    int next = dp[i][k - 1] + dp[k + 1][j] + sum[j] - sum[i - 1] - e[k];
                    dp[i][j] = min(dp[i][j], next);
                }
            }
        cout << dp[1][n] << '\n';
    }

    return 0;
}
