// Getaway
// UVa ID: 949
// Verdict: Accepted
// Submission Date: 2017-03-13
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

struct state
{
    int x, y, seconds;
    
    bool operator<(const state& a) const
    {
        return seconds > a.seconds;
    }
};

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
    
    int grid[100][100][4][4], visited[100][100], nv, nh;
    unordered_map<int, int> monitor;
    int offset[4][2] = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
    
    while (cin >> nv >> nh)
    {
        memset(grid, 0, sizeof(grid));
        memset(visited, 0, sizeof(visited));
        monitor.clear();
        
        int r, x1, y1, x2, y2;
        cin >> r;
        for (int i = 1; i <= r; i++)
        {
            cin >> x1 >> y1 >> x2 >> y2;
            grid[x1][y1][x2 - x1 + 1][y2 - y1 + 1] = 1;
        }
        
        int m, t;
        cin >> m;
        for (int i = 1; i <= m; i++)
        {
            cin >> t >> x1 >> y1;
            monitor[t] = y1 * nv + x1;
        }
        
        priority_queue<state> unvisited;
        unvisited.push(state{0, 0, 0});
        visited[0][0] = 1;
        
        while (!unvisited.empty())
        {
            state current = unvisited.top();
            unvisited.pop();
            
            if (current.x == (nv - 1) && current.y == (nh - 1))
            {
                cout << current.seconds << '\n';
                break;
            }
            
            int x = current.x, y = current.y;
            
            for (int k = 0; k < 4; k++)
            {
                int xx = current.x + offset[k][0], yy = current.y + offset[k][1];
                if (xx >= 0 && xx < nv && yy >= 0 && yy < nh)
                    if(!visited[xx][yy] && !grid[x][y][offset[k][0] + 1][offset[k][1] + 1])
                    {
                        visited[xx][yy] = 1;
                        int tt = current.seconds + 1;
                        while (monitor.find(tt) != monitor.end() && monitor[tt] == (yy * nv + xx)) tt++;
                        unvisited.push(state{xx, yy, tt});
                    }
            }
        }
    }
    
    return 0;
}
