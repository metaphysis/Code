[UVa 336 A Node Too Far](https://blog.csdn.net/metaphysis/article/details/161545030)

## 题目描述

为了避免网络消息（数据包）在网络中无限循环的问题，每个消息都包含一个**生存时间**（$\texttt{Time To Live, TTL}$）字段。该字段包含消息在被丢弃之前可以转发的节点数（站点、计算机等）。每次一个站点接收到消息时，它将 $\texttt{TTL}$ 字段减 $1$。如果消息的目的地就是当前站点，则忽略 $\texttt{TTL}$ 字段的值。但如果消息必须转发，且减 $1$ 后的 $\texttt{TTL}$ 字段为 $0$，则消息不会被转发。

在本题中，给定多个网络的描述，对于每个网络，需要确定给定初始节点和 $\texttt{TTL}$ 值时，无法到达的节点数量。

### 输入格式

输入包含多个网络配置。每个网络描述以整数 $NC$ 开头，表示节点之间的连接数。$NC = 0$ 表示输入数据结束。接下来 $NC$ 行，每行包含两个正整数，表示连接两个节点的通信线路。任意一对节点之间最多有一条直接通信线路，每个网络的节点数不超过 $30$。

每个网络配置之后，有多个查询，查询格式为两个整数：起始节点编号和初始 $\texttt{TTL}$ 设置。查询以一对 `0 0` 结束。

### 输出格式

对于每个查询，输出一行，显示测试用例编号（从 $1$ 开始）、不可达节点数、起始节点和初始 $\texttt{TTL}$ 值。

### 样例输入

```
16
10 15
15 20
15 55
10 50
55 40
55 60
40 20
40 50
50 60
60 65
20 25
20 30
30 47
35 30
35 40
35 50
35 2
35 3
1 1
1 2
3 2
3 3
0 0
0
```

### 样例输出

```
Case 1: 5 nodes not reachable from node 35 with TTL = 2.
Case 2: 1 nodes not reachable from node 35 with TTL = 3.
Case 3: 8 nodes not reachable from node 1 with TTL = 1.
Case 4: 5 nodes not reachable from node 1 with TTL = 2.
Case 5: 3 nodes not reachable from node 3 with TTL = 2.
Case 6: 1 nodes not reachable from node 3 with TTL = 3.
```

---

## 题目分析

### 问题的本质

这是一个**图中受限距离可达性**问题。给定一个无向图，从起始节点 $s$ 出发，消息每经过一条边 $\texttt{TTL}$ 减 $1$。消息可以到达的节点是那些从 $s$ 出发的最短路径长度 $\leq \texttt{TTL}$ 的节点。**不可达节点**包括：
1. 最短路径长度 $> \texttt{TTL}$ 的节点
2. 图本身不可达的节点（但题目保证图连通？不保证，需考虑）

实际上，由于每条边消耗 $1$ 个 $\texttt{TTL}$，消息能到达的节点正是那些与 $s$ 的距离（最短路径长度）$\leq \texttt{TTL}$ 的节点。

因此，问题转化为：
1. 计算所有节点之间的最短路径
2. 对于每个查询 $(s, \texttt{TTL})$，统计所有距离 $> \texttt{TTL}$ 的节点数量

### 节点编号处理

节点编号是正整数，但可能不连续（如样例中的 $10,15,20,25,30,35,40,47,50,55,60,65$）。需要进行**坐标离散化**，将节点编号映射到连续的 $1 \sim N$ 索引，以便使用邻接矩阵。

### 图的大小

每个网络节点数 $\leq 30$，使用 $\texttt{Floyd-Warshall}$ 算法计算全源最短路径非常合适。

## 参考代码

```cpp
// A Node Too Far
// UVa ID: 336
// Verdict: Accepted
// Submission Date: 2016-06-26
// UVa Run Time: 0.040s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);
    
    int distances[40][40];   // 距离矩阵，最大 30 个节点，多预留一些空间
    map<int, int> indexer;    // 节点编号 → 索引映射
    int cases = 0;
    
    int n;
    while (cin >> n, n)
    {
        // 初始化距离矩阵为无穷大
        for (int i = 0; i < 40; i++)
            for (int j = 0; j < 40; j++)
                distances[i][j] = 100000;
        
        indexer.clear();
        
        // 读取边并离散化节点编号
        for (int i = 1; i <= n; i++)
        {
            int start, end;
            cin >> start >> end;
            
            // 为未出现过的节点分配新索引
            if (indexer.find(start) == indexer.end())
                indexer[start] = indexer.size() + 1;
            if (indexer.find(end) == indexer.end())
                indexer[end] = indexer.size() + 1;
            
            int s = indexer[start];
            int e = indexer[end];
            distances[s][e] = 1;
            distances[e][s] = 1;
        }
        
        int N = indexer.size();  // 实际节点数
        
        // 对角线距离为 0
        for (int i = 1; i <= N; i++)
            distances[i][i] = 0;
        
        // Floyd-Warshall 算法计算全源最短路径
        for (int k = 1; k <= N; k++)
            for (int i = 1; i <= N; i++)
                for (int j = 1; j <= N; j++)
                    if (distances[i][k] + distances[k][j] < distances[i][j])
                        distances[i][j] = distances[i][k] + distances[k][j];
        
        // 处理查询
        int node, ttl;
        while (cin >> node >> ttl, node || ttl)
        {
            // 如果起始节点不在图中，则所有节点都不可达
            // 但题目保证起始节点一定存在于网络中
            int s = indexer[node];
            int counter = 0;
            
            for (int i = 1; i <= N; i++)
                if (distances[s][i] > ttl)
                    counter++;
                    
            cout << "Case " << ++cases << ": ";
            cout << counter << " nodes not reachable from node ";
            cout << node << " with TTL = " << ttl << "." << endl;
        }
    }
    
    return 0;
}
```
