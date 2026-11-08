
> **摘要**：本文讲解经典的天际线问题，给定若干底部对齐的矩形建筑物三元组 $(L_i, H_i, R_i)$，要求输出描述城市外轮廓的向量序列。文章从矩形覆盖的角度分析问题本质，采用离散化 + 扫描线的思路，用数组记录每个 $x$ 坐标处的最大高度，再扫描高度变化点生成转折点。时间复杂度约 $5 \times 10^7$，空间复杂度 $O(MAXN)$。

## 题目描述

给定一系列建筑物的位置信息，每个建筑物用一个三元组 $(L_i, H_i, R_i)$ 表示，其中 $L_i$ 和 $R_i$ 分别是建筑物的左右边界坐标 ($0 < L_i < R_i$)，$H_i$ 是建筑物的高度。所有建筑物都是底部对齐的矩形，且城市视为二维平面。要求根据这些建筑物的轮廓，输出描述整个城市天际线的向量序列。

**输入**  
- 一系列建筑物的三元组，每行一个。  
- 坐标均为小于 $10000$ 的整数，建筑物数量 $1 \leq n \leq 5000$。  
- 三元组已按 $L_i$ 升序排列。

**输出**  
- 一个向量序列，描述从最小 $x$ 坐标开始，沿天际线“行走”的路径。  
- 向量中奇数位表示 $x$ 坐标，偶数位表示高度。  
- 序列以高度 $0$ 结束。

**示例**  
输入：
```text
1 11 5
2 6 7
3 13 9
12 7 16
14 3 25
19 18 22
23 13 29
24 4 28
```
输出：
```text
1 11 3 13 9 0 12 7 16 3 19 18 22 3 23 13 29 0
```

## 题目分析

本题可以看作是一个二维平面上的矩形覆盖问题：多个矩形在 $x$ 轴上排列，高度不同，我们需要找出它们所形成的外轮廓线。

关键点：
- 每个矩形在 $[L_i, R_i)$ 区间内贡献一个高度 $H_i$。
- 在任意 $x$ 坐标处，可见高度为所有覆盖该点的矩形高度的最大值。
- 天际线由这些局部高度变化点构成：当高度发生变化时，就产生一个转折点。

## 解题思路

### 方法：离散化 + 扫描线

由于坐标范围较小（< $10000$），我们可以直接使用一个数组 `grid` 来记录每个整数 $x$ 坐标处的最大高度。

1. **初始化**  
   - 创建一个长度为 $MAXN$ 的数组 `grid`，初始值为 $0$。
   - 记录所有建筑物中最小左边界 `leftMost` 和最大右边界 `rightMost`。

2. **处理输入**  
   - 对于每个建筑物 $(L_i, H_i, R_i)$，在区间 $[L_i, R_i]$ 内更新 `grid[x]` 为 `max(grid[x], H_i)`。  
   - 注意：这里取的是闭区间，因为题目中建筑物右边界也是轮廓的一部分。

3. **生成输出**  
   - 从 `leftMost` 开始扫描到 `rightMost`。
   - 当高度发生变化时：
     - 若高度增加，输出当前 $x$ 和新高度。
     - 若高度降低，输出前一个 $x$（即 `i-1`）和新高度。
   - 最后输出 `rightMost` 和 $0$，表示轮廓结束。

### 复杂度分析
- 时间复杂度：最坏情况下，每个建筑物更新区间长度可达 $10000$，建筑物数量最多 $5000$，总操作次数约为 $5000 \times 10000 = 5 \times 10^7$，在合理优化下可以接受。
- 空间复杂度：$O(MAXN)$，即 $O(10010)$。

### 注意事项
- 建筑物右边界坐标 $R_i$ 处的轮廓高度应取 $0$，但实际代码中在更新区间时包含了右端点，因此在输出时需注意转折点的位置。
- 输出格式要求以 $0$ 结尾，表示轮廓回到地面。

## 代码实现

```cpp
// Skyline Problem
// UVa ID: 105
// Verdict: Accepted
// Submission Date: 2011-11-22
// UVa Run Time: 0.036s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

#define MAXN 10010
int grid[MAXN];

int main () {
    int left, height, right, leftMost, rightMost = 0;
    bool leftSetted = false;
    memset(grid, 0, sizeof(grid));
    while (cin >> left >> height >> right) {
        for (int i = left; i <= right; i++)
            grid[i] = max(grid[i], height);
        if (!leftSetted) {
            leftMost = left;
            leftSetted = true;
        }
        rightMost = max(rightMost, right);
    }
    cout << leftMost << " " << grid[leftMost];
    int current = leftMost;
    for (int i = leftMost; i <= rightMost; i++) {
        if (grid[i] == grid[current]) continue;
        else {
            if (grid[i] > grid[current]) cout << " " << i << " " << grid[i];
            else cout << " " << (i - 1) << " " << grid[i];
            current = i;
        }
    }
    cout << " " << rightMost << " 0\n";
    return 0;
}
```

## 总结

本题通过直接模拟每个 $x$ 坐标处的最大高度，巧妙地避免了复杂的几何计算。虽然时间复杂度较高，但得益于坐标范围小，依然可以在规定时间内完成。该方法直观易懂，适合作为入门级扫描线问题的练习。
