// Help the Winners
// UVa ID: 12030
// Verdict: Accepted
// Submission Date: 2018-10-10
// UVa Run Time: 0.100s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int N, g[16][16];
long long dp[1 << 16][2], T[16];

long long dfs(int idx, int mask, int state)
{
    if (idx == N) return state;
    if (~dp[mask][state]) return dp[mask][state];

    long long r = 0;
    for (int i = 0; i < N; i++)
    {
        if (mask & (1 << i)) continue;
        if (state == 0)
        {
            if (g[idx][i] == 2)
                r += T[N - 1 - idx];
            else
                r += dfs(idx + 1, mask | (1 << i), 0);
        }
        else if (state == 1)
        {
            if (g[idx][i] == 1)
                r += dfs(idx + 1, mask | (1 << i), 1);
        }
    }

    return dp[mask][state] = r;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    T[0] = 1;
    for (long long i = 1LL; i <= 15LL; i++)
        T[i] = T[i - 1] * i;

    int cases;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> N;
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                cin >> g[i][j];
        memset(dp, -1, sizeof(dp));
        long long r = dfs(0, 0, 1) + dfs(0, 0, 0);
        cout << "Case " << cs << ": " << r << '\n';
    }

    return 0;
}
