
> **摘要**：本文讨论经典的「盒子嵌套」问题：给定 $k$ 个 $n$ 维盒子，求最长的嵌套序列。核心思路是先将每个盒子的各维尺寸升序排序，把「存在某种排列使各维严格小于」的判定简化为排序后向量的逐维比较；随后把盒子视为结点、嵌套关系视为有向边，构建有向无环图（$\texttt{DAG}$），问题即转化为 $\texttt{DAG}$ 上的最长路径。借助动态规划在 $O(k^2 n)$ 时间内求出最长长度，并用前驱指针重建路径，按「从最内层到最外层」的顺序输出盒子原始编号。

## 题目描述

我们有一个 $n$ 维“盒子”，其尺寸由一个 $n$ 元组表示。两个盒子 $D$ 和 $E$ 之间存在“嵌套”关系，如果存在 $D$ 尺寸的一个排列，使得排列后的每个维度都严格小于 $E$ 的对应维度。给定 $k$ 个 $n$ 维盒子，要求找出最长的嵌套序列 $b_1, b_2, \dots, b_m$，使得 $b_i$ 能嵌套在 $b_{i+1}$ 中。

**输入**
- 包含多个测试用例。
- 每个用例第一行：盒子数量 $k$ 和维度 $n$。
- 接下来 $k$ 行：每个盒子的 $n$ 个尺寸。

**输出**
- 第一行：最长嵌套序列的长度。
- 第二行：构成该序列的盒子编号（按输入顺序编号，从 $1$ 开始），**从最内层（最小）盒子开始输出**。

**约束**
- $1 \leq n \leq 10$
- $1 \leq k \leq 30$

## 题目分析与解题思路

### 1. 问题转化

判断一个盒子 $D$ 能否嵌套在另一个盒子 $E$ 中，关键在于是否存在一个排列，使得 $D$ 的每个尺寸都小于 $E$ 的对应尺寸。

**关键观察**：  
如果我们将每个盒子的尺寸先按升序排序，那么 $D$ 能嵌套在 $E$ 中的条件就简化为了：排序后的 $D$ 的每个维度都严格小于排序后的 $E$ 的对应维度。  
这是因为：  
- 如果存在某种排列使得 $D$ 能嵌套在 $E$ 中，那么将 $D$ 和 $E$ 都按升序排序后，由于 $E$ 的排序只是其自身维度的重排，不会影响比较；而 $D$ 排序后，其最小对最小、次小对次小……的比较必然满足条件。
- 反之，如果排序后的 $D$ 每个维度都小于排序后的 $E$ 的对应维度，那么显然存在一种排列（即排序后的顺序）满足嵌套条件。

**因此，我们可以先对每个盒子的尺寸进行升序排序，然后直接比较排序后的向量即可判断嵌套关系。**

### 2. 建立有向无环图（$\texttt{DAG}$）

将每个盒子视为一个结点。如果盒子 $A$（排序后）能嵌套在盒子 $B$（排序后）中，则添加一条从 $A$ 到 $B$ 的有向边。  
这样我们就得到了一个有向无环图（$\texttt{DAG}$），因为嵌套关系是传递的且不会出现循环（否则会出现盒子能嵌套在自己内部的情况，与尺寸严格小于矛盾）。

### 3. 求最长路径

问题转化为：在 $\texttt{DAG}$ 中求最长路径（即最长嵌套序列）。  
由于 $k \leq 30$，我们可以使用动态规划（$\texttt{DP}$）求解：

设：
- $dp[i]$：以盒子 $i$ 为起点（即最内层盒子）的最长路径长度。
- $next[i]$：在最长路径中，盒子 $i$ 的下一个盒子编号（用于重建路径）。

状态转移方程：
$$
dp[i] = 1 + \max_{j: \text{box}_i \text{ nests in box}_j} dp[j]
$$
其中，如果不存在可嵌套的 $j$，则 $dp[i] = 1$（只包含自己）。

我们需要对所有盒子按某种顺序进行 $\texttt{DP}$，确保在计算 $dp[i]$ 时，所有可能的后继 $j$ 的 $dp[j]$ 已经计算好。  
一个简单的方法是将所有盒子按尺寸和（或按排序后的字典序）排序，然后从“最大”的盒子开始计算（因为大盒子不会被小盒子嵌套，所以它的 $dp$ 值只依赖自己）。  
另一种更通用的方法是记忆化搜索（递归+缓存），这样无需显式拓扑排序。

### 4. 路径重建与输出顺序

