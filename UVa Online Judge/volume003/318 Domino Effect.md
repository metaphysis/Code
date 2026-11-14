[UVa 318 Domino Effect](https://blog.csdn.net/metaphysis/article/details/161477447)


## 题目描述

你知道多米诺骨牌除了用来玩多米诺游戏之外还有其他用途吗？取一些多米诺骨牌，将它们直立摆放成一行，骨牌之间只留很小的间隔。如果操作得当，你可以推倒第一张骨牌，导致所有其他骨牌依次倒下（这就是“多米诺效应”这个短语的由来）。

虽然只有几张骨牌时这样做没什么意义，但在八十年代早期，一些人走向了另一个极端。他们使用数百万张不同颜色和材料的多米诺骨牌，用精心设计的倒下的骨牌图案填满整个大厅，创作出（短暂的）艺术作品。在这些构造中，通常不是只有一行骨牌同时倒下。

现在你的任务是：编写一个程序，给定这样一个由多米诺骨牌构成的行系统，计算出最后一张骨牌倒下的时间和位置。

系统由若干个**关键骨牌**（$\texttt{key dominoes}$）和连接它们的**普通骨牌行**组成。当一个关键骨牌倒下时，所有连接到它的行也会开始倒下（除了已经倒下的那些）。当倒下的行到达其他尚未倒下的关键骨牌时，这些关键骨牌也会倒下，并触发与其相连的行。骨牌行可以从任一端开始倒塌。甚至可能一行从两端同时倒塌，此时该行中最后倒下的骨牌位于两个关键骨牌之间的某个位置。

假设所有行的倒塌速度均匀。

### 输入格式

输入文件包含多个多米诺系统的描述。每个描述的第一行包含两个整数：
- $n$：关键骨牌的数量（$1 \leq n < 500$）
- $m$：连接关键骨牌的行数

关键骨牌编号为 $1$ 到 $n$。任意一对关键骨牌之间最多有一行，且图是连通的。

接下来的 $m$ 行，每行包含三个整数 $a$、$b$ 和 $l$，表示关键骨牌 $a$ 和 $b$ 之间有一行，从一端到另一端需要 $l$ 秒。

每个系统通过推倒 $1$ 号关键骨牌启动。

文件以空系统（$n = m = 0$）结束，该行不处理。

### 输出格式

对于每个系统，输出一行 `System #1`、`System #2` 等。然后输出一行，包含最后一张骨牌倒下的时间（精确到小数点后一位），以及最后一张骨牌倒下的位置（要么在关键骨牌处，要么在两个关键骨牌之间）。按输出样例所示的格式。如果存在多个解，输出任意一个。每个系统后输出一个空行。

### 样例输入

```
2 1
1 2 27
3 3
1 2 5
1 3 5
2 3 5
0 0
```

### 样例输出

```
System #1
The last domino falls after 27.0 seconds, at key domino 2.

System #2
The last domino falls after 7.5 seconds, between key dominoes 2 and 3.
```

---

## 题目分析

### 问题的本质

这是一个**图论 + 单源最短路径**问题。关键骨牌作为图的顶点，行作为带权边（权重为倒塌时间）。当 $1$ 号关键骨牌倒下时，倒塌过程沿着边传播。每个关键骨牌在到达时间倒下，然后触发其所有邻接边。

最后倒下的位置可能是：
1. 某个关键骨牌（其到达时间就是该骨牌倒下的时间）
2. 某条边的中间位置（当该边从两端同时倒塌时，最后倒下的是边的中点）

### 关键观察

设 $dist[i]$ 为从 $1$ 号关键骨牌出发，到达关键骨牌 $i$ 的最短时间（即该骨牌倒下的时间）。由于所有边都有正权重，可以使用 $\texttt{Dijkstra}$ 算法计算。

对于一条连接 $a$ 和 $b$、长度为 $l$ 的边：
- 如果 $dist[a]$ 和 $dist[b]$ 是骨牌 $a$ 和 $b$ 的倒下时间
- 则两边开始向对方传播的时间分别为 $dist[a]$ 和 $dist[b]$

如果 $|dist[a] - dist[b]| \ge l$，则这一边不会在中间相遇（一端在另一端开始之前就完全倒下了）。此时，最后倒下的位置在端点处。

如果 $|dist[a] - dist[b]| < l$，则两端在中间某点相遇。设相遇时间 $t$ 满足：
$$
t - dist[a] + t - dist[b] = l \implies 2t = l + dist[a] + dist[b] \implies t = \frac{l + dist[a] + dist[b]}{2}
$$

该相遇点距离 $a$ 为 $t - dist[a]$。

### 算法步骤

1. 使用 $\texttt{Dijkstra}$ 计算从 $1$ 出发到所有关键骨牌的最短路径 $dist[i]$
2. 检查所有关键骨牌，记录 $\max(2 \times dist[i])$（对应骨牌处的最后倒下时间，乘 $2$ 是为了统一使用整数比较）
3. 检查所有边，对于每条边 $(a,b,l)$，计算 $wasted = dist[a] + dist[b] + l$
   - 如果 $wasted > maxWastedTime$，则更新最后倒下的位置为这条边的中点
4. 输出结果：时间除以 $2$ 得到实际秒数，判断奇偶确定小数位

---

## 算法复杂度分析

### 时间复杂度

- $\texttt{Dijkstra}$ 算法：$O(m \log n)$，使用优先队列
- 检查所有骨牌和边：$O(n + m)$
- 总复杂度：$O(m \log n)$，$n < 500$，完全可行

### 空间复杂度

- 邻接表：$O(n + m)$
- 距离数组：$O(n)$
- 总空间复杂度：$O(n + m)$

---

## 正确性证明

**引理 1**：$\texttt{Dijkstra}$ 算法正确计算出从 $1$ 到每个关键骨牌的最短时间。

证明：边权为正，$\texttt{Dijkstra}$ 算法保证得到最短路径。$\square$

**引理 2**：关键骨牌 $i$ 的最后倒下时间为 $dist[i]$。

证明：$dist[i]$ 是从 $1$ 到 $i$ 的最短时间。由于所有边同时开始传播，到达 $i$ 的最早时间就是 $dist[i]$，而 $i$ 一旦到达就立即倒下。$\square$

**引理 3**：对于边 $(a,b,l)$，如果 $|dist[a] - dist[b]| < l$，则边上的最后倒下时间为 $(l + dist[a] + dist[b])/2$，位置在距 $a$ 为 $(l + dist[b] - dist[a])/2$ 处。

证明：设 $t_a = dist[a]$，$t_b = dist[b]$。从两端同时向中间传播，相遇点满足 $x + y = l$，$t_a + x = t_b + y = t$。解得 $t = (l + t_a + t_b)/2$，$x = (l + t_b - t_a)/2$。$\square$

**引理 4**：最后倒下的位置要么是某个关键骨牌，要么是某条边的中点。

证明：最后倒下的位置是“最后被覆盖”的点，这要么是最后一个被到达的关键骨牌，要么是某条边上从两端传播的交点。$\square$

---

## 参考代码

```cpp
// Domino Effect
// UVa ID: 318
// Verdict: Accepted
// Submission Date: 2016-07-02
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const long long int MAX_INT = numeric_limits<int>::max();

// 边结构体，用于 Dijkstra
struct edge
{
    int to;
    long long int weight;
    
    // 优先队列按权重升序
    bool operator<(edge x) const
    {
        return weight > x.weight;
    }
};

// 行结构体，存储原始边信息
struct link
{
    int from, to;
    long long int seconds;
};

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);
    
    int n, m, cases = 0;
    int from, to, seconds;
    long long int distances[510];

    while (cin >> n >> m, n)
    {
        // 初始化距离为无穷大
        fill(distances, distances + 510, MAX_INT);

        // 邻接表存储图
        vector<vector<edge>> edges(n + 1);
        // 存储原始边信息（用于检查边中点）
        vector<link> links;

        // 读取输入
        for (int i = 1; i <= m; i++)
        {
            cin >> from >> to >> seconds;
            edges[from].push_back((edge){to, seconds});
            edges[to].push_back((edge){from, seconds});
            links.push_back((link){from, to, seconds});
        }

        // Dijkstra 算法求单源最短路径
        distances[1] = 0;
        priority_queue<edge> unvisited;
        unvisited.push((edge){1, 0});

        while (!unvisited.empty())
        {
            edge v = unvisited.top();
            unvisited.pop();
            
            for (auto e : edges[v.to])
                if (distances[v.to] + e.weight < distances[e.to])
                {
                    distances[e.to] = distances[v.to] + e.weight;
                    unvisited.push((edge){e.to, distances[e.to]});
                }
        }

        // 检查关键骨牌处的最后倒下时间
        int startKey = 1, endKey = 1;
        long long int maxWastedTime = 0;
        for (int i = 1; i <= n; i++)
            if (2 * distances[i] > maxWastedTime)
            {
                startKey = endKey = i;
                maxWastedTime = 2 * distances[i];
            }

        // 检查边上的最后倒下时间
        for (auto l : links)
        {
            // 从两端传播的相遇时间 = (dist[a] + dist[b] + l) / 2
            // 乘以 2 用整数比较
            long long int wastedSeconds = distances[l.from] + distances[l.to] + l.seconds;
            if (wastedSeconds > maxWastedTime)
            {
                startKey = min(l.from, l.to);
                endKey = max(l.from, l.to);
                maxWastedTime = wastedSeconds;
            }
        }
 
        // 输出结果
        cout << "System #" << ++cases << endl;
        cout << "The last domino falls after " << maxWastedTime / 2;
        cout << (maxWastedTime % 2 ? ".5" : ".0") << " seconds, ";
        if (startKey == endKey)
            cout << "at key domino " << endKey << "." << endl;
        else
            cout << "between key dominoes " << startKey << " and " << endKey << "." << endl;
        cout << endl;
    }

    return 0;
}
```

---

## 总结

本题的核心在于：
1. **最短路径**：关键骨牌倒下时间等于从 $1$ 出发的最短时间
2. **边上的传播**：当两端传播时间差小于边长时，会在中间相遇
3. **统一整数计算**：将所有时间乘以 $2$ 避免浮点精度问题

### 关键点回顾

| 知识点 | 说明 |
|--------|------|
| 图模型 | 关键骨牌为顶点，行为边 |
| 最短路径 | $\texttt{Dijkstra}$ 算法 |
| 顶点时间 | $dist[i]$ 为骨牌 $i$ 倒下时间 |
| 边中点 | $t = (l + dist[a] + dist[b])/2$ |
| 整数技巧 | 所有时间乘 $2$，用整数运算 |
| 输出格式 | 保留一位小数 |

### 注意事项

1. **浮点精度**：通过乘 $2$ 用整数比较，避免浮点误差
2. **输出格式**：注意句点、空行和大小写
3. **边界情况**：$n = 1$ 时只有 $1$ 号骨牌

这种“最短路径 + 边上相遇时间计算”的解题模式，在传播类问题中具有典型性。
