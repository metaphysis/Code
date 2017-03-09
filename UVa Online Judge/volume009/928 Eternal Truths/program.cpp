// Eternal Truths
// UVa ID: 928
// Verdict: Accepted
// Submission Date: 2017-03-09
// UVa Run Time: 0.040s
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
    int x, y, sequence, moves;
};

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    char grid[310][310];
    int visited[310][310][4][4];
    int cases, R, C, startx, starty, endx, endy;
    int offset[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> R >> C;
        memset(grid, 0, sizeof(grid));
        
        for (int i = 1; i <= R; i++)
            for (int j = 1; j <= C; j++)
            {
                cin >> grid[i][j];
                if (grid[i][j] == 'S') startx = i, starty = j;
                if (grid[i][j] == 'E') endx = i, endy = j;
            }
        
        memset(visited, 0, sizeof(visited));
        
        queue<step> unvisited;
        step start = step{startx, starty, 1, 0};
        unvisited.push(start);
        
        int totalMoves = 0;
        while (!unvisited.empty())
        {
            step current = unvisited.front();
            unvisited.pop();
            
            if (current.x == endx && current.y == endy)
            {
                totalMoves = current.moves;
                break;
            }
                    
            for (int d = 0; d < 4; d++)
            {
                int xx, yy, flag = 1;
                for (int i = 1; i <= current.sequence; i++)
                {
                    xx = current.x + offset[d][0] * i, yy = current.y + offset[d][1] * i;
                    if (xx > R || xx < 1 || yy > C || yy < 1 || grid[xx][yy] == '#')
                    {
                        flag = 0;
                        break;
                    }
                }
                if (flag && !visited[xx][yy][(current.sequence % 3) + 1][d])
                {
                    visited[xx][yy][(current.sequence % 3) + 1][d] = 1;
                    step next = step{xx, yy, (current.sequence % 3) + 1, current.moves + 1};
                    unvisited.push(next);
                }
            }
        }
        
        if (totalMoves == 0)
            cout << "NO\n";
        else
            cout << totalMoves << '\n';
    }
    
    return 0;
}
