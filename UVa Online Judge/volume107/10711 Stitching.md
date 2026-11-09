
> **摘要**：本题要求在两个位于不同平面、顶点按逆时针给出的简单多边形之间构造三角网格曲面，使每个三角形恰好包含两个来自同一多边形的顶点和一个来自另一多边形的顶点，并让曲面总面积最小。文章将几何缝合问题抽象为 $m \times n$ 环形网格上的闭合路径问题，通过固定起始公共边把环形路径展开为单调路径，用动态规划求解最小面积，并枚举所有起始偏移取最优值，最终以 $O(m^2 n^2)$ 的复杂度完成求解。

## 题目描述

给定两个简单多边形（不一定凸），分别位于 $z = 0$ 和 $z = z_1$ 平面内，顶点均按逆时针顺序给出。需要在这两个多边形之间构造一个三角网格曲面，使得所有三角形顶点均取自两个多边形的顶点，且每个三角形恰好有两个顶点来自其中一个多边形，一个顶点来自另一个多边形，从而完整地“缝合”两个轮廓。要求该曲面的总面积最小，输出最小面积值。曲面由 $m + n$ 个三角形组成，其中 $m$、$n$ 分别为两个多边形的顶点数。

## 输入格式

第一行包含一个整数 $N$，表示测试用例数。  
每个测试用例的第一行包含三个数：$m$、$n$、$z_1$，其中 $m$ 和 $n$ 为整数（$2 < m, n \le 20$），$z_1$ 为正实数，表示第二个多边形所在平面的 $z$ 坐标（第一个多边形位于 $z = 0$ 平面）。  
接下来 $m + n$ 行，每行包含两个实数 $x$、$y$，表示一个顶点的坐标。前 $m$ 行属于第一个多边形，后 $n$ 行属于第二个多边形。多边形顶点按逆时针顺序排列。

## 输出格式

对于每个测试用例，输出一行一个实数，表示最小曲面面积，保留五位小数（可省略末尾零）。允许相对误差不超过 $0.01\%$。

## 样例

输入

```text
2
4 3 1
0 0
1 0
1 1
0 1
0 0
1 0
0.5 1
4 4 2
0 0
1 0
1 1
0 1
0 1
1 1
```

输出

```text
3.72474
8.00000
```

## 题目分析

将两个多边形的顶点分别编号为  
$P_0, P_1, \dots, P_{m-1}$ 和 $Q_0, Q_1, \dots, Q_{n-1}$。所有 $P_i$ 的 $z$ 坐标为 $0$，所有 $Q_j$ 的 $z$ 坐标为 $z_1$。

曲面由三角形构成，且每个三角形使用两个来自同一多边形的顶点和一个来自另一多边形的顶点。若当前三角形的公共边为 $(P_i, Q_j)$（即该边已在之前三角形中出现），则下一个三角形必须包含这两个顶点，并引入一个新顶点，该新顶点要么来自 $P$（变为 $(P_i, P_{i+1}, Q_j)$），要么来自 $Q$（变为 $(P_i, Q_j, Q_{j+1})$）。这种过程可以抽象为一个在 $m \times n$ 网格上的游走：每个格点 $(i, j)$ 代表公共边 $(P_i, Q_j)$，向右一步表示引入下一个 $Q$ 顶点，向下一步表示引入下一个 $P$ 顶点。由于顶点下标循环（$P_m = P_0$，$Q_n = Q_0$），游走最终必须回到起点，且每条水平线和每条竖直线恰好被跨越一次，以保证每个顶点恰好被引入一次。

因此，问题等价于：在 $m \times n$ 的环形网格中，找一条从某点出发、经过恰好 $m$ 次向下和 $n$ 次向右、最终回到起点的闭合路径，使得路径上每一步所对应三角形的面积之和最小。

## 解题思路

由于网格是循环的，直接处理环形路径较为复杂。考虑固定路径的起始公共边 $(P_{i_0}, Q_{j_0})$，将环形网格展开为普通矩形，路径变为从 $(0,0)$ 到 $(m,n)$ 的单调路径（只向右或向下）。对于固定的起始偏移 $(i_0, j_0)$，我们可以用动态规划求解该偏移下的最小面积。

定义 $\textit{dp}[d][r]$ 为从起点到达展开坐标 $(d, r)$ 的最小累计面积，其中 $d$ 表示已使用的 $P$ 顶点个数（即向下步数），$r$ 表示已使用的 $Q$ 顶点个数（即向右步数）。实际对应的顶点下标为：

- 当前 $P$ 顶点下标：$i = (i_0 + d) \bmod m$；
- 当前 $Q$ 顶点下标：$j = (j_0 + r) \bmod n$。

