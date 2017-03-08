// Walking Around Wisely
// UVa ID: 926
// Verdict: Accepted
// Submission Date: 2017-03-08
// UVa Run Time: 0.000s
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

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases, n;
    long long grid[40][40];
    int startx, starty, endx, endy;
    int blocked[40][40][4], workers, wx, wy;
    char direction;
    
    cin >> cases;
    
    for (int c = 1; c <= cases; c++)
    {
        cin >> n >> startx >> starty >> endx >> endy;
        
        memset(blocked, 0, sizeof(blocked));
        
        cin >> workers;
        for (int i = 1; i <= workers; i++)
        {
            cin >> wx >> wy >> direction;
            
            if (direction == 'W') blocked[wx][wy][1] = 1;
            if (direction == 'S') blocked[wx][wy][2] = 1;
            if (direction == 'E') blocked[wx + 1][wy][1] = 1;
            if (direction == 'N') blocked[wx][wy + 1][2] = 1;
        }
        
        memset(grid, 0, sizeof(grid));
        
        grid[startx - 1][starty] = 1;
        blocked[startx][starty][1] = 0;
        
        for (int i = starty; i <= endy; i++)
            for (int j = startx; j <= endx; j++)
            {
                if (!blocked[j][i][1]) grid[j][i] += grid[j - 1][i];
                if (!blocked[j][i][2]) grid[j][i] += grid[j][i - 1];
            }
            
        cout << grid[endx][endy] << '\n';
    }
    
    return 0;
}
