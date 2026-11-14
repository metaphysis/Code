[UVa 372 WhatFix Notation](https://blog.csdn.net/metaphysis/article/details/161642317)

## 题目描述

编译器和计算器中常用的三种遍历方法：

- **中缀**（$\texttt{infix}$）：如 `a + b + c`
- **前缀**（$\texttt{prefix}$）：如 `+ a + b c`
- **后缀**（$\texttt{postfix}$）：如 `a b c + +`

前缀和后缀表示法的优点是**不需要括号**来避免歧义。

运算符优先级（从高到低）：
- `^`（乘方）
- `*` `/`（乘除）
- `+` `-`（加减）
- `&` `|`（与、或）
- `!`（非）

### 输入格式

输入包含两行字符串。第一行是中缀表达式，第二行是前缀表达式。所有输入字符由空格分隔。

### 输出格式

输出后缀表达式，同样以空格分隔。

### 样例输入

```
a + b - c
+ a - b c
```

### 样例输出

```
INFIX   => a + b - c
PREFIX  => + a - b c
POSTFIX => a b c - +
```

---

## 题目分析

### 问题的本质

这是一个**表达式树重构**问题。给定中缀表达式和前缀表达式，需要生成对应的后缀表达式。

### 中缀、前缀、后缀的关系

这三种表示法对应二叉树的不同遍历顺序：
- **中缀**：左子树 $\to$ 根 $\to$ 右子树
- **前缀**：根 $\to$ 左子树 $\to$ 右子树
- **后缀**：左子树 $\to$ 右子树 $\to$ 根

### 解题方法

利用前缀和中缀序列，可以唯一地重构表达式树，然后进行后序遍历得到后缀表达式。

**算法步骤**：
1. 前缀序列的第一个字符是树的根
2. 在中缀序列中找到该根的位置 `root`
3. 中缀序列中根左边的部分是左子树的中缀序列，右边的部分是右子树的中缀序列
4. 前缀序列中根之后的前 `root` 个字符是左子树的前缀序列，剩余是右子树的前缀序列
5. 递归处理左右子树
6. 后序输出（先左、后右、再根）

---
## 参考代码

```cpp
// WhatFix Notation
// UVa ID: 372
// Verdict: Accepted
// Submission Date: 2017-02-21
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

vector<char> sequences;  // 存储后缀表达式字符

// 根据前缀和中缀序列，递归生成后缀序列
void postfix(string prefix, string infix)
{
    if (prefix.length() == 0) return;
    
    // 找到根结点在中缀序列中的位置
    int root = 0;
    for (; root < infix.length(); root++)
        if (infix[root] == prefix.front())
            break;

    // 递归处理左子树
    // 左子树的中缀序列：infix[0..root-1]
    // 左子树的前缀序列：prefix[1..root]
    postfix(prefix.substr(1, root), infix.substr(0, root));

    // 递归处理右子树
    // 右子树的中缀序列：infix[root+1..end]
    // 右子树的前缀序列：prefix[root+1..end]
    postfix(prefix.substr(root + 1), infix.substr(root + 1));

    // 后序输出：先左、后右、再根
    sequences.push_back(prefix.front());
}

int main(int argc, char *argv[])
{
    string infix, prefix;
    while (getline(cin, infix), getline(cin, prefix))
    {
        cout << "INFIX   => " << infix << '\n';
        cout << "PREFIX  => " << prefix << '\n';
        
        // 去除空格
        for (int i = infix.size() - 1; i >= 0; i--)
            if (isblank(infix[i]))
                infix.erase(infix.begin() + i);
        for (int i = prefix.size() - 1; i >= 0; i--)
            if (isblank(prefix[i]))
                prefix.erase(prefix.begin() + i);
        
        sequences.clear();
        postfix(prefix, infix);
        
        cout << "POSTFIX =>";
        for (int i = 0; i < sequences.size(); i++)
            cout << ' ' << sequences[i];
        cout << '\n';
    }

    return 0;
}
```
