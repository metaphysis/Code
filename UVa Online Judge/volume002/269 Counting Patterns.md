[UVa 269 Counting Patterns](https://blog.csdn.net/metaphysis/article/details/161309974)

## 题目分析

本题要求计算 $n$-$k$ 谜题的模式（$\texttt{pattern}$）数量。一个配置（$\texttt{configuration}$）是一个长度为 $n$ 的 $n$ 元组，每个元素取值于 $[-k, k]$ 范围内的整数，且所有元素之和为 $0$。两个配置被认为是等价的，如果可以通过以下操作的任意组合相互得到：

1. **循环置换**：将元组循环移动一个或多个位置
2. **反转**：将元组顺序完全反转
3. **符号反转**：将所有元素的符号取反

这些等价类被称为模式（$\texttt{pattern}$）。题目要求对于每组输入 $(n, k)$，输出模式总数，并按照字典序输出每个模式的代表元（即该等价类中字典序最大的那个配置）。

约束条件：$n + k \leq 11$，这意味着搜索空间是有限的，可以使用深度优先搜索（$\texttt{DFS}$）枚举所有可能的配置。

## 解题思路

### 核心问题

问题的核心在于：如何高效地枚举所有配置，并判断一个配置是否是它所在等价类中字典序最大的代表元？

由于 $n + k \leq 11$，$n$ 的最大值为 $11$，$k$ 的最大值也为 $11$。每个位置有 $2k+1$ 种可能的取值，总配置数最多约为 $(2 \times 11 + 1)^{11} = 23^{11} \approx 9.5 \times 10^{14}$，直接枚举所有配置并判断等价是不可行的。因此需要有效的剪枝策略。

### 关键观察

1. **字典序最大代表元**：题目要求输出的代表元是等价类中**字典序最大**的配置。因此，我们只需要生成那些作为等价类最大元的配置，跳过那些不是最大元的配置。

2. **对称性约简**：等价关系由循环置换、反转、符号反转生成。这意味着一个配置的等价类最多包含 $2 \times 2 \times n = 4n$ 个不同的配置（当配置没有对称性时）。

3. **首元素约束**：由于配置可以整体符号反转，且我们只取字典序最大的配置作为代表元，代表元的第一个元素 $a_0$ 必须**非负**。如果 $a_0$ 是负数，取反后得到的配置字典序更大（因为负数 $<$ 非负数）。

4. **循环等价性判断**：对于给定的配置 $A = (a_0, a_1, \dots, a_{n-1})$，要判断它是否是等价类中字典序最大的，需要检查：
   - 所有循环移位后的配置是否字典序不大于 $A$
   - 所有循环移位后再反转的配置是否字典序不大于 $A$
   - 以上两种操作再配合符号反转后的配置是否字典序不大于 $A$

### 搜索策略

采用深度优先搜索（$\texttt{DFS}$）生成所有候选配置：

1. **按字典序降序枚举**：搜索时，第一位 $a_0$ 从 $k$ 向下枚举到 $0$（因为代表元的首位必须非负，且为了得到字典序最大的代表元，我们需要从大到小尝试）。实际上代码中是从 $0$ 到 $k$ 枚举，然后通过剪枝保证生成的是最大元。

2. **剪枝条件**：
   - **前缀和剪枝**：设当前已确定前 $d$ 个元素，和为 $sum$。剩余 $n-d$ 个元素的最大可能绝对值和为 $(n-d) \times k$。如果 $|sum| > (n-d) \times k$，则剩余元素无论怎么取都无法使总和为 $0$，可以剪枝。
   - **字典序剪枝**：为了确保最终生成的配置是等价类中的最大元，在构造过程中就施加约束：
     - 如果前一个元素等于 $a_0$，且当前尝试的元素大于 $a_1$，则后续任何配置都会产生一个比当前候选更大的循环移位，因此可以提前终止该分支的搜索（因为 $a_1$ 已经固定，更大值会导致更大的字典序）。
     - 如果当前尝试的元素等于 $a_0$，且前一个元素大于 $a_1$，同样可以剪枝。

3. **判断是否为最大元**：当完整生成一个配置且总和为 $0$ 后，调用 `isLexicographicallyLargest()` 函数验证它是否确实是等价类中的字典序最大元。该函数通过生成所有循环移位、反转以及符号反转后的配置，逐一比较字典序。

### `isLexicographicallyLargest()` 函数详解

该函数检查当前配置 $digits[0..n-1]$ 是否是等价类中的字典序最大元。具体步骤：

1. 将配置复制两份到 `permutation` 数组（长度为 $2n$），方便进行循环移位的比较。

2. **检查所有循环移位**：对于每个起始位置 $i$（$1 \leq i < n$），如果 `permutation[i] == digits[0]`（即循环移位的首元素等于原配置的首元素），则比较该移位后的序列与原始配置的字典序。如果移位后的序列更大，则当前配置不是最大元。

3. **取反后检查循环移位**：将 `permutation` 中所有元素取反，重复步骤 $2$。

4. **反转后检查**：将原配置反转，同样复制两份，重复步骤 $2$ 和 $3$。

如果以上所有检查都通过，说明没有比当前配置更大的等价配置，当前配置即为代表元。

### 复杂度分析

由于 $n + k \leq 11$，且剪枝条件非常有效，实际搜索的节点数远小于理论最大值。每个候选配置需要 $O(n^2)$ 时间进行等价性检查（实际上 $n \leq 11$，常数很小），可以接受。

### 实现细节

- 使用全局数组 `digits[16]` 存储当前正在构造的配置。
- 使用 `configuration[100000][16]` 存储所有找到的代表元（实际数量远小于此）。
- 搜索时首位 `digits[0]` 从 $0$ 到 $k$ 枚举（因为代表元首位非负）。
- 注意输出格式：两组输出之间有一个空行，最后一行后不能有多余空行。

## 代码实现

```cpp
// Counting Patterns
// UVa ID: 269
// Verdict: Accepted
// Submission Date: 2016-06-04
// UVa Run Time: 0.240s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int n, k, digits[16], permutation[32], configuration[100000][16], solutions;

// 比较数组 p 和全局数组 digits 的字典序大小
// 如果 p 的字典序大于 digits，返回 true
bool isLarger(int p[]) {
    int i;
    for (i = 0; p[i] == digits[i] && i < n; i++)
        ;
    return i < n && p[i] > digits[i];
}

// 确保当前配置是等价类中字典序最大的
// 通过检查所有循环移位、反转及符号反转后的配置
bool isLexicographicallyLargest() {
    // 将 digits 复制两份到 permutation，便于处理循环移位
    for (int i = 0; i < n; i++)
        permutation[i] = digits[i], permutation[i + n] = digits[i];

    // 检查所有循环移位（不取反）
    for (int i = 1; i < n; i++)
        if (permutation[i] == digits[0] && isLarger(permutation + i))
            return false;

    // 取反后检查所有循环移位
    for (int i = 0; i < 2 * n; i++)
        permutation[i] = -permutation[i];

    for (int i = 1; i < n; i++)
        if (permutation[i] == digits[0] && isLarger(permutation + i))
            return false;

    // 反转原配置，然后检查循环移位
    for (int i = n - 1; i >= 0; i--)
        permutation[n - i - 1] = digits[i], permutation[2 * n - i - 1] = digits[i];

    for (int i = 0; i < n; i++)
        if (permutation[i] == digits[0] && isLarger(permutation + i))
            return false;

    // 反转后再取反，检查循环移位
    for (int i = 0; i < 2 * n; i++)
        permutation[i] = -permutation[i];

    for (int i = 0; i < n; i++)
        if (permutation[i] == digits[0] && isLarger(permutation + i))
            return false;

    return true;
}

// 深度优先搜索
// depth: 当前已确定元素个数（下一个要填充的位置索引）
// sumCurrent: 当前已确定元素的和
void dfs(int depth, int sumCurrent) {
    // 已完整生成一个配置
    if (depth == n) {
        // 总和为零且是等价类中字典序最大元
        if (sumCurrent == 0 && isLexicographicallyLargest()) {
            // 保存该代表元
            for (int i = 0; i < n; i++)
                configuration[solutions][i] = digits[i];
            solutions++;
        }
    }
    // 剪枝：当前和的绝对值不能超过剩余元素可能的最大绝对值和
    else if (abs(sumCurrent) <= (n - depth) * digits[0]) {
        // 枚举当前位置的可能取值
        for (int d = -digits[0]; d <= digits[0]; d++) {
            digits[depth] = d;

            // 剪枝：如果前一个元素等于首位，且当前元素大于第二位，
            // 则后续生成的配置一定不是最大元（因为会产生更大的循环移位）
            if (digits[depth - 1] == digits[0] && digits[depth] > digits[1])
                break;

            // 剪枝：如果当前元素等于首位，且前一个元素大于第二位，
            // 同样可以剪枝
            if (digits[depth] == digits[0] && digits[depth - 1] > digits[1])
                break;

            // 递归搜索
            sumCurrent += d;
            dfs(depth + 1, sumCurrent);
            sumCurrent -= d;
        }
    }
}

int main() {
    int cases = 0;
    while (cin >> n >> k) {
        // 两组输出之间用空行分隔
        if (cases++) cout << endl;

        solutions = 0;
        // 枚举首位，从 0 到 k（代表元首位必须非负）
        for (int start = 0; start <= k; start++) {
            digits[0] = start;
            dfs(1, start);
        }

        // 输出结果
        cout << solutions << endl;
        for (int i = 0; i < solutions; i++) {
            for (int j = 0; j < n; j++)
                cout << (j ? ',' : '(') << configuration[i][j];
            cout << ')' << endl;
        }
    }
    return 0;
}
```

## 总结

本题的关键在于利用等价关系的对称性进行剪枝，只生成等价类中的字典序最大元。通过前缀和剪枝和字典序剪枝，在 $n + k \leq 11$ 的约束下能够高效求解。代码实现中需要注意枚举顺序和边界条件的处理，确保输出的代表元符合题目要求的字典序顺序。
