// The Poor Giant
// UVa ID: 10688
// Verdict: Accepted
// Submission Date: 2018-01-28
// UVa Run Time: 0.070s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int dp[510][510];

int dfs(int n, int k)
{
    if (n <= 1) return dp[n][k] = 0;
    if (dp[n][k] == -1)
    {
        dp[n][k] = 0x3fffffff;
        for (int i = 1; i <= n; i++)
            dp[n][k] = min(dp[n][k], n * (k + i) + dfs(i - 1, k) + dfs(n - i, k + i));
    }
    return dp[n][k];
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, n, k;
    cin >> cases;
    memset(dp, -1, sizeof(dp));
    for (int c = 1; c <= cases; c++)
    {
        cin >> n >> k;
        dfs(n, k);
        cout << "Case " << c << ": " << dp[n][k] << '\n';
    }

    return 0;
}
