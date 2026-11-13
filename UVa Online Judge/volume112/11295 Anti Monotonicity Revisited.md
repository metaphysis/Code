
> **摘要**：本题给定一个 $1$ 到 $n$ 的排列，要求求出最长反单调子序列（满足 $A_0 > A_1 < A_2 > A_3 < \cdots$ 交替起伏）的长度、达到最长长度的方案数（对 $10000007$ 取模），以及所有排列上最长长度的平均值（四舍五入为整数）。核心思路是把子序列末尾元素分为峰值 `high` 与谷值 `low` 两类状态，用两个树状数组分别维护前缀最优长度与方案数，将 $O(n^2)$ 的转移优化到 $O(n \log n)$；平均长度则通过相邻比较符号的概率推导出闭式公式 $\left\lfloor \dfrac{4n+4}{6} \right\rfloor$。

# 题目描述

给定一个由 $1$ 到 $n$ 组成的排列，求其最长反单调子序列的长度。

反单调子序列满足：

$$
A_0 > A_1 < A_2 > A_3 < \cdots
$$

需要输出以下三个结果：

- 最长反单调子序列的长度；
- 达到最长长度的子序列数量，对 $10000007$ 取模；
- 所有 $1$ 到 $n$ 的排列中，最长反单调子序列长度的平均值，结果四舍五入为整数。

# 输入格式

每组测试数据包含以下内容：

- 第一行包含一个整数 $n$；
- 第二行包含 $n$ 个整数，表示一个 $1$ 到 $n$ 的排列。

输入包含多组测试数据，读至文件结束。

其中 $0 \le n \le 100000$。

# 输出格式

对于每组测试数据，输出一行，包含三个整数：

```text
最长长度  最长子序列数量  平均长度
```

第二个结果需要对 $10000007$ 取模。

# 样例输入

```text
10
1 9 2 3 4 10 5 7 8 6
5
2 4 1 3 5
```

# 样例输出

```text
6 9 7
3 5 4
```

# 题目分析

设当前选取的子序列最后一个元素为峰值或谷值。

如果当前子序列的最后一个元素是峰值，那么下一个元素必须比它小；如果当前子序列的最后一个元素是谷值，那么下一个元素必须比它大。因此，可以将状态分为两类：

- `high`：当前子序列最后一个元素处于峰值位置；
- `low`：当前子序列最后一个元素处于谷值位置。

对于排列中的元素 $a_i$：

- 如果前面存在一个 `low` 状态，且其最后元素小于 $a_i$，则可以将 $a_i$ 接到该子序列后面，形成 `high` 状态；
- 如果前面存在一个 `high` 状态，且其最后元素大于 $a_i$，则可以将 $a_i$ 接到该子序列后面，形成 `low` 状态。

直接枚举之前的所有元素会产生 $O(n^2)$ 的时间复杂度，无法处理 $n = 100000$ 的数据规模。

转移时只需要查询两类信息：

- 值小于 $a_i$ 的所有 `low` 状态中的最大长度及方案数；
- 值大于 $a_i$ 的所有 `high` 状态中的最大长度及方案数。

由于输入是排列，元素值恰好覆盖 $1$ 到 $n$，可以直接使用元素值作为数据结构下标。对于“值大于 $a_i$”的查询，将下标反向映射为 $n - a_i + 1$，便可以同样转换为前缀查询。

每个数据结构节点维护两个信息：

- 当前范围内的最大子序列长度；
- 达到该最大长度的方案数。

合并两个节点时：

- 长度较大的节点保留；
- 长度相同的节点将方案数相加；
- 方案数始终对 $10000007$ 取模。

此外，题目要求计算所有排列上的平均最长长度。该结果只与 $n$ 有关，与给定排列的具体顺序无关。

# 解题思路

## 最长长度与方案数状态

扫描排列中的每个元素 $a_i$，定义：

- `high` 表示以 $a_i$ 结尾，且 $a_i$ 位于峰值位置的最优状态；
- `low` 表示以 $a_i$ 结尾，且 $a_i$ 位于谷值位置的最优状态。

单独选择 $a_i$ 可以形成长度为 $1$ 的 `high` 状态，方案数为 $1$。

查询值小于 $a_i$ 的 `low` 状态，设查询结果为长度 $L$、方案数 $C$，则可以得到：

$$
high_i = (L + 1, C)
$$

查询值大于 $a_i$ 的 `high` 状态，设查询结果为长度 $L$、方案数 $C$，则可以得到：

$$
low_i = (L + 1, C)
$$

其中，查询不到合法前驱时，对应状态不存在。

## 使用树状数组优化查询

维护两个树状数组：

- `lowTree`：按照元素值维护 `low` 状态；
- `highTree`：按照反向元素值维护 `high` 状态。

对于 `lowTree`，查询下标 $a_i - 1$，即可得到所有值小于 $a_i$ 的 `low` 状态。

对于 `highTree`，将元素值 $x$ 映射为：

$$
n - x + 1
$$

