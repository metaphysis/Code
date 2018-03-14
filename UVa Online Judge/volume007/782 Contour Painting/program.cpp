// Contour Painting
// UVa ID: 782
// Verdict: Accepted
// Submission Date: 2017-10-24
// UVa Run Time: 0.020s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

char maze[40][100];
int rows = 0, visited[40][100];
int offsetx[4] = {0, 0, 1, -1}, offsety[4] = {1, -1, 0, 0};

void floodFill(int i, int j)
{
    if (i >= 0 && i < rows && j >= 0 && j < 100 && !visited[i][j] && maze[i][j] == ' ')
    {
        visited[i][j] = 1;
        bool flag = false;
        for (int k = 0; k < 4; k++)
        {
            int nexti = i + offsetx[k], nextj = j + offsety[k];
            if (nexti >= 0 && nexti < rows && nextj >= 0 && nextj < 100)
            {
                if (maze[nexti][nextj] != ' ' && maze[nexti][nextj] != '#')
                {
                    flag = true;
                    break;
                }
            }
        }
        if (flag)
            maze[i][j] = '#';
        for (int k = 0; k < 4; k++)
            floodFill(i + offsetx[k], j + offsety[k]);
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    cin.ignore(1024, '\n');
    
    string line;
    for (int c = 1; c <= cases; c++)
    {
        rows = 0;
        memset(maze, ' ', sizeof(maze));

        int stari, starj;
        while (getline(cin, line), line.front() != '_')
        {
            for (int i = 0; i < line.length(); i++)
            {
                maze[rows][i] = line[i];
                if (line[i] == '*')
                {
                    stari = rows;
                    starj = i;
                }
            }
            rows++;
        }

        maze[stari][starj] = ' ';
        memset(visited, 0, sizeof(visited));

        floodFill(stari, starj);
        
        for (int i = 0; i < rows; i++)
        {
            for (int columns = 99; columns >= 0; columns--)
            {
                if (maze[i][columns] != ' ')
                {
                    for (int j = 0; j <= columns; j++)
                        cout << maze[i][j];
                    break;
                }
            }
            cout << '\n';
        }
        cout << line << '\n';
    }

    return 0;
}
