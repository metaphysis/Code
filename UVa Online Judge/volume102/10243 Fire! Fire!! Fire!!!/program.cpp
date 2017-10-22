// Fire! Fire!! Fire!!!
// UVa ID: 10243
// Verdict: Accepted
// Submission Date: 2017-10-22
// UVa Run Time: 0.070s
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

list<int> edges[MAXV];
int g[MAXV][MAXV], color[MAXV], visited[MAXV], cx[MAXV], cy[MAXV], nx;

int dfs(int u)
{
    for (int v = 1; v <= nx; v++)
        if (g[u][v] && !visited[v])
        {
            visited[v] = 1;
            if (!cy[v] || dfs(cy[v]))
            {
                cx[u] = v, cy[v] = u;
                return 1;
            }
        }
    return 0;
}

int hungarian()
{
    int matches = 0;
    memset(cx, 0, sizeof(cx)); memset(cy, 0, sizeof(cy));
    for (int i = 1; i <= nx; i++)
        if (!cx[i])
        {
            memset(visited, 0, sizeof(visited));
            matches += dfs(i);
        }
    return matches;
}

int main(int argc, char *argv[])
{
    while (cin >> nx, nx > 0)
    {
        // 读入图数据。
        for (int u = 1; u <= nx; u++)
            edges[u].clear();
        for (int t, y, x = 1; x <= nx; x++)
        {
            cin >> t;
            for (int i = 1; i <= t; i++)
            {
                cin >> y;
                edges[x].push_back(y);
            }
        }

        // BFS二着色，构建二部图。
        memset(g, 0, sizeof(g));
        memset(color, 0, sizeof(color));
        memset(visited, 0, sizeof(visited));
        queue<int> unvisited; unvisited.push(1);
        visited[1] = 1, color[1] = 1;
        while (!unvisited.empty())
        {
            int u = unvisited.front(); unvisited.pop();
            for (auto v : edges[u])
            {
                if (!visited[v])
                {
                    visited[v] = 1;
                    color[v] = 3 - color[u];
                    unvisited.push(v);
                }
                if (color[u] < color[v]) g[u][v] = 1;
            }
        }
        
        // 使用匈牙利算法求匹配数，从而得到点覆盖数。
        if (nx == 1) cout << "1\n";
        else cout << hungarian() << '\n';
    }
    
	return 0;
}
