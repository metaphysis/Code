[UVa 382 Perfection](https://blog.csdn.net/metaphysis/article/details/161673587)

## 题目描述

根据 $1994$ 年微软 $\texttt{Encarta}$ 中《数论》条目的定义：

> 如果 $a, b, c$ 是整数，且 $a = bc$，则称 $a$ 是 $b$ 或 $c$ 的倍数，$b$ 或 $c$ 称为 $a$ 的除数或因子。如果 $c \neq \pm 1$，则 $b$ 称为 $a$ 的真因子。偶数（包括 $0$）是 $2$ 的倍数，例如 $-4, 0, 2, 10$；奇数是不是偶数的整数，例如 $-5, 1, 3, 9$。
>
> 完数（$\texttt{perfect number}$）是一个正整数，它等于其所有正真因子之和。例如 $6 = 1 + 2 + 3$，$28 = 1 + 2 + 4 + 7 + 14$，它们都是完数。
>
> 不是完数的正整数称为不完美数，根据其正真因子之和小于或大于该数本身，分别称为亏数（$\texttt{deficient}$）或盈数（$\texttt{abundant}$）。例如，$9$ 的真因子为 $1, 3$，和为 $4 < 9$，是亏数；$12$ 的真因子为 $1, 2, 3, 4, 6$，和为 $16 > 12$，是盈数。

你的任务是：给定一个数，判断它是完数、亏数还是盈数。

## 输入格式

输入包含若干个正整数（均不超过 $60000$），数量 $N$ 满足 $1 < N < 100$。以 $0$ 表示输入结束。

## 输出格式

第一行输出 `PERFECTION OUTPUT`。接下来 $N$ 行，每行按照示例格式输出：输入的整数右对齐在 $5$ 个字符宽度内，后跟两个空格，再跟描述字符串（`PERFECT`、`DEFICIENT` 或 `ABUNDANT`）。最后一行输出 `END OF OUTPUT`。

## 样例

**输入**

```
15 28 6 56 60000 22 496 0
```

**输出**

```
PERFECTION OUTPUT
   15  DEFICIENT
   28  PERFECT
    6  PERFECT
   56  ABUNDANT
60000  ABUNDANT
   22  DEFICIENT
  496  PERFECT
END OF OUTPUT
```

## 题目分析

本题的核心是：**计算一个正整数的所有正真因子之和，并与该数本身比较**。

定义真因子为除了该数本身以外的所有正因子。例如 $6$ 的真因子为 $1, 2, 3$，其和为 $6$，故 $6$ 是完数。

直接做法是：枚举 $1$ 到 $n-1$，检查每个数是否是 $n$ 的因子，累加求和。复杂度为 $O(n)$，对于 $n \leq 60000$ 且 $N < 100$，最坏情况为 $60000 \times 100 = 6 \times 10^6$，完全可行。

## 代码实现

```cpp
// Perfection
// UVa ID: 382
// Verdict: Accepted
// Submission Date: 2016-06-25
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);
    
    cout << "PERFECTION OUTPUT" << endl;
    
    int n;
    while (cin >> n, n)
    {
        int sum = 0;
        for (int i = 1; i < n; i++)
            if (n % i == 0)
                sum += i;
                
        cout << setw(5) << right << n;
        cout << "  ";
        if (sum == n) cout << "PERFECT" << endl;
        else if (sum < n) cout << "DEFICIENT" << endl;
        else cout << "ABUNDANT" << endl;
    }
    
    cout << "END OF OUTPUT" << endl;
    
    return 0;
}
```
