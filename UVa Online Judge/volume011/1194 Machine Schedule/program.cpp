// Machine Schedule
// UVa ID: 1194
// Verdict: Accepted
// Submission Date: 2016-11-08
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 110;

int g[MAXV][MAXV], vx[MAXV], vy[MAXV], cx[MAXV], cy[MAXV], nx, my, kj;

// 使用深度优先搜索寻找增广路，一次搜索只能使当前的匹配数增加1。
int dfs(int u)
{
    // 设置机器A的模式u为已访问。
    vx[u] = 1;

    // 考虑所有与模式u能够完成同一项作业的模式v。由于机器的初始状态为模式0，
    // 不需重启机器，故从模式1开始寻找增广路。
    for (int v = 1; v < my; v++)
        if (g[u][v] && !vy[v])
        {
            // 如果v尚未匹配或者v已经匹配但是从v出发可以找到增广路则匹配成功。
            vy[v] = 1;
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
    
    // 机器A和机器B最初工作在模式0，在模式0状态下可以完成的作业不需要重新
    // 启动机器，故从模式1开始匹配。
    for (int i = 1; i < nx; i++)
        if (!cx[i])
        {
            // 注意寻找之前需要将访问标记置为初始状态。
            memset(vx, 0, sizeof(vx)); memset(vy, 0, sizeof(vy));
            
            // 每找到一条增广路，可使得匹配数增加1。
            matches += dfs(i);
        }
    return matches;
}

int main(int argc, char *argv[])
{
    while (cin >> nx, nx > 0)
    {
        cin >> my >> kj;

        // 根据作业约束建立二部图。
        memset(g, 0, sizeof(g));
        for (int t, x, y, i = 0; i < kj; i++)
        {
            cin >> t >> x >> y;
            g[x][y] = 1;
        }

        // 使用匈牙利算法求匹配数，从而得到点覆盖数。
        cout << hungarian() << '\n';
    }
    
	return 0;
}
