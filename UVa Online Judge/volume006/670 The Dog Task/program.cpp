// The Dog Task
// UVa ID: 670
// Verdict: Accepted
// Submission Date: 2016-11-09
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 110;

// 非常怪异的误差控制，尝试了1e-7，1e-10，1e-15均为Wrong Answer。
const double EPSILON = 1e-20;

struct point
{
    int x, y;
};

point bob[MAXV], dog[MAXV];
int g[MAXV][MAXV], visited[MAXV], cx[MAXV], cy[MAXV], L, N, M;

// 判断兴趣点是否可到达。
bool accessible(point a, point b, point c)
{
    double distAB = sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
    double distAC = sqrt(pow(a.x - c.x, 2) + pow(a.y - c.y, 2));
    double distBC = sqrt(pow(b.x - c.x, 2) + pow(b.y - c.y, 2));
    
    return distAC + distBC < 2.0 * distAB - EPSILON;
}

// 完全不涉及浮点数运算亦为Wrong Answer。
bool accessible1(point a, point b, point c)
{
    int C = (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
    int A = (a.x - c.x) * (a.x - c.x) + (a.y - c.y) * (a.y - c.y);
    int B = (b.x - c.x) * (b.x - c.x) + (b.y - c.y) * (b.y - c.y);
    
    return 4 * A * B < (4 * C - A - B) * (4 * C - A - B);
}

// 使用深度优先搜索寻找增广路，一次搜索只能使当前的匹配数增加1。
int dfs(int u)
{
    // 考虑所有与u邻接且尚未访问的顶点v。
    for (int v = 0; v < M; v++)
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
    for (int i = 0; i < N; i++)
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

    cin >> L;
    for (int cases = 1; cases <= L; cases++)
    {
        if (cases > 1) cout << '\n';

        cin >> N >> M;
        for (int i = 0; i < N; i++) cin >> bob[i].x >> bob[i].y;
        for (int i = 0; i < M; i++) cin >> dog[i].x >> dog[i].y;
        
        // 根据兴趣点是否可达建立边。
        memset(g, 0, sizeof(g));
        for (int i = 0; i < N - 1; i++)
            for (int j = 0; j < M; j++)
                if (accessible(bob[i], bob[i + 1], dog[j]))
                    g[i][j] = 1;

        // 使用匈牙利算法求最大匹配数。
        cout << (N + hungarian()) << '\n';
        
        // 输出狗的路径。
        for (int i = 0; i < N - 1; i++)
        {
            cout << bob[i].x << ' ' << bob[i].y << ' ';
            if (cx[i] >= 0)
                cout << dog[cx[i]].x << ' ' << dog[cx[i]].y << ' ';
        }
        cout << bob[N - 1].x << ' ' << bob[N - 1].y << '\n';
    }
    
	return 0;
}
