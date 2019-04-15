// Snakes and Ladders
// UVa ID: 12910
// Verdict: Wrong Answer
// Submission Date: 2019-04-14
// UVa Run Time: 0.020s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int M = 256, N = 4096;

int W, H, S, advanced[M];
double dp[M][N];

double dfs(int block, int depth)
{
    if (block == W * H) return 0.0;
    if (dp[block][depth] >= 0) return dp[block][depth];
    if (depth >= N) return 0.0;
    double r = 1.0;
    for (int i = 1; i <= 6; i++)
    {
        int next = block + i, deepen = 0;
        if (next > W * H) next = 2 * W * H - next, deepen = 1;
        if (advanced[next] < next) deepen = 1;
        r += dfs(advanced[next], depth + deepen) / 6.0;
    }
    return dp[block][depth] = r;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> W >> H >> S)
    {
        iota(advanced, advanced + M, 0);
        for (int i = 1, ui, vi; i <= S; i++)
        {
            cin >> ui >> vi;
            advanced[ui] = vi;
        }
        for (int i = 0; i < M; i++)
            for (int j = 0; j < N; j++)
                dp[i][j] = -1;
        cout << fixed << setprecision(8) << dfs(1, 0) << '\n';
    }

    return 0;
}