值大于 $a_i$ 的元素经过映射后，其下标小于等于 $n - a_i$，因此查询前缀 $n - a_i$ 即可得到所有值大于 $a_i$ 的 `high` 状态。

每个树状数组节点保存一个二元组：

$$
(\text{最大长度}, \text{方案数})
$$

合并规则为：

$$
merge(X,Y)=
\begin{cases}
X, & X.len > Y.len \\
Y, & X.len < Y.len \\
(X.len,(X.cnt+Y.cnt)\bmod 10000007), & X.len = Y.len
\end{cases}
$$

当最大长度为 $0$ 时，方案数设为 $0$，表示该状态不存在。

扫描每个元素后，将其 `high` 状态和 `low` 状态分别更新到对应树状数组中，同时用全局答案维护整个排列中的最大长度和方案数。

## 平均长度

将排列中相邻元素的大小关系转换成符号序列：

```text
< 或 >
```

最长反单调子序列可以由首元素以及相邻比较符号发生变化的位置组成。

当 $n \ge 2$ 时：

- 首个比较符号为 `>` 的概率为 $\frac{1}{2}$；
- 对于中间位置，前后两个比较符号不同的概率为 $\frac{2}{3}$。

因此平均长度为：

$$
E = 1 + \frac{1}{2} + (n - 2) \times \frac{2}{3}
$$

化简得到：

$$
E = \frac{4n + 1}{6}
$$

四舍五入可以通过加上 $\frac{1}{2}$ 后向下取整实现：

$$
\left\lfloor \frac{4n + 1}{6} + \frac{1}{2} \right\rfloor=
\left\lfloor \frac{4n + 4}{6} \right\rfloor
$$

所以代码中使用：

```cpp
(4 * n + 4) / 6
```

当 $n = 0$ 时，空子序列长度为 $0$，方案数为 $1$，平均长度为 $0$。

## 复杂度分析

每个元素需要在两个树状数组中进行查询和更新，每次操作的时间复杂度为 $O(\log n)$。

因此：

- 时间复杂度为 $O(n \log n)$；
- 空间复杂度为 $O(n)$。

# 代码实现

```cpp
// Anti Monotonicity Revisited
// UVa ID: 11295
// Verdict: Accepted
// Submission Date: 2026-08-28
// UVa Run Time: 0.140s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int mod = 10000007;

struct Node {
    int len, cnt;
};

Node mergeNode(Node a, Node b) {
    if (a.len > b.len)
        return a;
    if (a.len < b.len)
        return b;
    if (a.len == 0)
        return {0, 0};
    return {a.len, (a.cnt + b.cnt) % mod};
}

struct FenwickTree {
    int size;
    vector<Node> tree;

    FenwickTree(int n) : size(n), tree(n + 1, {0, 0}) {
    }

    void update(int pos, Node value) {
        while (pos <= size) {
            tree[pos] = mergeNode(tree[pos], value);
            pos += pos & -pos;
        }
    }

    Node query(int pos) {
        Node result = {0, 0};
        while (pos > 0) {
            result = mergeNode(result, tree[pos]);
            pos -= pos & -pos;
        }
        return result;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while (cin >> n) {
        vector<int> arr(n + 1);
        for (int i = 1; i <= n; i++)
            cin >> arr[i];
        if (n == 0) {
            cout << "0 1 0\n";
            continue;
        }
        FenwickTree lowTree(n), highTree(n);
        int ansLen = 0, ansCnt = 0;
        for (int i = 1; i <= n; i++) {
            int value = arr[i], revValue = n - value + 1;
            Node high = {1, 1}, low = {0, 0};
            Node lowPrev = lowTree.query(value - 1);
            if (lowPrev.len > 0)
                high = mergeNode(high, {lowPrev.len + 1, lowPrev.cnt});
            Node highPrev = highTree.query(n - value);
            if (highPrev.len > 0)
                low = {highPrev.len + 1, highPrev.cnt};
            highTree.update(revValue, high);
            if (low.len > 0)
                lowTree.update(value, low);
            Node current = mergeNode(high, low);
            if (current.len > ansLen) {
                ansLen = current.len;
                ansCnt = current.cnt;
            } else if (current.len == ansLen) {
                ansCnt = (ansCnt + current.cnt) % mod;
            }
        }
        int meanLen = (4 * n + 4) / 6;
        cout << ansLen << ' ' << ansCnt % mod << ' ' << meanLen << '\n';
    }
    return 0;
}
```

# 总结

本题的关键在于将反单调子序列按照最后一个元素的角色分成 `high` 和 `low` 两种状态，并分别维护最长长度与方案数。

主要技巧包括：

- 使用状态转移描述峰值和谷值之间的交替关系；
- 使用两个树状数组完成前缀最优值查询；
- 通过反向下标将后缀查询转换为前缀查询；
- 在树状数组节点中同时维护最大长度和对应方案数；
- 利用相邻比较符号的概率计算所有排列中的平均最长长度。

最终算法的时间复杂度为 $O(n \log n)$，空间复杂度为 $O(n)$。
