[UVa 325 Identifying Legal Pascal Real Constants](https://blog.csdn.net/metaphysis/article/details/161513565)

## 题目描述

$\texttt{Pascal}$ 语言要求实数常量必须包含小数点或指数（以字母 $\texttt{e}$ 或 $\texttt{E}$ 开头，正式称为比例因子），或两者兼具，再加上通常的数字集合。如果包含小数点，则小数点两侧必须各至少有一位十进制数字。与预期一样，符号（$+$ 或 $-$）可以出现在整个数字之前、指数之前，或两者之前。指数不能包含小数位。空格可以出现在实数常量的前面或后面，但不能嵌入其中。

注意：$\texttt{Pascal}$ 实数常量的语法规则对实数的取值范围没有任何假设，本题也是如此。

任务：判断给定的候选字符串是否为合法的 $\texttt{Pascal}$ 实数常量。

### 输入格式

输入文件的每一行包含一个待分类的候选字符串。输入以只包含一个星号 $\texttt{*}$ 的行结束。

### 输出格式

对于输入的每一行，输出判断结果，格式如示例所示。

### 样例输入

```
1.2
1.
1.0e- 55
e- 12
6.5E
1e- 12
+4.1234567890E- 99999
7.6e+12.5
99
*
```

### 样例输出

```
1.2 is legal.
1. is illegal.
1.0e- 55 is legal.
e- 12 is illegal.
6.5E is illegal.
1e- 12 is legal.
+4.1234567890E- 99999 is legal.
7.6e+12.5 is illegal.
99 is illegal.
```

---

## 题目分析

### 问题的本质

这是一个**正则表达式匹配**问题。Pascal 实数常量的语法规则可以形式化为一个正则表达式，然后对每个输入字符串进行匹配判断。

### $\texttt{Pascal}$ 实数常量的语法规则

根据题目描述，合法的 $\texttt{Pascal}$ 实数常量必须满足以下条件：

1. **可选的前导符号**：整个数字前可以有 `+` 或 `-`
2. **整数部分**：至少有一位数字
3. **可选的小数部分**：
   - 如果包含小数点，小数点前后都必须有数字
   - 小数部分不能单独存在（即必须有整数部分）
4. **可选的指数部分**：
   - 以 `e` 或 `E` 开头
   - 指数部分可以有符号（`+` 或 `-`）
   - 指数部分必须包含至少一位数字
   - 指数不能包含小数位
5. **允许的前后空白**：空格可以出现在开头和结尾，但不能嵌入内部
6. **数字集合**：只能包含数字、可选的符号、小数点、字母 `e`/`E`

### 正则表达式的推导

根据上述规则，可以构造如下的正则表达式：

```
^\s*[+-]?\d+(\.\d+([eE][+-]?\d+)?|[eE][+-]?\d+)\s*$
```

逐部分解释：

| 部分 | 含义 |
|------|------|
| `^` | 字符串开头 |
| `\s*` | 前导空白（可选） |
| `[+-]?` | 前导符号（可选） |
| `\d+` | 至少一位数字（整数部分） |
| `(\.\d+([eE][+-]?\d+)?\|[eE][+-]?\d+)` | 小数部分或指数部分（二选一） |
| `\s*` | 后缀空白（可选） |
| `$` | 字符串结尾 |

其中 `\.\d+([eE][+-]?\d+)?` 表示小数部分后可选指数部分，`[eE][+-]?\d+` 表示只有指数部分（没有小数点）。

### 为什么不能是 `^\s*[+-]?\d*\.?\d+([eE][+-]?\d+)?\s*$`？

因为需要强制满足：
- 如果有小数点，小数点两边都必须有数字
- 如果只有指数部分，必须有整数部分

简单的 `\d*\.?\d+` 不能保证小数点前有数字（如 `.123` 是无效的）。

---
## 参考代码

```cpp
// Identifying Legal Pascal Real Constants
// UVa ID: 325
// Verdict: Accepted
// Submission Date: 2016-06-30
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);
    
    // 正则表达式：
    // ^\s*         可选的前导空白
    // [+-]?        可选的符号
    // \d+          至少一位整数部分
    // (\.\d+([eE][+-]?\d+)?  小数部分（可选指数）
    //  |           或者
    //  [eE][+-]?\d+)          只有指数部分
    // \s*$         可选的后缀空白
    string pattern = R"(^\s*[\+|-]?\d+(\.\d+([eE][\+|-]?\d+)?|[eE][\+|-]?\d+)\s*$)";
    regex e(pattern, regex_constants::icase);
        
    string line;
    while (getline(cin, line))
    {
        if (line == "*")
            break;

        // 移除行首尾的空白用于输出（可选，保持与样例一致）
        int left = 0, right = line.length() - 1;
        while (left < line.length() && isblank(line[left])) left++;
        while (right >= 0 && isblank(line[right])) right--;
        
        // 输出原始候选字符串（去除首尾空白）
        for (int i = left; i <= right; i++)
            cout << line[i];
            
        if (regex_match(line, e))
            cout << " is legal." << endl;
        else
            cout << " is illegal." << endl;
    }
    
    return 0;
}
```
