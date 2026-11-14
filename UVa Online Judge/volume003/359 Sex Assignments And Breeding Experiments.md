[UVa 359 Sex Assignments And Breeding Experiments](https://blog.csdn.net/metaphysis/article/details/161589245)

## 题目描述

每个人都知道家谱的图示表示。在这些“图片”中，使用点和线来表示家庭结构和家庭间的关系。例如，如果 $M$ 和 $F$ 是三个孩子（两个男孩和一个女孩）的父母，图形如下所示。

很容易想到大量的此类图形。有些可以表示家谱，有些则不能。你的任务是描述那些可以表示家谱的图形的特征。

为简化问题，我们假设处理的是一个完全由双性繁殖（$M$ 和 $F$）特征化的种群。如果通过对种群成员进行适当的性别分配，图形能够表示理论上可能发生的繁殖实验结果，则称该图形是 **`sexy`**（性感的），否则是 **`not sexy`**。

你需要编写一个程序来检查任意有向图，判断它是否为 `sexy`。

**注意**：
- 有向边 $x \to y$ 表示 $x$ 是 $y$ 的父母
- 每个个体通常恰好有两个父母
- 每个个体不能有两个同性别父母，也不能有两个以上的父母
- 繁殖实验不会无限延伸到过去；总会达到某个点，其中种群成员的一个或两个父母是未知的（即没有父母的节点）
- 假定个体的出生在时间上是顺序的

### 输入格式

输入包含一系列图形描述，格式如下：
- 第一行：两个整数 $n$（节点数）和 $m$（有向边数）
- 接下来 $m$ 行：每行两个整数 $x$、$y$，表示从节点 $x$ 到 $y$ 的一条有向边

输入以文件结束符（$\texttt{EOF}$）结束。

### 输出格式

对于输入文件中的每个图形，输出以下语句之一：
- `Graph number i is sexy`
- `Graph number i is not sexy`

其中 $i$ 是图形在输入文件中的编号。

### 样例输入

```
5 6
1 3
2 3
1 4
2 4
1 5
2 5
3 3
1 2
2 3
3 1
```

### 样例输出

```
Graph number 1 is sexy
Graph number 2 is not sexy
```

---

## 题目分析

### 问题的本质

这是一个**有向图约束满足问题**。给定一个有向图，需要判断是否存在一种给每个节点分配性别（$\texttt{M}$ 或 $\texttt{F}$）的方式，使得：
1. 每条边表示“父母-子女”关系（$x$ 是 $y$ 的父母）
2. 每个节点最多有两个父节点（入度 ≤ 2）
3. 如果一个节点有两个父节点，它们的性别必须不同（一个 $M$，一个 $F$）
4. 图必须是无环的（$\texttt{DAG}$），因为出生顺序要求时间上的先后关系

### 约束条件总结

设每个节点 $i$ 有一个布尔变量 $x_i$，表示性别（例如 $0$ 表示 $M$，$1$ 表示 $F$）：

1. **入度约束**：每个节点的入度 $≤ 2$
2. **性别异或约束**：如果节点 $i$ 有两个父节点 $a$ 和 $b$，则 $x_a \neq x_b$（即 $x_a \oplus x_b = 1$）
3. **无环性**：图中不能有有向环（因为出生顺序不能形成循环依赖）

### 问题分解

1. **检查入度**：每个节点入度 $≤ 2$
2. **检查 $\texttt{DAG}$**：图中不能有环
3. **$\texttt{2-SAT}$ 可满足性**：对于有两条入边的节点，它们的父节点性别必须不同，形成 $x_a \neq x_b$ 的约束。这是一个典型的 **$\texttt{2-SAT}$** 问题。

### $\texttt{2-SAT}$ 建模

对于约束 $x_a \neq x_b$，等价于：
- $(x_a \lor x_b) \land (\neg x_a \lor \neg x_b)$

在 $\texttt{2-SAT}$ 中，每个变量有两个文字：$x$（真）和 $\neg x$（假）。约束 $(a \lor b)$ 转化为两条蕴含边：
- $\neg a \to b$
- $\neg b \to a$

对于 $x_a \neq x_b$，即 $(x_a \lor x_b) \land (\neg x_a \lor \neg x_b)$：
- 从 $\neg x_a$ 到 $x_b$
- 从 $\neg x_b$ 到 $x_a$
- 从 $x_a$ 到 $\neg x_b$
- 从 $x_b$ 到 $\neg x_a$

---
## 参考代码

```cpp
// Sex Assignments and Breeding Experiments
// UVa ID: 359
// Verdict: Accepted
// Submission Date: 2018-05-04
// UVa Run Time: 0.060s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

bool sexy;
vector<int> color, degree, dfn, low, scc;
int dfstime, cscc;
vector<vector<int>> edges, parents;  // edges: 原图, parents: 父节点列表
stack<int> s;

// Tarjan 算法求强连通分量
void tarjan(int u)
{
    dfn[u] = low[u] = ++dfstime;
    s.push(u);
    for (auto v : edges[u])
    {
        if (!dfn[v])
            tarjan(v), low[u] = min(low[u], low[v]);
        else if (!scc[v])
            low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u])
    {
        ++cscc;
        while (true)
        {
            int v = s.top(); s.pop();
            scc[v] = cscc;
            if (u == v) break;
        }
    }
}

// DFS 检查是否有环（DAG）
void dfs(int u)
{
    if (!sexy) return;
    color[u] = 0;  // 正在访问
    for (auto v : edges[u])
        if (color[v] == -1)
            dfs(v);
        else if (color[v] == 0)  // 发现环
            sexy = false;
    color[u] = 1;  // 访问完成
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0, x, y, n, m;
    while (cin >> n >> m)
    {
        // 初始化
        edges.assign(n, vector<int>());
        parents.assign(n, vector<int>());
        degree.assign(n, 0);
        sexy = true;

        // 读取边
        for (int i = 1; i <= m; i++)
        {
            cin >> x >> y;
            x--, y--;
            edges[x].push_back(y);
            degree[y]++;
            // 入度不能超过 2
            if (degree[y] > 2) sexy = false;
            parents[y].push_back(x);
        }
        
        // 检查 DAG
        if (sexy)
        {
            color.assign(n, -1);
            for (int i = 0; i < n; i++)
                if (color[i] == -1)
                    dfs(i);
        }
        
        // 2-SAT 检查
        if (sexy)
        {
            // 构建 2-SAT 蕴含图，共 2n 个节点
            dfstime = 0, cscc = 0;
            while (!s.empty()) s.pop();
            edges.assign(2 * n, vector<int>());
            dfn.assign(2 * n, 0);
            low.assign(2 * n, 0);
            scc.assign(2 * n, 0);
            
            // 对于有两条入边的节点，添加 x_p1 != x_p2 约束
            for (int i = 0; i < n; i++)
                if (parents[i].size() > 1)
                {
                    int b1 = parents[i][0], b2 = parents[i][1];
                    // x_b1 != x_b2 转换为蕴含边
                    edges[b1 + n].push_back(b2);
                    edges[b2 + n].push_back(b1);
                    edges[b2].push_back(b1 + n);
                    edges[b1].push_back(b2 + n);
                }

            // 求强连通分量
            for (int i = 0; i < 2 * n; i++)
                if (!dfn[i])
                    tarjan(i);

            // 检查是否有矛盾
            for (int i = 0; i < n; i++)
                if (scc[i] == scc[i + n])
                {
                    sexy = false;
                    break;
                }
        }

        cout << "Graph number " << ++cases << " is ";
        cout << (sexy ? "sexy" : "not sexy") << '\n';
    }

    return 0;
}
```
