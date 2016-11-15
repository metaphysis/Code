// Sorting Slides
// UVa ID: 663
// Verdict: Accepted
// Submission Date: 2016-11-09
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

const int MAXV = 60, INF = 0x3f3f3f3f;

struct point
{
    int x, y;
};

struct rectangle
{
    int xmin, xmax, ymin, ymax;
};

rectangle rectangles[MAXV];
point points[MAXV];
int g[MAXV][MAXV], visited[MAXV], cx[MAXV], cy[MAXV], dx[MAXV], dy[MAXV];
int dist, heap, cases = 0;

// 判断点是否在矩形内。
bool pointInBox(point p, rectangle r)
{
    return p.x > r.xmin && p.x < r.xmax && p.y > r.ymin && p.y < r.ymax;
}

int bfs()
{
    queue<int> q;

    dist = INF;

    memset(dx, -1, sizeof(dx));
    memset(dy, -1, sizeof(dy));

    for (int i = 0; i < heap; i++)
        if (cx[i] == -1)
        {
            q.push(i);
            dx[i] = 0;
        }
    
    while (!q.empty())
    {
        int u = q.front(); q.pop();
        
        if (dx[u] > dist) break;

        for (int v = 0; v < heap; v++)
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
    for (int v = 0; v < heap; v++)
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
        for (int i = 0; i < heap; i++)
            if (cx[i] == -1)
                matches += dfs(i);
    }

    return matches;
}

int main(int argc, char *argv[])
{
    while (cin >> heap, heap > 0)
    {
        // 读入矩形和点的位置数据。
        for (int i = 0; i < heap; i++)
        {
            cin >> rectangles[i].xmin >> rectangles[i].xmax;
            cin >> rectangles[i].ymin >> rectangles[i].ymax;
        }
        
        for (int i = 0; i < heap; i++)
            cin >> points[i].x >> points[i].y;
        
        // 根据数字是否在某个矩形内建立有向边。
        memset(g, 0, sizeof(g));
        for (int i = 0; i < heap; i++)
            for (int j = 0; j < heap; j++)
                if (pointInBox(points[i], rectangles[j]))
                    g[i][j] = 1;

        // 使用匈牙利算法求最大匹配数。
        int maxMatch = hopcroftKarp();
        
        // 将任意一条有向边移除，再次求最大匹配数，检查最大匹配数是否减少，以此
        // 判定有向边是否唯一可确定。
        cout << "Heap " << ++cases << '\n';
        bool outputed = false;

        for (int i = 0; i < heap; i++)
            for (int j = 0; j < heap; j++)
                if (g[j][i])
                {
                    // 移除有向边。
                    g[j][i] = 0;
                    
                    // 再次求最大匹配数。
                    int nextMatch = hopcroftKarp();
                    
                    // 比较最大匹配数是否减小，减小表明移除的有向边为唯一可确定
                    // 的关联边。
                    if (nextMatch < maxMatch)
                    {
                        if (outputed) cout << ' ';
                        else outputed = true;
                        cout << '(' << (char)('A' + i) << ',' << (j + 1) << ')';
                    }

                    // 恢复有向边。
                    g[j][i] = 1;
                }

        if (!outputed) cout << "none";

        cout << "\n\n";
    }
    
	return 0;
}
