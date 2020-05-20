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

int N, m;
long long dp[32][32][2];

long long dfs(int i, int j, int mode)
{
    if (i == 1 && j == 1) return 1;
    if (~dp[i][j][mode]) return dp[i][j][mode];
    long long r = 0;
    if (mode == HIGHER) {
        for (int k = j; k < i; k++)
            r += dfs(i - 1, k, LOWER);
    } else {
        for (int k = 1; k < j; k++)
            r += dfs(i - 1, k, HIGHER);
    }
    return dp[i][j][mode] = r;
}

int main(int argc, char *argv[])
{
    memset(dp, -1, sizeof(dp));
    while (cin >> N >> m) {
        if (N <= 2) { cout << "1\n"; continue; }
        long long r = 0;
        if (m == 1) r = dfs(N - 1, 2, LOWER);
        else {
            for (int i = 1; i < m; i++)
                r += dfs(N - 1, i, HIGHER);
        }
        cout << r << '\n';
    }
    return 0;
}
