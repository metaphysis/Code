
> **摘要**：本题要求在二维平面上以原点为圆心，选择一个扇形区域覆盖至少 $K$ 个目标点，并使扇形面积最小。核心思路是：最优半径必等于某个目标点到原点的距离，因此只需枚举 $N$ 种候选半径；在固定半径下，将问题转化为「在按极角排序的点集中寻找覆盖至少 $K$ 个点的最小角度跨度」，利用角度周期性（复制数组并加 $2\pi$）配合双指针滑动窗口求解。整体时间复杂度 $O(N^2)$，空间复杂度 $O(N)$，可轻松通过 $N \le 5000$ 的数据规模。

## 题目描述

一种新型武器位于二维平面原点 $(0,0)$，能够攻击任意大小的扇形区域，该扇形所在圆的圆心即为武器位置。平面上给定 $N$ 个目标点，坐标互不相同，且没有目标位于原点。一个射击方案称为有效的，当且仅当它覆盖的目标点数量至少为 $K$。射击成本与扇形面积成正比，现要求在所有有效方案中，找出面积最小的最优射击方案，并输出该最小面积（保留两位小数）。

## 输入格式

输入包含多个测试用例。  
每个测试用例以两个非负整数 $N$ 和 $K$ 开头（$1 \le N \le 5000$，$K \le N$），随后 $N$ 行，每行两个整数 $X$、$Y$ 表示一个目标点的坐标。所有坐标的绝对值不超过 $1000$。  
两个连续测试用例之间由空行分隔。  
以 `N = 0` 且 `K = 0` 表示输入结束，该行不应被处理。

## 输出格式

对每个测试用例，按格式 `Case #x: y` 输出最小面积，其中 $x$ 为用例编号（从 $1$ 开始），$y$ 为保留两位小数的浮点数。

## 样例

**样例输入**
```
3 1
0 1
1 0
-5 -6

3 2
0 2
2 0
-5 -6

0 0
```

**样例输出**
```
Case #1: 0.00
Case #2: 3.14
```

## 题目分析

扇形由圆心角 $\theta$（$0 \le \theta \le 2\pi$）和半径 $R \ge 0$ 唯一确定，其面积为  
$S = \frac{\theta}{2} R^2$。由于圆心固定为原点，扇形覆盖某个点当且仅当该点的极角落在扇形角度范围内且到原点的距离不超过 $R$。

对于任意一个最优扇形，其半径 $R$ 必等于某个被覆盖目标点到原点的距离。若 $R$ 严格大于所有被覆盖点的距离，则可以将 $R$ 缩小至这些点中距离最大值，面积减小且覆盖点数不变，因此最优解中 $R$ 必然等于某个目标点的距离。  
同样，扇形两条边界射线中至少有一条会经过某个目标点。若两条边界都不经过任何点，则可以旋转扇形使角度减小直到某条边界碰到一个点，面积降低且覆盖点数不变。

因此，最优解可被如下方式穷举：  
- 枚举半径 $R$ 的平方值（取每个目标点的距离平方）。  
- 在距离不超过 $R$ 的点集中，寻找覆盖至少 $K$ 个点的最小角度跨度 $\theta_{\min}$。  
- 则该半径下的候选面积为 $\frac{\theta_{\min}}{2} R^2$。  
取所有半径枚举中的最小值即为全局最优解。

注意 $K=0$ 时，任意空扇形（角度为 $0$，半径为 $0$）即满足要求，面积为 $0$，无需进行任何计算。

## 解题思路

**步骤 $\texttt{1}$.** 预处理所有目标点的极角和距离平方。极角使用 $\texttt{atan2}(y,x)$ 计算并调整至 $[0, 2\pi)$ 区间，距离平方用 $x^2+y^2$ 表示。

**步骤 $\texttt{2}$.** 按极角升序对所有点编号，用于后续筛选后快速获得角度排序序列；按距离平方升序对所有点编号，用于枚举半径。

**步骤 $\texttt{3}$.** 外层循环遍历不同的距离平方值 $R^2$（跳过重复值）。对于每个 $R^2$，筛选出所有距离平方不超过 $R^2$ 的点，这些点的极角天然保持升序（因为步骤 $\texttt{2}$ 中按极角排序的顺序在筛选后仍然不变）。

