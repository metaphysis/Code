// Nuts and Bolts
// UVa ID: 11138
// Verdict: Accepted
// Submission Date: 2017-09-26
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

const int MAXV = 500, INF = 0x3f3f3f3f;

int g[MAXV][MAXV], visited[MAXV], cx[MAXV], cy[MAXV], dx[MAXV], dy[MAXV];
int nuts, bolts;

int bfs()
{
    queue<int> q;

    int dist = INF;

    memset(dx, -1, sizeof(dx));
    memset(dy, -1, sizeof(dy));

    for (int i = 0; i < nuts; i++)
        if (cx[i] == -1)
        {
            q.push(i);
            dx[i] = 0;
        }
    
    while (!q.empty())
    {
        int u = q.front(); q.pop();
        
        if (dx[u] > dist) break;

        for (int v = 0; v < bolts; v++)
            if (g[u][v] && dy[v] == -1)
            {
                dy[v] = dx[u] + 1;

                if (cy[v] == -1)
                    dist = dy[v];
                else
                {
                    dx[cy[v]] = dy[v] + 1;
                    q.push(cy[v]);
                }
            }
    }

    return dist != INF;
}

int dfs(int u)
{
    int dist = INF;

    for (int v = 0; v < bolts; v++)
        if (g[u][v] && !visited[v] && dy[v] == (dx[u] + 1))
        {
            visited[v] = 1;
            if (cy[v] != -1 && dy[v] == dist) continue;

            if (cy[v] == -1 || dfs(cy[v]))
            {
                cx[u] = v, cy[v] = u;
                return 1;
            }
        }

    return 0;
}

int hopcroftKarp()
{
    memset(cx, -1, sizeof(cx));
    memset(cy, -1, sizeof(cy));
    
    int matches = 0;
    while (bfs())
    {
        memset(visited, 0, sizeof(visited));
        for (int i = 0; i < nuts; i++)
            if (cx[i] == -1)
                matches += dfs(i);
    }

    return matches;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    
    for (int c = 1; c <= cases; c++)
    {
        cin >> nuts >> bolts;
        for (int i = 0; i < nuts; i++)
            for (int j = 0; j < bolts; j++)
                cin >> g[i][j];
                
        cout << "Case " << c << ": a maximum of ";
        cout << hopcroftKarp();
        cout << " nuts and bolts can be fitted together\n";
    }
    
    return 0;
}
