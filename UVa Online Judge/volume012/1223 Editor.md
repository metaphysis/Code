> **摘要**：本文讨论「求字符串中出现至少两次的最长子串长度」这一问题，两次出现允许重叠。核心思路是把问题转化为「任意两个后缀的最长公共前缀（$\texttt{LCP}$）的最大值」：先用倍增 + 基数排序在 $O(n\log n)$ 内构造后缀数组，再用 $\texttt{Kasai}$ 算法在 $O(n)$ 内求出相邻后缀的 $\textit{height}$ 数组，答案即为 $\max(\textit{height})$。文中给出了完整的正确性证明（引理 1～3）、复杂度分析以及可直接提交的代码实现，适用于长度不超过 $5000$ 的多组测试数据。
# 题目描述

给定一个字符串 $S$，需要找出其中出现至少两次的最长子串。两次出现可以相互重叠。

如果不存在长度大于 $0$ 的重复子串，则输出 $0$。

例如：

- `abcabcabc` 中，最长重复子串为 `abcabc`，长度为 $6`；
- `abcdefghikjlmn` 中没有重复字符，因此答案为 $0$；
- `abcdabcabb` 中最长重复子串长度为 $3$。

# 输入格式

第一行输入一个整数 $T$，表示测试数据组数。

接下来每组输入一行字符串 $S$。字符串只包含小写英文字母，长度不超过 $5000$。

# 输出格式

对于每组测试数据，输出一行一个整数，表示出现至少两次的最长子串长度。

# 样例输入

```text
3
abcdefghikjlmn
abcabcabc
abcdabcabb
```

# 样例输出

```text
0
6
3
```

# 题目分析

直接枚举所有子串并判断出现次数，时间复杂度较高。可以利用后缀数组解决这个问题。

对于字符串 $S$ 的两个后缀：

$$
S[i \dots n-1],\quad S[j \dots n-1]
$$

它们的最长公共前缀长度，正好表示从位置 $i$ 和位置 $j$ 开始的两个相同子串的最大长度。

因此，题目可以转化为：

> 求任意两个后缀的最长公共前缀长度的最大值。

将所有后缀按照字典序排序后，具有最大公共前缀的两个后缀一定可以在后缀数组中找到一对相邻后缀。于是只需要求相邻后缀之间最长公共前缀长度的最大值即可。

设后缀数组为 $\textit{sa}$，其中：

- $\textit{sa}[i]$ 表示字典序排名为 $i$ 的后缀起始位置；
- $\textit{height}[i]$ 表示后缀 $\textit{sa}[i]$ 与后缀 $\textit{sa}[i-1]$ 的最长公共前缀长度。

那么答案就是：

$$
\max_{1\le i<n} \textit{height}[i]
$$

# 解题思路

## 1. 构造后缀数组

使用倍增算法构造后缀数组。

初始时，每个后缀按照第一个字符排序，并以该字符作为排名。之后不断将排序关键字从一个字符扩展到 $2$ 个、$4$ 个、$8$ 个字符：

$$
(\text{rank}[i],\text{rank}[i+k])
$$

其中 $k$ 为当前已处理的长度。

如果两个后缀对应的二元组相同，则它们在当前长度下排名相同；否则根据二元组的字典序确定排名。

代码使用基数排序对二元组进行排序，从而将每轮排序的复杂度降为 $O(n)$。倍增轮数为 $O(\log n)$，所以构造后缀数组的总复杂度为：

$$
O(n\log n)
$$

## 2. 计算相邻后缀的最长公共前缀

构造出后缀数组后，使用 Kasai 算法计算 $\textit{height}$ 数组。

先建立逆排名数组：

$$
\textit{rank}[\textit{sa}[i]]=i
$$

对于起始位置为 $i$ 的后缀，设其排名为 $\textit{rank}[i]$。如果它不是字典序最小的后缀，就将它与前一个后缀逐字符比较，得到最长公共前缀长度。

Kasai 算法的关键是：相邻位置的后缀的最长公共前缀长度不会突然减少很多，因此在处理下一个位置时，可以复用前一次比较得到的结果，将比较次数控制在 $O(n)$。

最终扫描 $\textit{height}$ 数组，取最大值即可。

# 正确性证明

下面证明算法能够得到最长重复子串的长度。

## 引理 1

任意两个后缀的最长公共前缀对应一个在原字符串中出现至少两次的子串。

设两个后缀分别从位置 $i$ 和 $j$ 开始，它们的最长公共前缀长度为 $L$。那么：

$$
S[i \dots i+L-1]=S[j \dots j+L-1]
$$

因此，这个长度为 $L$ 的子串至少在位置 $i$ 和位置 $j$ 出现两次。两次出现可以重叠，因此该子串满足题目要求。

## 引理 2

字典序相邻的两个后缀的最长公共前缀长度，能够表示任意重复子串的最大长度。

设某个长度为 $L$ 的子串在位置 $i$ 和位置 $j$ 出现，那么从 $i$ 和 $j$ 开始的两个后缀的最长公共前缀长度至少为 $L$。

在后缀数组中，考虑这两个后缀之间的所有后缀。由于它们拥有相同的长度为 $L$ 的前缀，这些后缀会连续排列在后缀数组中的同一段区间内。该区间中相邻后缀的最长公共前缀长度都至少为 $L$。

因此，任意重复子串的长度都不会超过某一对相邻后缀的 $\textit{height}$ 值。

## 引理 3

$\max(\textit{height})$ 是最长重复子串的长度。

根据引理 1，每个 $\textit{height}[i]$ 都对应一个至少出现两次的子串，因此：

$$
\max(\textit{height})
$$

不会超过答案。

根据引理 2，任意重复子串的长度都不超过某个相邻后缀的最长公共前缀长度，因此答案不会超过 $\max(\textit{height})$。

两者结合可得：

$$
\text{答案}=\max(\textit{height})
$$

所以算法正确。

# 复杂度分析

设字符串长度为 $n$。

- 后缀数组构造：$O(n\log n)$；
- Kasai 算法计算最长公共前缀：$O(n)$；
- 扫描答案：$O(n)$；
- 空间复杂度：$O(n)$。

因此总时间复杂度为：

$$
O(n\log n)
$$

空间复杂度为：

$$
O(n)
$$

# 代码实现

```cpp
// Editor
// UVa ID: 1223
// Verdict: Accepted
// Submission Date: 2018-05-29
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 5010;
const int CHARSET = 256;

