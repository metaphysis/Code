
> **摘要**：本题给定若干城市及城市间隧道的防护人员需求矩阵，要求选出使所有城市连通且总人数最少的隧道集合。问题可建模为带权无向图的最小生成树，使用邻接矩阵配合 $\texttt{Prim}$ 算法在 $O(n^2)$ 时间内构造，再按人员需求、起点、终点依次排序输出结果。

# 题目描述

给定若干座城市，以及城市之间隧道的防护人员需求。若两个城市之间没有隧道，矩阵中的对应值为 $0$；否则该值表示保护这条隧道所需的人员数量。

需要选择一些隧道进行保护，使所有城市保持连通，并使所需防护人员总数最少。输出每组数据中应保护的隧道及其人员需求。

# 输入格式

输入包含多组测试数据。第一行是测试数据组数 $T$。

每组数据先给出城市数 $n$。城市按字母顺序标记为 $A$、$B$、$C$ 等。随后给出一个 $n\times n$ 的矩阵，矩阵中的值表示对应城市之间隧道的防护人员需求，值为 $0$ 表示不存在隧道。矩阵元素之间以逗号分隔。

# 输出格式

对每组数据，先输出 `Case` 和测试数据编号，格式为 `Case k:`。随后按照隧道防护人员需求从小到大的顺序，输出需要保护的隧道及对应人员数量。

若多条隧道的人员需求相同，则按照隧道两端城市的字母顺序排列。

# 样例输入

```text
1
6
0, 8, 12, 0, 0, 7
8, 0, 0, 3, 0, 0
12, 0, 0, 0, 6, 0
0, 3, 0, 0, 0, 4
0, 0, 6, 0, 0, 5
7, 0, 0, 4, 5, 0
```

# 样例输出

```text
Case 1:
B-D 3
D-F 4
E-F 5
C-E 6
A-F 7
```

# 题目分析

城市与隧道构成一个无向带权图：城市是顶点，隧道是边，防护人员数量是边权。保护一组隧道后，所有城市都必须连通，因此所选边需要构成一棵生成树。为了让防护人员总数最少，问题等价于在图中求一棵最小生成树。

使用 $\texttt{Prim}$ 算法逐步扩展生成树。算法维护每个尚未加入生成树的城市到当前生成树的最小边权，并每次选择其中最小的城市加入。加入时，若该城市有对应的连接边，就将这条边记录为生成树的一部分。

题目要求按边权输出结果，因此生成树构造完成后，还需要将选出的边排序。排序规则为先比较边权，再比较边的起点编号，最后比较终点编号。构造过程中遇到相同边权时，代码也按较小的城市编号处理父节点和待加入城市，从而使结果符合确定的选边规则。

# 解题思路

将输入矩阵存入邻接矩阵。城市编号从 $0$ 开始，对应字母依次为 $A$、$B$、$C$ 等。由于矩阵中的 $0$ 表示不存在隧道，只有权值非 $0$ 的位置才代表图中的边。

从编号为 $0$ 的城市开始执行 $\texttt{Prim}$ 算法。对于每个城市，记录它到当前生成树的最小边权、对应的父节点，以及它是否已经加入生成树。每轮从尚未加入的城市中选出到生成树距离最小的城市，将其加入，并将它与父节点之间的隧道加入结果集合。随后检查该城市连向其他未加入城市的边，并更新相应的最小边权和父节点。若存在相同权值的候选边，则优先选择编号较小的父节点；若多个城市到生成树的距离相同，则按父节点编号选择。

当所有城市都加入生成树后，结果集合中包含 $n-1$ 条隧道。将这些隧道按人员需求、起点编号、终点编号依次排序，再将城市编号转换为字母并输出。

对于含 $n$ 个城市的矩阵，$\texttt{Prim}$ 算法每轮扫描所有城市，并进行 $n$ 轮，时间复杂度为 $O(n^2)$。最终只需排序 $n-1$ 条生成树边，排序时间为 $O(n\log n)$，因此总时间复杂度为 $O(n^2)$。邻接矩阵占用 $O(n^2)$ 空间，其他数组和结果集合占用 $O(n)$ 空间，整体空间复杂度为 $O(n^2)$。

# 代码实现

下面的代码使用邻接矩阵保存隧道信息，通过 $\texttt{Prim}$ 算法构造最小生成树，并按题目要求排序输出隧道。

```cpp
// Oreon
// UVa ID: 1208
// Verdict: Accepted
// Submission Date: 2017-01-12
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAX_DIST = 1000000, MAXV = 26;

struct tunnel
{
    int from, to, weight;
    
    bool operator<(const tunnel& x) const
    {
        if (weight != x.weight) return weight < x.weight;
        else {
            if (from != x.from )
                return from < x.from;
            else
                return to < x.to;
        }
    }
};

int edges[MAXV][MAXV], n;
int parent[MAXV], dist_to_tree[MAXV], intree[MAXV];
vector<tunnel> tunnels;

void prim(int u)
{
    for (int i = 0; i < n; i++)
    {
        parent[i] = -1; intree[i] = 0; dist_to_tree[i] = MAX_DIST;
    }

    dist_to_tree[u] = 0;
    while (!intree[u])
    {
        intree[u] = 1;

        if (parent[u] != -1)
        {
            int from = parent[u], to = u;
            if (from > to) swap(from, to);
            tunnels.push_back((tunnel){from, to, dist_to_tree[u]});
        }
        
        for (int v = 0; v < n; v++)
        {
            if (!intree[v] && edges[u][v])
            {
                if (dist_to_tree[v] > edges[u][v])
                {
                    dist_to_tree[v] = edges[u][v];
                    parent[v] = u;
                }
                else
                {
                    if (dist_to_tree[v] == edges[u][v] && parent[v] > u)
                        parent[v] = u;
                }
            }
        }

        int min_dist_to_tree = MAX_DIST;
        for (int i = 0; i < n; i++)
        {
            if (!intree[i])
            {
                if (min_dist_to_tree > dist_to_tree[i])
                {
                    min_dist_to_tree = dist_to_tree[i];
                    u = i;
                }
                else
                {
                    if (min_dist_to_tree == dist_to_tree[i] && parent[i] < parent[u])
                       u = i;
                }
            }
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n;
        
        char comma;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
            {
                if (j > 0) cin >> comma;
                cin >> edges[i][j];
            }
        
        tunnels.clear();

        prim(0);

        sort(tunnels.begin(), tunnels.end());
        
        cout << "Case " << c << ":\n";
        for (auto t : tunnels)
        {
            cout << (char)('A' + t.from) << '-' << (char)('A' + t.to);
            cout << ' ' << t.weight << '\n';
        }
    }
    
    return 0;
}
```

# 总结

本题将城市和隧道建模为带权无向图，所需保护的隧道构成最小生成树。使用邻接矩阵配合 $\texttt{Prim}$ 算法，可以在 $O(n^2)$ 时间内完成构造；之后对选出的 $n-1$ 条边排序，即可按指定顺序输出。实现时需要正确识别矩阵中的逗号分隔格式，并在权值相同时按照城市编号进行确定性处理。
