[UVa 136 Ugly Numbers](https://blog.csdn.net/metaphysis/article/details/157426402)

## 题目描述

“丑数”（$\texttt{Ugly Numbers}$）是指那些质因数只包含 $2$、$3$ 或 $5$ 的正整数。通常约定 $1$ 也算作丑数。前 $11$ 个丑数为：

$$
1,\ 2,\ 3,\ 4,\ 5,\ 6,\ 8,\ 9,\ 10,\ 12,\ 15,\ \dots
$$

本题要求编写程序，找出并输出第 $1500$ 个丑数。

**输入格式**

无输入。

**输出格式**

输出一行，格式为：

```
The 1500'th ugly number is <number>.
```

其中 `<number>` 应替换为计算出的第 $1500$ 个丑数。

---

## 题目分析

我们需要生成一个序列，序列中的每个数都满足：其质因数只包含 $2$、$3$、$5$。换句话说，对于任意丑数 $n$，存在非负整数 $a$、$b$、$c$，使得：

$$
n = 2^a \times 3^b \times 5^c
$$

本题的核心在于**按顺序生成丑数**，并找到第 $1500$ 个。

---

## 解题思路

### 方法一：模拟法（朴素判断）

一种直接的方法是：从 $1$ 开始逐个判断每个正整数是否为丑数，直到找到第 $1500$ 个为止。

判断丑数的方法：
- 将该数不断除以 $2$、$3$、$5$，直到不能再被这三个数整除。
- 若最终结果为 $1$，则该数是丑数。

**优点**：实现简单，易于理解。  
**缺点**：效率较低，因为需要检查很多非丑数。不过对于第 $1500$ 个丑数，其值并不大（约为 $8.5 \times 10^5$）。

**时间复杂度**：$O(n \log n)$，其中 $n$ 是第 $1500$ 个丑数的值。

---

### 方法二：优先队列法（高效生成）

我们可以利用**最小堆**（优先队列）来按顺序生成丑数：

1. 初始化一个最小堆，将 $1$ 压入堆中。
2. 每次从堆中取出最小元素 $x$，它就是当前最小的丑数。
3. 将 $x \times 2$、$x \times 3$、$x \times 5$ 压入堆中（若尚未出现过）。
4. 用一个集合记录已生成的丑数，避免重复入堆。
5. 重复上述过程，直到取出第 $1500$ 个丑数。

**优点**：只生成丑数，无需判断非丑数，效率高。  
**缺点**：需要额外的数据结构（堆和集合）。

**时间复杂度**：$O(n \log n)$，其中 $n = 1500$。

---

## 代码实现

### 方法一代码（模拟法）

```cpp
// Ugly Numbers
// UVa ID: 136
// Verdict: Accepted
// Submission Date: 2016-01-08
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
int main() {
    long long int start = 1;
    int counter = 1;
    while (counter < 1500) {
        start++;
        long long int number = start;
        while (number % 2 == 0) number /= 2;
        while (number % 3 == 0) number /= 3;
        while (number % 5 == 0) number /= 5;
        if (number == 1) counter++;
    }
    cout << "The 1500'th ugly number is " << start << "." << endl;
    return 0;
}
```

### 方法二代码（优先队列法）

```cpp
// Ugly Numbers
// UVa ID: 136
// Verdict: Accepted
// Submission Date: 2016-01-08
// UVa Run Time: 0.000s
// 
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
typedef long long int bigNumber;
int main() {
    int factors[3] = { 2, 3, 5 };
    set<bigNumber> uglyNumbers;
    priority_queue<bigNumber, vector<bigNumber>, greater<bigNumber>> candidates;
    candidates.push(1);
    for (int i = 1; i <= 1500; i++) {
        bigNumber top;
        do {
            top = candidates.top();
            candidates.pop();
        }
        while (uglyNumbers.count(top) > 0);
        uglyNumbers.insert(top);
        for (int j = 0; j < 3; j++) {
            bigNumber next = top * factors[j];
            if (uglyNumbers.count(next) == 0) candidates.push(next);
        }
        if (i == 1500) {
            cout << "The 1500'th ugly number is " << top << "." << endl;
            break;
        }
    }
    return 0;
}
```

---

## 总结

本题展示了两种生成丑数的方法：
- **模拟法**：简单直接，适合输入规模不大的情况。
- **优先队列法**：高效且可扩展，适合需要生成大量丑数的场景。

两种方法均能快速通过，输出结果一致。对于此类“按条件生成序列”的问题，优先队列法是一种非常实用的技巧。

**最终答案**：第 $1500$ 个丑数为 $859963392$。
