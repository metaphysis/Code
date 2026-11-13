
> **摘要**：本题给定一棵由 $N$ 台计算机组成的树形网络，要求选出最少数量的服务器，使得每台客户机恰好与一台服务器相邻。文章从题目描述、输入输出格式出发，分析"恰好被一台服务器服务"这一约束带来的状态划分难点，给出树形动态规划的三状态设计（节点为服务器、由子节点服务、由父节点服务）及对应转移方程，并讨论叶子节点与根节点的边界处理。

# 题目描述

给定一棵由 $N$ 台计算机和 $N-1$ 条通信链路组成的网络。任意两台计算机之间都存在唯一的通信路径，因此该网络是一棵树。

部分计算机可以被选为服务器。每台服务器能够为与它直接相邻的所有计算机提供服务。没有被选为服务器的计算机称为客户机，每台客户机必须恰好与一台服务器相邻。

求满足条件的服务器集合的最小规模，即最少需要选择多少台服务器。

# 输入格式

输入包含多组测试数据。

每组测试数据首先输入一个整数 $N$，表示计算机数量。接下来输入 $N-1$ 行，每行包含两个整数 $u$ 和 $v$，表示计算机 $u$ 与计算机 $v$ 之间存在一条通信链路。

读入当前测试数据的边后，再读入一个整数作为分隔标记：

- 标记为 $0$ 时，表示当前测试数据结束，后面开始读入下一组测试数据。
- 标记为 $-1$ 时，表示所有测试数据结束。

当 $N=2$ 时，输入一条边后直接读入结束标记。

# 输出格式

对于每组测试数据输出一行一个整数，表示满足条件的最少服务器数量。

# 样例输入

```text
6
1 3
2 3
3 4
4 5
4 6
0
2
1 2
-1
```

# 样例输出

```text
2
1
```

# 题目分析

网络是一棵树，因此可以任选一个节点作为根，并将整棵树转化为有根树。对于每个节点，需要根据该节点是否为服务器，以及该节点由谁提供服务，建立树形动态规划状态。

服务器只会为相邻的客户机提供服务。若一个客户机同时与多个服务器相邻，则不满足“恰好由一台服务器服务”的条件。因此，处理某个节点时，不仅要考虑该节点是否为服务器，还要保证它与父节点、子节点之间的服务关系不会重复。

设当前节点为 $u$，其子树中的所有客户机都必须恰好被一台服务器服务。定义以下三个状态：

- $dp[u].in$：节点 $u$ 是服务器，求满足子树条件时的最少服务器数量。
- $dp[u].selfOut$：节点 $u$ 不是服务器，并且由某个子节点服务器提供服务，求满足子树条件时的最少服务器数量。
- $dp[u].selfChildOut$：节点 $u$ 不是服务器，并且由父节点服务器提供服务，求满足子树条件时的最少服务器数量。

当节点 $u$ 是服务器时，任何子节点都不能依靠节点 $u$ 提供服务，否则该子节点如果还由其他服务器服务，就会产生重复服务。因此，对于每个子节点 $v$，只能选择 $dp[v].in$ 或 $dp[v].selfChildOut$，转移为：

$$
dp[u].in = 1 + \sum_v \min(dp[v].in, dp[v].selfChildOut)
$$

当节点 $u$ 由某个子节点服务器服务时，必须保证所有子节点中恰好有一个子节点选择服务器状态。其他子节点不能选择服务器状态，只能通过自身的子树获得服务。因此，先为每个子节点选择 $\min(dp[v].in, dp[v].selfOut)$，再判断是否已经存在服务器子节点。如果没有，则必须额外将一个子节点从 $dp[v].selfOut$ 改为 $dp[v].in$，并选择代价增量最小的子节点。

当节点 $u$ 由父节点服务器服务时，节点 $u$ 不能再被任何子节点服务器服务。因此所有子节点都必须选择 $dp[v].selfOut$，转移为：

$$
dp[u].selfChildOut = \sum_v dp[v].selfOut
$$

叶子节点没有子节点，所以不能处于 $dp[u].selfOut$ 状态。因为叶子节点不是服务器时，只能由父节点服务。代码中将叶子的 $dp[u].selfOut$ 设置为无穷大，表示该状态不可行。

根节点没有父节点，因此不能使用 $dp[root].selfChildOut$ 状态。最终答案只能从根节点是服务器的状态和根节点由某个子节点服务的状态中选择。

代码中的变量 $\texttt{childIn}$ 统计满足 $dp[v].in < dp[v].selfOut$ 的子节点数量。当多个子节点都倾向于选择服务器状态时，根节点处无法直接使用这些独立最优选择，因为根节点作为客户机时必须恰好由一个子节点服务器提供服务。此时将根节点设为服务器可以消除多个子节点同时服务根节点造成的冲突，最终根据状态值和子节点情况确定答案。

