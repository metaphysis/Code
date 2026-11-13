[UVa 238 Jill's Bike](https://blog.csdn.net/metaphysis/article/details/161212187)

## 题目分析

$\texttt{Jill}$ 居住在一个 $n \times m$ 的矩形网格中，每个网格点（交叉口）都有一个海拔高度。她希望找到从起点到终点的最短路径，但需要满足以下三个规则：

1.  **坡度限制**：相邻网格点之间的海拔高度差不能超过 $10$ 米。
2.  **交通规则**：不能逆行（道路是单向的）。
3.  **最优原则**：总是走最短的可行路径（即边数最少的路径）。

题目输入描述了网格的尺寸、各点的海拔高度、一系列单向道路的定义（可能是一段连续的路径），以及若干个查询（起点和终点）。对于每个查询，需要输出一条满足上述条件的路径；如果起点和终点相同，则输出提示信息；如果没有符合条件的路径，也输出相应信息。

## 解题思路

本题的核心是在一个受限的网格图中寻找最短路径，可以采用以下步骤解决：

1.  **图的构建**：
    根据输入的海拔和单向道路定义，构建一个有向图。
    *   首先，为每个网格点分配一个唯一的整数 $\texttt{ID}$，例如 `id = 行号 * m + 列号`。
    *   对于每一条输入的单向道路定义 `start_street start_avenue end_street end_avenue`，它代表从 `(start_street, start_avenue)` 到 `(end_street, end_avenue)` 的一条连续路径，路径经过所有中间网格点。
    *   遍历该路径上的每一对相邻网格点（例如 `(si, sj)` 到 `(ei, ej)`），检查两点间的海拔差绝对值是否 $\le 10$。如果满足条件，则在有向图中添加一条从前者指向后者的边。如果不满足，则这条路径在此中断，但题目确保了输入的路径是有效的，所以我们按定义添加即可。

2.  **最短路径搜索**：
    由于每条边的权值都视为 $1$（从一点到相邻点），我们实际上是在一个无权有向图上寻找最短路径。 $\texttt{Dijkstra}$ 算法或 $\texttt{BFS}$ 都可以解决这个问题。本题的解题代码使用了 $\texttt{Dijkstra}$ 算法。
    *   从起点开始运行 $\texttt{Dijkstra}$ 算法，计算到所有点的最短距离（边数）。
    *   使用一个 `parent` 数组记录路径上的前驱节点，以便最终回溯出完整的路径。

3.  **路径输出**：
    *   如果起点等于终点，输出 `"To get from ... to ..., stay put!"`。
    *   如果从起点到终点的距离为无穷大（代码中用 `10000` 表示），则输出 `"There is no acceptable route from ... to ... ."`。
    *   否则，从终点开始，通过 `parent` 数组回溯到起点，得到逆序的路径。将路径反转后，按照要求的格式输出即可。

## 代码实现

```cpp
// Jill's Bike
// UVa ID: 238
// Verdict: Accepted
// Submission Date: 2016-06-02
// UVa Run Time: 0.200s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    // grid[node][0..3]: 存储从当前节点出发，在四个方向（东、西、南、北？）上的邻接点ID。
    // altitude[node]: 存储每个网格点的海拔高度。
    int grid[500][4], altitude[500];
    int n, m, cases = 0;
    
    while (cin >> n >> m)
    {
        // 初始化图和海拔数组
        memset(grid, 0, sizeof(grid));
        memset(altitude, 0, sizeof(altitude));
        
        // 读取海拔数据，注意存储索引从1开始，便于后续计算
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                cin >> altitude[i * m + j];
        
        // 开始构建有向图
        int starti, startj, endi, endj;
        // 读取道路定义，当 starti 为 0 时停止
        while (cin >> starti >> startj >> endi >> endj, starti > 0)
        {
            // 情况1: 同行水平移动 (streets 相同)
            if (starti == endi)
            {
                // 从左向右移动
                if (startj < endj)
                {
                    // 遍历路径上的每一小段
                    for (int j = startj; j < endj; j++)
                    {
                        // 检查海拔差是否满足 <= 10 的条件
                        if (abs(altitude[starti * m + j] - altitude[starti * m + j + 1]) <= 10)
                            // 将边存入 grid。这里的下标 [0] 可能代表向东的方向
                            grid[starti * m + j][0] = starti * m + j + 1;
                    }
                }
                // 从右向左移动
                else
                {
                    for (int j = startj; j > endj; j--)
                    {
                        if (abs(altitude[starti * m + j] - altitude[starti * m + j - 1]) <= 10)
                            // [1] 可能代表向西的方向
                            grid[starti * m + j][1] = starti * m + j - 1;
                    }
                }
            }
            // 情况2: 同列垂直移动 (avenues 相同)
            else if (startj == endj)
            {
                // 从上向下移动
                if (starti < endi)
                {
                    for (int i = starti; i < endi; i++)
                    {
                        if (abs(altitude[i * m + startj] - altitude[(i + 1) * m + startj]) <= 10)
                            // [2] 可能代表向南的方向
                            grid[i * m + startj][2] = (i + 1) * m + startj;
                    }
                }
                // 从下向上移动
                else
                {
                    for (int i = starti; i > endi; i--)
                    {
                        if (abs(altitude[i * m + startj] - altitude[(i - 1) * m + startj]) <= 10)
                            // [3] 可能代表向北的方向
                            grid[i * m + startj][3] = (i - 1) * m + startj;
                    }
                }
            }
        }
            
        // 处理每个查询，寻找最短路径
        while (cin >> starti >> startj >> endi >> endj, starti > 0)
        {
            // 在不同查询之间输出一个空行
            if (cases++)
                cout << endl;
            
            // 情况1: 起点和终点相同
            if (starti == endi && startj == endj)
            {
                cout << "To get from " << starti << "-" << startj;
                cout << " to " << endi << "-" << endj << ", stay put!" << endl;
                continue;
            }
            
            // Dijkstra 算法初始化
            int distances[500], parent[500] = {0}, visited[500] = {0};
            for (int i = 0; i < 500; i++)
                distances[i] = 10000; // 用一个很大的数表示无穷大
                
            // 起始节点的ID和初始化
            int current = starti * m + startj;
            distances[current] = 0;
            
            // Dijkstra 主循环
            while (visited[current] == 0)
            {
                visited[current] = 1; // 标记当前节点为已访问
                
                // 遍历从当前节点出发的4个可能方向
                for (int i = 0; i < 4; i++)
                {
                    int neighbor = grid[current][i];
                    // 如果邻接点存在且未被访问
                    if (neighbor > 0 && !visited[neighbor])
                    {
                        // 如果通过当前节点到达邻接点的路径更短，则更新距离和前驱
                        if (distances[current] + 1 < distances[neighbor])
                        {
                            distances[neighbor] = distances[current] + 1;
                            parent[neighbor] = current;
                        }
                    }
                }
                
                // 寻找下一个未访问且距离最小的节点作为当前节点
                int minDistance = 10000;
                for (int i = 1; i <= n; i++)
                    for (int j = 1; j <= m; j++)
                    {
                        int next = i * m + j;
                        if (!visited[next] && distances[next] < minDistance)
                        {
                            minDistance = distances[next];
                            current = next;
                        }
                    }
            }
            
            int start = starti * m + startj;
            int end = endi * m + endj;
            
            // 检查终点是否可达（距离是否仍为无穷大）
            if (distances[end] == 10000)
            {
                cout << "There is no acceptable route from ";
                cout << starti << "-" << startj;
                cout << " to " << endi << "-" << endj << "." << endl;
            }
            else
            {
                // 通过 parent 数组回溯路径
                vector <pair<int, int>> path;
                do
                {
                    // 将节点ID转换为 (street, avenue) 坐标
                    int ii = end / m, jj = end % m;
                    if (jj == 0)
                    {
                        ii--;
                        jj = m;
                    }
                    
                    path.push_back(make_pair(ii, jj));
                    end = parent[end];
                } while (end != start);
                
                // 回溯得到的路径是逆序的，需要反转
                reverse(path.begin(), path.end());
                
                // 按格式输出路径
                cout << starti << "-" << startj;
                for (int i = 0; i < path.size(); i++)
                    cout << " to " << path[i].first << "-" << path[i].second;
                cout << endl;
            }
        }
    }
    
	return 0;
}
```
