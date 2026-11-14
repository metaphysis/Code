[UVa 347 Run Run Runaround Numbers](https://blog.csdn.net/metaphysis/article/details/161557202)

## 题目描述

一个 $N$ 位循环数（$\texttt{runaround number}$）具有以下特征：

1. 它是一个恰好有 $N$ 位的整数，每位数字在 $1$ 到 $9$ 之间（不含 $0$）
2. 数字形成这样一个序列：每个数字指示序列中下一个数字的位置。具体做法是：从当前数字开始，向右数该数字所表示的位数，到达的下一个数字即为序列中的下一个数字。如果必要，计数从最右边绕回最左边。
3. 数字的最左边是序列的第一个数字，序列必须在使用完所有数字恰好一次后返回到这个起始数字
4. 数字中不会出现重复数字

例如，考虑数字 $81362$：

1. 从最左边的数字 $8$ 开始：$8\ 1\ 3\ 6\ 2$
2. 向右数 $8$ 位，结束于 $6$（绕回）：$8\ 1\ 3\ 6\ 2$
3. 向右数 $6$ 位，结束于 $2$：$8\ 1\ 3\ 6\ 2$
4. 向右数 $2$ 位，结束于 $1$：$8\ 1\ 3\ 6\ 2$
5. 向右数 $1$ 位，结束于 $3$：$8\ 1\ 3\ 6\ 2$
6. 向右数 $3$ 位，结束于 $8$（回到起点）：$8\ 1\ 3\ 6\ 2$

所有 $5$ 位数字各使用一次后回到了起点，因此 $81362$ 是一个循环数。

### 输入格式

输入包含多行，每行有一个整数 $R$（$2$ 到 $7$ 位）。最后一行只包含数字 $0$。

### 输出格式

对于每个输入数字（除了最后的 $0$），输出大于等于 $R$ 的最小循环数。

### 样例输入

```
12
123
1234
81111
82222
83333
911111
7654321
0
```

### 样例输出

```
Case 1: 13
Case 2: 147
Case 3: 1263
Case 4: 81236
Case 5: 83491
Case 6: 83491
Case 7: 913425
Case 8: 8124956
```

---

## 题目分析

### 问题的本质

这是一个**数字生成与搜索**问题。需要找到所有满足循环数性质的数字，然后对每个查询输出第一个大于等于 $R$ 的循环数。

### 循环数的性质

- 数字不包含 $0$
- 所有数字互不相同
- 从第一位开始，按照“向右移动当前数字指示的步数”的规则，经过 $N$ 步后恰好回到起点，且每个位置都被访问一次

### 搜索策略

由于最大位数为 $7$，且每位数字为 $1 \sim 9$，总搜索空间为所有排列，但需要满足上述条件。

一种高效的方法是使用深度优先搜索（$\texttt{DFS}$）生成所有循环数：
- 从第 $0$ 位（最左边）开始
- 每次选择一个未使用过的数字
- 计算下一步的位置，如果该位置未被访问，则继续
- 当所有位置都被访问且回到起点时，得到一个循环数

### 预处理

由于输入包含多个查询，且数字范围有限（最多 $7$ 位），可以预先计算所有循环数，存入集合中，然后对于每个查询使用二分查找（`lower_bound`）找到答案。

---

## 解题思路

### 步骤一：$\texttt{DFS}$ 生成循环数

```cpp
void dfs(int depth, int position, int length)
{
    if (visited[position])  // 如果当前位置已被访问
    {
        // 如果已经访问了所有位置，且回到了起点（position==0）
        if (depth == length && position == 0)
            candidates.insert(stoi(digits));
    }
    else
    {
        // 枚举下一个数字（1-9 中未使用过的）
        for (int digit = 1; digit <= 9; digit++)
            if (used[digit] == false)
            {
                digits[position] = '0' + digit;
                used[digit] = true;
                visited[position] = true;
                // 递归：下一步位置 = (当前位置 + 步数) % 长度
                dfs(depth + 1, (position + digit) % length, length);
                used[digit] = false;
                visited[position] = false;
            }
    }
}
```

### 步骤二：预先生成所有循环数

对于长度 $len$ 从 $2$ 到 $7$，执行 $\texttt{DFS}$ 生成该长度下的所有循环数。

```cpp
for (int length = 2; length <= 7; length++)
{
    digits.assign(length, '0');
    fill(visited.begin(), visited.end(), false);
    fill(used.begin(), used.end(), false);
    dfs(0, 0, length);
}
```

### 步骤三：查询

对于每个输入 $n$，使用 `set::lower_bound` 找到第一个 $\geq n$ 的循环数。

```cpp
while (cin >> n, n)
    cout << "Case " << ++cases << ": " << (*candidates.lower_bound(n)) << endl;
```

---
## 参考代码

```cpp
// Run Run Runaround Numbers
// UVa ID: 347
// Verdict: Accepted
// Submission Date: 2016-07-02
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

string digits;               // 当前数字字符串
set<int> candidates;         // 存储所有循环数
vector<bool> used(10);       // 数字是否已使用
vector<bool> visited(10);    // 位置是否已访问

// 深度优先搜索生成循环数
// depth: 已访问的位置数
// position: 当前位置
// length: 数字长度
void dfs(int depth, int position, int length)
{
    if (visited[position])  // 遇到已访问的位置
    {
        // 如果所有位置都已访问且回到起点，这是一个有效的循环数
        if (depth == length && position == 0)
            candidates.insert(stoi(digits));
    }
    else
    {
        // 枚举下一个数字（1-9 中未使用过的）
        for (int digit = 1; digit <= 9; digit++)
            if (used[digit] == false)
            {
                digits[position] = '0' + digit;
                used[digit] = true;
                visited[position] = true;
                // 下一步位置 = (当前位置 + 步数) % 长度
                dfs(depth + 1, (position + digit) % length, length);
                used[digit] = false;
                visited[position] = false;
            }
    }
}

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    // 预先生成所有 2-7 位的循环数
    for (int length = 2; length <= 7; length++)
    {
        digits.assign(length, '0');
        fill(visited.begin(), visited.end(), false);
        fill(used.begin(), used.end(), false);
        dfs(0, 0, length);
    }

    int n, cases = 0;
    while (cin >> n, n)
        cout << "Case " << ++cases << ": " << (*candidates.lower_bound(n)) << endl;

    return 0;
}
```
