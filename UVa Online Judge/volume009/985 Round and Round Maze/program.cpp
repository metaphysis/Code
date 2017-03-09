// Round and Round Maze
// UVa ID: 985
// Verdict: Accepted
// Submission Date: 2017-03-08
// UVa Run Time: 0.150s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

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
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

struct step
{
    int x, y, time, moves;
};

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int grid[510][510][4][4];
    int visited[510][510][4];
    int R, C;
    int offset[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    string plate;
    
    while (cin >> R >> C)
    {
        memset(grid, 0, sizeof(grid));

        int T = R * C - 1;
        for (int k = 0; k < T; k++)
        {
            int i = k / C, j = k % C;
            
            cin >> plate;

            if (plate.find('N') != plate.npos) grid[i][j][0][0] = 1;
            if (plate.find('E') != plate.npos) grid[i][j][0][1] = 1;
            if (plate.find('S') != plate.npos) grid[i][j][0][2] = 1;
            if (plate.find('W') != plate.npos) grid[i][j][0][3] = 1;
            
            for (int t = 1; t <= 3; t++)
            {
                if (grid[i][j][t - 1][3]) grid[i][j][t][0] = 1;
                if (grid[i][j][t - 1][0]) grid[i][j][t][1] = 1;
                if (grid[i][j][t - 1][1]) grid[i][j][t][2] = 1;
                if (grid[i][j][t - 1][2]) grid[i][j][t][3] = 1;
            }
        }
        
        memset(visited, 0, sizeof(visited));

        queue<step> unvisited;
        step start = step{0, 0, 0, 0};
        unvisited.push(start);
        
        int totalMoves = 0;
        while (!unvisited.empty())
        {
            step current = unvisited.front();
            unvisited.pop();
            
            if (current.x == (R - 1) && current.y == (C - 1))
            {
                totalMoves = current.moves;
                break;
            }

            for (int d = 0; d < 4; d++)
            {
                if (grid[current.x][current.y][current.time][d])
                {
                    int xx = current.x + offset[d][0], yy = current.y + offset[d][1];
                    int tt = (current.time + 1) % 4;
                    if (xx >= 0 && xx < R && yy >= 0 && yy < C && !visited[xx][yy][tt])
                    {
                        visited[xx][yy][tt] = 1;
                        step next = step{xx, yy, tt, current.moves + 1};
                        unvisited.push(next);
                    }
                }
            }
        }
        
        if (totalMoves == 0)
            cout << "no path to exit\n";
        else
            cout << totalMoves << '\n';
    }
    
    return 0;
}
