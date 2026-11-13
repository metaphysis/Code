
> **摘要**：本题给定 $C$ 种颜色的积木，每种颜色对应一个固定长度，要求用这些积木拼出长度为 $n$ 的长条，求方案数对 $100000007$ 取模的结果。由于 $n$ 最大可达 $10^{15}$，无法直接线性递推，需先按长度统计颜色数量 $cnt[d]$ 建立线性递推式，再借助特征多项式与多项式快速幂，在 $O(L^2 \log n)$ 时间内求出第 $n$ 项。

# 题目描述

$\texttt{John}$ 为 $\texttt{Johnny}$ 购买了 $C$ 种不同颜色的积木，每种颜色的积木数量均足够多。同一种颜色的积木长度相同，不同颜色的积木长度允许相同。

现在需要使用这些积木拼成一个长度为 $n$ 的长条。若两种拼法在某个位置使用的积木颜色不同，则两种拼法不同。求拼成长度为 $n$ 的方案数，结果对 $100000007$ 取模。

# 输入格式

第一行输入测试组数 $T$。

每组测试数据包含三行：

- 第一行输入颜色种类数 $C$。
- 第二行输入 $C$ 个整数，第 $i$ 个整数表示第 $i$ 种颜色积木的长度。
- 第三行输入目标长度 $n$。

数据范围如下：

- $1 \le T \le 25$；
- $1 \le C \le 100$；
- $1 \le len_i \le 750$；
- $1 \le n \le 10^{15}$。

# 输出格式

对于每组测试数据，输出一行：

```text
Case x: ans
```

其中 $x$ 表示测试数据编号，$ans$ 表示方案数对 $100000007$ 取模后的结果。

# 样例输入

```text
4
3
3 3 5
11
3
3 5 3
1111111111111
4
1 1 100 100
1000000
3
1 1 1
5
```

# 样例输出

```text
Case 1: 12
Case 2: 20634244
Case 3: 94126777
Case 4: 243
```

# 题目分析

每种颜色都代表一种独立的积木类型。即使两种积木长度相同，只要颜色不同，它们在拼接时仍然产生不同方案。

设 $cnt[d]$ 表示长度为 $d$ 的积木颜色数量，设最大积木长度为 $L$。定义 $\textit{f}[i]$ 表示拼出总长度为 $i$ 的方案数。

当最后放置一块长度为 $d$ 的积木时，前面部分必须恰好拼出长度 $i - d$。长度为 $d$ 的积木共有 $cnt[d]$ 种颜色，因此最后一块积木为长度 $d$ 时，对答案贡献：

$$
cnt[d] \times \textit{f}[i - d]
$$

将所有可用长度累加，得到递推关系：

$$
\textit{f}[i] = \sum_{d = 1}^{L} cnt[d] \times \textit{f}[i - d]
$$

其中，当 $i - d < 0$ 时，对应项不存在，不参与计算。

空拼接只有一种方式，因此初始状态为：

$$
\textit{f}[0] = 1
$$

当 $n$ 较小时，直接按照递推式计算即可。然而本题中 $n$ 最大达到 $10^{15}$，线性递推计算需要 $O(nL)$ 时间，无法完成。

递推式的阶数为 $L$，且 $L \le 750$。因此使用线性递推的多项式快速幂方法，在 $O(L^2 \log n)$ 时间内求出 $\textit{f}[n]$。

# 解题思路

根据递推式：

$$
\textit{f}[i] = cnt[1] \times \textit{f}[i - 1] + cnt[2] \times \textit{f}[i - 2] + \cdots + cnt[L] \times \textit{f}[i - L]
$$

构造特征多项式：

$$
x^L = cnt[1]x^{L - 1} + cnt[2]x^{L - 2} + \cdots + cnt[L]
$$

任意次数不小于 $L$ 的多项式项均能够通过上式降到次数小于 $L$。

设：

$$
x^n \bmod P(x) = a_0 + a_1x + a_2x^2 + \cdots + a_{L - 1}x^{L - 1}
$$

则递推序列的第 $n$ 项满足：

$$
\textit{f}[n] = a_0 \times \textit{f}[0] + a_1 \times \textit{f}[1] + a_2 \times \textit{f}[2] + \cdots + a_{L - 1} \times \textit{f}[L - 1]
$$