**步骤 $\texttt{4}$.** 对筛选出的极角数组执行双指针滑动窗口，求覆盖至少 $K$ 个点的最小角度跨度。  
由于角度具有周期性，将极角数组复制一份并整体加上 $2\pi$，得到长度为 $2M$ 的扩展数组（$M$ 为筛选后的点数）。在扩展数组上，左指针 $l$ 和右指针 $r$ 维护当前窗口，保证窗口内点数至少为 $K$，记录窗口角度跨度 $ext[r-1] - ext[l]$，并更新最小跨度。每当窗口内点数达到 $K$ 后，不断移动左指针缩小窗口，同时更新答案，直到点数不足 $K$。

**步骤 $\texttt{5}$.** 当前半径下的面积为 $(\text{最小跨度} / 2) \times R^2$，与全局答案取最小值。

**步骤 $\texttt{6}$.** 若 $K=0$，直接输出 $0.00$。

复杂度分析：外层枚举最多 $N$ 种不同半径，每次内部筛选和双指针扫描总时间复杂度为 $O(N)$，故整体时间复杂度为 $O(N^2)$。空间复杂度为 $O(N)$。$N \le 5000$ 时该复杂度可行。

## 代码实现

```cpp
// Fire-Control System
// UVa ID: 1432
// Verdict: Accepted
// Submission Date: 2026-07-16
// UVa Run Time: 0.200s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
const double PI = acos(-1.0);
struct Point {
    double ang;
    int d2;
};
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, K;
    int caseNo = 0;
    while (cin >> N >> K) {
        if (N == 0 && K == 0) break;
        ++caseNo;
        vector<Point> pts(N);
        for (int i = 0; i < N; ++i) {
            int x, y;
            cin >> x >> y;
            double a = atan2(y, x);
            if (a < 0) a += 2 * PI;
            pts[i].ang = a;
            pts[i].d2 = x * x + y * y;
        }
        if (K == 0) {
            cout << "Case #" << caseNo << ": ";
            cout << fixed << setprecision(2) << 0.00 << "\n";
            continue;
        }
        vector<int> idxAng(N);
        iota(idxAng.begin(), idxAng.end(), 0);
        sort(idxAng.begin(), idxAng.end(), [&](int a, int b) {
            return pts[a].ang < pts[b].ang;
        });
        vector<int> idxDist(N);
        iota(idxDist.begin(), idxDist.end(), 0);
        sort(idxDist.begin(), idxDist.end(), [&](int a, int b) {
            return pts[a].d2 < pts[b].d2;
        });
        double ans = 1e100;
        for (int i = 0; i < N; ++i) {
            int rIdx = idxDist[i];
            int R2 = pts[rIdx].d2;
            if (i > 0 && pts[idxDist[i - 1]].d2 == R2) continue;
            vector<double> angs;
            angs.reserve(N);
            for (int j = 0; j < N; ++j) {
                int pIdx = idxAng[j];
                if (pts[pIdx].d2 <= R2)
                    angs.push_back(pts[pIdx].ang);
            }
            int M = (int)angs.size();
            if (M < K) continue;
            vector<double> ext(2 * M);
            for (int j = 0; j < M; ++j) {
                ext[j] = angs[j];
                ext[j + M] = angs[j] + 2 * PI;
            }
            int left = 0, right = 0, cnt = 0;
            while (right < 2 * M) {
                while (right < 2 * M && cnt < K) {
                    ++cnt;
                    ++right;
                }
                if (cnt < K) break;
                while (cnt >= K) {
                    double width = ext[right - 1] - ext[left];
                    double area = (width / 2.0) * R2;
                    if (area < ans) ans = area;
                    --cnt;
                    ++left;
                }
            }
        }
        cout << "Case #" << caseNo << ": ";
        cout << fixed << setprecision(2) << ans << "\n";
    }
    return 0;
}
```

## 总结

本题的核心在于将扇形覆盖问题转化为“固定半径下的最小角度窗口”问题，并利用枚举半径和双指针滑动窗口进行求解。关键点包括：  
- 最优半径必为某个目标点的距离，因此只需枚举 $N$ 种候选半径。  
- 角度周期性的处理通过复制数组并加 $2\pi$ 实现。  
- 双指针算法在已排序的角度序列上高效求出最小覆盖窗口。  
- 特判 $K=0$ 可避免边界计算并直接得到答案。  
该解法时间复杂度 $O(N^2)$，在 $N=5000$ 的规模下运行良好，空间开销较小，代码实现简洁且易于理解。