题目要求输出时**从最内层盒子开始**，即路径的起点。  
因此，我们最终需要找到 $dp$ 值最大的盒子作为起点，然后沿着 $next$ 指针输出，直到无后继为止。

注意：盒子编号需按输入顺序给出，因此我们在排序前需要记录原始编号。

### 5. 复杂度分析

- 排序每个盒子的维度：$O(k \cdot n \log n)$
- 建立嵌套关系：$O(k^2 \cdot n)$（共 $k^2$ 对盒子，每对比较 $n$ 维）
- $\texttt{DP}$过程：$O(k^2)$
- 总复杂度在给定约束下完全可行。

## 代码实现

```cpp
// Stacking Boxes
// UVa ID: 103
// Verdict: Accepted
// Submission Date: 2011-10-17
// UVa Run Time: 0.012s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

#define MAXD 10
#define MAXN 30
#define END (-1)

struct box {
public:
    int dimensionality[MAXD];
    int dimensions;
    int index;

    bool operator<(const box &other) const {
        for (int i = 0; i < dimensions; i++)
            if (dimensionality[i] != other.dimensionality[i])
                return dimensionality[i] < other.dimensionality[i];
        return false;
    }

    bool nests(const box &other) const {
        for (int i = 0; i < dimensions; i++)
            if (dimensionality[i] >= other.dimensionality[i])
                return false;       
        return true;
    }
};

box boxes[MAXN];
int longest[MAXN];
int ancestor[MAXN];
int nBoxes, nDimensions;

void sequences(int current) {
    if (ancestor[current] != END)
        sequences(ancestor[current]);
    cout << (ancestor[current] == END ? "" : " ") << (boxes[current].index + 1);
}

void lis(void) {
    for (int i = 0; i < nBoxes; i++)
        for (int j = 0; j < i; j++)
            if (boxes[j].nests(boxes[i]) && (longest[j] + 1) > longest[i]) {
                longest[i] = longest[j] + 1;
                ancestor[i] = j;
            }

    int maximum = 0, marker;
    for (int i = 0; i < nBoxes; i++)
        if (maximum < longest[i]) {
            maximum = longest[i];
            marker = i;
        }

    cout << maximum << endl;
    sequences(marker);
    cout << endl;
}

int main() {
    while (cin >> nBoxes >> nDimensions) {
        for (int i = 0; i < nBoxes; i++) {
            longest[i] = 1;
            ancestor[i] = END;

            boxes[i].dimensions = nDimensions;
            boxes[i].index = i;

            for (int j = 0; j < nDimensions; j++)
                cin >> boxes[i].dimensionality[j];
            sort(boxes[i].dimensionality, boxes[i].dimensionality + nDimensions);
        }

        sort(boxes, boxes + nBoxes);

        lis();
    }

    return 0;
}
```

## 算法步骤总结

1. **读入数据**：对每个盒子的尺寸进行升序排序，并记录原始编号。
2. **整体排序**：将所有盒子按排序后的尺寸字典序排序（方便后续 $\texttt{DP}$）。
3. **动态规划求最长嵌套序列**：
   - `longest[i]` 表示以盒子 $i$ 结尾的最长序列长度。
   - `ancestor[i]` 记录在最长序列中盒子 $i$ 的前驱。
   - 遍历所有盒子对 $(j, i)$（$j < i$），如果 `boxes[j]` 能嵌套在 `boxes[i]` 中，则更新 `longest[i]` 和 `ancestor[i]`。

4. **输出结果**：找到 `longest` 最大的位置，递归输出路径。

## 示例

以题目样例输入为例：

```text
5 2
3 7
8 10
5 2
9 11
21 18
```

处理过程：
1. 每个盒子排序后得到（括号内为原始编号）：
   - (1) `3 7`
   - (3) `2 5`
   - (2) `8 10`
   - (4) `9 11`
   - (5) `18 21`
2. 按字典序排序后顺序为：`(3)`, `(1)`, `(2)`, `(4)`, `(5)`。
3. 嵌套关系：
   - `(3)` → `(1)` → `(2)` → `(4)` → `(5)`
   - 最长序列长度为 $5$，路径为 `3 1 2 4 5`。

输出：
```text
5
3 1 2 4 5
```

## 注意事项

- 盒子编号从 $1$ 开始，代码中存储时从 $0$ 开始，输出时需 $+1$。
- 可能存在多个最长序列，输出任意一个即可。
- 输入可能包含多个测试用例，需持续处理直到文件结束。

---

通过以上分析，我们将嵌套问题转化为 $\texttt{DAG}$ 上的最长路径问题，并利用动态规划高效求解。代码实现简洁，运行效率高，能够处理最大规模的输入数据。
