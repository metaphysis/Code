// Optimal Binary Search Tree
// UVa ID: 10304
// Verdict: Accepted
// Submission Date: 2018-09-20
// UVa Run Time: 1.620s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int INF = 0x7f7f7f7f;

int n, f[256], dp[256][256], sum[256];

int dfs(int l, int r)
{
    if (l >= r) return dp[l][r] = 0;
    if (~dp[l][r]) return dp[l][r];
    dp[l][r] = INF;
    for (int k = l; k <= r; k++)
        dp[l][r] = min(dp[l][r], dfs(l, k - 1) + dfs(k + 1, r) + sum[r] - sum[l - 1] - f[k]);
    return dp[l][r];
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> n)
    {
        sum[0] = 0;
        for (int i = 1; i <= n; i++)
        {
            cin >> f[i];
            sum[i] = f[i] + sum[i - 1];
        }
        memset(dp, -1, sizeof(dp));
        cout << dfs(1, n) << '\n';
    }

    return 0;
}
