[UVa 348 Optimal Array Multiplication Sequence](https://blog.csdn.net/metaphysis/article/details/161557216)

## 题目描述

给定两个矩阵 $A$ 和 $B$，我们可以使用标准矩阵乘法定义计算 $C = A \times B$：

$$
C_{i,j} = \sum_k A_{i,k} \times B_{k,j}
$$

矩阵 $A$ 的列数必须等于矩阵 $B$ 的行数。设 $rows(A)$ 和 $cols(A)$ 分别表示 $A$ 的行数和列数。计算整个 $C$ 数组所需的单个乘法次数为 $rows(A) \times cols(B) \times cols(A)$。

当需要计算多于两个矩阵的乘积时，不同的计算顺序会导致不同的乘法次数。例如，对于三个矩阵 $X$、$Y$、$Z$，计算 $XYZ$ 可以有两种顺序：

- $(XY)Z$：先计算 $XY$，再乘以 $Z$
- $X(YZ)$：先计算 $YZ$，再乘以 $X$

给定一系列矩阵的尺寸，需要确定最优的计算顺序，使得所需的单个乘法次数最少。

### 输入格式

每个测试用例以一个整数 $N$ 开始，表示需要相乘的矩阵数量。接下来 $N$ 对整数，每对给出一个矩阵的行数和列数。矩阵的顺序与输入顺序相同。$N = 0$ 表示输入结束。$N$ 不超过 $10$。

### 输出格式

对于每个测试用例，输出一行，包含一个带括号的表达式，明确表示矩阵相乘的顺序。矩阵命名为 $\texttt{A1}$、$\texttt{A2}$、……、$\texttt{AN}$。前缀输出用例编号。

### 样例输入

```
3
1 5
5 20
20 1
3
5 10
10 20
20 35
6
30 35
35 15
15 5
5 10
10 20
20 25
0
```

### 样例输出

```
Case 1: (A1 x (A2 x A3))
Case 2: ((A1 x A2) x A3)
Case 3: ((A1 x (A2 x A3)) x ((A4 x A5) x A6))
```

---

## 题目分析

### 问题的本质

这是一个经典的**矩阵链乘**（$\texttt{matrix chain multiplication}$）问题。给定一系列矩阵的维度，需要找到一种添加括号的方式，使得标量乘法的总次数最少。

### 矩阵乘法的代价

如果矩阵 $A$ 的维度为 $p \times q$，矩阵 $B$ 的维度为 $q \times r$，则计算 $A \times B$ 的乘法次数为 $p \times q \times r$，结果矩阵的维度为 $p \times r$。

### 动态规划状态定义

设 $dp[i][j]$ 表示计算从矩阵 $i$ 到矩阵 $j$ 的乘积所需的最少乘法次数。设 $dim[i-1]$ 表示第 $i$ 个矩阵的行数，$dim[i]$ 表示第 $i$ 个矩阵的列数（也是第 $i+1$ 个矩阵的行数）。

递推关系：
$$
dp[i][j] = \min_{i \leq k < j} \{ dp[i][k] + dp[k+1][j] + dim[i-1] \times dim[k] \times dim[j] \}
$$

边界条件：$dp[i][i] = 0$（单个矩阵不需要乘法）。

### 路径记录

使用 $split[i][j]$ 记录最优的分割点 $k$，以便在最后输出括号化表达式。

---
## 参考代码

```cpp
// Optimal Array Multiplication Sequence
// UVa ID: 348
// Verdict: Accepted
// Submission Date: 2016-06-29
// UVa Run Time: 0.040s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAX_INTEGER = numeric_limits<int>::max();

int dimensions[15];          // 矩阵维度：dim[i-1] 行数，dim[i] 列数
int multiplications[15][15]; // dp[i][j]：Ai..Aj 的最少乘法次数
int selectedK[15][15];       // 记录最优分割点

// 初始化 dp 数组
void initialize(int n)
{
    for (int i = 1; i <= n; i++)
        for (int j = i; j <= n; j++)
            multiplications[i][j] = MAX_INTEGER;
}

// 递归计算最优乘法次数（记忆化搜索）
int findOptimalMultiplication(int i, int j)
{
    if (multiplications[i][j] < MAX_INTEGER)
        return multiplications[i][j];
    
    if (i == j)
        multiplications[i][j] = 0;
    else
    {
        for (int k = i; k <= j - 1; k++)
        {
            int count = findOptimalMultiplication(i, k) +
                        findOptimalMultiplication(k + 1, j) +
                        dimensions[i - 1] * dimensions[k] * dimensions[j];
                
            if (count < multiplications[i][j])
            {
                multiplications[i][j] = count;
                selectedK[i][j] = k;
            }
        }
    }

    return multiplications[i][j];
}

// 递归输出最优括号化表达式
void printOptimalSequence(int i, int j)
{
    if (i == j)
        cout << "A" << i;
    else
    {
        cout << "(";
        printOptimalSequence(i, selectedK[i][j]);
        cout << " x ";
        printOptimalSequence(selectedK[i][j] + 1, j);
        cout << ")";
    }
}

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);
    
    int n, cases = 0;
    while (cin >> n, n)
    {
        // 读取矩阵维度
        for (int i = 1; i <= n; i++)
        {
            int row, column;
            cin >> row >> column;
            dimensions[i - 1] = row;
            if (i == n) dimensions[i] = column;
        }

        initialize(n);
        
        findOptimalMultiplication(1, n);
        cout << "Case " << ++cases << ": ";
        printOptimalSequence(1, n);
        cout << endl;
    }

    return 0;
}
```
