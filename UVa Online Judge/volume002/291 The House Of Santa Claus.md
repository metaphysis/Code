[UVa 291 The House Of Santa Claus](https://blog.csdn.net/metaphysis/article/details/161386536)

## 题目分析

本题是一道经典的图论与回溯问题。题目背景源于儿童时代的一个趣味谜题：在不抬起铅笔、不重复绘制同一条线段的前提下，一笔画出一个特定形状的“房子”——也就是图 1 所示的图形。这个图形由 $5$ 个顶点和 $8$ 条边构成，形状如同一个正方形上方加一个三角形屋顶。

题目要求我们在计算机上“绘制”这个房子，并且**起点固定为左下角顶点**（按照题目中的标号，左下角为顶点 $1$）。我们需要输出**所有可能的笔画顺序序列**，并且序列要按照数字串的**字典序递增**排列。每个序列表示经过顶点的顺序，长度为 $9$（因为 $8$ 条边需要访问 $9$ 个顶点，起点算一次）。

例如，样例输出中的 `12435123` 就是一个合法的顶点访问序列。

## 解题思路
### 问题本质

题目要求从顶点 $1$ 出发，**不重复经过同一条边**，遍历完所有 $8$ 条边，求所有可能的顶点访问序列。这正是**一笔画问题**中的欧拉路径问题，但这里不是求任意一条路径，而是**枚举所有可能的路径**。

由于每条边只能走一次，当访问完 $8$ 条边时，顶点序列长度为 $8 + 1 = 9$。起点固定为 $1$。

### 算法选择：$\texttt{DFS}$ + 回溯

因为图规模很小（$5$ 个顶点，$8$ 条边），我们可以使用深度优先搜索（$\texttt{DFS}$）结合回溯来枚举所有可能的路径。

**状态表示**：
- 当前所在顶点 `index`
- 已经走过的边数 `visited`（从 $0$ 开始，当 `visited == 8` 时表示所有边走完）
- 当前路径 `path`，存储已访问的顶点序列
- 一个邻接矩阵 `drawed[6][6]` 或二维数组，记录某条边是否已经被走过（无向图，所以两个方向同时标记）

**搜索过程**：
1. 从起点 $1$ 出发，`visited = 0`，`path` 为空。
2. 在 `dfs(index, visited)` 中：
   - 如果 `visited == 8`，说明已经走完所有边，此时将当前顶点 `index` 加入路径（因为路径中最后一个顶点还未加入），输出完整路径，然后回溯。
   - 否则，遍历当前顶点的所有邻接点：
     - 如果当前边（`index -> neighbor`）没有被走过：
       - 标记该边为已走过（两个方向都标记）。
       - 将当前顶点 `index` 加入路径。
       - 递归调用 `dfs(neighbor, visited + 1)`。
       - 回溯：将 `index` 从路径中移除，清除边的标记。

**注意**：输出时，路径中的顶点按顺序拼接成一个数字串，每找到一个完整路径就输出一行。

### 字典序的保证

由于题目要求输出按字典序递增，而我们在遍历邻接表时，如果邻接表本身是按照顶点编号从小到大排列的，那么 $\texttt{DFS}$ 的搜索顺序天然就是字典序递增的。这里在构造 `edges` 时，`push_back` 的顺序已经确保了从小到大（例如 `edges[1]` 中依次加入 $2, 3, 5$）。

### 复杂度分析

图有 $5$ 个顶点，$8$ 条边，完全遍历所有欧拉路径的时间复杂度在最坏情况下是指数级的，但由于图的规模极小，$\texttt{DFS}$ 回溯完全可以接受。实际解法运行时间接近 $0$ 秒。

## 代码实现

```cpp
// The House Of Santa Claus
// UVa ID: 291
// Verdict: Accepted
// Submission Date: 2016-05-09
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> edges(6);   // 邻接表，存储图的连接关系，顶点编号从1到5
int drawed[6][6] = { 0 };      // 边是否已绘制，drawed[i][j]=1 表示边(i,j)已走过
vector<int> path;              // 存储当前路径上的顶点序列

// 深度优先搜索，index表示当前所在顶点，visited表示已经走过的边数
void dfs(int index, int visited) {
    // 如果已经走完了全部8条边，输出当前路径
    if (visited == 8) {
        path.push_back(index);                     // 将最后一个顶点加入路径
        for (int i = 0; i < path.size(); i++)
            cout << path[i];                       // 输出顶点编号，不换行
        cout << endl;                              // 输出完一条路径后换行
        path.erase(path.end() - 1);                // 移除最后一个顶点，回溯
        return;
    }
    // 遍历当前顶点的所有邻接点
    for (int i = 0; i < edges[index].size(); i++) {
        // 如果当前边还没有被绘制过（无向图需检查两个方向）
        if (drawed[index][edges[index][i]] == 0 && drawed[edges[index][i]][index] == 0) {
            // 标记这条边为已绘制（两个方向都标记）
            drawed[index][edges[index][i]] = 1 = drawed[edges[index][i]][index] = 1;
            // 将当前顶点加入路径
            path.push_back(index);
            // 递归搜索下一个顶点，已走边数+1
            dfs(edges[index][i], visited + 1);
            // 回溯：移除当前顶点
            path.erase(path.end() - 1);
            // 回溯：清除边的标记，以便其他路径使用
            drawed[index][edges[index][i]] = 0;
            drawed[edges[index][i]][index] = 0;
        }
    }
}

int main() {
    cin.tie(0); cin.sync_with_stdio(false);
    // 构建无向图，顶点编号1~5，按照题目中房子的形状定义连接关系
    edges[1].push_back(2); edges[1].push_back(3); edges[1].push_back(5);
    edges[2].push_back(1); edges[2].push_back(3); edges[2].push_back(5);
    edges[3].push_back(1); edges[3].push_back(2); edges[3].push_back(4); edges[3].push_back(5);
    edges[4].push_back(3); edges[4].push_back(5);
    edges[5].push_back(1); edges[5].push_back(2); edges[5].push_back(3); edges[5].push_back(4);
    // 从顶点1出发，初始已走边数为0
    dfs(1, 0);
    return 0;
}
```

## 总结

本题利用 $\texttt{DFS}$ 回溯法，枚举了从固定起点出发、不重复经过同一条边的所有欧拉路径。由于图规模小，算法简洁高效。关键在于正确构建图的邻接表，并在回溯过程中正确维护边的访问状态，同时通过邻接表的顺序保证输出结果的字典序。
