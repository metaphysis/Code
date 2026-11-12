[UVa 117 The Postal Worker Rings Once](https://blog.csdn.net/metaphysis/article/details/156644008)

## 题目分析

本题是一道图论问题，背景为邮递员需要遍历所有街道至少一次，最终返回起点，并希望总路程最短。题目要求我们根据给定的街道序列，计算完成上述任务的最小代价。

每条街道用一个字符串表示，字符串的首尾字母代表该街道连接的两个交叉路口，字符串的长度代表该街道的代价（长度）。题目保证：
- 每个交叉路口的度（与该路口相连的街道数）为偶数或奇数；
- 整个图中最多有两个奇度顶点；
- 所有交叉路口都是连通的。

## 解题思路

这是一个典型的**中国邮递员问题**（$\texttt{Chinese Postman Problem}$）在无向图上的简化版本。关键在于利用**欧拉路径/回路**的性质：

1. **欧拉回路存在条件**：一个无向连通图存在欧拉回路（每条边恰好走一次且回到起点）当且仅当所有顶点的度均为偶数。此时最小总代价就是所有边的长度之和。

2. **欧拉路径存在条件**：如果图中有恰好两个奇度顶点，那么存在一条欧拉路径（每条边恰好走一次，但起点和终点不同）。为了形成回路，我们必须额外重复走某些边，使得所有顶点度变为偶数。最小额外代价就是**两个奇度顶点之间的最短路径长度**。

因此，解题步骤如下：

- 读入所有街道，累计总边权（字符串长度之和），并统计每个字母（顶点）的度。
- 如果没有奇度顶点，直接输出总边权。
- 如果有两个奇度顶点，计算它们之间的最短路径长度，并将其加到总边权上，输出结果。
- 计算最短路径可以使用 **$\texttt{Floyd-Warshall}$** 算法，因为顶点数最多只有 $26$ 个（小写字母），该算法的时间复杂度为 $O(26^3)$，完全可行。

## 算法步骤

1. 初始化邻接矩阵为极大值，度数组为 $0$。
2. 读入每条街道：
   - 更新总边权；
   - 在邻接矩阵中记录边权（注意是无向边）；
   - 更新两个端点的度。
3. 遇到 `deadend` 时：
   - 检查奇度顶点数量：
     - 若为 $0$，直接输出总边权；
     - 若为 $2$，运行 $\texttt{Floyd-Warshall}$ 计算两奇点间最短路径，输出总边权加该最短路径。
4. 重置数据，继续处理下一个测试用例。

## 代码实现

```cpp
// The Postal Worker Rings Once
// UVa ID: 117
// Verdict: Accepted
// Submission Date: 2016-04-12
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net
//
// [解题方法]
// 图论，欧拉路径。根据题意，奇点数目为 1 的情况不可能出现，奇点数
// 目只可能为 0 或者 2。当奇点数为 0 时，很好办，走遍所有边仅一次的最小花
// 费是所有边权的和，而奇点数目为 2 时，最小花费是所有边权的和加上这两个奇点
// 之间的最短路径长度。为了简便，可以采用 Floyd-Warshall 算法来得到两点
// 间的最短路径长度。

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 27, MAXN = 10240;

// 邻接矩阵表示图。
struct graph {
    int weight[MAXV][MAXV], nvertices;
};

graph g;
int lengthOfStreet, crossroad[MAXV];
    
// 利用 Floyd-Warshall 算法计算所有点对之间的最短距离。
void floydWarshall() {
    int vertices = g.nvertices;
    for (int i = 1; i <= vertices; i++) g.weight[i][i] = 0;
    for (int k = 1; k <= vertices; k++)
        for (int i = 1; i <= vertices; i++)
            for (int j = 1; j <= vertices; j++)
                g.weight[i][j] = min(g.weight[i][j], g.weight[i][k] + g.weight[k][j]);
}

void initialize() {
    lengthOfStreet = 0;
    g.nvertices = MAXV - 1;
    for (int i = 1; i < MAXV; i++) {
        crossroad[i] = 0;
        for (int j = 1; j < MAXV; j++) g.weight[i][j] = MAXN;
    }
}

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    initialize();
    string street;
    while (cin >> street) {
        if (street == "deadend") {
            int start, end;
            bool found = false;
            for (int i = 1; i < MAXV; i++)
                if (crossroad[i] & 1) {
                    if (found == false) start = i;
                    else end = i;
                    found = true;
                }
            if (found) {
                floydWarshall();
                cout << (lengthOfStreet + g.weight[start][end]) << "\n";
            } else cout << lengthOfStreet << "\n";
            initialize();
        } else {
            lengthOfStreet += street.length();
            char front = street.front(), back = street.back();
            g.weight[front - 'a' + 1][back - 'a' + 1] = street.length();
            g.weight[back - 'a' + 1][front - 'a' + 1] = street.length();
            crossroad[front - 'a' + 1]++;
            crossroad[back - 'a' + 1]++;
        }
    }
    return 0;
}
```

## 复杂度分析

- 时间复杂度：对于每个测试用例， $\texttt{Floyd-Warshall}$ 算法运行一次，复杂度为 $O(26^3)$，整体可以视为常数时间。
- 空间复杂度：邻接矩阵和度数组均为 $O(26^2)$。

## 总结

本题关键在于识别出它是一个**中国邮递员问题**的简化版本，并利用欧拉图的性质进行求解。通过统计奇度顶点个数，并结合最短路径算法，即可高效求解。代码实现简洁，适合作为图论入门题目。
