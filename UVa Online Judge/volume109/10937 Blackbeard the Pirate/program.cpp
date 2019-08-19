// Blackbeard the Pirate
// UVa ID: 10937
// Verdict: Accepted
// Submission Date: 2018-11-01
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f;

struct NODE { int x, y, w; } nuts[24];

int dp[11][1 << 11];
int X, Y, g[16][16], visited[64][64], N, indexer[10240];
int offset[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
char grid[64][64];

int dfs(int u, int mask)
{
    if (mask == (1 << N) - 1) return g[u][0];
    if (~dp[u][mask]) return dp[u][mask];
    int r = INF;
    for (int v = 0; v < N; v++)
        if (v != u && !(mask & (1 << v)))
            r = min(r, g[u][v] + dfs(v, mask | (1 << v)));
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
        if (grid[u.x][u.y] == '!' || grid[u.x][u.y] == '@')
            g[id][indexer[u.x * Y + u.y]] = u.w;
        for (int k = 0; k < 4; k++)
        {
            int nextx = u.x + offset[k][0], nexty = u.y + offset[k][1];
            if (nextx < 0 || nextx >= X || nexty < 0 || nexty >= Y) continue;
            if (visited[nextx][nexty]) continue;
            if (grid[nextx][nexty] != '.' && grid[nextx][nexty] != '!' && grid[nextx][nexty] != '@') continue;
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
        if (X == 0) break;
        int Lx, Ly;
        for (int i = 0; i < X; i++)
            for (int j = 0; j < Y; j++)
            {
                cin >> grid[i][j];
                if (grid[i][j] == '@')
                    Lx = i, Ly = j;
            }

        N = 0;
        indexer[Lx * Y + Ly] = N;
        nuts[N++] = NODE{Lx, Ly, 0};
        for (int i = 0; i < X; i++)
            for (int j = 0; j < Y; j++)
                if (grid[i][j] == '!')
                {
                    indexer[i * Y + j] = N;
                    nuts[N++] = NODE{i, j, 0};
                }

        for (int i = 0; i < X; i++)
            for (int j = 0; j < Y; j++)
                if (grid[i][j] == '*')
                {
                    for (int ii = -1; ii <= 1; ii++)
                        for (int jj = -1; jj <= 1; jj++)
                        {
                            int nexti = i + ii, nextj = j + jj;
                            if (nexti < 0 || nexti >= X || nextj < 0 || nextj >= Y) continue;
                            if (grid[nexti][nextj] == '.' || grid[nexti][nextj] == '!' || grid[nexti][nextj] == '@')
                                grid[nexti][nextj] = 'X';
                        }
                }

        int C = 0;
        for (int i = 0; i < X; i++)
            for (int j = 0; j < Y; j++)
                if (grid[i][j] == '@' || grid[i][j] == '!')
                    C++;
        if (N != C)
        {
            cout << "-1\n";
            continue;
        }

        memset(g, INF, sizeof(g));
        for (int i = 0; i < N; i++)
            bfs(nuts[i], i);

        int flag = 1;
        for (int i = 0; i < N; i++)
            if (g[0][i] == INF)
            {
                flag = 0;
                break;
            }
        if (!flag)
        {
            cout << "-1\n";
            continue;
        }

        memset(dp, -1, sizeof(dp));
        cout << dfs(0, 1) << '\n';
    }

    return 0;
}
