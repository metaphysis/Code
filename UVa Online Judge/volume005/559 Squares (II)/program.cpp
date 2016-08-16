// Squares (II)
// UVa ID: 559
// Verdict: 
// Submission Date: 
// UVa Run Time: s
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

int games, h, w, m, grid[1100][1100];

int findMaximumSquare(int r, int c, int smallest)
{
    int size = smallest;
    while (true)
    {
        bool valid = true;
        int nextr = r + size, nextc = c;
        for (int s = 1; s <= size + 1; s++)
        {
            if (nextr > h || nextc > w || grid[nextr][nextc])
            {
                valid = false;
                break;
            }
            nextc += 1;
        }
        
        if (!valid)
            break;

        nextc = c + size;
        for (int s = 1; s <= size + 1; s++)
        {
            if (nextr < r || grid[nextr][nextc])
            {
                valid = false;
                break;
            }
            nextr -= 1;
        }
        
        if (!valid)
            break;
          
        size++;  
    }
            
    return size;
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    cin >> games;
    
    int r, c;
    for (int g = 1; g <= games; g++)
    {
        cin >> h >> w >> m;
        
        for (int y = 1; y <= h; y++)
            for (int x = 1; x <= w; x++)
                grid[y][x] = 0;

        for (int i = 1; i <= m; i++)
        {
            cin >> r >> c;
            int size = findMaximumSquare(r, c, 0);
            
            //cout << "r = " << r << " c = " << c << " size = " << size << '\n';

            for (int y = 0; y < size; y++)
                for (int x = 0; x < size; x++)
                    grid[r + y][c + x] = 1;
                    
            //for (int y = 1; y <= h; y++)
            //{
            //    for (int x = 1; x <= w; x++)
            //        cout << grid[y][x];
            //    cout << '\n';
            //}
        }
        
        int max_size = 0, max_x, max_y;
        for (int y = 1; y <= h; y++)
            for (int x = 1; x <= w; x++)
                if (!grid[y][x])
                {
                    int next_size = findMaximumSquare(y, x, max_size);
                    if (next_size > max_size)
                    {
                        max_size = next_size;
                        max_y = y;
                        max_x = x;
                    }
                }
        
        if (max_size == 0)
            cout << "game over\n";
        else
            cout << max_y << ' ' << max_x << ' ' << max_size << '\n';
    }
    
	return 0;
}
