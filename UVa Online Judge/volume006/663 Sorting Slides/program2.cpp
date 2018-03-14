// Sorting Slides
// UVa ID: 663
// Verdict: Accepted
// Submission Date: 2016-11-07
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 60;

int g[MAXV][MAXV], visited[MAXV], cx[MAXV], cy[MAXV];
int tx, ty;

int dfs(int u)
{
    for (int v = 0; v < ty; v++)
        if (g[u][v] && !visited[v])
        {
            visited[v] = 1;
            if (cy[v] == -1 || dfs(cy[v]))
            {
                cx[u] = v;
                cy[v] = u;
                return 1;
            }
        }

    return 0;
}

// 匈牙利算法求最大匹配数。
int hungarian()
{
    memset(cx, -1, sizeof(cx)); memset(cy, -1, sizeof(cy));
    
    int matches = 0;
    for (int i = 0; i < tx; i++)
        if (cx[i] == -1)
        {
            memset(visited, 0, sizeof(visited));
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

bool pointInBox(point p, rectangle r)
{
    return p.x > r.xmin && p.x < r.xmax && p.y > r.ymin && p.y < r.ymax;
}

int main(int argc, char *argv[])
{
    int cases = 0;
    while (cin >> ty, ty > 0)
    {
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

        cout << "Heap " << ++cases << '\n';
        bool outputed = false;
        
        // 使用匈牙利算法求最大匹配数。
        int maxMatch = hungarian();
        
        // 因为需要按照幻灯片编号升序输出，故移除有向边的顺序要相应改变。
        for (int i = 0; i < tx; i++)
            for (int j = 0; j < ty; j++)
                if (g[j][i])
                {
                    // 移除有向边。
                    g[j][i] = 0;
                    
                    // 再次求最大匹配数。
                    int nextMatch = hungarian();
                    
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
