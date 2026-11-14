[UVa 344 Roman Digititis](https://blog.csdn.net/metaphysis/article/details/161557151)

## 题目描述

许多人都熟悉较小数值的罗马数字表示法。符号 `i`、`v`、`x`、`l` 和 `c` 分别表示十进制数值 $1$、$5$、$10$、$50$ 和 $100$。要表示其他数值，将这些符号按需拼接，较小的符号写在右边。例如，数字 $3$ 表示为 `iii`，数字 $73$ 表示为 `lxxiii`。

此规则的例外情况出现在个位数为 $4$ 或 $9$，以及十位数为 $40$ 或 $90$ 时。对于这些情况，罗马数字表示为 `iv`（$4$）、`ix`（$9$）、`xl`（$40$）和 `xc`（$90$）。因此，$24$、$39$、$44$、$49$ 和 $94$ 的罗马数字表示分别为 `xxiv`、`xxxix`、`xliv`、`xlix` 和 `xciv`。

许多书籍的序言页使用罗马数字编号，从第一页的 `i` 开始，依次递增。假设书籍序言不超过 $100$ 页。问：要编号序言的所有页面，需要多少个 `i`、`v`、`x`、`l` 和 `c` 字符？

例如，一个 $5$ 页的序言使用罗马数字 `i`、`ii`、`iii`、`iv`、`v`，总共需要 $7$ 个 `i` 字符和 $2$ 个 `v` 字符。

### 输入格式

输入包含一系列 $1$ 到 $100$ 之间的整数，以 $0$ 结束。

### 输出格式

对于每个输入整数（除了最后的 $0$），输出一行，包含该整数以及每种字符所需的数量。格式如样例所示。

### 样例输入

```
1 2 20 99 0
```

### 样例输出

```
1: 1 i, 0 v, 0 x, 0 l, 0 c
2: 3 i, 0 v, 0 x, 0 l, 0 c
20: 28 i, 10 v, 14 x, 0 l, 0 c
99: 140 i, 50 v, 150 x, 50 l, 10 c
```

---

## 题目分析

### 问题的本质

这是一个**罗马数字生成与字符计数**问题。需要：
1. 将 $1$ 到 $n$ 的每个整数转换为罗马数字表示
2. 统计所有罗马数字字符串中每个字符（`i`、`v`、`x`、`l`、`c`）出现的总次数

### 罗马数字的表示规则

本题使用简化版的罗马数字规则（仅涉及 $100$ 以内的数）：
- 基本符号：`i`（$1$）、`v`（$5$）、`x$（$10$）、`l`（$50$）、`c`（$100$）
- 加法规则：较小符号在右侧表示相加
- 减法规则：$4$ 和 $9$ 使用减法表示（`iv`、`ix`、`xl`、`xc`）

### 数字分解

对于 $100$ 以内的数，可以分解为：
- 百位：$100$ 表示为 `c`
- 十位：$10 \sim 90$
- 个位：$1 \sim 9$

### 预计算

由于 $n \leq 100$，可以预先计算 $1$ 到 $100$ 每个数的罗马数字表示，然后累加计数。

---
## 参考代码

```cpp
// Roman Digititis
// UVa ID: 344
// Verdict: Accepted
// Submission Date: 2016-06-25
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

string digits = "ivxlc";  // 需要统计的五种字符

// 个位数 1-9 的罗马数字表示
vector<string> single = {
    "i", "ii", "iii", "iv", "v", "vi", "vii", "viii", "ix"
};

// 十位数 10-100 的罗马数字表示（索引 0 对应 10，索引 9 对应 100）
vector<string> tens = {
    "x", "xx", "xxx", "xl", "l", "lx", "lxx", "lxxx", "xc", "c"
};

// 将 1-100 的整数转换为罗马数字
string numberToRoman(int i)
{
    string text;
    // 处理百位（只有 100）
    if (i >= 100)
    {
        text += "c";
        i %= 100;
    }
    // 处理十位
    if (i >= 10)
    {
        text += tens[i / 10 - 1];
        i %= 10;
    }
    // 处理个位
    if (i > 0)
        text += single[i - 1];
    
    return text;
}

int main(int argc, char *argv[])
{
    int n;
    while (cin >> n, n)
    {
        map<char, int> counter;
        // 初始化计数器
        for (auto c : digits)
            counter[c] = 0;
        
        // 累加 1 到 n 的所有罗马数字字符
        for (int i = 1; i <= n; i++)
        {
            string text = numberToRoman(i);
            for (auto c : text)
                counter[c]++;
        }
        
        // 输出结果
        cout << n << ":";
        for (auto c : digits)
        {
            cout << " " << counter[c] << " " << c;
            if (c != 'c') cout << ",";
        }
        cout << endl;
    }
    
    return 0;
}
```
