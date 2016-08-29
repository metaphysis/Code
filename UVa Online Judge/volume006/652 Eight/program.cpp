// Eight
// UVa ID: 652
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

struct state
{
    string grid, moves;
    int i, j;
};

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases, offset[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
    string move = "udrl";
    
    cin >> cases;
    
    for (int c = 1; c <= cases; c++)
    {
        if (c > 1)
            cout << '\n';
        
        string grid(9, 0);
        int location = 0;
        for (int i = 0; i < 9; i++)
        {
            cin >> grid[i];
            if (grid[i] == 'x')
            {
                location = i;
                grid[i] = '9';
            }
        }
        
        string target = "123456789", start;
        queue<state> unvisited;
        unvisited.push((state){grid, start, location / 3, location % 3});
        set<int> visited;
        
        bool unsolvable = true;
        while (!unvisited.empty())
        {
            state current = unvisited.front();
            unvisited.pop();
            
            if (current.grid == target)
            {
                cout << current.moves << '\n';
                unsolvable = false;
                break;
            }
            
            int tag = 0;
            for (int i = 0; i < current.grid.length(); i++)
                tag = tag * 10 + current.grid[i] - '0';

            if (visited.find(tag) == visited.end())
            {
                visited.insert(tag);
                for (int k = 0; k < 4; k++)
                {
                    int nexti = current.i + offset[k][0];
                    int nextj = current.j + offset[k][1];
                    
                    if (nexti >= 0 && nexti < 3 && nextj >= 0 && nextj < 3)
                    {
                        string next_grid = current.grid;
                        swap(next_grid[current.i * 3 + current.j], next_grid[nexti * 3 + nextj]);
                        unvisited.push((state){next_grid, current.moves + move[k], nexti, nextj});
                    }
                }
            }
        }
        
        if (unsolvable)
            cout << "unsolvable\n";
    }
    
	return 0;
}