整体过程分为以下步骤。

步骤 $\texttt{1}$. 统计每一种积木长度出现的颜色数量，得到数组 $cnt$。

步骤 $\texttt{2}$. 使用普通递推预处理 $\textit{f}[0]$ 到 $\textit{f}[L - 1]$，这些值作为线性递推的初始项。

步骤 $\texttt{3}$. 使用多项式快速幂计算 $x^n \bmod P(x)$。多项式乘法后，最高次数达到 $2L - 2$。

步骤 $\texttt{4}$. 对每一个次数为 $i$ 且满足 $i \ge L$ 的项，利用特征多项式进行降次：

$$
x^i = x^{i - L} \times x^L
$$

代入特征多项式后：

$$
x^i = \sum_{d = 1}^{L} cnt[d] \times x^{i - d}
$$

因此，次数为 $i$ 的系数会分配到次数为 $i - 1$ 至 $i - L$ 的位置。

步骤 $\texttt{5}$. 将最终多项式的各项系数与初始序列对应相乘并求和，得到 $\textit{f}[n]$。

多项式乘法的时间复杂度为 $O(L^2)$，快速幂进行 $O(\log n)$ 次乘法，因此总时间复杂度为：

$$
O(L^2 \log n)
$$

空间复杂度为：

$$
O(L)
$$

# 代码实现

```cpp
// Game of Blocks
// UVa ID: 11868
// Verdict: Accepted
// Submission Date: 2026-08-28
// UVa Run Time: 1.110s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const long long mod = 100000007;

vector<long long> multiplyPoly(const vector<long long> &first, const vector<long long> &second, const vector<long long> &count) {
    int len = static_cast<int>(count.size()) - 1, i, j, d;
    long long value;
    vector<long long> result(2 * len - 1, 0);
    for (i = 0; i < len; i++)
        for (j = 0; j < len; j++)
            result[i + j] = (result[i + j] + first[i] * second[j]) % mod;
    for (i = 2 * len - 2; i >= len; i--) {
        value = result[i];
        if (value == 0)
            continue;
        for (d = 1; d <= len; d++)
            result[i - d] = (result[i - d] + value * count[d]) % mod;
    }
    result.resize(len);
    return result;
}

long long solveCase(int colorCount, const vector<int> &lengths, long long n) {
    int i, length, maxLen = 0;
    for (i = 0; i < colorCount; i++)
        maxLen = max(maxLen, lengths[i]);
    vector<long long> count(maxLen + 1, 0), initial(maxLen, 0);
    for (i = 0; i < colorCount; i++)
        count[lengths[i]]++;
    initial[0] = 1;
    for (i = 1; i < maxLen; i++) {
        for (length = 1; length <= i; length++)
            initial[i] = (initial[i] + count[length] * initial[i - length]) % mod;
    }
    vector<long long> result(maxLen, 0), base(maxLen, 0);
    result[0] = 1;
    if (maxLen == 1)
        base[0] = count[1];
    else
        base[1] = 1;
    while (n > 0) {
        if (n & 1)
            result = multiplyPoly(result, base, count);
        n >>= 1;
        if (n > 0)
            base = multiplyPoly(base, base, count);
    }
    long long answer = 0;
    for (i = 0; i < maxLen; i++)
        answer = (answer + result[i] * initial[i]) % mod;
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount, caseId, colorCount, i;
    long long n;
    cin >> testCount;
    for (caseId = 1; caseId <= testCount; caseId++) {
        cin >> colorCount;
        vector<int> lengths(colorCount);
        for (i = 0; i < colorCount; i++)
            cin >> lengths[i];
        cin >> n;
        cout << "Case " << caseId << ": " << solveCase(colorCount, lengths, n) << '\n';
    }
    return 0;
}
```

# 总结

本题的核心是将不同颜色但长度相同的积木计入同一长度的可选数量 $cnt[d]$，从而建立线性递推关系。

由于目标长度 $n$ 达到 $10^{15}$，普通递推无法完成计算。通过特征多项式和多项式快速幂，将求第 $n$ 项的问题转化为计算 $x^n$ 的模多项式结果，最终在 $O(L^2 \log n)$ 时间内完成求解。
