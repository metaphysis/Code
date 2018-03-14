// The Same Game
// UVa ID: 758
// Verdict: Accepted
// Submission Date: 2017-10-22
// UVa Run Time: 0.060s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

char maze[10][15], shadow[10][15];
int visited[10][15], offset[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

void floodFill(int i, int j, char old, int &cnt)
{
    if (i >= 0 && i <= 9 && j >= 0 && j <= 14 && !visited[i][j] && maze[i][j] == old)
    {
        cnt++;
        visited[i][j] = 1;
        for (int k = 0; k < 4; k++)
            floodFill(i + offset[k][0], j + offset[k][1], old, cnt);
    }
}

void remove(int i, int j, char old, char replaced)
{
    if (i >= 0 && i <= 9 && j >= 0 && j <= 14 && maze[i][j] == old)
    {
        maze[i][j] = replaced;
        for (int k = 0; k < 4; k++)
            remove(i + offset[k][0], j + offset[k][1], old, replaced);
    }
}

void compress()
{
    memset(shadow, '0', sizeof(shadow));
    for (int i = 0, x = 0; i < 15; i++)
    {
        int y = 9;
        for (int j = 9; j >= 0; j--)
        {
            if (maze[j][i] != '0')
            {
                shadow[y][x] = maze[j][i];
                y--;
            }
        }
        if (y != 9) x++;
    }
    memcpy(maze, shadow, sizeof(shadow));
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0;
    
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        if (c > 1) cout << '\n';
        cout << "Game " << c << ":\n\n";

        for (int i = 0; i < 10; i++)
            for (int j = 0; j < 15; j++)
                cin >> maze[i][j];
                
        int balls = 150, score = 0, step = 1;
        while (true)
        {
            memset(visited, 0, sizeof(visited));
            int removed = 0, row = -1, column = -1;
            for (int i = 0; i < 15; i++)
                for (int j = 9; j >= 0; j--)
                {
                    if (visited[j][i] || maze[j][i] == '0') continue;
                    int cnt = 0;
                    floodFill(j, i, maze[j][i], cnt);
                    if (removed < cnt) removed = cnt, row = j, column = i;
                }

            if (removed == 1) break;
            cout << "Move " << step++;
            cout << " at (" << (10 - row) << ',' << (column + 1);
            cout << "): removed " << removed << " balls of color ";
            cout << maze[row][column] << ", got ";
            cout << (removed - 2) * (removed - 2) << " points.\n";
            balls -= removed;
            score += (removed - 2) * (removed - 2);

            if (balls == 0) break;
            remove(row, column, maze[row][column], '0');
            compress();
        }
        if (balls == 0) score += 1000;
        cout << "Final score: " << score << ", with " << balls << " balls remaining.\n";
    }

    return 0;
}
