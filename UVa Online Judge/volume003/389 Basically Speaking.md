[UVa 389 Basically Speaking](https://blog.csdn.net/metaphysis/article/details/161673686)

## 题目描述

$\texttt{Really Neato Calculator}$ 公司最近雇佣你的团队来帮助设计他们的 $\texttt{Super Neato Model I}$ 计算器。作为计算机科学家，你建议这个新计算器能够进行进制转换。公司认为这是一个绝妙的主意，并要求你的团队提出原型程序来进行进制转换。

$\texttt{Super Neato Model I}$ 计算器具有以下特点：
- $7$ 位数字显示
- 按钮包括大写字母 $A \sim F$ 以及数字 $0 \sim 9$
- 支持 $2 \sim 16$ 进制

### 输入格式

输入每行包含一个进制转换。每行有三个数据：
- 第一个：要转换的数字（可能有前导零）
- 第二个：源进制
- 第三个：目标进制

数字之间有一个或多个空格。有多行输入，程序应读取到文件结束。

### 输出格式

输出转换后的数字，在 $7$ 位显示中右对齐。如果数字太大无法显示（超过 $7$ 位），则输出 `ERROR`（也是右对齐）。

### 样例输入

```
1111000 2 10
1111000 2 16
2102101 3 10
2102101 3 15
12312 4 2
1A 15 2
ABCD 16 15
03 13 10
```

### 样例输出

```
    120
     78
   1765
    7CA
  ERROR
  11001
   D071
      3
```

---

## 题目分析

### 问题的本质

这是一个**进制转换**问题。需要：
1. 将给定进制的数字转换为十进制
2. 将十进制转换为目标进制
3. 格式化输出（$7$ 位右对齐，超长输出 `ERROR`）

### 字符映射

- 数字 `0`~`9` 对应数值 $0 \sim 9$
- 字母 `A`~`F` 对应数值 $10 \sim 15$

### 数据范围

输入数字长度未知，但 $7$ 位显示限制意味着十进制转换后的数值可能很大。使用 $32$ 位整数足够，因为 $16^7 = 2^{28} \approx 2.68 \times 10^8$，在 $32$ 位范围内。

---

## 参考代码

```cpp
// Basically Speaking
// UVa ID: 389
// Verdict: Accepted
// Submission Date: 2016-06-27
// UVa Run Time: 0.270s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);
    
    string number;
    int base1, base2;
    string digits = "0123456789ABCDEF";
    map<char, int> key;
    
    // 建立字符到数值的映射
    for (int i = 0; i < digits.length(); i++)
        key.insert(make_pair(digits[i], i));
        
    while (cin >> number >> base1 >> base2)
    {
        // 转换为十进制
        int value = 0;
        for (int i = 0; i < number.length(); i++)
            value = value * base1 + key[number[i]];
        
        // 转换为目标进制
        string target;
        while (value)
        {
            target.insert(target.begin(), digits[value % base2]);
            value /= base2;
        }
        
        // 处理值为 0 的情况
        if (target.length() == 0) 
            target = "0";
        
        // 检查是否超出 7 位显示
        if (target.length() > 7) 
            target = "ERROR";
        
        // 输出，右对齐宽度 7
        cout << setw(7) << right << target << endl;
    }
    
    return 0;
}
```
