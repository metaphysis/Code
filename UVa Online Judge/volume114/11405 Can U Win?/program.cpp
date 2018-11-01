// Can U Win?
// UVa ID: 11405
// Verdict: Accepted
// Submission Date: 2018-11-01
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f;

struct NODE
{
    int x, y, w;
} nuts[10];

int dp[10][1 << 10];
int X, Y, M, dist[10][10], visited[10][10], N, indexer[128];
int offset[8][2] = {{-1, -2}, {-2, -1}, {-2, 1}, {-1, 2}, {1, 2}, {2, 1}, {2, -1}, {1, -2}};
char grid[10][10];

int dfs(int u, int mask)
{
    if (mask == (1 << N) - 1) return 0;
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
        if (grid[u.x][u.y] == 'k' || grid[u.x][u.y] == 'P')
            dist[id][indexer[u.x * Y + u.y]] = u.w;
        for (int k = 0; k < 8; k++)
        {
            int nextx = u.x + offset[k][0], nexty = u.y + offset[k][1];
            if (nextx < 0 || nextx >= X || nexty < 0 || nexty >= Y) continue;
            if (grid[nextx][nexty] == 'p' || grid[nextx][nexty] == 'K') continue;
            if (visited[nextx][nexty]) continue;
            visited[nextx][nexty] = 1;
            q.push(NODE{nextx, nexty, u.w + 1});
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> M;
        X = Y = 8;
        int Lx, Ly;
        for (int i = 0; i < X; i++)
            for (int j = 0; j < Y; j++)
            {
                cin >> grid[i][j];
                if (grid[i][j] == 'k')
                    Lx = i, Ly = j;
            }

        N = 0;
        indexer[Lx * Y + Ly] = N;
        nuts[N++] = NODE{Lx, Ly, 0};
        for (int i = 0; i < X; i++)
            for (int j = 0; j < Y; j++)
                if (grid[i][j] == 'P')
                {
                    indexer[i * Y + j] = N;
                    nuts[N++] = NODE{i, j, 0};
                }

        memset(dist, INF, sizeof(dist));
        for (int i = 0; i < N; i++)
            bfs(nuts[i], i);

        int flag = 1;
        for (int i = 0; i < N; i++)
            if (dist[0][i] == INF)
            {
                flag = 0;
                break;
            }
        if (!flag)
        {
            cout << "No\n";
            continue;
        }

        memset(dp, -1, sizeof(dp));
        int m = dfs(0, 1);
        if (m <= M) cout << "Yes\n";
        else cout << "No\n";
    }

    return 0;
}
