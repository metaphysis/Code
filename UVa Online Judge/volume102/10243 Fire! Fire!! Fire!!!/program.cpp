// Fire! Fire!! Fire!!!
// UVa ID: 10243
// Verdict: Accepted
// Submission Date: 2016-11-08
// UVa Run Time: 0.000s
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

const int MAXV = 1010;

int g[MAXV][MAXV], colored[MAXV], visited[MAXV], cx[MAXV], cy[MAXV], nx;

// 使用深度优先搜索寻找增广路，一次搜索只能使当前的匹配数增加1。
int dfs(int u)
{
    for (int v = 1; v <= nx; v++)
        if (g[u][v] && !visited[v])
        {
            // 如果v尚未匹配或者v已经匹配但是从v出发可以找到增广路则匹配成功。
            visited[v] = 1;
            if (!cy[v] || dfs(cy[v]))
            {
                // 更改匹配。
                cx[u] = v;
                cy[v] = u;
                return 1;
            }
        }
        
    // 未能找到增广路，已经是最大匹配。
    return 0;
}

// 匈牙利算法求最大匹配数。
int hungarian()
{
    int matches = 0;
    memset(cx, 0, sizeof(cx)); memset(cy, 0, sizeof(cy));

    for (int i = 1; i <= nx; i++)
        if (!cx[i])
        {
            // 注意寻找之前需要将访问标记置为初始状态。
            memset(visited, 0, sizeof(visited));
            
            // 每找到一条增广路，可使得匹配数增加1。
            matches += dfs(i);
        }

    return matches;
}

int main(int argc, char *argv[])
{
    while (cin >> nx, nx > 0)
    {
        // 建立二部图。
        memset(g, 0, sizeof(g));
        
        
        for (int t, y, x = 1; x <= nx; x++)
        {
            cin >> t;
            for (int i = 1; i <= t; i++)
            {
                cin >> y;
                g[x][y] = g[y][x] = 1;
            }
        }

        memset(colored, 0, sizeof(colored));
        memset(visited, 0, sizeof(visited));
        
        queue<int> unvisited;
        unvisited.push(1);
        visited[1] = 1;

        while (!unvisited.empty())
        {
            int u = unvisited.front();
            unvisited.pop();
            
            for (int v = 1; v <= nx; v++)
                if (g[u][v] && !visited[v])
                {
                    visited[v] = 1;
                    colored[v] = !colored[u];
                    unvisited.push(v);
                }
        }
        
        for (int u = 1; u <= nx; u++)
            for (int v = u + 1; v <= nx; v++)
                if (colored[u] == colored[v])
                    g[u][v] = g[v][u] = 0;

        for (int u = 1; u <= nx; u++)
            cout << colored[u] << ' ';
        cout << '\n';
        
        // 使用匈牙利算法求匹配数，从而得到点覆盖数。
        cout << hungarian() << '\n';
    }
    
	return 0;
}
