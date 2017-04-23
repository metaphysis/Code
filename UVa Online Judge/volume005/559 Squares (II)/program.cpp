// Squares (II)
// UVa ID: 559
// Verdict: 
// Submission Date: 
// UVa Run Time: s
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
#include <vector>

using namespace std;

int games, h, w, m, grid[1100][1100] = {0};

void findMaximumSquare(int &r, int &c, int &s, bool largest)
{
    s = 0;
    for (int i = 1; i <= h; i++)
        for (int j = w; j >= 1; j--)
        {
            if (grid[i][j])
            {
                if (j <= (w - 1))
                    grid[i][j] = min(grid[i - 1][j], min(grid[i - 1][j + 1], grid[i][j + 1])) + 1;
                else
                    grid[i][j] = 1;
                
                if (largest)
                {
                    if (s < grid[i][j] || (s == grid[i][j] && (i > r || j < c)))
                    {
                        s = grid[i][j];
                        r = i, c = j;
                    }
                }
                else
                {
                    if (i == r && j == c)
                        break;
                }
            }
        }
        
    if (!largest) s = grid[r][c];
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    cin >> games;
    
    int r, c, s;
    for (int g = 1; g <= games; g++)
    {
        cin >> h >> w >> m;
        
        for (int y = 1; y <= h; y++)
            for (int x = 1; x <= w; x++)
                grid[y][x] = 1;

        for (int i = 1; i <= m; i++)
        {
            cin >> r >> c;

            r = h - r + 1;
            findMaximumSquare(r, c, s, false);

            // fill the occupied cell.
            for (int y = 0; y < s; y++)
                for (int x = 0; x < s; x++)
                    grid[r - y][c + x] = 0;
        }
        
        findMaximumSquare(r, c, s, true);
        
        if (s == 0)
            cout << "game over\n";
        else
        {
            r = h - r + 1;
            cout << r << ' ' << c << ' ' << s << '\n';
        }
    }
    
	return 0;
}
