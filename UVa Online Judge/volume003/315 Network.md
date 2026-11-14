[UVa 315 Network](https://blog.csdn.net/metaphysis/article/details/161477161)

## 题目描述

电话线路公司正在建立一个新的电话电缆网络。他们将几个地点（编号为 $1$ 到 $N$）连接起来，线路是双向的。每个地点都有一个电话交换机。从每个地点都可以通过线路到达其他任何地点（图是连通的）。

当某个地点的电源发生故障时，该交换机会停止工作。除了该故障地点本身无法到达外，还可能导致其他地点之间无法相互连接。在这种情况下，该故障地点被称为**关键点**（$\texttt{critical place}$，即割点）。

要求：编写程序，计算网络中所有关键点的数量。

### 输入格式

输入文件由多个数据块组成，每个数据块描述一个网络：
- 第一行：地点数量 $N < 100$
- 接下来的若干行：每行包含一个地点编号，后跟与该地点直接相连的若干个地点编号
- 每个数据块以一行 `0` 结束
- 最后一个数据块只有一行 $N = 0$

### 输出格式

对于每个数据块（最后一个除外），输出一行，包含关键点的数量。

### 样例输入

```
5
5 1 2 3 4
0
6
2 1 3 5 4 6 2
0
0
```

### 样例输出

```
1
2
```

---

## 题目分析

### 问题的本质

这是一个**无向连通图的割点**（$\texttt{articulation point}$）计数问题。割点是指删除该顶点及其关联边后，图的连通分量数量增加的顶点。

关键点：
- 图是无向图
- 图是连通的（输入保证）
- 需要找出所有割点

### 割点的定义

在无向连通图中，顶点 $v$ 是割点当且仅当删除 $v$ 后，图不再连通。

### 经典算法：$\texttt{Tarjan}$ 算法

$\texttt{Tarjan}$ 算法可以在 $O(V+E)$ 时间内找到无向图的所有割点。算法基于深度优先搜索（$\texttt{DFS}$），引入两个重要概念：

- **`dfn[u]`**：顶点 $u$ 的深度优先数（访问时间戳）
- **`low[u]`**：顶点 $u$ 及其后代顶点能够回溯到的最早祖先的 `dfn` 值

### 割点的判定条件

对于 $\texttt{DFS}$ 树中的顶点 $u$：

1. **根节点**：如果根节点有至少两个子节点，则根节点是割点
2. **非根节点**：如果存在子节点 $v$ 满足 `low[v] >= dfn[u]`，则 $u$ 是割点

### 算法推导

在 $\texttt{DFS}$ 过程中：

1. 初始化 `dfn[u] = low[u] = ++time`
2. 对于每个邻接点 $v$：
   - 如果 $v$ 未被访问（树边），递归访问 $v$，然后更新：
     ```
     low[u] = min(low[u], low[v])
     ```
     如果 `low[v] >= dfn[u]`，则 $u$ 是割点（非根节点）
   - 如果 $v$ 已被访问且 $v$ 不是父节点（回边），更新：
     ```
     low[u] = min(low[u], dfn[v])
     ```

3. 如果是根节点且子节点数 $\geq 2$，则根节点是割点

---

## 解题思路

### 步骤一：图的存储

使用邻接表存储图，由于输入可能包含重复边，使用 `set<int>` 自动去重。

### 步骤二：输入解析

输入格式较特殊：
- 每行第一个数字是起点，后面是该起点的所有邻接点
- 每个数据块以 `0` 结束
- 最后一个数据块以 `0` 开始并立即结束

使用 `getline` 逐行读取，`istringstream` 解析数字。

### 步骤三：$\texttt{Tarjan}$ 算法实现

```cpp
int dfs(int u, int parent) {
    int lowu = dfn[u] = ++dfstime;
    int children = 0;
    
    for (auto v : edges[u]) {
        if (!dfn[v]) {  // 树边
            children++;
            int lowv = dfs(v, u);
            lowu = min(lowu, lowv);
            if (lowv >= dfn[u] && parent != -1)
                ic[u] = 1;  // 非根节点割点条件
        } else if (v != parent) {  // 回边
            lowu = min(lowu, dfn[v]);
        }
    }
    
    // 根节点割点条件
    if (parent == -1 && children >= 2)
        ic[u] = 1;
    
    return lowu;
}
```

### 步骤四：计数输出

遍历所有顶点，统计 `ic[i] == 1` 的数量并输出。

---

## 算法复杂度分析

### 时间复杂度

- 每个顶点访问一次，每条边访问两次
- 总复杂度：$O(V + E)$
- $V < 100$，$E$ 最多约 $V^2/2$，完全可行

### 空间复杂度

- 邻接表存储：$O(V + E)$
- 辅助数组：$O(V)$
- 总空间复杂度：$O(V + E)$

---

## 正确性证明

**引理 1**：在 $\texttt{DFS}$ 树中，如果非根节点 $u$ 存在子节点 $v$ 满足 `low[v] >= dfn[u]`，则 $u$ 是割点。

证明：`low[v] >= dfn[u]` 表示 $v$ 及其后代无法通过回边到达 $u$ 的祖先。因此，删除 $u$ 后，$v$ 所在的子树与 $u$ 的祖先部分断开，图不再连通。$\square$

**引理 2**：如果根节点 $r$ 在 $\texttt{DFS}$ 树中有至少两个子节点，则 $r$ 是割点。

证明：由于无向图不存在横叉边，根的两个子节点之间没有直接路径（只能通过根连接）。删除根后，这两个子节点所在的子树相互断开。$\square$

**引理 3**：算法覆盖了所有割点。

证明：$\texttt{Tarjan}$ 算法的正确性已在图论中得到证明。$\square$

---

## 参考代码

```cpp
// Network
// UVa ID: 315
// Verdict: Accepted
// Submission Date: 2017-10-21
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

// 顶点数目最大值
const int MAXV = 110;

// 使用邻接表来表示图，set 自动去重
vector<set<int>> edges;

// dfn: 各顶点的深度优先数（访问时间戳）
// ic: 是否为割点，1 表示是割点
// dfstime: 时间戳计数器
int dfn[MAXV], ic[MAXV], dfstime = 0;

// Tarjan 算法求割点
// u: 当前访问的顶点
// parent: 父顶点（根节点为 -1）
// 返回顶点 u 的 low 值
int dfs(int u, int parent)
{
    int lowu = dfn[u] = ++dfstime;  // 初始化 low 值为自身 dfn
    int children = 0;                // 子树计数（仅用于根节点）
    
    // 遍历所有邻接顶点
    for (auto v : edges[u])
    {
        if (!dfn[v])  // v 未被访问，即树边
        {
            ++children;
            int lowv = dfs(v, u);    // 递归访问子节点
            lowu = min(lowu, lowv);  // 更新 low[u]
            
            // 非根节点：如果子节点无法回溯到 u 的祖先，则 u 是割点
            if (lowv >= dfn[u])
                ic[u] = 1;
        }
        else if (v != parent)  // v 已被访问且不是父节点，即回边
        {
            lowu = min(lowu, dfn[v]);  // 用祖先的 dfn 更新 low[u]
        }
    }

    // 根节点：如果子节点数 >= 2，则是割点
    if (parent < 0 && children == 1)
        ic[u] = 0;

    return lowu;
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
 
    string line;
    while (getline(cin, line))
    {
        int n = stoi(line);
        if (n == 0) break;  // 输入结束

        // 初始化邻接表
        edges.assign(n + 1, set<int>());
        
        // 读取数据块
        istringstream iss;
        while (getline(cin, line), line != "0")
        {
            iss.clear();
            iss.str(line);

            int start, next;
            iss >> start;
            while (iss >> next)
            {
                edges[start].insert(next);
                edges[next].insert(start);
            }
        }
        
        // 重置数组
        dfstime = 0;
        memset(ic, 0, sizeof(ic));
        memset(dfn, 0, sizeof(dfn));
        
        // 从顶点 1 开始 DFS（图是连通的）
        dfs(1, -1);
        
        // 统计割点数量
        int count = 0;
        for (int i = 1; i <= n; i++)
            if (ic[i])
                count++;

        cout << count << '\n';
    }
    
    return 0;
}
```

---

## 总结

本题的核心在于：
1. **割点判定**：使用 $\texttt{Tarjan}$ 算法
2. **`dfn` 和 `low` 数组**：记录访问时间和最早祖先
3. **两种割点条件**：根节点多子树、非根节点子节点 low 值 ≥ 当前 dfn

### 关键点回顾

| 知识点 | 说明 |
|--------|------|
| 割点定义 | 删除后增加连通分量数 |
| `dfn[u]` | 深度优先数（访问时间） |
| `low[u]` | 能回溯到的最早祖先的 `dfn` |
| 根节点条件 | 子节点数 ≥ 2 |
| 非根节点条件 | 存在子节点 `low[v] >= dfn[u]` |
| 时间复杂度 | $O(V+E)$ |

### 算法思想的应用

$\texttt{Tarjan}$ 算法是图论中的经典算法，除了求割点，还可以用于求：
- 桥（$\texttt{bridge}$）
- 强连通分量（$\texttt{SCC}$）
- 双连通分量（$\texttt{BCC}$）

掌握这个算法对于解决图的连通性问题非常有帮助。
