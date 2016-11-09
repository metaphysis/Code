// Sorting Slides
// UVa ID: 663
// Verdict: Accepted
// Submission Date: 2016-11-07
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

const int MAXV = 60;

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
int g[MAXV][MAXV], visited[MAXV], cx[MAXV], cy[MAXV], heap, cases = 0;

// 判断点是否在矩形内。
bool pointInBox(point p, rectangle r)
{
    return p.x > r.xmin && p.x < r.xmax && p.y > r.ymin && p.y < r.ymax;
}

// 使用深度优先搜索寻找增广路，一次搜索只能使当前的匹配数增加1。
int dfs(int u)
{
    // 考虑所有与u邻接且尚未访问的顶点v。
    for (int v = 0; v < heap; v++)
        if (g[u][v] && !visited[v])
        {
            // 如果v尚未匹配或者v已经匹配但是从v出发可以找到增广路则匹配成功。
            visited[v] = 1;
            if (cy[v] == -1 || dfs(cy[v]))
            {
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
    memset(cx, -1, sizeof(cx)); memset(cy, -1, sizeof(cy));
    
    // 从每个非饱和点出发寻找增广路。
    for (int i = 0; i < heap; i++)
        if (cx[i] == -1)
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
        int maxMatch = hungarian();
        
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
