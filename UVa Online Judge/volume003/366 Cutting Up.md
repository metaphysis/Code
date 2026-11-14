[UVa 366 Cutting Up](https://blog.csdn.net/metaphysis/article/details/161147618)

## 题目描述

拼布者经常需要将布料切割成 $1 \times 1$ 的小正方形。他们有一种特殊工具（旋转切割刀），可以一次切割多层布料，切割层数的上限由布料类型决定（题目输入的第一个参数 $K$）。切割时，无论切割长度是多少，难度都是一样的，因此问题的关键是最小化切割次数，而不是切割长度。

切割规则如下：
- 布料可以叠放，且**叠放的布料不需要形状完全相同**。
- 切割之间可以重新排列布料。
- 布料不能被折叠。
- 切割必须沿整数坐标进行（即从边到边，将一块布料切成两块）。
- 最终必须得到 $m \times n$ 个 $1 \times 1$ 的小正方形，没有浪费。

输入包含多行，每行三个整数：$K$（最大可切割层数，$1 \le K \le 200$）、$m$（高度，$1 \le m \le 20$）、$n$（宽度，$1 \le n \le 20$）。输入以 `0 0 0` 结束。

输出格式为 `m by n takes x cuts`，每组输出后跟一个空行。

## 题目分析

这是一道具有特殊性质的最优化问题。直觉上，切割布料的过程可以看作：一开始有一块 $m \times n$ 的矩形，每次操作可以选择若干块布料（数量不超过 $K$），将它们叠放在一起，然后沿某条直线切一刀，使得每块被切中的布料都分成两块更小的矩形。最终目标是全部变成 $1 \times 1$。

由于 $m, n \le 20$，状态空间理论上有限，但直接 $\texttt{BFS}$ 或 $\texttt{DP}$ 会遇到两个困难：
1. 状态表示复杂（多重集，最多 $400$ 种不同的矩形，每种数量可达 $400$）。
2. 每次切割可以同时处理多种不同形状的矩形，分支因子极大。

然而，题目允许不同形状叠放这一特性，大大简化了问题：我们不再需要为每种形状单独考虑切割，而是可以**一次性切割当前所有“还需要被切”的矩形中最需要切的那些**。

## 解题思路

### 贪心策略的合理性

核心贪心策略是：

> 每一轮，从所有尚未变成 $1 \times 1$ 的矩形中，选择面积最大的 $\min(K, \text{需要切的矩形总数})$ 个矩形，每个矩形都沿着**较长边的一半**（向下取整）切一刀，其余矩形保留不动。重复直到全部是 $1 \times 1$。

为什么这样能得到最优解？

1. **一刀切多块**：由于允许不同形状叠放，一次切割可以同时作用于多个矩形，因此我们希望在每一刀中尽可能多地切割“大块”的矩形，因为大块矩形需要更多次切割才能变小。
2. **按面积排序**：面积越大的矩形，距离 $1 \times 1$ 的“距离”越远，优先处理它们可以更快地减少总工作量。
3. **沿较长边中间切**：这是最平衡的切法，可以最大化切完后两块的“最小面积”，从而让两块都能在后续被继续切割，避免出现细长条需要额外切割的情况。实际上，对于矩形，每次切成两半（或尽可能接近一半）是最优的切割策略。

### 与 $\texttt{BFS}$ 或 $\texttt{DP}$ 的关系

理论上，本题可以用 $\texttt{BFS}$ 精确求解，但状态空间巨大（每种矩形的数量范围 $0$ 到 $400$，有 $400$ 种矩形），$\texttt{BFS}$ 会组合爆炸。而本题的数据范围（$m,n \le 20$）和允许不同形状叠放，使得贪心策略恰好是全局最优的。这种贪心可以被视为一种**基于优先级的贪心 $\texttt{BFS}$**，每一步都选择当前最紧迫的任务进行切割。

$\texttt{DP}$ 方法也不可行，因为切割过程涉及并行处理多个矩形，无法简单地用单矩形的 $\texttt{DP}$ 叠加。

### 算法步骤

1. 用 `vector<pair<int, int>>` 存储当前所有矩形的尺寸 `(width, height)`，初始只有一块 `(n, m)`。
2. 初始化切割次数 `cuts = 0`。
3. 循环直到所有矩形都是 $1 \times 1$：
   - 收集所有面积大于 $1$ 的矩形到 `needToCut`。
   - 按面积降序排序。
   - 取前 `take = min(K, needToCut.size())` 个矩形。
   - 对这些矩形，若宽度 ≥ 高度，则水平切（将宽度分成 `width/2` 和 `width - width/2`）；否则垂直切。
   - 未选中的矩形直接保留。
   - 切割次数加 $1$。
4. 输出结果。

## 复杂度分析

- 每轮切割，需要处理的矩形个数最多为当前布料的总块数。初始为 $1$ 块，之后每切一刀会增加若干块。
- 由于每次切掉最大的矩形且切法平衡，矩形数量增长较慢。
- 总切割次数不超过 $m \times n$（最坏情况每次只切一块），实际远小于此。
- 空间复杂度 $O(m \times n)$。

## 代码实现

```cpp
// Cutting Up
// UVa ID: 366
// Verdict: Accepted
// Submission Date: 2026-05-16
// UVa Run Time: 0.010s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    int l, h, w;
    while (cin >> l >> h >> w) {
        if (l == 0 && h == 0 && w == 0) break;
        
        // 当前所有矩形的集合，每个矩形用 (width, height) 表示
        vector<pair<int, int>> pieces;
        pieces.push_back({w, h});
        int cuts = 0;
        
        while (true) {
            // 收集所有需要切割（面积 > 1）的矩形
            vector<pair<int, int>> needToCut;
            for (auto p : pieces)
                if (p.first * p.second > 1)
                    needToCut.push_back(p);
            
            if (needToCut.empty()) break;   // 全部是 1x1，结束
            
            // 按面积降序排序，优先切大块
            sort(needToCut.begin(), needToCut.end(), [](pair<int, int> a, pair<int, int> b) {
                return a.first * a.second > b.first * b.second;
            });
            
            vector<pair<int, int>> newPieces;
            int take = min(l, (int)needToCut.size());   // 本次最多切 l 个
            
            // 对选中的矩形，每个都从较长边的一半处切一刀
            for (int i = 0; i < take; i++) {
                auto p = needToCut[i];
                if (p.first >= p.second) {   // 宽度 >= 高度，水平切
                    newPieces.push_back({p.first / 2, p.second});
                    newPieces.push_back({p.first - (p.first / 2), p.second});
                } else {                     // 高度 > 宽度，垂直切
                    newPieces.push_back({p.first, p.second / 2});
                    newPieces.push_back({p.first, p.second - (p.second / 2)});
                }
            }
            
            // 未选中的矩形原样保留
            for (int i = take; i < (int)needToCut.size(); i++)
                newPieces.push_back(needToCut[i]);
            
            pieces = newPieces;
            cuts++;
        }
        
        cout << h << " by " << w << " takes " << cuts << " cuts\n\n";
    }
    return 0;
}
```

## 总结

本题的关键在于认识到：**允许不同形状叠放** 使得我们可以在一刀中同时切割多个矩形，从而将问题转化为一个贪心过程：每次优先切割当前面积最大的若干个矩形，且采用最平衡的切法。这种贪心策略在该问题的约束下能够达到全局最优，代码实现简洁高效。
