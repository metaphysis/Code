
> **摘要**：本文讨论一道排列计数与字典序定位相结合的算法题：给定 $N$、$L$ 和 $K$，要求在所有由 $1$ 至 $N$ 组成的排列中，找出最长递增子序列（$\texttt{LIS}$）长度恰好为 $L$ 的排列，并输出其中字典序第 $K$ 小的一个，若总数不足 $K$ 则输出 `-1`。由于 $N!$ 级别的枚举在 $N=13$ 时已不可行，文章将问题转化为「给定前缀，统计合法补全方案数」，再按字典序逐位确定答案。核心技巧是用耐心排序维护当前前缀的 $\texttt{LIS}$ 状态，以 `usedMask` 与 `tailMask` 两个二进制掩码刻画前缀，并通过三进制编码把两个集合状态压缩为记忆化搜索的下标，配合方案数截断到 $10^9$ 防止溢出。最终算法的时间复杂度为 $O(N \times 3^N)$，空间复杂度为 $O(3^N)$，在 $N < 14$ 的限制下可高效通过全部测试数据。

# 题目描述

给定 $N$、$L$ 和 $K$，要求在所有由数字 $1$ 至 $N$ 组成的排列中，找出最长递增子序列长度恰好为 $L$ 的排列，并按照字典序从小到大排列。

输出其中字典序第 $K$ 小的排列。如果满足条件的排列总数少于 $K$，输出 `-1`。

当一个排列 $A$ 的第一个不同位置上的元素小于排列 $B$ 对应位置的元素时，称排列 $A$ 的字典序小于排列 $B$。

例如，当 $N = 4$、$L = 2$ 时，符合条件的前几个排列为：

```text
1 4 3 2
2 1 4 3
2 4 1 3
2 4 3 1
```

排列 `1 4 2 3` 的最长递增子序列长度为 $3$，因此不符合条件。

# 输入格式

第一行包含测试数据组数 $T$。

接下来每行包含三个整数 $N$、$L$ 和 $K$，其中：

- $1 < N < 14$；
- $1 \le L \le N$；
- $1 \le K \le 10^9$。

输入数据中至多有 $15$ 组测试数据满足 $N = 13$。

# 输出格式

对于每组测试数据，首先输出：

```text
Case x:
```

其中 $x$ 表示测试数据编号。

如果存在满足条件的第 $K$ 小排列，在后面输出该排列中的 $N$ 个数字，数字之间使用空格分隔。

如果满足条件的排列总数少于 $K$，输出：

```text
Case x: -1
```

# 样例输入

```text
4
4 2 3
4 2 4
4 2 15
4 2 13
```

# 样例输出

```text
Case 1: 2 4 1 3
Case 2: 2 4 3 1
Case 3: -1
Case 4: 4 3 1 2
```

# 题目分析

直接枚举所有排列需要处理 $N!$ 个排列。当 $N = 13$ 时，排列数量已经非常庞大，无法通过逐个枚举排列并计算最长递增子序列来完成。

本题要求的是字典序第 $K$ 小的合法排列，而不是所有合法排列。因此可以按照字典序逐位确定答案。对于当前位置，依次尝试所有还没有使用过的数字，并统计每个候选数字能够产生的合法排列数量：

- 如果当前候选数字产生的合法排列数量小于 $K$，则第 $K$ 小排列不在这一部分中，直接跳过这一部分，并令 $K$ 减去该部分的排列数量。
- 如果当前候选数字产生的合法排列数量大于等于 $K$，则答案的当前位置确定为该数字，并继续确定下一位。

问题转化为：给定一个已经确定的排列前缀，计算使用剩余数字补全后，最终最长递增子序列长度恰好为 $L$ 的排列数量。

为了高效维护当前前缀的最长递增子序列，需要使用耐心排序方法。维护数组 `tail`，其中 `tail[i]` 表示长度为 $i + 1$ 的递增子序列的最小末尾元素。加入新数字 $x$ 时，将 `tail` 中第一个大于等于 $x$ 的元素替换为 $x$；如果不存在这样的元素，则将 $x$ 添加到 `tail` 的末尾。`tail` 的长度就是当前前缀的最长递增子序列长度。

由于排列中的数字范围是 $1$ 至 $N$，并且 `tail` 中的元素始终严格递增，所以只需要记录哪些数字已经使用，以及哪些已经使用的数字位于 `tail` 中，就能唯一确定当前状态。

# 解题思路

使用两个二进制状态表示当前前缀：

- `usedMask`：第 $i$ 位为 $1$ 表示数字 $i + 1$ 已经使用。
- `tailMask`：第 $i$ 位为 $1$ 表示数字 $i + 1$ 当前位于 `tail` 数组中。

设状态为 $(usedMask, tailMask)$，定义：

$$
f(usedMask, tailMask)
$$

表示从当前状态继续填入所有剩余数字后，最终最长递增子序列长度恰好为 $L$ 的排列数量。

由于不同状态会被反复访问，因此使用记忆化搜索保存每个状态的结果。

加入一个未使用数字 $x$ 时，需要按照耐心排序的规则更新 `tail`：

