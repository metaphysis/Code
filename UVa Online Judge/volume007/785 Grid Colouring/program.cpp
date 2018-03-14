// Grid Colouring
// UVa ID: 785
// Verdict: Accepted
// Submission Date: 2016-12-01
// UVa Run Time: 0.110s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

char maze[35][85];
int offset[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

void flood_fill(int i, int j, char old, char replaced)
{
    if (i >= 0 && i < 35 && j >= 0 && j < 85 && maze[i][j] == old)
    {
        maze[i][j] = replaced;
        for (int k = 0; k < 4; k++)
            flood_fill(i + offset[k][0], j + offset[k][1], old, target);
    }
}

int main(int argc, char *argv[])
{
    string line;
    while (getline(cin, line))
    {
        memset(maze, ' ', sizeof(maze));
        
        int rows = 0; char wall = 0;

        do
        {
            for (int i = 0; i < line.length(); i++)
            {
                maze[rows][i] = line[i];
                if (wall == 0 && line[i] != ' ') wall = line[i];
            }
            
            maze[rows++][line.length()] = '\n';

        } while (getline(cin, line), line.front() != '_');

        for (int i = 0; i < rows; i++)
            for (int j = 0; j < 85; j++)
            {
                if (maze[i][j] == '\n') break;
                if (maze[i][j] != wall && maze[i][j] != ' ')
                {
                    char replaced = maze[i][j];
                    maze[i][j] = ' ';
                    flood_fill(i, j, ' ', replaced);
                }
            }

        for (int i = 0; i < rows; i++)
            for (int j = 0; j < 85; j++)
            {
                cout << maze[i][j];
                if (maze[i][j] == '\n') break;
            }

        cout << line << '\n';
    }
    
	return 0;
}
