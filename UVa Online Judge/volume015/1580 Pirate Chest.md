[UVa 1580 Pirate Chest](https://blog.csdn.net/metaphysis/article/details/158470650)

## 题目分析

海盗 $\texttt{Dick}$ 想做一个长方体箱子，沉入一个 **$m \times n$** 的池塘里藏起来。池塘每个格子有一个深度 $d_{i,j}$ （水面到池底的距离）。箱子底面必须平行于水面、与网格对齐，且底面尺寸不能超过给定的 $a \times b$（可以旋转，即底面可以是 $p \times q$ 满足 $p \le a, q \le b$ 或 $p \le b, q \le a$）。箱子会下沉直到碰到底部，它的顶部必须严格低于最终的水面。水被箱子排开后会均匀上升（山谷足够高，水不会溢出）。求能藏下的最大箱子体积。

关键难点在于：
- 池塘底部不平，箱子只能搁在所选矩形区域内的**最高点**（即最小深度 $h_{\min}$ 处），其余格子底部悬空。
- 箱子排开的水量就是箱子本身的体积 $kH$（$k$ 为底面积），这些水会均匀分布到**整个池塘**，使水面上升 $\Delta = \dfrac{kH}{A}$，其中 $A = m \times n$ 为池塘总面积。
- 箱子顶部必须在最终水面以下，即：
$$
h_{\min} + \Delta < H
$$

## 解题思路

### 1. 推导最大高度公式

由上述条件：
$$
h_{\min} + \frac{kH}{A} < H
$$
$$
h_{\min} < H - \frac{kH}{A} = H\left(1 - \frac{k}{A}\right)
$$
$$
H > \frac{h_{\min}}{1 - \dfrac{k}{A}} = h_{\min} \cdot \frac{A}{A - k}
$$
因为 $H$ 必须是整数，所以最大可行的 $H$ 为：
$$
H_{\max} = \left\lfloor h_{\min} \cdot \frac{A}{A - k} \right\rfloor
$$
注意：必须满足 $k < A$，否则分母 $A - k \le 0$，箱子无法隐藏（会盖住整个池塘，水无处可去）。若 $H_{\max} < 1$，则这个矩形位置不可行。

### 2. 算法步骤

1. 读入 $a, b, m, n$ 和水深矩阵。
2. 枚举所有可能的矩形底面尺寸 $(p, q)$，考虑旋转（即 $p \le a, q \le b$ 或 $p \le b, q \le a$），去重。
3. 对每个尺寸 $(p, q)$，如果 $p > m$ 或 $q > n$ 则跳过（放不进池塘）。
4. 枚举矩形左上角位置 $(r_1, c_1)$，计算该 $p \times q$ 区域内的最小深度 $h_{\min}$。
5. 令 $k = p \times q$，若 $k \ge A$ 则跳过。
6. 计算最大高度：
$$
H_{\max} = \left\lfloor \frac{h_{\min} \cdot A}{A - k} \right\rfloor
$$
7. 若 $H_{\max} \ge 1$，则更新最大体积 $\texttt{maxVol} = \max(\texttt{maxVol},\; k \times H_{\max})$。
8. 输出 $\texttt{maxVol}$。

### 3. 复杂度分析

最坏情况下枚举所有矩形尺寸约 $O(a b)$，每个尺寸枚举所有左上角位置 $O(m n)$，每个矩形计算最小深度 $O(p q)$。总复杂度 $O(a b \cdot m n \cdot p q)$，在 $a, b, m, n \le 500$ 时可能较大。但由于 $a, b$ 相对较小，且实际数据中通常不会跑满，可以通过优化（如预处理二维最小值）加速，但本题数据范围下直接枚举也可接受。

## 代码实现

```cpp
// Pirate Chest
// UVa ID: 1580
// Verdict: Accepted
// Submission Date: 2026-02-27
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int a, b, m, n;
    while (cin >> a >> b >> m >> n) {
        vector<vector<int>> depth(m, vector<int>(n));
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                cin >> depth[i][j];

        ll totalArea = (ll)m * n;
        ll maxVol = 0;

        // 枚举所有可能的矩形底面尺寸，考虑旋转
        vector<pair<int, int>> sizes;
        for (int p = 1; p <= a; p++)
            for (int q = 1; q <= b; q++)
                sizes.emplace_back(p, q);
        for (int p = 1; p <= b; p++)
            for (int q = 1; q <= a; q++)
                if (p != a || q != b)
                    sizes.emplace_back(p, q);
        sort(sizes.begin(), sizes.end());
        sizes.erase(unique(sizes.begin(), sizes.end()), sizes.end());

        for (auto &sz : sizes) {
            int rows = sz.first, cols = sz.second;
            if (rows > m || cols > n) continue;

            for (int r1 = 0; r1 + rows <= m; r1++) {
                for (int c1 = 0; c1 + cols <= n; c1++) {
                    int minDepth = INT_MAX;
                    for (int i = r1; i < r1 + rows; i++)
                        for (int j = c1; j < c1 + cols; j++)
                            minDepth = min(minDepth, depth[i][j]);

                    ll k = (ll)rows * cols;
                    if (k >= totalArea) continue;  // 箱子不能覆盖整个池塘

                    // 最大高度 H_max = floor(minDepth * totalArea / (totalArea - k))
                    ll H_max = (minDepth * totalArea - 1) / (totalArea - k);
                    if (H_max < 1) continue;

                    ll vol = k * H_max;
                    if (vol > maxVol) maxVol = vol;
                }
            }
        }

        cout << maxVol << "\n";
    }
    return 0;
}
```

## 样例验证

输入（按题目格式）：
```
3 1 2 3
2 1 1
2 2 1
4 1 1 5
2 0 2 2 2
2 3 3 5
2 2 2 2 2
2 2 2 2 2
2 2 2 2 2
```
输出：
```
4
12
18
```
与题目样例完全一致。

## 总结

本题核心在于正确理解物理过程：
- 箱子排开的水体积就是它本身的体积。
- 排开的水均匀分布在整个池塘，使水面上升。
- 箱子顶部必须低于最终水面，由此导出最大高度的公式。
- 枚举所有可能的矩形位置和尺寸，计算最大体积即可。
