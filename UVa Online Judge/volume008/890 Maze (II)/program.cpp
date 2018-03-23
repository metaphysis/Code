// Maze (II)
// UVa ID: 890
// Verdict: Accepted
// Submission Date: 2018-03-23
// UVa Run Time: 0.050s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

char command, board[80][80];
int M, N, visited[40][40], offset[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
int wall[40][40][4];
map<char, int> direction = {{'U', 0}, {'R', 1}, {'D', 2}, {'L', 3}};

bool allVisited(int r, int c)
{
    for (int k = 0; k < 4; k++)
    {
        int nextr = r + offset[k][0], nextc = c + offset[k][1];
        if (nextr >= 1 && nextr <= M && nextc >= 1 && nextc <= N)
            if (!visited[nextr][nextc])
                return false;
    }
    return true;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, r, c, n;
    cin >> cases;
    while (cases--)
    {
        cin >> M >> N >> r >> c;

        memset(visited, 0, sizeof(visited));
        memset(wall, 1, sizeof(wall));
        vector<int> rows, clns;
        rows.push_back(r); clns.push_back(c);
        visited[r][c] = 1;

        while (rows.size())
        {
            r = rows.back(), c = clns.back();
            if (allVisited(r, c))
            {
                rows.pop_back(); clns.pop_back();
                continue;
            }
            cin >> command;
            if (command == 'F')
            {
                cin >> n;
                reverse(rows.begin() + n - 1, rows.end());
                reverse(clns.begin() + n - 1, clns.end());
            }
            else
            {
                int k = direction[command];
                int nextr = r + offset[k][0], nextc = c + offset[k][1];
                rows.push_back(nextr), clns.push_back(nextc);
                wall[r][c][k] = wall[nextr][nextc][(k + 2) % 4] = 0;
                visited[nextr][nextc] = 1;
            }
        }

        memset(board, ' ', sizeof(board));
        for (int i = M; i >= 1; i--)
            for (int j = 1; j <= N; j++)
            {
                if (wall[i][j][0]) board[2 * (M - i) + 1][2 * j] = '_';
                if (wall[i][j][1]) board[2 * (M - i) + 2][2 * j + 1] = '|';
                if (wall[i][j][2]) board[2 * (M - i) + 2][2 * j] = '_';
                if (wall[i][j][3]) board[2 * (M - i) + 2][2 * j - 1] = '|';
            }
        M = 2 * M + 1, N = 2 * N + 1;
        for (int i = 1; i <= M; i++)
        {
            if (i >= 3 && (i - 3) % 2 == 0) continue;
            for (int j = 1; j <= N; j++)
            {
                if (i == 1 && j == N) break;
                cout << board[i][j];
            }
            cout << '\n';
        }
        cout << '\n';
    }

    return 0;
}
