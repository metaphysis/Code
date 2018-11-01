// Nuts for Nuts
// UVa ID: 10944
// Verdict: Accepted
// Submission Date: 2018-10-31
// UVa Run Time: 0.020s
//
// 版权所有（N）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f;

struct NODE
{
    int x, y, w;
} nuts[24];

int dp[16][1 << 16];
int X, Y, dist[24][24], visited[24][24], N, indexer[512];
char grid[24][24];

int dfs(int u, int mask)
{
    if (mask == (1 << N) - 1) return dist[u][0];
    if (~dp[u][mask]) return dp[u][mask];
    int r = INF;
    for (int v = 0; v < N; v++)
        if (v != u && !(mask & (1 << v)))
            r = min(r, dist[u][v] + dfs(v, mask | (1 << v)));
    return dp[u][mask] = r;
}

void bfs(NODE u, int id)
{
    queue<NODE> q;
    q.push(u);
    memset(visited, 0, sizeof(visited));
    visited[u.x][u.y] = 1;
    while (!q.empty())
    {
        u = q.front(); q.pop();
        if (grid[u.x][u.y] == '#' || grid[u.x][u.y] == 'L')
            dist[id][indexer[u.x * Y + u.y]] = u.w;
        for (int i = -1; i <= 1; i++)
            for (int j = -1; j <= 1; j++)
            {
                int nextx = u.x + i, nexty = u.y + j;
                if (nextx < 0 || nextx >= X || nexty < 0 || nexty >= Y) continue;
                if (visited[nextx][nexty]) continue;
                visited[nextx][nexty] = 1;
                q.push(NODE{nextx, nexty, u.w + 1});
            }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> X >> Y)
    {
        int Lx, Ly;
        for (int i = 0; i < X; i++)
            for (int j = 0; j < Y; j++)
            {
                cin >> grid[i][j];
                if (grid[i][j] == 'L')
                    Lx = i, Ly = j;
            }

        N = 0;
        indexer[Lx * Y + Ly] = N;
        nuts[N++] = NODE{Lx, Ly, 0};
        for (int i = 0; i < X; i++)
            for (int j = 0; j < Y; j++)
                if (grid[i][j] == '#')
                {
                    indexer[i * Y + j] = N;
                    nuts[N++] = NODE{i, j, 0};
                }

        for (int i = 0; i < N; i++)
            bfs(nuts[i], i);

        //for (int i = 0; i < N; i++)
        //    for (int j = 0; j < N; j++)
        //        dist[i][j] = max(abs(nuts[i].x - nuts[j].x), abs(nuts[i].y - nuts[j].y));

        memset(dp, -1, sizeof(dp));
        cout << dfs(0, 1) << '\n';
    }

    return 0;
}
