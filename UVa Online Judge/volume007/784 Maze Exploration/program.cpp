// Maze Exploration
// UVa ID: 784
// Verdict: Accepted
// Submission Date: 2016-11-29
// UVa Run Time: 0.010s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <vector>

using namespace std;

char maze[35][85];
int offset[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

void flood_fill(int i, int j, char old, char target)
{
    if (i >= 0 && i < 35 && j >= 0 && j < 85 && maze[i][j] == old)
    {
        maze[i][j] = target;

        for (int k = 0; k < 4; k++)
            flood_fill(i + offset[k][0], j + offset[k][1], old, target);
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases = 0;
    cin >> cases;
    cin.ignore(1024, '\n');

    for (int c = 1; c <= cases; c++)
    {
        memset(maze, ' ', sizeof(maze));

        string line;
        
        int r = 0, x = 0, y = 0;
        while (getline(cin, line), line.front() != '_')
        {
            int i = 0;
            for ( ; i < line.length(); i++)
            {
                maze[r][i] = line[i];
                if (line[i] == '*')
                {
                    x = r, y = i;
                }
            }
            
            maze[r][i] = '\n';
            r++;
        }

        maze[x][y] = ' ';
        flood_fill(x, y, ' ', '#');

        for (int i = 0; i < r; i++)
            for (int j = 0; j < 80; j++)
            {
                cout << maze[i][j];
                if (maze[i][j] == '\n')
                    break;
            }

        cout << line << '\n';
    }
    
	return 0;
}
