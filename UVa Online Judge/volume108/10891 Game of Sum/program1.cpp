// Game of Sum
// UVa ID: 10891
// Verdict: Accepted
// Submission Date: 2018-10-28
// UVa Run Time: 0.020s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int INF = 0x7f7f7f7f;
int n, visited[110][110];
int xi[110], sum[110], dp[110][110];

int dfs(int i, int j)
{
    if (visited[i][j] || i > j) return dp[i][j];
    visited[i][j] = 1;
    int r = -INF;
    for (int k = i; k <= j; k++)
    {
        r = max(r, sum[j] - sum[i - 1] - dfs(k + 1, j));
        r = max(r, sum[j] - sum[i - 1] - dfs(i, k - 1));
    }
    return dp[i][j] = r;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> n, n)
    {
        memset(sum, 0, sizeof(sum));
        for (int i = 1; i <= n; i++)
        {
            cin >> xi[i];
            sum[i] = xi[i] + sum[i - 1];
        }
        memset(visited, 0, sizeof(visited));
        memset(dp, 0, sizeof(dp));
        int r = dfs(1, n);
        cout << (2 * r - sum[n]) << '\n';
    }

    return 0;
}
