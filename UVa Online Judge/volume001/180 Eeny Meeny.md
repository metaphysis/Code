[UVa 180 Eeny Meeny](https://blog.csdn.net/metaphysis/article/details/160861917)

## 题目分析

本题描述了一个有趣的部落选举酋长的过程。部落成员站成一个圆圈，从某个起始位置开始，按照固定的节奏念出 `Eeny meeny miny mo` 的韵律，每次念到字母 `o` 时，当前指向的人就被淘汰出局，然后从下一个人继续重复这个过程，直到只剩下一个人，这个人就成为新酋长。

题目给出了一个关键信息：计数序列是固定的，长度为 $15$ 个音节（实际上就是 `Eeny meeny miny mo` 这个短语的字母循环）。具体序列为：`E, e, n, y, M, e, e, n, y, M, i, n, y, M, o`，然后重复。每次碰到 `o` 就淘汰当前指向的人。

问题的核心是：给定一个可能的人数范围 $[lower, upper]$，以及淘汰方向可以是顺时针或逆时针，要求找出离起始位置 `Mxogbgwq` 最近的安全位置（即编号最小的位置），使得无论实际人数是多少（在给定范围内），也无论淘汰方向是顺时针还是逆时针，这个位置都不会成为酋长（即不会被淘汰到最后）。如果不存在这样的安全位置，则输出 `Better estimate needed`。

## 解题思路

这是一个经典的约瑟夫问题变种。在经典约瑟夫问题中，每数到第 $k$ 个人就淘汰一人。本题中，固定步长 $m = 15$（因为每 $15$ 个字母出现一次 ‘o’），但需要注意的是，淘汰发生在计数的过程中，实际的步长是 $15$。

### 约瑟夫问题的递推公式

对于经典的约瑟夫问题，如果有 $n$ 个人，每次淘汰第 $k$ 个人，最后存活者的位置（从 $0$ 开始编号）可以通过递推得到：

$$J(1) = 0$$
$$J(n) = (J(n-1) + k) \bmod n$$

这里 $k = 15$，$J(n)$ 表示从 $0$ 开始编号的存活者位置。

### 方向的处理

题目考虑了顺时针和逆时针两个方向：
- 顺时针淘汰的结果就是经典约瑟夫问题的解 $J(n)$
- 逆时针淘汰等价于顺时针淘汰的对称位置，即 $n - J(n)$（在 $0$ 基编号下）

由于编号从起始位置 Mxogbgwq 开始算作第 $1$ 个位置，我们需要进行编号转换：
- 顺时针淘汰时，酋长位置为 $J(n) + 1$（转为 $1$ 基编号）
- 逆时针淘汰时，酋长位置为 $(n - J(n)) \bmod n$，当该值为 $0$ 时对应第 $n$ 个位置

### 算法步骤

1. **预处理**：由于人数最多为 $10^6$，我们可以预先计算出所有 $n$ 对应的顺时针和逆时针酋长位置。
2. **标记不安全位置**：对于给定范围 $[\text{lower}, \text{upper}]$ 内的每个 $n$，将顺时针和逆时针酋长位置标记为不安全。
3. **查找安全位置**：从 $1$ 开始向上查找第一个未被标记的位置，即为答案。由于要求“离 Mxogbgwq 最近”，而 Mxogbgwq 是起始位置（即位置 $1$），所以编号最小的安全位置就是最近的。

### 复杂度分析

预处理时间复杂度为 $O(N)$，其中 $N = 10^6$。对于每组查询，需要遍历范围 $[lower, upper]$ 标记不安全位置，最坏情况 $O(N)$，然后扫描查找安全位置。总复杂度可以接受。

## 代码实现

```cpp
// Eeny Meeny
// UVa ID: 180
// Verdict: Accepted
// Submission Date: 2016-02-22
// UVa Run Time: 0.035s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// lower 和 upper 分别表示人数的下界和上界
// m 是固定步长，即 "Eeny meeny miny mo" 的长度为 15
int lowerBound, upperBound, step = 15;
// chiefCW[i] 表示 i 个人时顺时针淘汰的酋长位置（0 基编号）
// chiefCCW[i] 表示 i 个人时逆时针淘汰的酋长位置（0 基编号）
// safe[i] 标记第 i 个位置是否安全（初始为 1 表示安全，0 表示不安全）
int chiefCW[1000010], chiefCCW[1000010], safe[1000010];

// 预处理函数：计算所有人数对应的顺时针和逆时针酋长位置
void findChief() {
    // 初始化数组
    fill(chiefCW, chiefCW + 1000010, 0);
    fill(chiefCCW, chiefCCW + 1000010, 0);

    // select 表示当前存活者的位置（0 基编号）
    int select = 0;
    // 只有一个人时，存活者位置为 0
    chiefCW[1] = 0;
    // 使用递推公式计算 n = 2 到 1000000 的情况
    for (int j = 2; j <= 1000000; j++)
    {
        // 约瑟夫递推公式：J(n) = (J(n-1) + k) % n
        select = (select + step) % j;
        // 顺时针淘汰的酋长位置
        chiefCW[j] = select;
        // 逆时针淘汰的酋长位置（对称位置）
        chiefCCW[j] = (j - select) % j;
    }
}

// 查找并输出第一个安全位置
bool findFirstSafePosition() {
    // 初始化安全标记数组，假设所有位置都安全
    fill(safe, safe + upperBound, 1);

    // 对于范围内的人数，标记对应的酋长位置为不安全
    for (int i = lowerBound; i <= upperBound; i++) {
        // 顺时针方向的酋长位置（转为 1 基编号）
        safe[chiefCW[i] + 1] = 0;
        // 逆时针方向的酋长位置（转为 1 基编号）
        // 注意当 chiefCCW[i] = 0 时对应第 i 个位置
        if (chiefCCW[i] == 0) safe[i] = 0;
        else safe[chiefCCW[i]] = 0;
    }

    // 从位置 1 开始查找第一个安全位置
    // 题目要求输出离 Mxogbgwq 最近的位置，即编号最小的安全位置
    for (int i = 1; i < lowerBound / 2; i++)
        if (safe[i] == 1) {
            cout << i << "\n";
            return true;
        }

    // 没有找到安全位置
    cout << "Better estimate needed\n";
    return false;
}

int main() {
    // 加速输入输出
    cin.tie(0);
    cout.sync_with_stdio(false);

    // 预处理所有人数的酋长位置
    findChief();

    // 读入多组数据，直到 "0 0" 结束
    while (cin >> lowerBound >> upperBound, lowerBound || upperBound)
    {
        // 确保 lowerBound <= upperBound
        if (lowerBound > upperBound)
            swap(lowerBound, upperBound);

        findFirstSafePosition();
    }

    return 0;
}
```

## 关键点说明

1. **编号转换**：程序中 $0$ 基编号和 $1$ 基编号的转换需要注意。递推公式 $J(n)$ 给出的是 $0$ 基编号，而题目中的位置从 $1$ 开始计数。

2. **逆时针处理**：逆时针淘汰的酋长位置可以通过对称性得到，即 $n - J(n)$（当结果为 $n$ 时对应位置 $n$，即编号转换后的第 $n$ 个位置）。

3. **边界条件**：当 `chiefCCW[i] == 0` 时，逆时针方向的酋长是第 $i$ 个人，需要标记 `safe[i] = 0`。

4. **查找范围**：代码中查找安全位置只循环到 `lowerBound / 2`，这是一个优化，因为安全位置如果存在，通常会在较小的位置出现。如果在这个范围内没有找到，则输出需要更好估计。
