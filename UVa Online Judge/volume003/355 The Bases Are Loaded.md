[UVa 355 The Bases Are Loaded](https://blog.csdn.net/metaphysis/article/details/161588738)

## 题目描述

编写一个程序，将指定进制（$2 \sim 16$）下的整数转换为另一种进制（$2 \sim 16$）下的整数。高于 $9$ 的“数字”用单个大写字母表示：例如，$10$ 用 $\texttt{A}$，$15$ 用 $\texttt{F}$，等等。

### 输入格式

每行包含三个值：
- 第一个值：正整数，表示输入数字的进制
- 第二个值：正整数，表示目标进制
- 第三个值：实际要转换的数字（用第一个进制表示）

数字可能包含表示高于 $9$ 的字母，也可能包含无效的“数字”。每个数字不超过 $10$ 个字符。每行中的输入值之间至少有一个空格分隔。

### 输出格式

输出由原始数字后跟字符串 $\texttt{base}$，再跟原始进制，后跟 $\texttt{=}$，再跟转换后的数字，后跟 $\texttt{base}$，再跟目标进制组成。

如果原始数字无效，则输出：
```
original_Value is an illegal base original_Base number
```

### 样例输入

```
2 10 10101
5 3 126
15 11 A4C
```

### 样例输出

```
10101 base 2 = 21 base 10
126 is an illegal base 5 number
A4C base 15 = 1821 base 11
```

---

## 题目分析

### 问题的本质

这是一个**进制转换**问题。需要：
1. 验证输入数字在给定进制下是否合法（每位数字小于进制数）
2. 将合法数字转换为十进制数值
3. 将十进制数值转换为目标进制表示

### 数字表示

- $0 \sim 9$：字符 `0` 到 `9`
- $10 \sim 15$：字符 `A` 到 `F`
- 输入数字最多 $10$ 个字符，进制最大 $16$，因此十进制数值最大约为 $16^{10} \approx 1.1 \times 10^{12}$，在 $64$ 位整数范围内

### 特殊处理

- 数字 `0`：转换后仍为 `0`
- 无效数字：任何位上的数字值 $\geq$ 进制数
## 参考代码

```cpp
// The Bases Are Loaded
// UVa ID: 355
// Verdict: Accepted
// Submission Date: 2016-06-27
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);

    string number;
    int base1, base2;
    string digits = "0123456789ABCDEF";
    map<char, int> key;

    // 建立字符到数值的映射
    for (int i = 0; i < digits.length(); i++)
        key.insert(make_pair(digits[i], i));

    while (cin >> base1 >> base2 >> number) {
        // 验证数字是否合法
        bool isLegal = true;
        for (int i = 0; i < number.length(); i++)
            if (key[number[i]] >= base1) {
                isLegal = false;
                break;
            }
        if (!isLegal) {
            cout << number << " is an illegal base " << base1 << " number" << endl;
            continue;
        }
        // 转换为十进制
        long long value = 0;
        for (int i = 0; i < number.length(); i++)
            value = value * base1 + key[number[i]];
        
        // 转换为目标进制
        string target;
        while (value > 0) {
            target.insert(target.begin(), digits[value % base2]);
            value /= base2;
        }
        // 处理值为 0 的情况
        if (target.length() == 0) target = "0";
        cout << number << " base " << base1 << " = " << target << " base " << base2 << endl;
    }
    return 0;
}
```
