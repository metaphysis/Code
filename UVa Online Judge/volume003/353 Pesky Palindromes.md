[UVa 353 Pesky Palindromes](https://blog.csdn.net/metaphysis/article/details/161588600)

## 题目描述

**回文**（$\texttt{palindrome}$）是指一个或多个字符组成的序列，从左向右读和从右向左读相同。例如，`Z`、`TOT` 和 `MADAM` 是回文，但 `ADAM` 不是。

你的任务是：编写一个程序，读取一系列字符串，对于每个字符串，确定其中**不同**的回文子串的数量。

### 输入格式

输入文件包含多个字符串，每行一个，每个字符串最多 $80$ 个字符，从第 $1$ 列开始。

### 输出格式

对于每个非空输入行，输出一行，格式如样例所示。

### 样例输入

```
boy adam madam tot
```

### 样例输出

```
The string 'boy' contains 3 palindromes.
The string 'adam' contains 4 palindromes.
The string 'madam' contains 5 palindromes.
The string 'tot' contains 3 palindromes.
```

### 样例解释

- `boy` 中的 $3$ 个不同回文子串：`b`、`o`、`y`
- `adam` 中的 $4$ 个不同回文子串：`a`、`d`、`m`、`ada`
- `madam` 中的 $5$ 个不同回文子串：`m`、`a`、`d`、`ada`、`madam`
- `tot` 中的 $3$ 个不同回文子串：`t`、`o`、`tot`

---

## 题目分析

### 问题的本质

这是一个**回文子串枚举与去重**问题。给定一个字符串，需要找出所有不同的回文子串。

### 回文的特点

回文有两种类型：
- **奇长度回文**：中心是一个字符，左右对称扩展
- **偶长度回文**：中心是两个相同字符，左右对称扩展

### 枚举策略

可以枚举每个可能的回文中心，向左右扩展，收集所有回文子串。时间复杂度 $O(n^2)$，$n \leq 80$，完全可行。

### 去重

使用 `set<string>` 自动去重，最后输出集合大小。
## 参考代码

```cpp
// Pesky Palindromes
// UVa ID: 353
// Verdict: Accepted
// Submission Date: 2016-06-27
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    string line;
    while (cin >> line) {
        set<string> palindromes;  // 存储不同的回文子串
        // 枚举奇长度回文（中心为单个字符）
        for (int i = 0; i < line.length(); i++) {
            int left = i, right = i;
            // 向左右扩展直到不能构成回文
            while (left >= 0 && right < line.length() && line[left] == line[right]) {
                palindromes.insert(line.substr(left, right - left + 1));
                left--;
                right++;
            }
        }
        // 枚举偶长度回文（中心为两个字符之间的位置）
        for (int i = 1; i < line.length(); i++) {
            int left = i - 1, right = i;
            while (left >= 0 && right < line.length() && line[left] == line[right]) {
                palindromes.insert(line.substr(left, right - left + 1));
                left--;
                right++;
            }
        }
        cout << "The string '" << line << "' contains " << palindromes.size() << " palindromes." << endl;
    }
    return 0;
}
```
