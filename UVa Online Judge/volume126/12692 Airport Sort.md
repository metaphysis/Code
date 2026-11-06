
> **摘要**：本题给出 $n$ 名乘客的随机登机队列，每位乘客的票号决定其所属区域（每 $k$ 张票为一个区域）。要求比较两种重排策略的耗时差 $X - Y$：相邻交换的最少次数 $X$ 等价于区域序列的逆序对数量，可用归并排序在 $O(n \log n)$ 内求出；同时移动的最短时间 $Y$ 等价于最小化最大偏移的匹配问题，将各区域内乘客的初始位置升序排列后与目标位置顺序配对即可取到最优。最终输出 $X - Y$，总复杂度 $O(T \cdot n \log n)$。

## 题目描述

有若干航空公司不预先指定座位号，每位乘客的登机牌上有一个唯一的整数，范围在 $[1, n]$ 中，其中 $n$ 为飞机总座位数。每个票号属于某个“区域”（$\texttt{zone}$）。若一个区域包含 $k$ 张票，则票号 $[1, k]$ 属于区域 $1$，$[k+1, 2k]$ 属于区域 $2$，依此类推，最后一个区域可能不足 $k$ 张票。

登机前，所有 $n$ 名乘客随机排成一行。为了加快登机，理想的排列是：前 $k$ 人属于区域 $1$，接下来的 $k$ 人属于区域 $2$，依此类推。给出两种重排方式：

1. **相邻交换**：每秒只能交换一对相邻乘客的位置，直到达到目标顺序。所需最少时间记为 $X$。
2. **同时移动**：所有乘客同时走向自己的正确位置。从位置 $x$ 移动到位置 $y$ 需要 $|x-y|$ 秒。所需最少时间记为 $Y$。

要求计算 $X - Y$，即第一种方式比第二种方式慢多少秒。

## 输入格式

第一行为整数 $T$（$T < 50$），表示测试用例数。  
每个测试用例包含两行：  
第一行有两个正整数 $n$（$n \le 20000$）和 $k$（$k \le n$），含义如上。  
第二行包含 $n$ 个互不相同的整数，范围为 $[1, n]$，表示队伍从前到后各乘客的票号。

## 输出格式

对于每个测试用例，输出 `Case i: X - Y`，其中 $X - Y$ 为整数。

## 样例

输入

```
3
10 3
3 7 1 2 4 6 5 8 10 9
11 3
1 2 3 4 5 6 7 8 9 10 11
5 2
5 4 3 2 1
```

输出

```
Case 1: 1
Case 2: 0
Case 3: 4
```

## 题目分析

本题需要计算两种不同重排策略所需的最少时间，并求其差。

**区域划分**：  
给定票号 $t$，它所属的区域编号为 $\textit{zone}(t) = \lfloor (t-1) / k \rfloor + 1$（从 $1$ 开始编号）。共有 $m = \lceil n / k \rceil$ 个区域，第 $r$ 个区域包含的票号区间为 $[(r-1)k+1, \min(rk, n)]$，其长度为 $\textit{len}[r] = \min(k, n - (r-1)k)$。

最终目标排列只需保证所有属于同一区域的乘客被安排到连续的区间内，且区域编号按升序排列。同一区域内乘客之间的相对顺序可以任意，因为区域内部不要求顺序。

**第一种策略（相邻交换）**：  
相邻交换排序所需的最少交换次数等于原序列中**逆序对**的数量，其中逆序定义为：若位置 $i < j$ 且 $\textit{zone}[i] > \textit{zone}[j]$，则构成一个逆序对。这是因为最终要求区域编号非递减，任何“大区域在前、小区域在后”的错位都必须通过相邻交换纠正，而每次相邻交换最多消除一个逆序对，因此最小交换次数恰为逆序对总数。

**第二种策略（同时移动）**：  
所有乘客同时向各自目标位置移动，耗时等于所有乘客中移动距离的最大值。我们需要为每个区域的乘客分配该区域内的连续位置，使得最大移动距离最小。  
对于每个区域 $r$，其目标位置区间为 $[L_r, R_r]$，其中 $L_1 = 1$，$L_{r+1} = R_r + 1$，$R_r = L_r + \textit{len}[r] - 1$。  
该区域内的乘客初始位置（在原队伍中的下标）已知，我们需要将每个乘客分配到一个目标位置，使得最大偏移最小。根据贪心原理，将初始位置升序排列后，按顺序分配给目标位置 $L_r, L_r+1, \dots, R_r$ 时，最大偏移达到最小。这是因为这是经典的“最小化最大绝对差”的匹配问题，排序后顺序匹配是最优的。  
因此，对于每个区域，计算 $\max_{j=0}^{\textit{len}[r]-1} |\textit{pos}_r[j] - (L_r + j)|$，其中 $\textit{pos}_r[j]$ 为该区域内乘客初始位置的升序序列。全局 $Y$ 取所有区域该值的最大值。

最终答案 $X - Y$ 即为所求。

## 解题思路

