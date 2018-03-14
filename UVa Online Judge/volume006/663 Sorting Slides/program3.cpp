// Sorting Slides
// UVa ID: 663
// Verdict: Accepted
// Submission Date: 2016-11-09
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 60, INF = 0x3f3f3f3f;

int g[MAXV][MAXV], visited[MAXV], cx[MAXV], cy[MAXV], dx[MAXV], dy[MAXV];
int tx, ty;

int bfs()
{
    queue<int> q;

    int dist = INF;

    memset(dx, -1, sizeof(dx)); memset(dy, -1, sizeof(dy));

    for (int i = 0; i < tx; i++)
        if (cx[i] == -1)
        {
            q.push(i);
            dx[i] = 0;
        }
    
    while (!q.empty())
    {
        int u = q.front(); q.pop();
        
        if (dx[u] > dist) break;

        for (int v = 0; v < ty; v++)
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

    for (int v = 0; v < ty; v++)
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
    memset(cx, -1, sizeof(cx)); memset(cy, -1, sizeof(cy));
    
    int matches = 0;
    while (bfs())
    {
        memset(visited, 0, sizeof(visited));
        for (int i = 0; i < tx; i++)
            if (cx[i] == -1)
                matches += dfs(i);
    }

    return matches;
}

struct point
{
    int x, y;
};

struct rectangle
{
    int xmin, xmax, ymin, ymax;
};

point points[MAXV];
rectangle rectangles[MAXV];

// 判断点是否在矩形内。
bool pointInBox(point p, rectangle r)
{
    return p.x > r.xmin && p.x < r.xmax && p.y > r.ymin && p.y < r.ymax;
}


int main(int argc, char *argv[])
{
    int cases = 0;

    while (cin >> ty, ty > 0)
    {
        // 读入矩形和点的位置数据。
        tx = ty;
        for (int i = 0; i < ty; i++)
        {
            cin >> rectangles[i].xmin >> rectangles[i].xmax;
            cin >> rectangles[i].ymin >> rectangles[i].ymax;
        }
        for (int i = 0; i < tx; i++) cin >> points[i].x >> points[i].y;
        
        // 根据数字是否在某个矩形内建立有向边。
        memset(g, 0, sizeof(g));
        for (int i = 0; i < tx; i++)
            for (int j = 0; j < ty; j++)
                if (pointInBox(points[i], rectangles[j]))
                    g[i][j] = 1;

        // 将任意一条有向边移除，再次求最大匹配数，检查最大匹配数是否减少，以此
        // 判定有向边是否唯一可确定。
        cout << "Heap " << ++cases << '\n';
        bool outputed = false;

        // 使用匈牙利算法求最大匹配数。
        int maxMatch = hopcroftKarp();
        
        // 因为需要按照幻灯片编号升序输出，故移除有向边的顺序要相应改变。
        for (int i = 0; i < tx; i++)
            for (int j = 0; j < ty; j++)
                if (g[j][i])
                {
                    // 移除有向边。
                    g[j][i] = 0;
                    
                    // 再次求最大匹配数。
                    int nextMatch = hopcroftKarp();
                    
                    // 比较最大匹配数是否减小，减小表明移除的有向边为唯一可确定的关联边。
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