# 解题思路

首先使用邻接表存储树。由于树中每条边都是无向边，所以插入一条通信链路时，需要同时添加两个方向的邻接关系。

以节点 $0$ 作为根节点进行深度优先遍历。遍历到节点 $u$ 时，先递归处理所有子节点，再根据子节点的动态规划结果计算节点 $u$ 的三个状态。

计算 $dp[u].in$ 时，节点 $u$ 已经是服务器。每个子节点只能选择自己成为服务器，或者由自己的子节点提供服务，不能选择由节点 $u$ 提供服务的状态，因此累加 $\min(dp[v].in, dp[v].selfChildOut)$。

计算 $dp[u].selfChildOut$ 时，节点 $u$ 已经由父节点提供服务。为了避免子节点服务器再次服务节点 $u$，每个子节点必须选择 $dp[v].selfOut$，因此将所有这些状态相加。

计算 $dp[u].selfOut$ 时，节点 $u$ 不是服务器，并且必须由某个子节点服务器提供服务。首先对每个子节点取 $\min(dp[v].in, dp[v].selfOut)$。如果当前最优选择中已经包含服务器子节点，则不需要额外调整；如果没有服务器子节点，则选择代价增加最小的子节点改为服务器状态。若节点没有子节点，则该状态不可行。

深度优先遍历结束后，根节点不能由父节点服务，因此答案在 $dp[0].in$ 和 $dp[0].selfOut$ 中产生。代码还结合子节点的最优状态数量处理根节点的特殊情况，保证根节点作为客户机时不会被多个服务器同时服务。

每条边和每个节点都只在深度优先遍历中被处理有限次，因此时间复杂度为 $O(N)$。邻接表、边数组和动态规划数组均为线性规模，空间复杂度为 $O(N)$。

# 代码实现

```cpp
// Perfect Service
// UVa ID: 1218
// Verdict: Accepted
// Submission Date: 2018-11-07
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 10010, INF = 0x3f3f3f3f;

struct EDGE
{
    int u, v, next;
    EDGE (int u = 0, int v = 0, int next = 0): u(u), v(v), next(next) {}
} edges[MAXV << 1];

struct NODE
{
    int in, selfOut, selfChildOut;
} dp[MAXV];

int indx, head[MAXV];

void addEdge(int u, int v)
{
    edges[indx] = EDGE(u, v, head[u]);
    head[u] = indx++;
    edges[indx] = EDGE(v, u, head[v]);
    head[v] = indx++;
}

int dfs(int u, int father)
{
    dp[u].in = 1;
    dp[u].selfOut = dp[u].selfChildOut = 0;
    int x = INF, noChild = 1, noChildIn = 1, childIn = 0;
    for (int i = head[u]; ~i; i = edges[i].next)
    {
        int v = edges[i].v;
        if (v == father) continue;
        dfs(v, u);
        noChild = 0;
        //dp[u].in += min(dp[v].in, min(dp[v].selfOut, dp[v].selfChildOut));
        dp[u].in += min(dp[v].in, dp[v].selfChildOut);
        dp[u].selfOut += min(dp[v].in, dp[v].selfOut);
        if (dp[v].in > dp[v].selfOut) x = min(x, dp[v].in - dp[v].selfOut);
        else
        {
            noChildIn = 0;
            if (dp[v].in < dp[v].selfOut) childIn++;
        }
        dp[u].selfChildOut = min(INF, dp[u].selfChildOut + dp[v].selfOut);
    }
    if (noChild) dp[u].selfOut = INF;
    else 
    {
        if (noChildIn) dp[u].selfOut += x;
    }
    return childIn;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n;
    while (cin >> n)
    {
        indx = 0;
        memset(head, -1, sizeof(head));
        for (int i = 1, u, v; i < n; i++)
        {
            cin >> u >> v;
            u--, v--;
            addEdge(u, v);
        }
        int childIn = dfs(0, 0);
        if (dp[0].selfOut < dp[0].in)
        {
            if (childIn >= 2) cout << dp[0].in;
            else cout << dp[0].selfOut;
        }
        else cout << dp[0].in;
        cout << '\n';
        cin >> n;
        if (n == -1) break;
    }

    return 0;
}
```

# 总结

本题的核心是树形动态规划。每个节点需要区分服务器状态、由子节点服务状态以及由父节点服务状态，从而准确描述客户机的服务来源。

转移时必须注意以下关键点：

- 节点为服务器时，子节点不能再通过该节点获得服务。
- 节点由父节点服务时，所有子节点都不能成为直接服务该节点的服务器。
- 节点由子节点服务时，必须保证恰好有一个子节点承担服务。
- 根节点没有父节点，不能使用由父节点提供服务的状态。
- 叶节点不能处于由子节点提供服务的状态。

通过深度优先遍历计算每个子树的状态，整棵树可以在线性时间内完成处理。
