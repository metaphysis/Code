[UVa 406 Prime Cuts](https://blog.csdn.net/metaphysis/article/details/161736946)

## 题目描述

题目要求从 $1$ 到 $N$ 的素数列表中，截取中心位置的一段连续素数进行输出。具体规则如下：

- 首先找出 $1$ 到 $N$ 之间（包含 $1$ 和 $N$）的所有素数。注意本题中 $1$ 被视为素数。
- 设素数列表的长度为 $L$。
- 如果 $L$ 为偶数，则输出列表中心的 $2C$ 个素数。
- 如果 $L$ 为奇数，则输出列表中心的 $2C - 1$ 个素数。
- 如果所需的中心素数数量超过了列表本身的大小，则输出整个素数列表。

## 输入格式

输入包含多组测试数据，每组数据占一行。每行包含两个整数 $N$ 和 $C$，其中：
- $N$（$1 \le N \le 1000$）表示素数列表的上限。
- $C$（$1 \le C \le N$）用于确定输出素数的数量。

## 输出格式

对于每组测试数据，输出一行，格式为：
```
N C: 素数1 素数2 素数3 ...
```
其中：
- $N$ 和 $C$ 按原值输出，后面紧跟一个冒号和空格。
- 输出的每个素数前面有恰好一个空格。
- 每组输出后面跟一个空行。

## 样例

输入

```cpp
21 2
18 2
18 18
100 7
```

输出

```cpp
21 2: 5 7 11

18 2: 3 5 7 11

18 18: 1 2 3 5 7 11 13 17

100 7: 13 17 19 23 29 31 37 41 43 47 53 59 61 67
```

## 题目分析

本题的核心是生成 $1$ 到 $N$ 的素数列表，然后根据列表长度的奇偶性确定要输出的中心子序列。

### 素数的定义与范围

本题中有一个特殊规定：**$1$ 被视为素数**。这与通常的数学定义不同，需要注意。因此素数列表始终包含 $1$。

$N$ 的最大值为 $1000$，因此可以直接使用简单的素数判定方法（如试除法）来生成素数列表，无需使用复杂的筛法。

### 中心位置的确定

设素数列表为 $p[0], p[1], \ldots, p[L-1]$，其中 $L$ 为列表长度。

**情况一：$L$ 为偶数**
- 需要输出 $2C$ 个素数。
- 中心位置：列表中间的两个元素是 $p[L/2 - 1]$ 和 $p[L/2]$。
- 从这两个元素向两侧扩展，共输出 $2C$ 个元素。
- 起始索引为 $\textit{start} = L/2 - C$，结束索引为 $\textit{end} = L/2 + C - 1$。

**情况二：$L$ 为奇数**
- 需要输出 $2C - 1$ 个素数。
- 中心位置：列表中间的元素是 $p[(L-1)/2]$。
- 从这个元素向两侧扩展，共输出 $2C - 1$ 个元素。
- 起始索引为 $\textit{start} = (L-1)/2 - (C - 1)$，结束索引为 $\textit{end} = (L-1)/2 + (C - 1)$。

### 边界处理

如果计算出的 $\textit{start} < 0$ 或 $\textit{end} \ge L$，说明需要的中心素数数量超过了列表大小，此时应输出整个列表（即从 $p[0]$ 到 $p[L-1]$）。

### 特殊情况

- 当 $C$ 足够大时，$2C$ 或 $2C - 1$ 可能超过 $L$，此时直接输出整个列表。
- 注意 $C$ 的取值范围是 $1 \le C \le N$，但 $N$ 可能小于 $L$（例如 $N=1$ 时 $L=1$），此时 $C$ 可能大于 $L$，需要正确处理。

由于 $N$ 最大为 $1000$，且输入包含多组数据，可以预先计算出 $1$ 到 $1000$ 的所有素数，存储在全局数组中。这样每组测试数据只需从预先生成的素数表中截取 $1$ 到 $N$ 的部分即可。

素数判定使用试除法：对于每个数 $x$（$2 \le x \le 1000$），检查是否存在 $2$ 到 $\sqrt{x}$ 之间的因子。如果没有，则 $x$ 是素数。同时将 $1$ 也加入素数列表。

对于每组输入的 $N$ 和 $C$：
1. 从预先生成的素数表中，取出所有 $\le N$ 的素数，得到当前列表。
2. 设列表长度为 $L$。
3. 计算需要输出的数量 $K$：
   - 若 $L$ 为偶数，则 $K = 2C$。
   - 若 $L$ 为奇数，则 $K = 2C - 1$。
4. 如果 $K \ge L$，则输出整个列表。
5. 否则，计算起始索引：
   - 若 $L$ 为偶数：$\textit{start} = L/2 - C$
   - 若 $L$ 为奇数：$\textit{start} = (L-1)/2 - (C - 1)$
6. 输出从 $\textit{start}$ 到 $\textit{start} + K - 1$ 的所有素数。

输出时严格按照格式：先输出 $N$ 和 $C$，中间用一个空格分隔，然后输出冒号和空格，接着输出每个素数，每个素数前面有一个空格。输出结束后打印一个空行。

## 代码实现

```cpp
// Prime Cuts
// UVa ID: 406
// Verdict: Accepted
// Submission Date: 2016-07-20
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int primes[200], cnt = 0;

void generate_primes()
{
    primes[cnt++] = 1;
    for (int i = 2; i <= 1000; i++)
    {
        bool is_prime = true;
        for (int j = 2; j <= sqrt(i); j++)
        {
            if (i % j == 0)
            {
                is_prime = false;
                break;
            }
        }
        if (is_prime) primes[cnt++] = i;
    }
}

int main(int argc, char *argv[])
{
    generate_primes();
    
    int N, C;
    while (cin >> N >> C)
    {
        vector<int> selected;
        for (int i = 0; i < cnt && primes[i] <= N; i++)
            selected.push_back(primes[i]);
            
        int size = selected.size();
        cout << N << ' ' << C << ':';
        
        if (size % 2 == 1)
        {
            int need = 2 * C - 1;
            if (need >= size)
            {
                for (int i = 0; i < size; i++)
                    cout << ' ' << selected[i];
            }
            else
            {
                int start = size / 2 - (C - 1);
                for (int i = start; i < start + need; i++)
                    cout << ' ' << selected[i];
            }
        }
        else
        {
            int need = 2 * C;
            if (need >= size)
            {
                for (int i = 0; i < size; i++)
                    cout << ' ' << selected[i];
            }
            else
            {
                int start = size / 2 - C;
                for (int i = start; i < start + need; i++)
                    cout << ' ' << selected[i];
            }
        }
        cout << "\n\n";
    }
    
    return 0;
}
```