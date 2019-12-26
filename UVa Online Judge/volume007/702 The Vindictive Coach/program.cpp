// The Vindictive Coach
// UVa ID: 702
// Verdict: TLE
// Submission Date: 2018-09-30
// UVa Run Time: 3.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int HIGHER = 0, LOWER = 1;

int N, m, ONES;
long long dp[1 << 22][22][2];

long long dfs(int mask, int last, int mode)
{
    if (~dp[mask][last][mode]) return dp[mask][last][mode];
    if (mask == ONES) return 1LL;
    long long r = 0;
    if (mode == HIGHER)
    {
        for (int bit = last + 1; bit < N; bit++)
        {
            if (mask & (1 << bit)) continue;
            r += dfs(mask | (1 << bit), bit, LOWER);
        }
    }
    else
    {
        for (int bit = 0; bit < last; bit++)
        {
            if (mask & (1 << bit)) continue;
            r += dfs(mask | (1 << bit), bit, HIGHER);
        }
    }
    return dp[mask][last][mode] = r;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> N >> m)
    {
        if (N <= 2)
        {
            cout << "1\n";
            continue;
        }
        for (int i = 0; i < (1 << N); i++)
            for (int j = 0; j < N; j++)
                dp[i][j][0] = dp[i][j][1] = -1;
        ONES = (1 << N) - 1;
        if (m == 1)
            cout << dfs(5, 2, LOWER) << '\n';
        else
            cout << dfs(1 << (m - 1), m - 1, LOWER) << '\n';
    }

    return 0;
}
