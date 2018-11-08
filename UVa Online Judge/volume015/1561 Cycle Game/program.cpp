// Cycle Game
// UVa ID: 1561
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int numbers[24], dp[24][32][32];

int dfs(int u, int left, int right)
{
    if (~dp[u][left][right]) return dp[u][left][right];
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, n, ai;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> n;
        for (int i = 0; i < n; i++)
            cin >> numbers[i];
        memset(dp, -1, sizeof(dp));
        dfs(0, numbers[n - 1], numbers[0]);
    }

    return 0;
}
