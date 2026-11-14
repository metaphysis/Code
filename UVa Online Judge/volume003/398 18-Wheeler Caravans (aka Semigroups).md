[UVa 398 18-Wheeler Caravans (aka Semigroups)](https://blog.csdn.net/metaphysis/article/details/161705494)

## 题目描述

集合 $S$ 上的二元运算是一个函数，将 $S$ 中每个有序元素对映射到 $S$ 中的唯一元素。如果对于所有 $x, y \in S$ 有 $x \# y = y \# x$，则称该运算是**可交换的**（$\texttt{commutative}$）。如果对于所有 $x, y, z \in S$ 有 $(x \# y) \# z = x \# (y \# z)$，则称该运算是**可结合的**（$\texttt{associative}$）。

一个具有可结合二元运算的集合 $<S, \#>$ 称为**半群**（$\texttt{semigroup}$）。如果二元运算既是可结合的又是可交换的，则称为**可交换半群**。

### 输入格式

输入第一行包含整数 $n$（$1 \leq n \leq 26$）。下一行包含 $n$ 个唯一的小写字母（不一定按字母顺序排列）。接下来 $n$ 行是“乘法”表的主体，每行包含 $n$ 个小写字母。第一行对应表的第一行，依此类推。行和列的顺序与定义集合元素的行中的顺序一致。

表之后，输入文件包含一行整数 $n$（$0 \leq n \leq 26$）。如果 $n > 0$，则还有另一个集合和对应的表。如果 $n = 0$，则到达输入文件末尾。

### 输出格式

对于每个集合和表，输出：
1. `S = {a,b,c,d}`（按输入顺序）
2. 一行：空格 + `#|` + 元素（无空格或逗号）
3. 一行：空格 + `-+` + $n$ 个连字符
4. $n$ 行：空格 + 元素 + `|` + 该行表体（无空格）
5. 一个空行
6. 以下结果之一：
   - `COMMUTATIVE SEMIGROUP`
   - `SEMIGROUP BUT NOT COMMUTATIVE (x#y IS NOT EQUAL TO y#x)`
   - `NOT A SEMIGROUP: x#y = z WHICH IS NOT AN ELEMENT OF THE SET`
   - `NOT A SEMIGROUP: (x#y)#z IS NOT EQUAL TO x#(y#z)`
7. 一行 $30$ 个连字符
8. 一个空行

### 样例输入

```
3
abc
abc
bca
cab
3
abc
abc
bca
cad
4
acdb
aaaa
aaca
aada
aaab
5
abcde
aaaaa
bbabb
cccbc
ddddd
eeeee
0
```

### 样例输出

```
S = {a,b,c}
 #|abc
 -+---
 a|abc
 b|bca
 c|cab

COMMUTATIVE SEMIGROUP
------------------------------

S = {a,b,c}
 #|abc
 -+---
 a|abc
 b|bca
 c|cad

NOT A SEMIGROUP: c#c = d WHICH IS NOT AN ELEMENT OF THE SET
------------------------------

S = {a,c,d,b}
 #|acdb
 -+----
 a|aaaa
 c|aaca
 d|aada
 b|aaab

SEMIGROUP BUT NOT COMMUTATIVE (c#d IS NOT EQUAL TO d#c)
------------------------------
```

---

## 题目分析

### 问题的本质

这是一个**代数结构验证**问题。给定一个有限集合和一个二元运算的乘法表，需要判断：
1. 运算结果是否都在集合内（封闭性）
2. 运算是否可结合（结合律）
3. 运算是否可交换（交换律）

### 算法步骤

1. **封闭性检查**：表中所有结果都必须在集合中
2. **结合律检查**：对所有 $a, b, c \in S$，验证 $(a \# b) \# c = a \# (b \# c)$
3. **交换律检查**：对所有 $a, b \in S$，验证 $a \# b = b \# a$

### 复杂度

- $n \leq 26$，结合律检查需 $O(n^3)$，约 $17576$ 次，完全可行

---
## 参考代码

```cpp
// 18-Wheeler Caravans (aka Semigroups)
// UVa ID: 398
// Verdict: Accepted
// Submission Date: 2016-07-08
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;
        
int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    int n, cases = 0;
    while (cin >> n, n)
    {
        vector<char> elements(n);
        vector<string> table(n);
        map<char, int> location;
        
        // 读取元素
        for (int i = 0; i < n; i++)
        {
            cin >> elements[i];
            location[elements[i]] = i;
        }

        // 读取乘法表
        for (int i = 0; i < n; i++)
        {
            cin >> table[i];
        }

        // 输出表头
        if (cases++) cout << endl;
  
        cout << "S = {";
        for (int i = 0; i < n; i++)
        {
            if (i > 0) cout << ",";
            cout << elements[i];
        }
        cout << "}" << endl;

        cout << " #|";
        for (int i = 0; i < n; i++)
            cout << elements[i];
        cout << endl;

        cout << " -+" << string(n, '-') << endl;

        for (int i = 0; i < n; i++)
            cout << " " << elements[i] << "|" << table[i] << endl;
        cout << endl;
        
        // 封闭性检查
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
            {
                char result = table[i][j];
                if (location.find(result) == location.end())
                {
                    cout << "NOT A SEMIGROUP: " << elements[i] << "#" << elements[j];
                    cout << " = " << result << " WHICH IS NOT AN ELEMENT OF THE SET" << endl;
                    goto exit_processing;
                }
            }
        
        // 结合律检查
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                for (int k = 0; k < n; k++)
                {
                    char left = table[location[table[i][j]]][k];
                    char right = table[i][location[table[j][k]]];
                    if (left != right)
                    {
                        cout << "NOT A SEMIGROUP: (";
                        cout << elements[i] << "#" << elements[j] << ")#" << elements[k];
                        cout << " IS NOT EQUAL TO ";
                        cout << elements[i] << "#(" << elements[j] << "#" << elements[k] << ")" << endl;
                        goto exit_processing;
                    }
                }
        
        // 交换律检查
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
            {
                if (table[i][j] != table[j][i])
                {
                    cout << "SEMIGROUP BUT NOT COMMUTATIVE (";
                    cout << elements[i] << "#" << elements[j];
                    cout << " IS NOT EQUAL TO ";
                    cout << elements[j] << "#" << elements[i] << ")" << endl;
                    goto exit_processing;
                }
            }
        
        cout << "COMMUTATIVE SEMIGROUP" << endl;
            
exit_processing:
        cout << string(30, '-') << endl;
    }
    
    return 0;
}
```
