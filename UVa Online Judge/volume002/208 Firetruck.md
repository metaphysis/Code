[UVa 208 Firetruck](https://blog.csdn.net/metaphysis/article/details/161010330)

## 题目分析

题目要求找出从消防站（街角 $1$）到火灾发生地（给定街角编号）的所有简单路径（不重复经过任何节点），并按照字典序输出所有路径及路径总数。城市地图由若干条无向边表示，节点编号小于 $21$，且消防站始终位于节点 $1$。

需要注意的是，图中可能存在一些与火灾地点不连通的节点，搜索时应避免进入这些“死胡同”，否则会导致大量无效回溯，造成时间超限。

## 解题思路

### 1. 预处理连通性

由于节点数量最多为 $20$，可以使用 $\texttt{Floyd}$ 算法或 $\texttt{BFS}$ 预处理任意两点之间的连通性。在本题解中，使用 $\texttt{Floyd}$ 算法计算最短路径长度（或仅判断连通性），若从当前节点 $u$ 无法到达火灾节点 $\texttt{fire}$，则没有必要继续沿 $u$ 进行深度优先搜索。

### 2. 深度优先搜索（$\texttt{DFS}$）

从节点 $1$ 开始进行 $\texttt{DFS}$，每次尝试访问相邻节点前，先通过 $\texttt{Floyd}$ 预处理的连通性判断该相邻节点是否能到达火灾节点。这样可以有效剪枝，避免无效搜索。

### 3. 字典序输出

为了保证输出路径按照字典序排列，需要对每个节点的邻接表进行排序。由于输入中的边可能重复，还需对邻接表进行去重。

### 4. 路径记录与输出

使用一个数组 $\texttt{path}$ 记录当前路径上的节点，当搜索到火灾节点时，按格式输出路径（第一个节点固定为 $1$，无需在 $\texttt{path}$ 中存储节点 $1$）。

## 代码实现

```cpp
// Firetruck
// UVa ID: 208
// Verdict: Accepted
// Submission Date: 2016-04-26
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAX_INT = numeric_limits<int>::max();

vector<vector<int>> edges;   // 邻接表
vector<bool> visited;            // 节点访问标记
vector<int> path;                // 当前路径（不包括起始节点1）
int fire, routes;                   // 火灾节点编号，路径总数
long long weight[21][21];           // Floyd算法使用的邻接矩阵

// Floyd算法预处理任意两点之间的最短路径（或连通性）
void floyd() {
    for (int k = 1; k <= 20; k++)
        for (int i = 1; i <= 20; i++)
            for (int j = 1; j <= 20; j++) {
                long long through = weight[i][k] + weight[k][j];
                if (weight[i][j] > through)
                    weight[i][j] = through;
            }
}

// 深度优先搜索回溯
// corner: 当前所在的节点编号
// length: 当前路径长度（path数组中已存储的节点数）
void backtrack(int corner, int length) {
    // 到达火灾节点，输出一条完整路径
    if (corner == fire) {
        routes++;
        cout << 1;
        for (int i = 0; i < length; i++)
            cout << " " << path[i];
        cout << "\n";
        return;
    }
    
    // 遍历当前节点的所有邻接点
    for (int i = 0; i < edges[corner].size(); i++) {
        int next = edges[corner][i];
        // 剪枝条件：节点未访问，且从该节点能到达火灾节点
        if (visited[next] == false && weight[next][fire] < MAX_INT) {
            visited[next] = true;
            path[length] = next;          // 记录路径
            backtrack(next, length + 1);  // 递归搜索
            visited[next] = false;        // 回溯
        }
    }
}

int main() {
    cin.tie(0);
    cout.sync_with_stdio(false);
    
    int cases = 0, start, end;
    
    visited.resize(21);
    path.resize(21);
        
    // 循环处理每个测试用例
    while (cin >> fire) {
        // 初始化邻接表
        edges.clear();
        edges.resize(21);
        
        // 初始化Floyd距离矩阵，不相邻的点之间距离设为无穷大
        for (int i = 1; i <= 20; i++)
            for (int j = 1; j <= 20; j++)
                weight[i][j] = MAX_INT;
            
        // 读入边，直到 "0 0" 结束
        while (cin >> start >> end, start && end) {
            edges[start].push_back(end);
            edges[end].push_back(start);
            weight[start][end] = 1;
            weight[end][start] = 1;
        }
        
        // 对每个节点的邻接表进行排序和去重，保证输出路径字典序
        for (int i = 0; i < edges.size(); i++)
            if (edges[i].size() > 0) {
                sort(edges[i].begin(), edges[i].end());
                int n = unique(edges[i].begin(), edges[i].end()) -
                    edges[i].begin();
                edges[i].erase(edges[i].begin() + n, edges[i].end());
            }
        
        // 输出用例编号
        cases++;
        cout << "CASE " << cases << ":\n";
        
        // Floyd预处理连通性
        floyd();
        
        // 从节点1开始深度优先搜索
        routes = 0;
        fill(visited.begin(), visited.end(), false);
        visited[1] = true;
        backtrack(1, 0);
        
        // 输出路径总数
        cout << "There are ";
        cout << routes;
        cout << " routes from the firestation to streetcorner ";
        cout << fire << ".\n";
    }
    
    return 0;
}
```

## 复杂度分析

- **时间复杂度**：$\texttt{Floyd}$ 预处理 $O(20^3) = O(8000)$，对于每个测试用例可忽略不计。$\texttt{DFS}$ 在剪枝后，实际搜索的路径数即为有效路径数，在最坏情况下（完全图）路径数量可能很大，但由于 $n \leq 20$ 且要求简单路径，实际可接受。
- **空间复杂度**：邻接表 $O(n + m)$，其中 $n \leq 20$，$m$ 为边数，均为常数级别。

## 总结

本题的核心是通过 $\texttt{Floyd}$ 或 $\texttt{BFS}$ 预处理节点与火灾地点的连通性，从而在 $\texttt{DFS}$ 过程中进行有效剪枝，避免搜索无法到达火灾地点的分支。同时，通过对邻接表排序，保证了输出路径的字典序。这种做法在 $n \leq 20$ 的范围内表现良好。
