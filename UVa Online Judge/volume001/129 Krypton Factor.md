[UVa 129 Krypton Factor](https://blog.csdn.net/metaphysis/article/details/156751475)

## 题目分析

本题要求生成“困难序列”，定义如下：  
一个序列中如果存在两个相邻且相同的子串，则该序列为“简单序列”，否则为“困难序列”。  
题目要求按字典序生成第 $n$ 个困难序列，序列中的字符取自字母表前 $L$ 个大写字母（$1 \leq L \leq 26$）。  
输入以两个 $0$ 结束。  
输出时，序列每 $4$ 个字符一组，组间用空格隔开；若组数超过 $16$，则从第 $17$ 组开始换行。  
序列长度不超过 $80$。

例如，当 $L = 3$ 时，前 $7$ 个困难序列为：

```
A
AB
ABA
ABAC
ABACA
ABACAB
ABACABA
```

## 解题思路

### 1. 核心问题：如何判断“困难序列”？

题目要求序列中不能包含两个相邻且相同的子串。  
例如：`ABACBCBAD` 中 `CB` 相邻重复出现，因此是简单序列。  
我们需要一个高效的判断函数，对于任意序列，判断其是否合法。

一种直接的判断方法是：  
设当前序列为 $s$，检查所有可能的子串长度 $j$（从 $1$ 到 $\lfloor \frac{|s|}{2} \rfloor$），  
对于每个起始位置 $i$，比较 $s[i:i+j]$ 与 $s[i+j:i+2j]$ 是否相同。  
如果存在相同，则说明有相邻重复子串，序列不合法。

### 2. 生成字典序第 $n$ 个困难序列

由于序列长度有限（最大 $80$），且字母表大小 $L$ 不超过 $26$，  
我们可以使用**回溯法（$\texttt{DFS}$）**按字典序生成序列。

具体步骤：

1. 从空串开始，每次尝试在当前串末尾添加一个字母（从字母表前 $L$ 个字母中选择）。
2. 每次添加后，调用判断函数检查新串是否合法（即是否为困难序列）。
3. 如果合法，则继续向下递归；否则尝试下一个字母。
4. 每次找到一个合法序列时，计数器加一。当计数器等于 $n$ 时，输出当前序列并结束搜索。

**剪枝优化**：  
- 当当前串不合法时，直接回溯，不继续扩展。
- 每次尝试添加字母时，可以跳过那些显然会导致重复的字母（例如上一个字母相同的字母可以直接跳过，因为相邻相同字符会导致非法）。

### 3. 输出格式要求

- 序列每 $4$ 个字符一组，组间用空格隔开。
- 如果组数超过 $16$ 组（即长度超过 $64$ 个字符），则从第 $65$ 个字符开始换行。
- 输出序列后，在下一行输出序列长度。

### 4. 算法复杂度

- 判断函数时间复杂度为 $O(|s|^3)$，但 $|s| \leq 80$，可以接受。
- 回溯搜索最坏情况下会尝试所有组合，但实际由于剪枝，效率较高。
- 题目保证 $n$ 不会超过可生成的困难序列总数，因此搜索不会无限进行。

## 代码实现

```cpp
// Krypton Factor
// UVa ID: 129
// Verdict: Accepted
// Submission Date: 2015-12-01
// UVa Run Time: 0.000s
//
// 版权所有（C）2015，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

bool isValid(string line) {
    if (line.length() == 1)
        return true;
    for (int j = 1; j <= line.length() / 2; j++)
        for (int i = 0; i < line.length() - j; i++)
            if (line.substr(i, j) == line.substr(i + j, j))
                return false;
    return true;
}

void display(string line) {
    bool newLinePrinted = false;
    for (int i = 1; i <= line.length(); i++) {
        cout << line[i - 1];
        if (i % 64 == 0) {
            cout << endl;
            newLinePrinted = true;
        } else if (i % 4 == 0 && i < line.length()) {
            cout << " ";
            newLinePrinted = false;
        }
    }
    if (newLinePrinted == false) cout << endl;
    cout << line.length() << endl;
}

void lexicographical(int n, int L) {
    string alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string line = "A";
    int counter = 1, start = 0;
    while (counter < n) {
        bool found = false;
        for (int i = start; i < L; i++) {
            if (alpha[i] == line[line.length() - 1]) continue;
            else if (isValid(line + alpha[i])) {
                found = true;
                start = 0;
                counter++;
                line += alpha[i];
                break;
            }
        }
        if (found == false) {
            start = line[line.length() - 1] - 'A' + 1;
            line.erase(line.length() - 1, 1);
        }
    }
    display(line);
}

int main() {
    int n, L;
    while (cin >> n >> L, n || L) lexicographical(n, L);
    return 0;
}
```

## 总结

本题是一道经典的“困难序列”生成问题，通过回溯法和剪枝可以有效求解。关键点在于理解“相邻重复子串”的判断，以及如何按字典序生成序列。输出格式需要注意分组和换行的规则，避免格式错误导致无法通过。