// 根据第二关键字进行计数排序，再根据第一关键字进行计数排序
void radixSort(int *s, int *a, int *b, int n, int m)
{
    static int cnt[MAXN];

    memset(cnt, 0, (max(n, m) + 1) * sizeof(int));

    for (int i = 0; i < n; i++)
        cnt[s[a[i]]]++;

    for (int i = 1; i <= m; i++)
        cnt[i] += cnt[i - 1];

    for (int i = n - 1; i >= 0; i--)
        b[--cnt[s[a[i]]]] = a[i];
}

// 倍增算法构造后缀数组
void suffixArray(int *s, int *sa, int n, int m)
{
    static int ranks[MAXN] = {};
    static int a[MAXN] = {};
    static int b[MAXN] = {};

    // 初始排名为字符本身
    iota(ranks, ranks + max(n, m) + 1, 0);

    // 按首字符排序
    radixSort(s, ranks, sa, n, m);

    // 根据首字符重新编号
    ranks[sa[0]] = 0;
    for (int i = 1; i < n; i++)
    {
        ranks[sa[i]] = ranks[sa[i - 1]];
        ranks[sa[i]] += (s[sa[i]] != s[sa[i - 1]]);
    }

    // 每次将已排序长度扩大一倍
    for (int k = 1; k < n; k <<= 1)
    {
        for (int i = 0; i < n; i++)
        {
            // 第一关键字：当前位置的排名
            a[i] = ranks[i] + 1;

            // 第二关键字：后移 k 位后的排名
            // 0 表示已经超出字符串末尾
            b[i] = (i + k >= n) ? 0 : (ranks[i + k] + 1);

            // 待排序的后缀起点
            sa[i] = i;
        }

        // 先按第二关键字排序，再按第一关键字排序
        radixSort(b, sa, ranks, n, n);
        radixSort(a, ranks, sa, n, n);

        // 重新编号
        ranks[sa[0]] = 0;
        for (int i = 1; i < n; i++)
        {
            ranks[sa[i]] = ranks[sa[i - 1]];

            if (a[sa[i - 1]] != a[sa[i]] ||
                b[sa[i - 1]] != b[sa[i]])
            {
                ranks[sa[i]]++;
            }
        }
    }
}

// 使用 Kasai 算法计算 height 数组
void getHeight(int *s, int *sa, int *height, int n)
{
    static int ranks[MAXN] = {};

    height[0] = 0;

    // 建立每个后缀的排名
    for (int i = 0; i < n; i++)
        ranks[sa[i]] = i;

    for (int i = 0, k = 0; i < n; i++, (k ? k-- : 0))
    {
        if (ranks[i])
        {
            int previousSuffix = sa[ranks[i] - 1];

            while (s[i + k] == s[previousSuffix + k])
                k++;

            height[ranks[i]] = k;
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int cases;
    cin >> cases;

    while (cases--)
    {
        string str;
        cin >> str;

        int n = static_cast<int>(str.length());

        int s[MAXN], sa[MAXN], height[MAXN];

        for (int i = 0; i < n; i++)
            s[i] = str[i];

        // 末尾哨兵，小写字母均大于 0
        s[n] = 0;

        suffixArray(s, sa, n, CHARSET);
        getHeight(s, sa, height, n);

        cout << *max_element(height, height + n) << '\n';
    }

    return 0;
}
```

# 总结

本题的核心是将“最长出现至少两次的子串”转化为“任意两个后缀的最长公共前缀最大值”。

具体步骤如下：

1. 使用倍增算法构造后缀数组；
2. 使用 $\texttt{Kasai}$ 算法计算相邻后缀的最长公共前缀数组；
3. 取所有最长公共前缀长度的最大值。

由于后缀数组中的相邻后缀能够覆盖任意两个后缀之间的最长公共前缀，最终只需扫描 `height` 数组即可得到答案。
