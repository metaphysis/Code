[UVa 193 Graph Coloring](https://blog.csdn.net/metaphysis/article/details/160942142)

## 题目分析

题目要求对一个无向图进行黑白染色，使得相邻节点不能同时为黑色，并且黑色节点的数量最大化。图的大小为 $n \leq 100$，需要输出最大黑色节点数以及一种可行的方案。

由于 $n$ 最大为 $100$，暴力枚举所有 $2^n$ 种情况不可行。但题目中图的边数没有明确上界，在 $\texttt{UVa OJ}$ 的测试数据中，回溯法足以通过。

## 解题思路

采用 $\texttt{DFS}$ 回溯法，按节点编号从 $1$ 到 $n$ 依次决定每个节点是否染成黑色。

对于当前节点 `node`，有两种选择：

1. **尝试染成黑色**：要求当前节点与之前已染成黑色的节点都不相邻。如果满足条件，就将其染黑并递归到下一个节点。
2. **不染成黑色**：直接递归到下一个节点。

当递归到 $n + 1$ 时，说明所有节点都已处理完毕，此时统计黑色节点数量，如果比当前最优解更大，则更新最优解并记录方案。

### 正确性说明

该回溯算法实际上搜索了所有可能的合法染色方案。由于每次染黑前都会检查与已有黑节点的邻接关系，保证了方案的有效性。在叶子节点处更新最优解，因此最终得到的必然是最大黑色节点数。

### 复杂度分析

最坏情况下的时间复杂度为 $O(2^n)$，但由于剪枝（只有当节点不与任何黑节点相邻时才尝试染黑），实际运行效率远高于理论最坏情况。对于 UVa 的测试数据，该算法可以快速通过。

## 代码实现

```cpp
// Graph Coloring
// UVa ID: 193
// Verdict: Accepted
// Submission Date: 2016-03-16
// UVa Run Time: 0.003s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net
//

#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> edges;  // 邻接表，存储无向图
vector<bool> black;         // 标记节点是否染成黑色
vector<int> answer;         // 存储最优解中的黑色节点列表
int maximum, n;             // maximum 为最大黑色节点数，n 为节点数

// 深度优先搜索回溯
// node 表示当前处理的节点编号（从 1 开始）
void backtrack(int node) {
    // 所有节点处理完毕
    if (node == n + 1) {
        // 统计当前方案中的黑色节点数
        int total = 0;
        for (int i = 1; i <= n; i++)
            if (black[i])
                total++;
        // 更新最优解
        if (total > maximum) {
            maximum = total;
            answer.clear();
            for (int i = 1; i <= n; i++)
                if (black[i])
                    answer.push_back(i);
        }
        
        return;
    }
    // 检查当前节点是否与某个已被染黑的节点相邻
    bool blacked = false;
    for (int i = 0; i < edges[node].size(); i++)
        if (black[edges[node][i]]) {
            blacked = true;
            break;
        }
    // 如果相邻节点中没有黑色，则可以尝试将当前节点染成黑色
    if (blacked == false) {
        black[node] = true;          // 染黑
        backtrack(node + 1);         // 处理下一个节点
        black[node] = false;         // 回溯，恢复状态
    }
    // 将当前节点保持白色，继续搜索
    backtrack(node + 1);
}

// 求解当前图的最优染色方案并输出结果
void findMaximum() {
    maximum = 0;
    black.resize(n + 1);
    fill(black.begin(), black.end(), false);
    backtrack(1);  // 从节点 1 开始搜索
    // 输出最大黑色节点数
    cout << maximum << "\n";
    // 输出一种最优染色方案中的黑色节点列表
    for (int i = 0; i < answer.size(); i++) cout << (i > 0 ? " " : "" ) << answer[i];
    cout << "\n";
}

int main() {
    int m, k, start, end;
    cin >> m;  // 读取测试用例个数
    while (m--) {
        cin >> n >> k;  // 读取节点数 n 和边数 k
        // 初始化邻接表（1-based 索引）
        edges.clear();
        edges.resize(n + 1);
        // 读入 k 条边，构建无向图
        for (int i = 1; i <= k; i++) {
            cin >> start >> end;
            edges[start].push_back(end);
            edges[end].push_back(start);
        }
        findMaximum();  // 求解并输出结果
    }
    return 0;
}
```

## 总结

本题是经典的图染色问题，通过回溯法可以高效求解。核心剪枝在于：只有当节点不与任何已选黑色节点相邻时，才尝试将其染黑，这保证了搜索过程中只生成合法方案。对于 $n \leq 100$ 的规模，该算法在测试数据上表现良好。
