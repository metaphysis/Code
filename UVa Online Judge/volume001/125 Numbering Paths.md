[UVa 125 Numbering Paths](https://blog.csdn.net/metaphysis/article/details/156709710)

## 题目描述

本题要求计算在一个由单向街道组成的城市中，从每个交叉路口到另一个交叉路口的不同路径数量。交叉路口用非负整数标识，单向街道由一对整数 $j$ $k$ 表示，代表从 $j$ 到 $k$ 的单向街道。若两个交叉路口之间存在无穷多条路径（即存在环路），则输出 $-1$ 。输入包含多个城市的数据，每个城市以街道数量开始，随后是若干对整数表示街道。每个城市的交叉路口编号从 $0$ 到最大编号。要求输出一个矩阵，其中 $M[j][k]$ 表示从 $j$ 到 $k$ 的路径数，若无穷多则输出 $-1$ 。

## 题目分析

本题本质上是求有向图中任意两点间的路径数量，并处理存在环路导致路径数无穷的情况。由于交叉路口数量不超过 $30$ ，可以使用 $\texttt{Floyd-Warshall}$ 算法的变种来解决。

关键点在于：
1. 初始化矩阵 $matrix[i][j] = 1$ 若存在从 $i$ 到 $j$ 的直接边。
2. 使用 $\texttt{Floyd-Warshall}$ 算法累积路径数： $matrix[i][j] += matrix[i][k] \times matrix[k][j]$ 。
3. 若存在环路（即 $matrix[k][k] > 0$ ），则所有经过 $k$ 的路径数都会变成无穷大，即设置为 $-1$ 。

## 解题思路

1. **读入数据**：对于每个城市，读入街道数量，然后读入每一条街道，更新邻接矩阵，并记录最大的交叉路口编号。
2. **$\texttt{Floyd-Warshall}$ 算法计算路径数**：
   - 第一遍三重循环：对于每个中间节点 $k$ ，更新 $matrix[i][j] += matrix[i][k] \times matrix[k][j]$ 。这利用了动态规划的思想，计算从 $i$ 到 $j$ 经过 $k$ 的路径数。
   - 第二遍三重循环：检查每个节点 $k$ 是否在环上（ $matrix[k][k] > 0$ ）。如果是，则对于所有 $i$ 和 $j$ ，若 $matrix[i][k]$ 和 $matrix[k][j]$ 都非零，说明从 $i$ 到 $j$ 的路径可以经过该环无限次，因此 $matrix[i][j] = -1$ 。
3. **输出结果**：按照格式输出矩阵。

## 时间复杂度

$\texttt{Floyd-Warshall}$ 算法的时间复杂度为 $O(n^3)$ ，其中 $n \leq 30$ ，因此完全可以在规定时间内完成。

## 代码实现

```cpp
// Numbering Paths
// UVa ID: 125
// Verdict: Accepted
// Submission Date: 2015-11-27
// UVa Run Time: 0.000s
//
// 版权所有（C）2015，邱秋。metaphysis # yeah dot net


#include <bits/stdc++.h>

using namespace std;

#define MAXV 31

int matrix[MAXV][MAXV];
int largest;

void floyd() {
    for (int k = 0; k <= largest; k++)
        for (int i = 0; i <= largest; i++)
            for (int j = 0; j <= largest; j++)
                matrix[i][j] += matrix[i][k] * matrix[k][j];
    for (int k = 0; k <= largest; k++)
        if (matrix[k][k])
            for (int i = 0; i <= largest; i++)
                for (int j = 0; j <= largest; j++)
                    if (matrix[i][k] && matrix[k][j])
                        matrix[i][j] = -1;
}

int main(int ac, char *av[]) {
    int intersections;
    int cases = 0;
    int start, end;
    while (cin >> intersections) {
        largest = 0;
        memset(matrix, 0, sizeof(matrix));
        for (int i = 1; i <= intersections; i++) {
            cin >> start >> end;
            matrix[start][end] = 1;
            largest = max(largest, max(start, end));
        }
        floyd();
        cout << "matrix for city " << cases++ << endl;
        for (int i = 0; i <= largest; i++) {
            cout << matrix[i][0];
            for (int j = 1; j <= largest; j++) cout << " " << matrix[i][j];
            cout << endl;
        }
    }
    return 0;
}
```

## 总结

本题通过 $\texttt{Floyd-Warshall}$ 算法的变种，巧妙地解决了有向图中路径计数的问题，并处理了环路导致的无穷路径情况。代码简洁高效，适合作为图论中路径计数问题的经典例题。