- 在 `tail` 中寻找第一个大于等于 $x$ 的元素；
- 如果找到，将该元素从 `tail` 中删除，并加入 $x$；
- 如果没有找到，直接将 $x$ 加入 `tail`。

在位运算中，`tailMask` 中不小于 $x$ 的数字可以通过掩码得到。取其中最低位的数字，就对应 `tail` 中第一个大于等于 $x$ 的元素。

记忆化搜索的终止条件如下：

- 如果当前 `tail` 的长度已经大于 $L$，则不可能再得到目标答案，返回 $0$；
- 如果所有数字都已经使用，则当 `tail` 的长度等于 $L$ 时返回 $1$，否则返回 $0$。

为了将两个掩码编码成一个记忆化数组下标，给每个数字设置三种状态：

- $0$：数字没有使用；
- $1$：数字已经使用，但不在 `tail` 中；
- $2$：数字已经使用，并且位于 `tail` 中。

因此，每个数字有三种状态，总状态数量为：

$$
3^N
$$

代码使用 `pow3[i]` 保存 $3^i$。对于第 $i$ 个数字，其状态变化可以直接反映到三进制编码中：

- 从状态 $0$ 变为状态 $2$，编码增加 $2 \times 3^i$；
- 如果替换了原来位于 `tail` 中的数字，则还需要减去被替换数字对应的 $3^j$。

所有排列数量最多只需要区分是否达到 $10^9$，因为输入中的 $K$ 不超过 $10^9$。因此每次累加方案数时都使用 `min` 将结果限制在 $10^9$，避免计数溢出，同时不会影响答案判断。

确定排列时，从左到右枚举当前位置的候选数字。对于每个候选数字，调用记忆化搜索计算其对应的合法排列数量：

- 若数量小于当前 $K$，跳过该候选数字；
- 否则选定该数字，更新状态并进入下一个位置。

当所有位置都确定后，得到的排列就是字典序第 $K$ 小的合法排列。

# 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, lis, lim;
vector<int> memo, pow3;

int countWays(int usedMask, int tailMask, int code) {
    int &res = memo[code];
    if (res != -1) return res;
    if (__builtin_popcount(tailMask) > lis) return res = 0;
    if (usedMask == (1 << n) - 1) return res = (__builtin_popcount(tailMask) == lis);
    res = 0;
    for (int val = 0; val < n; val++) if (!(usedMask & (1 << val))) {
        int valBit = 1 << val, geMask = tailMask & ~((1 << val) - 1), repBit = geMask & -geMask;
        int nextTail = repBit ? ((tailMask ^ repBit) | valBit) : (tailMask | valBit);
        int nextCode = repBit ? code + 2 * pow3[val] - pow3[__builtin_ctz(repBit)] : code + 2 * pow3[val];
        res = min(lim, res + countWays(usedMask | valBit, nextTail, nextCode));
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, kth;
    cin >> t;
    lim = 1000000000;
    while (t--) {
        cin >> n >> lis >> kth;
        pow3.assign(n + 1, 1);
        for (int i = 1; i <= n; i++) pow3[i] = pow3[i - 1] * 3;
        memo.assign(pow3[n], -1);
        int total = countWays(0, 0, 0);
        static int caseNum = 0;
        cout << "Case " << ++caseNum << ":";
        if (total < kth) {
            cout << " -1\n";
            continue;
        }
        int usedMask = 0, tailMask = 0, code = 0;
        for (int pos = 0; pos < n; pos++) {
            for (int val = 0; val < n; val++) if (!(usedMask & (1 << val))) {
                int valBit = 1 << val, geMask = tailMask & ~((1 << val) - 1), repBit = geMask & -geMask;
                int nextTail = repBit ? ((tailMask ^ repBit) | valBit) : (tailMask | valBit);
                int nextCode = repBit ? code + 2 * pow3[val] - pow3[__builtin_ctz(repBit)] : code + 2 * pow3[val];
                int ways = countWays(usedMask | valBit, nextTail, nextCode);
                if (ways < kth) kth -= ways;
                else {
                    cout << ' ' << val + 1;
                    usedMask |= valBit;
                    tailMask = nextTail;
                    code = nextCode;
                    break;
                }
            }
        }
        cout << '\n';
    }
    return 0;
}
```

# 总结

本题的核心是将“求字典序第 $K$ 小排列”转化为“统计每个候选前缀能够产生的合法方案数”。

主要技巧包括：

- 使用耐心排序维护当前前缀的最长递增子序列状态；
- 使用 `usedMask` 表示已经使用的数字；
- 使用 `tailMask` 表示耐心排序中的末尾数组；
- 使用三进制编码将两个集合状态压缩为一个记忆化搜索下标；
- 使用记忆化搜索统计合法补全方案数；
- 按字典序逐位尝试，并利用方案数跳过无关分支；
- 将方案数截断到 $10^9$，防止整数溢出。

状态总数为 $3^N$，每个状态最多枚举 $N$ 个转移，因此时间复杂度为：

$$
O(N \times 3^N)
$$

空间复杂度为：

$$
O(3^N)
$$

在 $N < 14$ 的限制下，该方法能够高效完成所有测试数据。
