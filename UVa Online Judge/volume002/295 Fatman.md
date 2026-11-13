[UVa 295 Fatman](https://blog.csdn.net/metaphysis/article/details/161388516)

## 题目分析

本题描述了一个有趣的几何与路径规划问题：在一个宽度为 $W$、长度为 $L$ 的矩形过道中，存在 $N$ 个障碍物（视为点）。一个人从过道左侧移动到右侧，在俯视图中这个人是一个不可压缩的圆盘，直径为 $d$。当两个障碍物之间的距离小于 $d$ 时，人无法从它们之间穿过；**注意**：题目中给出的判定条件是：直径为 $d$ 的人无法通过距离小于 $d$ 的两个障碍物之间的缝隙。这意味着人的圆心可以无限接近障碍物，只要圆盘边缘不碰到障碍物即可。类似地，人也不能穿过墙壁，因此圆心距离上墙壁和下墙壁至少为 $d/2$。

但题目简化了建模方式：将人的直径 $d$ 直接与障碍物之间的距离比较，并将墙壁视为特殊的“障碍物”。具体建模方法如下：

- 上墙壁可以看作一个“虚拟障碍物”，当人的直径 $d$ 大于障碍物到上墙壁的距离时，该障碍物与上墙壁“连通”。
- 下墙壁类似。
- 如果两个障碍物之间的欧几里得距离小于 $d$，则它们“连通”。

最终，如果上墙壁和下墙壁通过这些“连通关系”连接到了同一个连通分量中，那么人就无法从左侧穿到右侧（因为上下被堵住了）。反之，如果上下墙壁不连通，则存在一条从左到右的通道。

## 解题思路

### 1. 问题转化

假设人的直径为 $d$。我们定义：

- 障碍物 $i$ 与上墙壁的距离为 $W - Y_i$，若 $W - Y_i < d$，则障碍物 $i$ 与上墙壁连通。
- 障碍物 $i$ 与下墙壁的距离为 $Y_i$，若 $Y_i < d$，则障碍物 $i$ 与下墙壁连通。
- 两个障碍物 $i$、$j$ 之间的欧氏距离 $dist(i,j) = \sqrt{(X_i - X_j)^2 + (Y_i - Y_j)^2}$，若 $dist(i,j) < d$，则它们连通。

我们构造一个图，节点包括所有障碍物以及两个特殊节点：`top`（代表上墙壁）和 `bottom`（代表下墙壁）。如果两个节点满足上述连通条件，则在它们之间连一条无向边。

那么，人能否从左到右通过？**答案是**：如果存在一条从 `top` 到 `bottom` 的路径，则上下墙壁连通，意味着人的直径太大，被障碍物堵住了，无法通过；反之，如果没有这样的路径，则人可以通过。

### 2. 单调性

显然，直径 $d$ 越大，越容易连通（因为条件更宽松），所以 `top` 与 `bottom` 是否连通关于 $d$ 是单调的：

- 当 $d$ 很小时，没有连通，人可以轻松通过。
- 随着 $d$ 增大，连通性逐渐出现，一旦 `top` 和 `bottom` 连通，更大的 $d$ 也会保持连通。

因此我们可以使用 **二分查找** 来找到最大可行的 $d$，即临界点：小于该值时上下不连通，大于该值时上下连通。

### 3. 二分查找边界

- 下界 `low = 0.0`，人可以无限瘦。
- 上界 `high = W`，因为直径最大不可能超过过道宽度（否则圆盘无法放入过道）。实际上更精确的上界可以是 $W$ 本身，或者最大的障碍物间距等，但 $W$ 是安全且方便的选择。

二分查找终止条件：当 `high - low` 足够小（如 $10^{-9}$）时停止，输出 `low` 作为答案。

### 4. 判断函数 `squeezeThrough(d)`

该函数判断当直径为 $d$ 时，人是否能通过：

1. 调用 `build(d)` 构建图。
2. 从 `top` 开始执行 $\texttt{DFS}$ 或 $\texttt{BFS}$。
3. 如果 `bottom` 被访问到，说明上下连通，返回 `false`（无法通过）；否则返回 `true`（可以通过）。

### 5. 图的构建

设障碍物索引为 $0 \sim N-1$，`top = N`，`bottom = N+1`。

- 两两障碍物间：若距离 `< d`，连边。
- 障碍物与 `top`：若 $W - Y_i < d$，则连边 `top-i`。
- 障碍物与 `bottom`：若 $Y_i < d$，则连边 `i-bottom`。

注意：代码中没有为 `top` 和 `bottom` 之间的直接连边，因为它们之间没有物理意义。

## 算法复杂度

- 每个测试用例二分查找约 $\log_2(\frac{W}{10^{-9}}) \approx 60$ 次迭代。
- 每次 `squeezeThrough` 需要构建图：$O(N^2)$ 计算距离并建边。
- 每次 $\texttt{DFS}$：$O(N + E)$，其中 $E \le N^2 + 2N$。
- $N \le 100$，因此总复杂度很低。

## 边界情况

- 当 $W = 0$ 时，过道宽度为 $0$，只能通过直径为 $0$ 的人，直接输出 `0.0000`。
- 当 $N = 0$ 时，没有障碍物，最大直径为 $W$，二分查找会正确收敛到 $W$。

## 代码实现（带注释）

```cpp
// Fatman
// UVa ID: 295
// Verdict: Accepted
// Submission Date: 2016-06-03
// UVa Run Time: 0.870s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

// http://www.algorithmist.com/index.php/UVa_295

#include <bits/stdc++.h>

using namespace std;

vector<pair<int, int>> obstacles;   // 存储所有障碍物的坐标 (X, Y)
vector<vector<int>> edges;          // 邻接表表示的图
vector<bool> visited;               // DFS 访问标记
int L, W, N, top, bottom;           // L: 过道长度(本题中未使用), W: 宽度, N: 障碍物数量
                                    // top: 上墙壁节点索引, bottom: 下墙壁节点索引

// 计算两个障碍物之间的欧几里得距离
double distances(pair<int, int> x, pair<int, int> y)
{
    return sqrt(pow(x.first - y.first, 2) + pow(x.second - y.second, 2));
}

// 根据给定的直径 d 构建图
void build(double diameter)
{
    edges.clear();

    // 图中共有 N 个障碍物 + 2 个虚拟墙壁节点
    for (int i = 0; i < obstacles.size() + 2; i++)
        edges.push_back(vector<int>());

    // 构建障碍物之间的边：距离小于 diameter 则连通
    for (int i = 0; i < obstacles.size(); i++)
    {
        for (int j = i + 1; j < obstacles.size(); j++)
            if (distances(obstacles[i], obstacles[j]) < diameter)
            {
                edges[i].push_back(j);
                edges[j].push_back(i);
            }

        // 障碍物 i 与上墙壁的边：障碍物到上边界的距离 < diameter
        if (W - obstacles[i].second < diameter)
            edges[top].push_back(i);

        // 障碍物 i 与下墙壁的边：障碍物到下边界的距离 < diameter
        if (obstacles[i].second < diameter)
            edges[i].push_back(bottom);
    }
}

// 深度优先遍历
void dfs(int vertex)
{
    visited[vertex] = true;
    for (int i = 0; i < edges[vertex].size(); i++)
        if (visited[edges[vertex][i]] == false)
            dfs(edges[vertex][i]);
}

// 判断直径为 diameter 时人能否通过
// 返回 true 表示能通过（上下墙壁不连通）
// 返回 false 表示不能通过（上下墙壁连通）
bool squeezeThrough(double diameter)
{
    build(diameter);                // 根据直径构建图
    fill(visited.begin(), visited.end(), false); // 重置访问标记
    dfs(top);                       // 从上墙壁开始 DFS
    return visited[bottom] == false; // 如果下墙壁未被访问，则上下不连通，可以通过
}

int main(int argc, char *argv[])
{
    int cases;
    cin >> cases;

    for (int runs = 1; runs <= cases; runs++)
    {
        cin >> L >> W >> N;

        obstacles.clear();
        for (int i = 1, x, y; i <= N; i++)
        {
            cin >> x >> y;
            obstacles.push_back(make_pair(x, y));
        }

        // 特殊情况：宽度为 0，只能通过直径为 0 的人
        if (W == 0)
        {
            cout << "Maximum size in test case " << runs << " is ";
            cout << fixed << setprecision(4) << (double)W << "." << endl;
            continue;
        }

        // 设定虚拟墙壁节点的索引
        top = obstacles.size();          // 上墙壁编号为 N
        bottom = obstacles.size() + 1;   // 下墙壁编号为 N+1
        visited.resize(obstacles.size() + 2);

        // 二分查找最大可行的直径
        double high = W, low = 0.0, middle;
        while (fabs(high - low) >= 1E-9)   // 精度 1e-9
        {
            middle = (high + low) / 2.0;
            if (squeezeThrough(middle))    // 若可以通过，尝试更大的直径
                low = middle;
            else                           // 若不能通过，减小直径
                high = middle;
        }

        cout << "Maximum size in test case " << runs << " is ";
        cout << fixed << setprecision(4) << low << "." << endl;
    }

    return 0;
}
```

## 总结

本题的核心在于将几何可行性问题转化为图论中的连通性问题：

1. 人的直径 $d$ 决定了“连通”的阈值。
2. 通过将上下墙壁视为特殊节点，可以判断 $d$ 是否导致上下墙壁连通。
3. 利用单调性进行二分查找，高效求得最大可行直径。
