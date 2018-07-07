// Maze
// UVa ID: 10890
// Verdict: Accepted
// Submission Date: 2018-07-06
// UVa Run Time: 0.040s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f;

int N, T, S, COST;
int X[40] = {0}, Y[40] = {0}, dist[40][40];

void dfs(int u, int mask, int cost)
{
    if (cost + dist[u][T - 1] >= COST) return;
    if (__builtin_popcount(mask) == S)
    {
        COST = min(COST, cost + dist[u][T - 1]);
        return;
    }
    for (int v = 1; v <= T - 2; v++)
        if (!(mask & (1 << v)))
            dfs(v, mask | (1 << v), cost + dist[u][v]);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int x, y, cases = 0;
    while (cin >> N >> T >> S)
    {
        if (N == 0) break;

        for (int i = 1; i <= T; i++)
            cin >> X[i] >> Y[i];
        X[T + 1] = Y[T + 1] = N - 1;
        T += 2;
        for (int i = 0; i < T; i++)
            for (int j = 0; j < T; j++)
                dist[i][j] = abs(X[i] - X[j]) + abs(Y[i] - Y[j]);

        COST = INF;
        dfs(0, 0, 0);

        cout << "Case " << ++cases << ": " << COST << '\n';
    }

    return 0;
}
