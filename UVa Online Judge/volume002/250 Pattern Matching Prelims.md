[UVa 250 Pattern Matching Prelims](https://blog.csdn.net/metaphysis/article/details/161278906)

## 题目分析

本题属于光学字符识别（$\texttt{OCR}$）中的预处理问题。在字符识别过程中，扫描得到的图像往往存在噪声、形变，导致字符的大小、位置和方向发生变化。为了能够将扫描图像与标准模板进行匹配，需要找到图像中的一个基准点——**重心**（$\texttt{Center of Gravity}$），作为对齐的参考点。

### 重心的定义

对于一个 $n \times m$ 的灰度矩阵，每个元素的值在 $[0,1]$ 之间，$0$ 表示白色，$1$ 表示黑色。重心的位置由行和列分别独立确定：

- **行的选择**：假设重心在第 $i$ 行，那么忽略第 $i$ 行后，上方所有行的元素之和与下方所有行的元素之和的差值应尽可能小。
- **列的选择**：类似地，忽略第 $j$ 列后，左侧所有列的元素之和与右侧所有列的元素之和的差值应尽可能小。

特别地，如果存在多个满足最小差值的行或列，则选择**行号最大、列号最大**的那一组。

### 输入输出格式

- 输入由多组数据组成，每组数据第一行为两个整数 $R$ 和 $C$，分别表示矩阵的行数和列数，满足 $1 \leq R, C \leq 25$。接下来是 $R \times C$ 个浮点数，按照行主序给出。输入以 `0 0` 结束。
- 输出格式：对于每组数据，输出 `Case k: center at (r, c)`，其中 $k$ 从 $1$ 开始编号。

### 样例分析

以题目中的 $5 \times 5$ 矩阵为例：

```
0.7 0.75 0.7 0.75 0.8
0.55 0.3 0.2 0.1 0.7
0.8 0.1 0.0 0.0 0.8
0.7 0.0 0.0 0.0 0.8
0.8 0.9 0.8 0.75 0.9
```

计算各行元素之和：
- 第 $1$ 行：$3.7$
- 第 $2$ 行：$1.85$
- 第 $3$ 行：$1.7$
- 第 $4$ 行：$1.5$
- 第 $5$ 行：$4.15$

总行和：$12.9$。

对于行 $i=3$（忽略第 $3$ 行），上方行和 = $3.7 + 1.85 = 5.55$，下方行和 = $1.5 + 4.15 = 5.65$，差值为 $0.1$。因此重心在第 $3$ 行。

类似地，计算各列之和，可得重心在第 $3$ 列。

## 解题思路

### 初步思考

最直接的方法是：对于每一行 $i$，分别计算上方元素和与下方元素和，然后求差值，找到最小差值对应的行。列也类似。时间复杂度为 $O(R \times C \times (R + C))$。由于 $R, C \leq 25$，这个复杂度完全可行（约 $25 \times 25 \times 50 = 31250$ 次操作）。

但我们可以进一步优化。

### 前缀和优化

注意到“忽略第 $i$ 行”后，上方元素和就是第 $1$ 行到第 $i-1$ 行的元素之和，下方元素和就是第 $i+1$ 行到第 $R$ 行的元素之和。因此，如果我们预先计算出每一行的元素和（即**行前缀和**），就可以在 $O(1)$ 时间内得到任意分割的上下方元素和。

设：
- $rowSum[i]$ 表示原矩阵第 $i$ 行的元素之和（$1 \leq i \leq R$）。
- $prefixRow[i] = \sum_{k=1}^{i} rowSum[k]$ 表示前 $i$ 行的元素和。

那么：
- 忽略第 $i$ 行后，上方元素和 = $prefixRow[i-1]$。
- 下方元素和 = $totalSum - prefixRow[i]$，其中 $totalSum = prefixRow[R]$。

差值 = $\big| prefixRow[i-1] - (totalSum - prefixRow[i]) \big| = \big| totalSum - prefixRow[i] - prefixRow[i-1] \big|$。

同理，对于列：
- $colSum[j]$ 表示原矩阵第 $j$ 列的元素之和。
- $prefixCol[j] = \sum_{k=1}^{j} colSum[k]$。
- 忽略第 $j$ 列后，左侧元素和 = $prefixCol[j-1]$，右侧元素和 = $totalSum - prefixCol[j]$。
- 差值 = $\big| totalSum - prefixCol[j] - prefixCol[j-1] \big|$。

### 处理多个最优解

题目要求：如果有多行能使差值最小，选择行号最大的；列同理。因此我们在遍历行和列时，应该从大到小遍历，并仅在遇到**更小**的差值时才更新答案，这样最后一个遇到的“相等”差值就不会覆盖之前更大的行号。

### 边界情况

- 当 $R=1$ 时，没有“上方”和“下方”行，此时忽略唯一的一行后，上下方和均为 $0$，差值为 $0$，重心行取 $1$。
- 当 $C=1$ 时类似。

在代码实现中，我们从 $R-2$ 开始下降到 $1$，并将初始的最小行设为 $R-1$（最后一行的上一行），初始差值设为 $\big|totalSum\big|$。这样可以正确处理边界。

### 浮点数精度

由于输入是浮点数，直接比较相等可能因精度问题出错。因此我们使用一个小的容差值 `EPSILON = 1E-6`，在比较 $temp < minDifference$ 时，使用 `temp + EPSILON < minDifference` 来避免浮点误差。

## 代码实现

```cpp
// Pattern Matching Prelims
// UVa ID: 250
// Verdict: Accepted
// Submission Date: 2016-05-23
// UVa Run Time: 0.040s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const double EPSILON = 1E-6;  // 浮点数比较的容差值

int main() {
    cin.tie(0);                         // 加速输入输出
    cout.sync_with_stdio(false);
    
    vector<double> sumOfRows, sumOfColumns;  // 存储行和列的前缀和
    
    int row, column, cases = 0;
    while (cin >> row >> column, row && column)  // 读取矩阵大小，遇到0 0结束
    {
        sumOfRows.clear();
        sumOfColumns.clear();
        
        sumOfRows.resize(row);          // 调整行前缀和数组大小
        sumOfColumns.resize(column);    // 调整列前缀和数组大小
        
        fill(sumOfRows.begin(), sumOfRows.end(), 0.0);
        fill(sumOfColumns.begin(), sumOfColumns.end(), 0.0);
        
        double value;
        // 读取矩阵元素，同时累加每一行和每一列的和
        for (int i = 0; i < row; i++)
            for (int j = 0; j < column; j++)
            {
                cin >> value;
                sumOfRows[i] += value;     // 累加到对应行
                sumOfColumns[j] += value;  // 累加到对应列
            }
            
        // 计算行前缀和：sumOfRows[i] 现在表示前 i+1 行的元素和
        for (int i = 1; i < sumOfRows.size(); i++)
            sumOfRows[i] += sumOfRows[i - 1];
            
        // 计算列前缀和：sumOfColumns[j] 现在表示前 j+1 列的元素和
        for (int j = 1; j < sumOfColumns.size(); j++)
            sumOfColumns[j] += sumOfColumns[j - 1];
        
        double total = sumOfRows[row - 1];  // 矩阵所有元素的总和
        
        // 寻找最优行：从最后一行向前遍历，保证遇到相等差值时保留更大的行号
        int minRow = row - 1;
        double minDifference = fabs(total);  // 初始差值：忽略第一行时的情况
        
        // i 从 row-2 到 1，对应实际行号从 row-1 到 2（因为需要上下都有行）
        for (int i = row - 2; i >= 1; i--)
        {
            // 忽略第 i+1 行（0-indexed）时的差值
            double temp = fabs(total - sumOfRows[i] - sumOfRows[i - 1]);
            // 如果找到更小的差值，更新答案
            if (temp + EPSILON < minDifference)
            {
                minRow = i;
                minDifference = temp;
            }
        }
        
        // 寻找最优列：从最后一列向前遍历
        int minColumn = column - 1;
        minDifference = fabs(total);  // 初始差值：忽略第一列时的情况
        
        for (int j = column - 2; j >= 1; j--)
        {
            double temp = fabs(total - sumOfColumns[j] - sumOfColumns[j - 1]);
            if (temp + EPSILON < minDifference)
            {
                minColumn = j;
                minDifference = temp;
            }
        }
        
        // 将 0-indexed 转换为 1-indexed 输出
        minRow++;
        minColumn++;
        
        cout << "Case " << ++cases;
        cout << ": center at (" << minRow << ", " << minColumn << ")" << endl;
    }
    
    return 0;
}
```

## 复杂度分析

- **时间复杂度**：$O(R \times C)$，主要来自输入读取和前缀和计算，遍历行和列各需 $O(R + C)$。
- **空间复杂度**：$O(R + C)$，用于存储行和列的前缀和。

## 总结

本题的核心是利用前缀和技巧将原本需要 $O(R \times C)$ 的区间和查询优化为 $O(1)$，从而快速计算忽略某行或某列后的上下/左右元素和。同时需要注意浮点精度处理和多个最优解时的选择规则。
