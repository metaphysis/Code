[UVa 333 Recognizing Good ISBNs](https://blog.csdn.net/metaphysis/article/details/161533406)

## 题目描述

如今出版的大多数书籍都被分配了一个唯一标识该书的代码。国际标准书号（$\texttt{ISBN}$）通常是 $10$ 位十进制数字的序列，但在某些情况下，大写字母 $\texttt{X}$ 也可作为第 $10$ 位出现。$\texttt{ISBN}$ 中可能在不同位置包含连字符（以便于阅读），但没有其他意义。样例输入和输出展示了 $\texttt{ISBN}$ 的多种合法和非法形式。

实际上，$\texttt{ISBN}$ 中只有前 $9$ 位数字用于标识书籍。第 $10$ 个字符作为校验位，用于验证前 $9$ 位数字是否正确。校验位的选择使得按照下述算法计算的值能被 $11$ 整除。由于校验位有时可能需要达到 $10$ 才能保证被 $11$ 整除，$\texttt{ISBN}$  设计者选择了一个特殊符号来代表 $10$，这就是 $\texttt{X}$ 的作用。

### $\texttt{ISBN}$  校验算法

计算两个和 $s1$ 和 $s2$，其中 $s2$ 是每个数字加入 $s1$ 后的部分和的总和。如果最终 $s2$ 的值能被 $11$ 整除，则 $\texttt{ISBN}$ 正确。

以正确的 $\texttt{ISBN}$ `0-13-162959-X` 为例：

| $\texttt{ISBN}$ 中的数字 | 部分和 $s1$ |
|------------|-----------|
| $0$ | $0$ |
| $1$ | $1$ |
| $3$ | $4$ |
| $1$ | $5$ |
| $6$ | $11$ |
| $2$ | $13$ |
| $9$ | $22$ |
| $5$ | $27$ |
| $9$ | $36$ |
| $10 (X)$ | $46$ |

$s2$ 是所有部分和的总和：
```
0 + 1 + 4 + 5 + 11 + 13 + 22 + 27 + 36 + 46 = 165
```
$165$ 能被 $11$ 整除，因此 $\texttt{ISBN}$ 正确。

### 输入格式

输入文件每行包含一个 $\texttt{ISBN}$ 候选字符串，前后可能有额外的空格。每行不超过 $80$ 个字符。候选字符串可能包含非法字符，也可能多于或少于所需的 $10$ 位数字。输入以文件结束符（$\texttt{EOF}$）结束。

### 输出格式

对于每个候选 $\texttt{ISBN}$，输出该字符串（去除前后空格）以及判断结果（`correct` 或 `incorrect`）。

### 样例输入

```
0- 89237- 010- 6
0- 8306- 3637- 4
0- 06- 017758- 6
This_is_garbage
1- 56884- 030- 6
0- 8230- 2571- 3
0- 345- 31386- 0
0- 671- 88858- 7
0- 8104- 5687- 7
0- 671- 74119- 5
0- 812- 52030- 0
0- 345- 24865- 1- 150
0- 452- 26740- 4
0- 13- 139072- 4
0- 1315- 2447- X
```

### 样例输出

```
0- 89237- 010- 6 is correct.
0- 8306- 3637- 4 is correct.
0- 06- 017758- 6 is correct.
This_is_garbage is incorrect.
1- 56884- 030- 6 is correct.
0- 8230- 2571- 3 is correct.
0- 345- 31386- 0 is correct.
0- 671- 88858- 7 is correct.
0- 8104- 5687- 7 is correct.
0- 671- 74119- 5 is correct.
0- 812- 52030- 0 is correct.
0- 345- 24865- 1- 150 is incorrect.
0- 452- 26740- 4 is correct.
0- 13- 139072- 4 is correct.
0- 1315- 2447- X is correct.
```

---

## 题目分析

### 问题的本质

这是一个**字符串解析 + 校验和计算**问题。需要从包含可能连字符和空格的字符串中提取出 $10$ 个有效字符（数字或 $\texttt{X}$），然后计算加权和校验。

### $\texttt{ISBN}$ 的组成

- 前 $9$ 位：数字 $0 \sim 9$
- 第 $10$ 位：数字 $0 \sim 9$ 或大写字母 $\texttt{X}$（代表 $10$）

### 格式要求

- 连字符可以出现在任意位置，忽略不计
- 空格可以出现在前后或中间，但需要去除首尾空格后输出原字符串
- 无效字符（字母、标点等）会导致 $\texttt{ISBN}$ 非法
- 数字数量必须恰好为 $10$
- $\texttt{X}$ 只能出现一次，且只能出现在最后一位（隐含条件，由算法自动判断）

### 校验算法

设提取出的有效数字为 $d_1, d_2, \dots, d_{10}$，其中 $d_i \in [0,9]$，$d_{10}$ 可以为 $10$（$\texttt{X}$）。

定义：
$$
s1_i = \sum_{k=1}^{i} d_k
$$
$$
s2 = \sum_{i=1}^{10} s1_i
$$

$\texttt{ISBN}$ 合法当且仅当：
1. 恰好有 $10$ 个有效数字
2. 如果有 $\texttt{X}$，它必须是最后一个有效数字
3. $s2 \bmod 11 = 0$

---
## 参考代码

```cpp
// Recongnizing Good ISBNs
// UVa ID: 333
// Verdict: Accepted
// Submission Date: 2016-06-28
// UVa Run Time: 0.050s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);
    
    string line;
    while (getline(cin, line))
    {
        int term = 0;      // 当前部分和 s1
        int sum = 0;       // 所有部分和的总和 s2
        bool correct = true;
        int counter = 0;   // 有效数字计数
        int indexer = 0;   // 字符位置计数
        int digitIndex = -1;  // 最后一个数字的位置
        int xIndex = -1;      // X 出现的位置
        
        // 扫描每个字符
        for (auto c : line)
        {
            indexer++;  // 1-based 位置计数
        
            if (isdigit(c))
            {
                counter++;
                digitIndex = indexer;
                term += c - '0';      // 更新 s1
                sum += term;          // 累加到 s2
            }
            else if (c == 'X')
            {
                counter++;
                // X 只能出现一次
                if (xIndex == -1)
                    xIndex = indexer;
                else
                {
                    correct = false;
                    break;
                }
                
                term += 10;   // X 代表 10
                sum += term;
            }
            
            // 如果已经超过 10 位有效数字，提前终止
            if (counter > 10)
                break;
        }
        
        // 判断有效数字数量是否正确，以及 X 是否在最后一位
        if (counter != 10 || (xIndex > 0 && xIndex < digitIndex))
            correct = false;
        
        // 去除原字符串的首尾空格，用于输出
        int left = 0, right = line.length() - 1;
        while (left < line.length() && isblank(line[left])) left++;
        while (right >= 0 && isblank(line[right])) right--;
        
        for (int i = left; i <= right; i++)
            cout << line[i];

        // 输出判断结果
        if (!correct) 
            cout << " is incorrect.\n";
        else if (sum % 11 == 0) 
            cout << " is correct.\n";
        else 
            cout << " is incorrect.\n";
    }
    
    return 0;
}
```
