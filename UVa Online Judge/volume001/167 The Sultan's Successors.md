[UVa 167 The Sultan's Successors](https://blog.csdn.net/metaphysis/article/details/158808153)

## 题目分析

本题是一个经典的八皇后问题的变种。与标准八皇后问题只要求找到所有合法布局不同，本题在 $8 \times 8$ 的棋盘上每个格子都有一个权值（$1$ 到 $99$ 之间的整数），要求在所有合法布局中，选取皇后所在位置的格子权值之和最大的那个布局，并输出这个最大和。

## 解题思路

### 1. 问题拆解

本题可以拆解为两个子问题：

- 生成八皇后的所有合法布局。
- 对每个布局计算皇后所在格子的权值之和，并取最大值。

### 2. 生成所有合法布局

八皇后问题的合法布局要求：

- 每行恰好有一个皇后。
- 每列恰好有一个皇后。
- 任意两个皇后不在同一对角线上。

我们可以用**回溯法**生成所有合法布局。一种经典方法是用一个长度为 $8$ 的数组 $\texttt{column}$ 表示每行皇后所在的列号，初始化为 $[0,1,2,3,4,5,6,7]$，然后生成所有排列。对于每个排列，检查是否满足对角线约束（即 $\left| i - j \right| \neq \left| \texttt{column}[i] - \texttt{column}[j] \right|$ 对所有 $i \neq j$ 成立）。满足条件的排列就是合法布局。

### 3. 存储布局

由于棋盘是固定的 $8 \times 8$，合法布局的总数是 $92$ 个（八皇后问题的经典结论）。我们可以预先计算出所有合法布局，将每个布局中皇后所在的格子编号（按行优先顺序，从 $0$ 到 $63$）存储起来，这样在后续处理每个棋盘数据时，只需要查表累加即可，避免了重复计算。

### 4. 求最大和

对于每个输入的棋盘数据（$64$ 个整数），遍历所有预存的合法布局，计算每个布局的权值和，取最大值输出即可。

### 5. 输入输出格式

- 第一行是一个整数 $k$，表示棋盘的数量。
- 接下来 $k$ 组数据，每组是 $8 \times 8$ 的整数矩阵。
- 输出 $k$ 行，每行是一个右对齐、宽度为 $5$ 的整数，表示该棋盘的最大可能得分。

## 代码实现

代码实现了上述思路：

- 使用 $\texttt{next\_permutation}$ 生成所有列排列，检查对角线冲突。
- 合法布局的格子编号存入 $\texttt{positions}$ 向量。
- 对每个棋盘数据，遍历 $\texttt{positions}$ 计算和并取最大值。
- 使用 $\texttt{setw(5)}$ 和 $\texttt{right}$ 控制输出格式。

```cpp
// The Sultan's Successors
// UVa ID: 167
// Verdict: Accepted
// Submission Date: 2016-02-18
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int number[64], k;
vector<int> column;
vector<vector<int>> positions;

// 判断皇后在对角线上是否会互相攻击。
bool isSolution() {
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < i; j++)
            if (abs(i - j) == abs(column[i] - column[j]))
                return false;
    return true;
}

// 回溯查找所有可能排列。
void backtrack() {
    for (int i = 0; i < 8; i++) column.push_back(i);
    do {
        if (isSolution()) {
            vector<int> solution;
            for (int i = 0; i < 8; i++) solution.push_back(i * 8 + column[i]);
            positions.push_back(solution);
        }
    } while (next_permutation(column.begin(), column.end()));
}

// 对符合要求的放置方案求数值和。
int findMaxSum() {
    int maxSum = 0;
    for (int i = 0; i < positions.size(); i++) {
        int sum = 0;
        for (int j = 0; j < positions[i].size(); j++)
            sum += number[positions[i][j]];
        maxSum = max(sum, maxSum);
    }
    return maxSum;
}

// 读入数据，查找最大值并输出。
int main() {
    backtrack();
    cin >> k;
    while (k--) {
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
                cin >> number[i * 8 + j];
        cout << setw(5) << right << findMaxSum() << endl;
    }
    return 0;
}
```

## 总结

本题是八皇后问题的简单扩展，核心在于**生成所有合法布局**和**查表计算权值和**。由于合法布局数量固定且很少，预计算布局可以大幅提高效率，使得代码运行时间极短。这种“预计算 + 查表”的思想在解决多组数据输入的问题时非常实用。
