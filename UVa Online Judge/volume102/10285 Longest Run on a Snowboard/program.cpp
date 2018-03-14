// Longest Run on a Snowboard
// UVa ID: 10285
// Verdict: Accepted
// Submission Date: 2018-02-14
// UVa Run Time: 0.650s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int R, C, grid[110][110], edges[110][110][4];
int offset[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
int visited[110][110], dist[110][110];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    string name;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> name >> R >> C;
        for (int i = 1; i <= R; i++)
            for (int j = 1; j <= C; j++)
                cin >> grid[i][j];

        int longest = 0;
        for (int i = 1; i <= R; i++)
            for (int j = 1; j <= C; j++)
            {
                memset(visited, 0, sizeof(visited));
                memset(dist, 0, sizeof(dist));
                queue<pair<int, int>> q;
                q.push(make_pair(i, j));
                visited[i][j] = dist[i][j] = 1;
                while (!q.empty())
                {
                    pair<int, int> u = q.front(); q.pop();
                    for (int k = 0; k < 4; k++)
                    {
                        int nexti = u.first + offset[k][0], nextj = u.second + offset[k][1];
                        if (nexti < 0 || nexti > R || nextj < 1 || nextj > C) continue;
                        if (grid[nexti][nextj] <= grid[u.first][u.second]) continue;
                        if (dist[nexti][nextj] < dist[u.first][u.second] + 1)
                        {
                            dist[nexti][nextj] = dist[u.first][u.second] + 1;
                            visited[nexti][nextj] = 1;
                            q.push(make_pair(nexti, nextj));
                        }
                    }
                }
                for (int i = 1; i <= R; i++)
                    for (int j = 1; j <= C; j++)
                        longest = max(longest, dist[i][j]);
            }
        cout << name << ": " << longest << '\n';
    }

    return 0;
}
