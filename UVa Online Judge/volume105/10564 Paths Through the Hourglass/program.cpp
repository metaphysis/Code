// Paths Through the Hourglass
// UVa ID: 10564
// Verdict: Accepted
// Submission Date: 2020-03-15
// UVa Run Time: 0.020s
//
// 版权所有（C）2020，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct data
{
    long long cnt;
    int idx;
    string path;
} dp[45][25][510];

int N, S, g[45][25];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> N >> S)
    {
        if (N == 0) break;

        memset(g, -1, sizeof g);
        for (int i = 1; i <= 2 * N; i++)
            for (int j = 1; j <= N; j++)
                for (int s = 0; s <= S; s++)
                {
                    dp[i][j][s].cnt = 0;
                    dp[i][j][s].idx = N + 1;
                }

        for (int j = 1; j <= N; j++)
        {
            cin >> g[1][j];
            dp[1][j][g[1][j]].cnt = 1;
            dp[1][j][g[1][j]].idx = j;
            dp[1][j][g[1][j]].path.clear();
        }

        for (int i = 2; i <= N; i++)
        {
            for (int j = 1; j <= (N - i + 1); j++)
            {
                cin >> g[i][j];
                for (int s = S; s >= g[i][j]; s--)
                {
                    if (dp[i - 1][j][s - g[i][j]].cnt)
                    {
                        dp[i][j][s].cnt += dp[i - 1][j][s - g[i][j]].cnt;
                        int idx = dp[i - 1][j][s - g[i][j]].idx;
                        string path = dp[i - 1][j][s - g[i][j]].path + 'R';
                        if (idx < dp[i][j][s].idx || (idx == dp[i][j][s].idx && path < dp[i][j][s].path))
                        {
                            dp[i][j][s].idx = idx;
                            dp[i][j][s].path = path;
                        }
                    }

                    if (dp[i - 1][j + 1][s - g[i][j]].cnt)
                    {
                        dp[i][j][s].cnt += dp[i - 1][j + 1][s - g[i][j]].cnt;
                        int idx = dp[i - 1][j + 1][s - g[i][j]].idx;
                        string path = dp[i - 1][j + 1][s - g[i][j]].path + 'L';
                        if (idx < dp[i][j][s].idx || (idx == dp[i][j][s].idx && path < dp[i][j][s].path))
                        {
                            dp[i][j][s].idx = idx;
                            dp[i][j][s].path = path;
                        }
                    }
                }
            }
        }

        for (int i = 1; i <= (N - 1); i++)
        {
            for (int j = 1; j <= (i + 1); j++)
            {
                cin >> g[N + i][j];
                for (int s = S; s >= g[N + i][j]; s--)
                {
                    if (j - 1 >= 1 && dp[N + i - 1][j - 1][s - g[N + i][j]].cnt)
                    {
                        dp[N + i][j][s].cnt += dp[N + i - 1][j - 1][s - g[N + i][j]].cnt;
                        int idx = dp[N + i - 1][j - 1][s - g[N + i][j]].idx;
                        string path = dp[N + i - 1][j - 1][s - g[N + i][j]].path + 'R';
                        if (idx < dp[N + i][j][s].idx || (idx == dp[N + i][j][s].idx && path < dp[N + i][j][s].path))
                        {
                            dp[N + i][j][s].idx = idx;
                            dp[N + i][j][s].path = path;
                        }
                    }
                    if (g[N + i - 1][j] != -1 && dp[N + i - 1][j][s - g[N + i][j]].cnt)
                    {
                        dp[N + i][j][s].cnt += dp[N + i - 1][j][s - g[N + i][j]].cnt;
                        int idx = dp[N + i - 1][j][s - g[N + i][j]].idx;
                        string path = dp[N + i - 1][j][s - g[N + i][j]].path + 'L';
                        if (idx < dp[N + i][j][s].idx || (idx == dp[N + i][j][s].idx && path < dp[N + i][j][s].path))
                        {
                            dp[N + i][j][s].idx = idx;
                            dp[N + i][j][s].path = path;
                        }
                    }
                }
            }
        }

        long long cnt = 0;
        int bestIdx = N + 1;
        string bestPath;
        for (int i = 1; i <= N; i++)
        {
            if (dp[2 * N - 1][i][S].cnt)
            {
                cnt += dp[2 * N - 1][i][S].cnt;
                if (dp[2 * N - 1][i][S].idx < bestIdx || (bestIdx == dp[2 * N - 1][i][S].idx && dp[2 * N - 1][i][S].path < bestPath))
                {
                    bestIdx = dp[2 * N - 1][i][S].idx;
                    bestPath = dp[2 * N - 1][i][S].path;
                }
            }
        }
        cout << cnt << '\n';
        if (cnt > 0) cout << (bestIdx - 1) << ' ' << bestPath;
        cout << '\n';
    }

    return 0;
}
