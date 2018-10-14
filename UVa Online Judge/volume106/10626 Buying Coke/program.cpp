// Buying Coke
// UVa ID: 10626
// Verdict: Accepted
// Submission Date: 2018-10-14
// UVa Run Time: 0.040s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int S, C, N1, N5, N10, INF = 0x3f3f3f3f;
int dp[151][151][51];

int dfs(int c, int n5, int n10)
{
    if (c == C) return 0;
    if (~dp[c][n5][n10]) return dp[c][n5][n10];
    int r = INF;
    if (n5 >= 2) r = min(r, 2 + dfs(c + 1, n5 - 2, n10));
    if (n5 >= 1 && (S - c * 8 - n5 * 5 - n10 * 10) >= 3) r = min(r, 4 + dfs(c + 1, n5 - 1, n10));
    if (n10 >= 1) r = min(r, 1 + dfs(c + 1, n5, n10 - 1));
    if (n10 >= 1 && (S - c * 8 - n5 * 5 - n10 * 10) >= 3) r = min(r, 4 + dfs(c + 1, n5 + 1, n10 - 1));
    if ((S - c * 8 - n5 * 5 - n10 * 10) >= 8) r = min(r, 8 + dfs(c + 1, n5, n10));
    return dp[c][n5][n10] = r;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> C >> N1 >> N5 >> N10;
        S = N1 + N5 * 5 + N10 * 10;
        memset(dp, -1, sizeof(dp));
        cout << dfs(0, N5, N10) << '\n';
    }

    return 0;
}
