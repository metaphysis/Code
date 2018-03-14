// Gathering cell
// UVa ID: 11487
// Verdict: Accepted
// Submission Date: 2018-02-24
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 12, INF = 0x3f3f3f3f, MOD = 20437;

struct cell
{
    int i, j;
    cell (int i = 0, int j = 0): i(i), j(j) {}
};

int n, dist[MAXV][MAXV], path[MAXV][MAXV];
int offset[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
cell cells[32];
char grid[MAXV][MAXV];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0;
    while (cin >> n, n > 0)
    {
        int cnt = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
            {
                cin >> grid[i][j];
                if (isalpha(grid[i][j]))
                {
                    cells[grid[i][j] - 'A'] = cell(i, j);
                    cnt = max(cnt, grid[i][j] - 'A' + 1);
                }
            }

        bool impossible = false;
        int sumOfDist = 0, cntOfPath = 1;
        for (int i = 1; i < cnt; i++)
        {
            memset(dist, 0x3f, sizeof(dist));
            memset(path, 0, sizeof(path));

            cell c = cells[i - 1];
            queue<cell> q;
            q.push(c);
            dist[c.i][c.j] = 0;
            path[c.i][c.j] = 1;

            // BFS.
            while (!q.empty())
            {
                c = q.front(); q.pop();
                for (int k = 0; k < 4; k++)
                {
                    int nexti = c.i + offset[k][0], nextj = c.j + offset[k][1];
                    if (nexti >= 0 && nexti < n && nextj >= 0 && nextj < n)
                    {
                        if (dist[nexti][nextj] > dist[c.i][c.j] + 1)
                        {
                            dist[nexti][nextj] = dist[c.i][c.j] + 1;
                            path[nexti][nextj] = path[c.i][c.j];
                            if (grid[nexti][nextj] == '.')
                                q.push(cell(nexti, nextj));
                        }
                        else if (dist[nexti][nextj] == (dist[c.i][c.j] + 1))
                        {
                            path[nexti][nextj] += path[c.i][c.j];
                            path[nexti][nextj] %= MOD;
                        }
                    }
                }
            }

            // Food picked.
            grid[cells[i - 1].i][cells[i - 1].j] = '.';

            if (dist[cells[i].i][cells[i].j] == INF)
            {
                impossible = true;
                break;
            }

            sumOfDist += dist[cells[i].i][cells[i].j];
            cntOfPath *= path[cells[i].i][cells[i].j];
            cntOfPath %= MOD;
        }
        
        cout << "Case " << ++cases << ": ";
        if (impossible) cout << "Impossible\n";
        else cout << sumOfDist << ' ' << cntOfPath << '\n';
    }

    return 0;
}
