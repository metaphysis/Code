[UVa 116 Unidirectional TSP](https://blog.csdn.net/metaphysis/article/details/156643956)

## 问题描述

该问题要求在一个 $m \times n$ 的整数矩阵中找到一条从左到右的路径，使得路径上所有格子的整数之和最小。路径从第一列的任意一行开始，每一步只能从当前列的某一行走到下一列的**相邻行**（水平或对角线方向），并且矩阵的**第一行和最后一行是相邻的**（即矩阵在垂直方向上是环形的）。每一步的合法移动方式如图例所示（见原题图例）。

**路径的权值** 是路径经过的 $n$ 个格子中的整数之和。  
**输出要求** 对每个矩阵输出两行：第一行是构成最小权值路径的行号序列（共 $n$ 个），第二行是该路径的总权值。如果有多个最小权值路径，输出字典序最小的路径。

**注意**：  
- 输入可能包含多个矩阵，直到文件结束。  
- $1 \leq m \leq 10$，$1 \leq n \leq 100$。  
- 整数可能为负，路径权值不会超过 $2^{30}$ 可表示的范围。

---

## 题目分析与解题思路

### 问题抽象

我们有一个 $m \times n$ 的矩阵，要从第一列的任意一行出发，每次向右移动一列，并且移动时只能到相邻行（包括环形相邻）。目标是找到一条从第一列到最后一列的路径，使得路径上数字之和最小。

由于 $n$ 最大为 $100$，$m$ 最大为 $10$，因此状态总数最多为 $10 \times 100 = 1000$，可以使用**动态规划**求解。

### 动态规划状态定义

设 $dp[i][j]$ 表示从第 $j$ 列的第 $i$ 行出发，到达最后一列的最小路径权值（包括当前格子）。  
状态转移方程为：

$$
dp[i][j] = matrix[i][j] + \min \begin{cases} 
dp[i-1 \text{（环状）}][j+1] \\
dp[i][j+1] \\
dp[i+1 \text{（环状）}][j+1]
\end{cases}
$$

其中“环状”表示当 $i=1$ 时，上一行是 $m$；当 $i=m$ 时，下一行是 $1$。

### 字典序最小的路径

由于要求输出字典序最小的路径，我们需要在动态规划过程中**记录每个状态的前驱行号**。  
字典序比较是针对**路径的行号序列**，因此我们应该**从最后一列开始向第一列递推**，这样在更新 $dp[i][j]$ 时，可以优先选择行号较小的前驱。

具体做法：
1. 从 $j = n-1$ 到 $j = 1$ 反向递推。
2. 对于每个 $(i, j)$，计算三个可能前驱 $(i-1, j+1), (i, j+1), (i+1, j+1)$（注意环状处理）。
3. 选择权值最小的前驱，若权值相同，选择行号最小的前驱（以保证字典序最小）。
4. 记录 $parent[i][j]$ 为选择的下一行行号。

### 初始化与结果提取

- 初始化：对于最后一列 $j=n$，$dp[i][n] = matrix[i][n]$。
- 最终答案：找到第一列中 $dp[i][1]$ 最小的 $i$，若有多个相同，取最小的 $i$（字典序最小要求）。
- 路径输出：从第一列的 $i$ 开始，依次通过 $parent[i][j]$ 输出下一列的行号，直到最后一列。

---

## 复杂度分析

- 时间复杂度：$O(m \times n)$，每个格子计算三次比较。
- 空间复杂度：$O(m \times n)$，用于存储 $dp$ 和 $parent$ 数组。

---

## 代码实现

```cpp
// Unidirectional TSP
// UVa ID: 116
// Verdict: Accepted
// Submission Date: 2016-04-12
// UVa Run Time: 0.030s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int m, n, minRow, preRow, minWeight;
int parent[11][101], matrix[11][101];

int main(int ac, char *av[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    while (cin >> m >> n) {
        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
                cin >> matrix[i][j];
        // 从右往左进行动态规划，即列优先处理，从倒数第二列开始，因为需要字典序最小
        // 的最小权和路径，如果从左往右处理，可以得到行号最小的权和方案，但是不一定
        // 是字典序最小的。
        for (int j = n - 1; j >= 1; j--)
            for (int i = 1; i <= m; i++) {
                minWeight = INT_MAX;
                preRow = (i == 1 ? m : i - 1);
                if (minWeight > matrix[preRow][j + 1]) {
                    minWeight = matrix[preRow][j + 1];
                    minRow = preRow;
                } else if (minWeight == matrix[preRow][j + 1] && minRow > preRow)
                    minRow = preRow;
                if (minWeight > matrix[i][j + 1]) {
                    minWeight = matrix[i][j + 1];
                    minRow = i;
                }
                else if (minWeight == matrix[i][j + 1] && minRow > i)
                    minRow = i;
                preRow = (i == m ? 1 : i + 1);
                if (minWeight > matrix[preRow][j + 1]) {
                    minWeight = matrix[preRow][j + 1];
                    minRow = preRow;
                } else if (minWeight == matrix[preRow][j + 1] && minRow > preRow)
                    minRow = preRow;
                matrix[i][j] += minWeight;
                parent[i][j] = minRow;
            }
        // 找第一列权和最小的单元格。
        minWeight = INT_MAX;
        for (int i = 1; i <= m; i++)
            if (matrix[i][1] < minWeight) {
                minWeight = matrix[i][1];
                minRow = i;
            }
        // 输出路径与最小权和。
        cout << minRow;
        int next = 1, preRow = minRow;
        while (next < n) {
            cout << " " << parent[preRow][next];
            preRow = parent[preRow][next];
            next++;
        }
        cout << "\n";
        cout << matrix[minRow][1] << "\n";
    }
    return 0;
}
```

---

## 总结

本题是一道典型的**动态规划**问题，关键在于**反向递推**以方便字典序比较，以及**环形边界**的处理。通过记录每个状态的前驱，可以在 $O(m \times n)$ 时间内同时求出最小权值和字典序最小的路径。适合用于练习动态规划中的路径记录与字典序优化。
