// Simple Minded Hashing
// UVa ID: 10912
// Verdict: Accepted
// Submission Date: 2018-01-20
// UVa Run Time: 0.010s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int dp[30][360][30];

int dfs(int L, int S, int C)
{
    if (S < 0) return 0;
    if (S == 0)
    {
        if (L == 0) return 1;
        else return 0;
    }
    if (L == 0)
    {
        if (S == 0) return 1;
        else return 0;
    }

    if (dp[L][S][C] >= 0) return dp[L][S][C];

    dp[L][S][C] = 0;
    for (int c = 1; c <= C; c++)
        dp[L][S][C] += dfs(L - 1, S - c, c - 1);
    return dp[L][S][C];
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int L, S, cases = 0;
    memset(dp, -1, sizeof(dp));
    while (cin >> L >> S)
    {
        if (L == 0 && S == 0) break;
        cout << "Case " << ++cases << ": "; 
        if (L > 26 || S > 351) { cout << "0\n"; continue; }
        cout << dfs(L, S, 26) << '\n';
    }

    return 0;
}