1. 读入测试用例数 $T$。
2. 对每个测试用例：
   - 读入 $n, k$ 以及数组 $a[1..n]$。
   - 计算每个位置 $i$ 的区域编号 $\textit{zone}[i] = \lfloor (a[i]-1) / k \rfloor + 1$。
   - 计算区域总数 $m = \lceil n / k \rceil$ 以及每个区域的大小 $\textit{len}[r]$。
   - 收集每个区域中乘客的初始位置：遍历 $i$ 从 $1$ 到 $n$，将 $i$ 加入 $\textit{pos}[\textit{zone}[i]]$。由于遍历顺序升序，每个 $\textit{pos}[r]$ 自然升序。
   - 计算 $Y$：维护当前起始位置 $\textit{cur}$，对每个区域 $r$，设目标位置为 $\textit{cur}, \textit{cur}+1, \dots$，与 $\textit{pos}[r]$ 逐个配对，更新 $Y = \max(Y, |\textit{pos}[r][j] - (\textit{cur}+j)|)$，然后 $\textit{cur}$ 增加 $\textit{len}[r]$。
   - 计算 $X$：对 $\textit{zone}[1..n]$ 数组求逆序对数量。使用归并排序实现，时间复杂度 $O(n \log n)$。
   - 输出 `Case i: X - Y`。

**正确性保证**：
- 逆序对与相邻交换最小次数的等价性来自排序网络的基本结论。
- 顺序匹配保证最大偏移最小的证明：对于一维点集和目标区间，顺序配对是使最大绝对差最小的最优策略（可以通过交换论证证明，若存在交叉配对，则交换后可减少或保持最大差）。
- 所有计算均为确定步骤，不依赖任何随机或近似。

**复杂度分析**：
- 每个测试用例，区域划分和位置收集为 $O(n)$。
- 归并排序求逆序对为 $O(n \log n)$。
- 总复杂度为 $O(T \cdot n \log n)$，在 $n \le 20000$、$T < 50$ 的限制下可行。空间复杂度 $O(n)$。

## 代码实现

```cpp
// Airport Sort
// UVa ID: 12692
// Verdict: Accepted
// Submission Date: 2026-07-13
// UVa Run Time: 0.040s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 归并排序求逆序对
long long mergeSort(vector<int>& arr, vector<int>& tmp, int left, int right) {
    if (left >= right) return 0;
    int mid = (left + right) / 2;
    long long inv = mergeSort(arr, tmp, left, mid) + mergeSort(arr, tmp, mid + 1, right);
    int i = left, j = mid + 1, idx = left;
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) tmp[idx++] = arr[i++];
        else {
            tmp[idx++] = arr[j++];
            inv += (mid - i + 1);
        }
    }
    while (i <= mid) tmp[idx++] = arr[i++];
    while (j <= right) tmp[idx++] = arr[j++];
    for (int p = left; p <= right; ++p) arr[p] = tmp[p];
    return inv;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int caseNo = 1; caseNo <= T; ++caseNo) {
        int n, k;
        scanf("%d %d", &n, &k);
        vector<int> a(n + 1);
        for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);

        // 1. 计算每个位置的区域编号
        vector<int> zone(n + 1);
        for (int i = 1; i <= n; ++i) zone[i] = (a[i] - 1) / k + 1;

        // 2. 计算每个区域的大小
        int m = (n + k - 1) / k;
        vector<int> len(m + 1);
        int curStart = 1;
        for (int r = 1; r <= m; ++r) {
            len[r] = min(k, n - (r - 1) * k);
        }

        // 3. 收集每个区域的初始位置（升序）
        vector<vector<int>> pos(m + 1);
        for (int i = 1; i <= n; ++i) pos[zone[i]].push_back(i);

        // 4. 计算 Y
        int Y = 0;
        int curPos = 1;
        for (int r = 1; r <= m; ++r) {
            int L = curPos;
            int sizeR = len[r];
            for (int j = 0; j < sizeR; ++j) {
                int target = L + j;
                int dist = abs(pos[r][j] - target);
                if (dist > Y) Y = dist;
            }
            curPos += sizeR;
        }

        // 5. 计算 X（逆序对数量）
        vector<int> arr(n + 1);
        for (int i = 1; i <= n; ++i) arr[i] = zone[i];
        vector<int> tmp(n + 1);
        long long X = mergeSort(arr, tmp, 1, n);

        // 6. 输出结果
        printf("Case %d: %lld\n", caseNo, X - Y);
    }
    return 0;
}
```

## 总结

本题的核心在于将两种不同的“排序”策略转化为已知的计算模型：
- 相邻交换等价于逆序对计数，这是排序网络的基本结论。
- 同时移动等价于最小化最大偏移的匹配问题，通过排序后顺序配对即可最优。

关键技巧：
- 将票号映射到区域编号，忽略同一区域内的内部顺序，简化问题。
- 归并排序同时完成排序和逆序对计数，效率高且代码简洁。
- 对于 $Y$ 的计算，利用贪心的顺序配对性质，避免复杂的二分或网络流。

本题综合考察了逆序对计算、贪心匹配以及基本的数组处理能力，适合作为算法基础训练的题目。
