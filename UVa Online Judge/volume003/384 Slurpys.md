[UVa 384 Slurpys](https://blog.csdn.net/metaphysis/article/details/161673607)

## 题目描述

基于一组约束识别字符串是一个常见的计算问题。

**$\texttt{Slurpy}$** 是一种具有特定属性的字符串。你的程序将读取字符串并判断它们是否为 $\texttt{Slurpy}$。

### 定义

**$\texttt{Slump}$** 是一个满足以下属性的字符串：

1. 第一个字符是 `D` 或 `E`
2. 第一个字符后跟一个或多个 `F`
3. `F` 的序列后跟一个 $\texttt{Slump}$ 或一个 `G`，以此结束整个 $\texttt{Slump}$
4. 除此之外都不是 $\texttt{Slump}$

例如：`DFFEFFFG` 是一个 $\texttt{Slump}$（以 `D` 开头，后跟两个 `F`，再跟 $\texttt{Slump}$ `EFFFG`）

**$\texttt{Slimp}$** 是一个满足以下属性的字符串：

1. 第一个字符是 `A`
2. 如果是两个字符的 $\texttt{Slimp}$，则第二个字符是 `H`
3. 如果不是两个字符，则属于以下两种形式之一：
   - `A` + `B` + $\texttt{Slimp}$ + `C`
   - `A` + $\texttt{Slump}$ + `C`
4. 除此之外都不是 $\texttt{Slimp}$

**$\texttt{Slurpy}$** 是一个由 $\texttt{Slimp}$ 后跟 $\texttt{Slump}$ 组成的字符串。

### 输入格式

第一行包含整数 $N$（$1 \leq N \leq 10$），表示字符串数量。接下来 $N$ 行，每行包含一个由字母组成的字符串（长度 $1 \sim 60$）。

### 输出格式

第一行输出 `SLURPYS OUTPUT`。接下来 $N$ 行，每行输出 `YES` 或 `NO`。最后一行输出 `END OF OUTPUT`。

### 样例输入

```
2
AHDFG
DFGAH
```

### 样例输出

```
SLURPYS OUTPUT
YES
NO
END OF OUTPUT
```

---

## 题目分析

### 问题的本质

这是一个**递归下降解析**问题。需要根据给定的上下文无关文法判断字符串是否属于定义的语言。

### 文法规则

```
Slump  → D F+ (Slump | G)
Slimp  → A H | A B Slimp C | A Slump C
Slurpy → Slimp Slump
```

### 解析方法

使用递归下降解析器，维护一个全局位置指针，尝试匹配规则。

---

## 参考代码

```cpp
// Slurpys
// UVa ID: 384
// Verdict: Accepted
// Submission Date: 2016-06-30
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

bool isC();
bool isSlump();
bool isSlimp();
bool isSlurpy();

string line;
int position;

// 解析字符 'C'
bool isC()
{
    if (position < line.length() && line[position] == 'C')
    {
        position++;
        return true;
    }
    return false;
}

// 解析 Slump: D/E F+ (Slump | G)
bool isSlump()
{
    if (position >= line.length()) return false;
    if (line[position] != 'D' && line[position] != 'E') return false;
    position++;
    
    // 至少一个 F
    bool atLeastOneF = false;
    while (position < line.length() && line[position] == 'F')
    {
        atLeastOneF = true;
        position++;
    }
    if (!atLeastOneF) return false;
    
    // 以 G 结尾
    if (position < line.length() && line[position] == 'G')
    {
        position++;
        return true;
    }
    // 或者后面跟一个 Slump
    return isSlump();
}

// 解析 Slimp: A H | A B Slimp C | A Slump C
bool isSlimp()
{
    if (position >= line.length() || line[position] != 'A') return false;
    position++;
    
    // 情况1：AH
    if (position < line.length() && line[position] == 'H')
    {
        position++;
        return true;
    }
    // 情况2：A B Slimp C
    else if (position < line.length() && line[position] == 'B')
    {
        position++;
        if (!isSlimp()) return false;
        if (position < line.length() && line[position] == 'C')
        {
            position++;
            return true;
        }
        return false;
    }
    // 情况3：A Slump C
    else
    {
        if (!isSlump()) return false;
        if (position < line.length() && line[position] == 'C')
        {
            position++;
            return true;
        }
        return false;
    }
}

// 解析 Slurpy: Slimp + Slump
bool isSlurpy()
{
    int savedPos = position;
    if (isSlimp() && isSlump() && position == line.length())
        return true;
    position = savedPos;
    return false;
}

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);
    
    string firstLine;
    getline(cin, firstLine);
    int n = stoi(firstLine);
    
    cout << "SLURPYS OUTPUT" << endl;
    
    for (int i = 1; i <= n; i++)
    {
        getline(cin, line);
        position = 0;
        cout << (isSlurpy() ? "YES" : "NO") << endl;
    }   
    
    cout << "END OF OUTPUT" << endl;
    
    return 0;
}
```
