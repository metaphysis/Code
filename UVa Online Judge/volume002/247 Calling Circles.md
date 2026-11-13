[UVa 247 Calling Circles](https://blog.csdn.net/metaphysis/article/details/161249671)

## 题目分析

本题要求根据通话记录找出所有“通话圈”。所谓“通话圈”，是指一组人，其中任意两人之间可以通过直接或间接的通话互相联系。更精确地说，如果两个人之间存在一条有向路径从 $A$ 到 $B$，同时也存在一条有向路径从 $B$ 到 $A$，那么 $A$ 和 $B$ 属于同一个通话圈。

题目输入包含多个数据集，每个数据集先给出人数 $n$ 和通话记录数 $m$，然后是 $m$ 行通话记录，每行两个名字表示一次通话（从第一个人打给第二个人）。当 $n = 0$ 且 $m = 0$ 时输入结束。输出时每个数据集先输出标题行，然后每行输出一个通话圈的所有名字，名字之间用 “`, `”（逗号加空格）分隔，不同数据集之间用空行分隔。

### 关键点

1. **有向图模型**：每个人是图的一个顶点，每条通话记录 $u \rightarrow v$ 是一条有向边。
2. **强连通分量的定义**：题目描述的“通话圈”本质上就是有向图中的 **强连通分量（$\texttt{Strongly Connected Component，SCC}$）** ，即分量内任意两个顶点 $u$ 和 $v$ 都互相可达（存在 $u$ 到 $v$ 的路径和 $v$ 到 $u$ 的路径）。
3. **人数限制**：$n \leq 25$，数据规模很小，可以采用 Floyd 算法求传递闭包。

### 输入输出细节

- 名字是大小写敏感的，只包含字母，长度不超过 $25$。
- 每个数据集可能包含的名字数量可能少于给定的 $n$（从样例可以看出，实际的 $n$ 是根据输入的边去重后的人数，而不是第一行给的 $n$）。代码中通过动态分配索引来解决这个问题，将第一行的 $n$ 实际上用于初始化但后续重新计算为实际人数。
- 输出顺序没有严格要求，但通常按照每个分量中第一个出现的人名顺序输出。

## 解题思路

### 思路概述

由于 $n \leq 25$，我们可以使用 **$\texttt{Floyd-Warshall}$ 算法** 来计算所有点对之间的可达性（即传递闭包）。然后对于每一对顶点 $(i, j)$，如果 $i$ 可达 $j$ 且 $j$ 可达 $i$，则 $i$ 和 $j$ 属于同一个强连通分量。

### 具体步骤

#### 1. 数据读取与建图

- 使用 $\texttt{map<string, int>}$ 将每个名字映射到整数编号。
- 使用 $\texttt{map<int, string>}$ 将编号映射回名字，便于输出。
- 邻接矩阵 $\texttt{edges[i][j]}$ 初始化为一个大数（如 $10000$），表示不可达。当读入一条通话 $u \rightarrow v$ 时，设置 $\texttt{edges[u][v]} = 1$。

#### 2. $\texttt{Floyd-Warshall}$ 求传递闭包

Floyd 算法的核心思想是动态规划：设 $\texttt{edges[i][j]}$ 表示从 $i$ 到 $j$ 的最短路径长度（或是否存在路径）。对于本题，我们只关心是否存在路径，因此可以将 $\texttt{edges[i][j]}$ 初始化为 $\infty$（不可达）或 $1$（直接可达），然后通过以下方式更新：

$$
edges[i][j] = \min(edges[i][j],\; edges[i][k] + edges[k][j])
$$

如果最终 $\texttt{edges[i][j]} < \infty$，则 $i$ 可达 $j$。由于 $n$ 很小，三重循环 $O(n^3)$ 完全可行（$25^3 = 15625$ 次操作）。

#### 3. 寻找强连通分量

对于每个未输出的顶点 $i$，创建一个新的分量，将 $i$ 加入。然后遍历所有其他未输出的顶点 $j$，如果 $\texttt{edges[i][j]} < \infty$ 且 $\texttt{edges[j][i]} < \infty$，则 $j$ 与 $i$ 互相可达，属于同一分量，将其加入并标记为已输出。

注意：这种做法的正确性依赖于 $\texttt{Floyd-Warshall}$ 算法已经计算了所有可达性。由于传递闭包具有传递性，如果 $i$ 和 $j$ 互相可达，$i$ 和 $k$ 互相可达，则 $j$ 和 $k$ 也必然互相可达。因此我们只需要以每个分量的“代表元”为基准，收集所有与其互相可达的点即可。

#### 4. 输出格式

按照题目要求，每个分量的名字以 “`, `” 分隔，一行输出一个分量。不同数据集之间输出一个空行（第一个数据集之前不需要空行）。

## 代码实现（$\texttt{Folyd-Warshall}$ 算法）

```cpp
// Calling Circles
// UVa ID: 247
// Verdict: Accepted
// Submission Date: 2016-05-10
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 10000;        // 定义一个大数，表示无穷大（不可达）
int edges[25][25];             // 邻接矩阵，存储有向边的权重（1 表示直接可达）
map<string, int> indexer;      // 名字 -> 编号
map<int, string> names;        // 编号 -> 名字
int n, m;                      // n 为实际人数，m 为通话记录数

// Floyd-Warshall 算法，求所有点对之间的最短路径长度
// 由于边权为 1，最终 edges[i][j] < MAXN 表示 i 可达 j
void floyd()
{   
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (edges[i][k] + edges[k][j] < edges[i][j])
                    edges[i][j] = edges[i][k] + edges[k][j];
}

// 找出所有强连通分量（通话圈）并输出
void findAllCircles()
{
    floyd();   // 先计算传递闭包
    
    vector<bool> outputed(n);          // 标记每个顶点是否已经被输出
    fill(outputed.begin(), outputed.end(), false);
    
    for (int i = 0; i < n; i++)
    {
        if (outputed[i] == false)      // 找到一个未输出的顶点，作为新分量的起点
        {
            vector<int> circle;        // 存储当前分量的所有顶点编号
            circle.push_back(i);
            outputed[i] = true;
            
            // 遍历所有其他未输出的顶点，检查是否与 i 互相可达
            for (int j = 0; j < n; j++)
                if (outputed[j] == false && edges[i][j] < MAXN && edges[j][i] < MAXN)
                {
                    circle.push_back(j);
                    outputed[j] = true;
                }
            
            // 输出当前分量的所有名字，用 ", " 分隔
            for (int j = 0; j < circle.size(); j++)
            {
                if (j > 0)
                    cout << ", ";
                cout << names[circle[j]];
            }
            cout << "\n";
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), cout.sync_with_stdio(false);
    
    int cases = 0;                     // 数据集编号
    string name1, name2;

    while (cin >> n >> m, n > 0)       // 当 n 和 m 均为 0 时结束
    {
        // 初始化邻接矩阵为无穷大（不可达）
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                edges[i][j] = MAXN;
        
        // 重新初始化，n 将用于记录实际出现的人数
        n = 0;
        indexer.clear();
        names.clear();
        
        // 读入 m 条通话记录
        for (int i = 1; i <= m; i++)
        {
            cin >> name1 >> name2;
            // 如果名字未出现过，分配新编号
            if (indexer.find(name1) == indexer.end())
            {
                indexer[name1] = n;
                names[n] = name1;
                n++;
            }
            if (indexer.find(name2) == indexer.end())
            {
                indexer[name2] = n;
                names[n] = name2;
                n++;
            }
            // 添加有向边 name1 -> name2，权重设为 1（表示可达）
            edges[indexer[name1]][indexer[name2]] = 1;
        }
        
        // 输出空行分隔不同的数据集（第一个数据集前不输出空行）
        if (cases++) cout << "\n";
        
        cout << "Calling circles for data set " << cases << ":\n";
    
        findAllCircles();
    }
    
	return 0;
}
```

## 代码实现（$\texttt{Kosaraju}$ 算法）

```cpp
// Calling Circles
// UVa ID: 247
// Verdict: Accepted
// Submission Date: 2017-10-20
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 110;
int visited[MAXV], n, cscc;
vector<list<int>> edges1(MAXV), edges2(MAXV);
vector<int> fn, scc;

int m;
map<string, int> indexer;
map<int, string> names;

void dfs(int u)
{
    visited[u] = 1;
    for (auto v : edges1[u])
        if (!visited[v])
            dfs(v);
    fn.push_back(u);
}

void reverseGraph()
{
    for (int u = 1; u <= n; u++)
        for (auto v : edges1[u])
            edges2[v].push_back(u);
}

void rdfs(int u)
{
    visited[u] = 1;
    for (auto v : edges2[u])
        if (!visited[v])
            rdfs(v);
    scc.push_back(u);
}

void kosaraju()
{
    fn.clear();
    memset(visited, 0, sizeof visited);
    for (int u = 1; u <= n; u++)
        if (!visited[u])
            dfs(u);
    
    reverseGraph();

    cscc = 0;
    memset(visited, 0, sizeof visited);
    while (fn.size())
    {
        int u = fn.back();
        if (!visited[u]) 
        {
            cscc++, scc.clear();

            rdfs(u);

            for (int i = 0; i < scc.size(); i++)
            {
                if (i) cout << ", ";
                cout << names[scc[i]];
            }
            cout << '\n';
        }
        fn.pop_back();
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), cout.sync_with_stdio(false);

    int cases = 0;
    string name1, name2;

    while (cin >> n >> m, n > 0)
    {
        for (int u = 1; u <= n; u++) edges1[u].clear(), edges2[u].clear();

        n = 0;
        indexer.clear(), names.clear();
        for (int i = 1; i <= m; i++)
        {
            cin >> name1 >> name2;
            if (indexer.find(name1) == indexer.end())
            {
                indexer[name1] = ++n;
                names[n] = name1;
            }
            if (indexer.find(name2) == indexer.end())
            {
                indexer[name2] = ++n;
                names[n] = name2;
            }
            edges1[indexer[name1]].push_back(indexer[name2]);
        }

        if (cases++ > 0) cout << '\n';
        cout << "Calling circles for data set " << cases << ":\n";

        kosaraju();
    }

	return 0;
}
```
## 复杂度分析

- **时间复杂度**：$\texttt{Floyd-Warshall}$ 算法为 $O(n^3)$，其中 $n \leq 25$，故最多约 $15625$ 次操作，非常快。加上找分量的 $O(n^2)$ 扫描，总体可忽略不计。
- **空间复杂度**：邻接矩阵大小为 $25 \times 25 = 625$，加上两个 $\texttt{map}$ 存储最多 $25$ 个名字，空间占用极小。

## 总结

本题是有向图中求强连通分量的经典应用。由于数据范围很小，使用 $\texttt{Floyd-Warshall}$ 算法求传递闭包然后根据互相可达的条件聚合顶点是一种简洁直观的做法。对于更大的图（如 $n \leq 1000$），则需要使用 $\texttt{Tarjan}$ 算法或 $\texttt{Kosaraju}$ 算法，但本题 $n \leq 25$ 使得 $\texttt{Floyd-Warshall}$ 成为最简单高效的解决方案。