转移分为两种：

1. **向右一步**（从 $(d, r-1)$ 到 $(d, r)$）：新三角形为 $(P_i, Q_{j-1}, Q_j)$，其中 $j = (j_0 + r) \bmod n$，$j-1$ 为前一个 $Q$ 顶点下标；
2. **向下一步**（从 $(d-1, r)$ 到 $(d, r)$）：新三角形为 $(P_{i-1}, P_i, Q_j)$，其中 $i = (i_0 + d) \bmod m$，$i-1$ 为前一个 $P$ 顶点下标。

初始条件 $\textit{dp}[0][0] = 0$，其余设为无穷大。最终 $\textit{dp}[m][n]$ 即为该起始偏移下的最小面积。

三角形面积使用三维叉积计算，公式为：

$$
\textit{Area} = \frac{1}{2} \left\| \overrightarrow{AB} \times \overrightarrow{AC} \right\|
$$

其中 $A, B, C$ 为三角形的三个顶点。

枚举所有可能的起始偏移 $(i_0, j_0)$（共 $m \times n$ 种），对每个偏移运行一次 DP，取所有结果的最小值即为答案。由于 $m, n \le 20$，总复杂度 $O(m^2 n^2)$ 可接受。

## 复杂度分析

- 时间复杂度：$O(m^2 n^2)$，因为对每个起始偏移执行 $O(mn)$ 的 DP，共计 $m n$ 个偏移。
- 空间复杂度：$O(mn)$，用于存储 $\texttt{DP}$ 表。

## 代码实现

```cpp
// Stitching
// UVa ID: 10711
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Point3D {
    double x, y, z;
};

// 计算三角形面积（三维叉积）
double triangleArea(const Point3D& a, const Point3D& b, const Point3D& c) {
    double v1x = b.x - a.x, v1y = b.y - a.y, v1z = b.z - a.z;
    double v2x = c.x - a.x, v2y = c.y - a.y, v2z = c.z - a.z;
    double cx = v1y * v2z - v1z * v2y;
    double cy = v1z * v2x - v1x * v2z;
    double cz = v1x * v2y - v1y * v2x;
    return 0.5 * sqrt(cx * cx + cy * cy + cz * cz);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;
    cout << fixed << setprecision(5);
    while (N--) {
        int m, n;
        double z1;
        cin >> m >> n >> z1;
        vector<Point3D> P(m), Q(n);
        for (int i = 0; i < m; ++i) {
            cin >> P[i].x >> P[i].y;
            P[i].z = 0.0;
        }
        for (int j = 0; j < n; ++j) {
            cin >> Q[j].x >> Q[j].y;
            Q[j].z = z1;
        }
        const double INF = 1e100;
        double ans = INF;
        // 枚举起始偏移 (i0, j0)
        for (int i0 = 0; i0 < m; ++i0) {
            for (int j0 = 0; j0 < n; ++j0) {
                vector<vector<double>> dp(m + 1, vector<double>(n + 1, INF));
                dp[0][0] = 0.0;
                for (int d = 0; d <= m; ++d) {
                    for (int r = 0; r <= n; ++r) {
                        if (d == 0 && r == 0) continue;
                        double best = INF;
                        // 从左边来（向右一步）
                        if (r > 0) {
                            int i = (i0 + d) % m;
                            int jPrev = (j0 + r - 1) % n;
                            int jCur = (j0 + r) % n;
                            double cost = triangleArea(P[i], Q[jPrev], Q[jCur]);
                            best = min(best, dp[d][r - 1] + cost);
                        }
                        // 从上方来（向下一步）
                        if (d > 0) {
                            int iPrev = (i0 + d - 1) % m;
                            int iCur = (i0 + d) % m;
                            int j = (j0 + r) % n;
                            double cost = triangleArea(P[iPrev], P[iCur], Q[j]);
                            best = min(best, dp[d - 1][r] + cost);
                        }
                        dp[d][r] = best;
                    }
                }
                ans = min(ans, dp[m][n]);
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
```

## 总结

本题巧妙地将几何曲面重建问题转化为网格上的最短路径问题。关键在于识别出三角形序列与网格路径的一一对应关系，并通过枚举起始偏移消除循环依赖，从而将环形路径转化为标准的单调 $\texttt{DP}$。计算面积时使用三维叉积避免了海伦公式可能带来的精度问题。该解法利用了 $m, n$ 较小的条件，实现了简洁高效的枚举 $\texttt{DP}$，是处理此类二维轮廓缝合问题的典型思路。
