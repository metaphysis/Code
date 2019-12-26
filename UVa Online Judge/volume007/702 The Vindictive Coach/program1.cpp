// The Vindictive Coach
// UVa ID: 702
// Verdict: Accepted
// Submission Date: 2018-10-11
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int HIGHER = 0, LOWER = 1;

int N, m, ONES;
long long dp[24][24][2];

long long dfs(int high, int low, int mode)
{
    if (high == 0 && low == 0) return 1;
    if ((high <= 0 && mode == LOWER) || (low <= 0 && mode == HIGHER)) return 0;
    if (~dp[high][low][mode]) return dp[high][low][mode];
    long long r = 0;
    if (mode == HIGHER)
    {
        for (int i = 1; i <= low; i++)
            r += dfs(high + i - 1, low - i, LOWER);
    }
    else
    {
        for (int i = 1; i <= high; i++)
            r += dfs(high - i, low + i - 1, HIGHER);
    }
    return dp[high][low][mode] = r;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    memset(dp, -1, sizeof(dp));
    while (cin >> N >> m)
    {
        if (N <= 2)
        {
            cout << "1\n";
            continue;
        }
        if (m == 1)
            cout << dfs(N - 3, 1, HIGHER) << '\n';
        else
            cout << dfs(N - m, m - 1, HIGHER) << '\n';
    }

    return 0;
}
