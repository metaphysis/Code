// Car Rallying
// UVa ID: 959
// Verdict: Accepted
// Submission Date: 2018-11-08
// UVa Run Time: 0.070
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f;

int A, B, C;
int track[10010], dp[10010][25], speed[10010][25];

void build()
{
    for (int i = 0; i < C; i++)
    {
        speed[i][0] = track[i];
        for (int j = 1; j < 25 && i + j < C; j++)
            speed[i][j] = min(speed[i][j - 1], track[i + j]);
    }
}

int dfs(int spot, int v)
{
    if (spot == C) return 0;
    if (~dp[spot][v]) return dp[spot][v];
    int r = INF;
    for (int a = 0; a <= A; a++)
    {
        if (v + a == 0) continue;
        int next = min(spot + v + a - 1, C - 1);
        if (speed[spot][next - spot] < v + a) break;
        r = min(r, 1 + dfs(next + 1, v + a));
    }
    for (int b = 0; b <= B; b++)
    {
        if (v - b <= 0) break;
        int next = min(spot + v - b - 1, C - 1);
        if (speed[spot][next - spot] < v - b) continue;
        r = min(r, 1 + dfs(next + 1, v - b));
    }
    return dp[spot][v] = r;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, N, V;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> A >> B;
        A /= 10, B /= 10, C = 0;
        while (cin >> N >> V)
        {
            if (N == 0 && V == 0) break;
            V /= 10;
            for (int i = 0; i < N; i++)
                track[C++] = V;
        }
        track[C++] = 1000;
        build();
        memset(dp, -1, sizeof(dp));
        cout << dfs(0, 0) << '\n';
    }

    return 0;
}
