[UVa 326 Extrapolation Using a Difference Table](https://blog.csdn.net/metaphysis/article/details/161513674)

## 题目描述

外推序列的一种古老技术是基于差分表的使用。给定一个包含 $4$ 个值的序列，例如 $3, 6, 10, 15$，其差分表如下所示：

```
3   3   1   0
6   4   1
10  5
15
```

- 第一列是原始序列值
- 第二列是第一阶差分（相邻项的差）
- 第三列是第二阶差分
- 最后一列是第 $n-1$ 阶差分（$n$ 为序列长度）

对于 $n=4$ 的序列，差分表有 $4$ 列，最后一列只有一个值，表示第 $3$ 阶差分。

为了外推，我们假设第 $n-1$ 阶差分是常数。基于这个假设，可以反向计算：
- 先计算第 $n-1$ 阶差分的下一个值（与之前相同）
- 然后计算第 $n-2$ 阶差分的下一个值
- 依此类推，直到计算出序列的下一个值

### 输入格式

输入包含多个外推请求。每个请求的第一行是一个整数 $n$（$0 < n \leq 10$），指定要扩展的序列长度。当 $n = 0$ 时程序终止。

如果 $n$ 非零，接下来是 $n$ 个整数，表示给定的序列元素。每个外推请求的最后一项是 $k$（$k \geq 1$），表示要执行的外推次数。

要求：计算原序列经过 $k$ 次外推后的第 $n+k$ 项值。

### 输出格式

对于每个请求，输出一行，格式如样例所示。

### 样例输入

```
4
3 6 10 15
1
4
3 6 10 15
2
3
2 4 6
20
6
3 9 12 5 18 -4
10
0
```

### 样例输出

```
Term 5 of the sequence is 21
Term 6 of the sequence is 28
Term 23 of the sequence is 46
Term 16 of the sequence is -319268
```

---

## 题目分析

### 问题的本质

这是一个**差分表外推**问题。给定一个长度为 $n$ 的序列，通过构造差分表，假设最高阶差分为常数，然后反向计算外推值。

### 差分表的数学原理

设原序列为 $a_1, a_2, \dots, a_n$。

定义：
- 一阶差分：$\Delta a_i = a_{i+1} - a_i$
- 二阶差分：$\Delta^2 a_i = \Delta a_{i+1} - \Delta a_i$
- $\dots$
- $n-1$ 阶差分：$\Delta^{n-1} a_i$（只有一个值）

在差分表中，我们通常用**压缩存储**的方式：只保留每个差分序列中可用于外推的部分。

### 外推算法

假设 $\Delta^{n-1} a_i$ 为常数 $c$。那么：
- $\Delta^{n-2} a_{n-1} = \Delta^{n-2} a_{n-2} + c$
- 依此类推，可以逐步计算出 $\Delta a_n$，然后计算出 $a_{n+1}$

重复 $k$ 次，即可得到 $a_{n+k}$。
## 参考代码

```cpp
// Extraploation Using a Difference Table
// UVa ID: 326
// Verdict: Accepted
// Submission Date: 2016-06-28
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    int n;
    while (cin >> n, n)
    {
        vector<long long int> number;
        // 读取原序列的 n 个值
        for (int i = 1; i <= n; i++)
        {
            int value;
            cin >> value;
            number.push_back(value);
        }

        // 构建差分表的压缩形式
        // 经过此循环后：
        // number[0] 存储最高阶差分（第 n-1 阶差分）
        // number[1] 存储第 n-2 阶差分的第一个值
        // ...
        // number[n-1] 存储原序列的第一个值
        for (int i = n - 1; i >= 1; i--)
            for (int j = 0; j <= i - 1; j++)
                number[j] = number[j + 1] - number[j];

        int k;
        cin >> k;
        
        // 进行 k 次外推
        // 每次外推：从最高阶差分开始累加，计算出新的序列值
        for (int i = 1; i <= k; i++)
            for (int j = 1; j <= n - 1; j++)
                number[j] += number[j - 1];

        // 输出结果，number.back() 即为第 n+k 项的值
        cout << "Term " << (n + k) << " of the sequence is " << number.back() << endl;
    }

    return 0;
}
```
