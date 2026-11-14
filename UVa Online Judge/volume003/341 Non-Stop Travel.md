[UVa 341 Non-Stop Travel](https://blog.csdn.net/metaphysis/article/details/161557110)

## 题目描述

$\texttt{David}$ 讨厌在开车时遇到停车标志、让行标志和交通信号灯。为了最大限度地减少这种烦恼，他准备了常去区域的交通地图，并测量了每个路口的平均延误时间（以秒为单位）。他想找到指定起点和终点之间能够最小化路口延误的路线（无论为了避开延误需要行驶多远距离），并请求你的帮助。

### 输入格式

对于每个区域，$\texttt{David}$ 提供一张地图。地图数据首先给出路口数量 $NI$（不超过 $10$ 个）。路口从 $1$ 开始顺序编号。

对于每个路口，输入指定从该路口出发的街道数量，然后对于每条街道，输入目标路口编号和该路口的平均延误时间。

在最后一个路口的数据之后，输入起点和终点的路口编号。

整个输入由一系列地图组成，最后跟一个单独的整数 $0$。

**注意**：
- 每条街道是**单向**的。要表示双向街道，需要包含两个方向的记录。
- 从 $I$ 到 $J$ 最多只有一条街道。
- 每个区域中，最小平均延误的路线是唯一的。

### 输出格式

对于每个区域，按顺序输出一行，包含区域编号、路线经过的路口序列以及总延误时间。格式如样例所示。

### 样例输入

```
5
2 3 3 4 6
3 1 2 3 7 5 6
1 4 5
0
1 4
7
2 4 2 1 2 5
1 1 6
1 2 7
4 2 5 3 13 4 8 5 18
2 3 7 6 14
1 6 6
2 3 5 5 9 3 6 2
7 9 4 6 1 7 2
0
1 7
0
```

### 样例输出

```
Case 1: Path = 2 1 4; 8 second delay
Case 2: Path = 1 2 3 6 7; 20 second delay
```

---

## 题目分析

### 问题的本质

这是一个**单源最短路径**问题。给定一个有向图，每个顶点（路口）有经过时的延误（边权），需要找到从起点到终点的最短路径（总延误最小）。

关键点：
- 顶点数 $\leq 10$，图很小
- 每条边有权重（延误时间）
- 需要输出路径
- 图是**有向图**

### 与经典最短路径的区别

这里延误与**路口**关联，而不是与**道路**关联。但从输入格式看，延误是在街道数据中给出的，实际上是**到达目标路口时的延误**。因此，可以将其视为边权。

### 算法选择

由于图很小，可以使用：
- $\texttt{Dijkstra}$ 算法（$O(N^2)$ 实现，$N \leq 10$，简单高效）
- $\texttt{Bellman-Ford}$ 算法
- $\texttt{Floyd-Warshall}$ 算法（全源最短路径）

### 路径记录

在更新距离的同时，记录每个节点的前驱节点 `parent[v]`，最终从终点回溯到起点即可得到路径。

---

## 参考代码

```cpp
// Non-Stop Travel
// UVa ID: 341
// Verdict: Accepted
// Submission Date: 2016-06-28
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct edge
{
    int index, delay;  // 目标路口编号，延误时间
};

// 递归输出路径
void findPath(int parent[], int end, int start)
{
    if (end != start)
        findPath(parent, parent[end], start);
    cout << " " << end;
}

int main(int argc, char *argv[])
{
    int n, cases = 0;
    while (cin >> n, n)
    {
        // 构建邻接表
        vector<vector<edge>> edges(n + 1);
        for (int i = 1; i <= n; i++)
        {
            int pairs;
            cin >> pairs;
            for (int j = 1; j <= pairs; j++)
            {
                int next, delay;
                cin >> next >> delay;
                edges[i].push_back((edge){next, delay});
            }
        }
        
        // 读取起点和终点
        int start, end;
        cin >> start >> end;
        
        // Dijkstra 算法数据结构
        int distances[n + 1], parent[n + 1], visited[n + 1];
        
        fill(distances, distances + n + 1, -1);  // -1 表示不可达
        fill(parent, parent + n + 1, -1);
        fill(visited, visited + n + 1, 0);
        distances[start] = 0;
        
        int current = start;
        while (visited[current] == 0)
        {
            visited[current] = 1;
            
            // 松弛当前节点的所有出边
            for (int i = 0; i < edges[current].size(); i++)
            {
                edge e = edges[current][i];
                if (visited[e.index] == 0)
                {
                    if (distances[e.index] == -1 || 
                        distances[current] + e.delay < distances[e.index])
                    {
                        distances[e.index] = distances[current] + e.delay;
                        parent[e.index] = current;
                    }
                }
            }
            
            // 选择未访问的距离最小的节点
            int minDistance = -1;
            for (int i = 1; i <= n; i++)
                if (visited[i] == 0)
                {
                    if (distances[i] >= 0 && (minDistance == -1 || distances[i] < minDistance))
                    {
                        minDistance = distances[i];
                        current = i;
                    }
                }
        }
        
        // 输出结果
        cout << "Case " << ++cases << ": Path =";
        findPath(parent, end, start);
        cout << "; " << distances[end] << " second delay" << endl;
    }
    
    return 0;
}
```
