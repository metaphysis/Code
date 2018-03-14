// Sticker Collector Robot
// UVa ID: 11831
// Verdict: Accepted
// Submission Date: 2018-01-29
// UVa Run Time: 0.010s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    map<char, int> dir = {{'N', 0}, {'L', 1}, {'S', 2}, {'O', 3}};
    int n, m, s, x, y, d;
    int offset[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}}, visited[110][110];
    char grid[110][110], orientation, command;

    while (cin >> n >> m >> s, n > 0)
    {
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
            {
                cin >> grid[i][j];
                if (grid[i][j] != '*' && grid[i][j] != '.' && grid[i][j] != '#')
                    x = i, y = j;
            }
            
        int total = 0;
        d = dir[grid[x][y]];
        memset(visited, 0, sizeof(visited));
        for (int i = 1; i <= s; i++)
        {
            cin >> command;
            // Left turn.
            if (command == 'D')
            {
                d = (d + 1) % 4;
            }
            // Right turn.
            else if (command == 'E')
            {
                d = (d + 3) % 4;
            }
            else
            {
                int nextx = x + offset[d][0], nexty = y + offset[d][1];
                if (nextx < 1 || nexty < 1 || nextx > n || nexty > m) continue;
                if (grid[nextx][nexty] == '#') continue;
                x = nextx, y = nexty;
            }
            if (!visited[x][y] && grid[x][y] == '*')
                total++;
            visited[x][y] = 1;
        }
        cout << total << '\n';
    }

    return 0;
}
