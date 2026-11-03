
> **摘要**：本题研究矩形台球桌内小球在弹性碰撞与恒定摩擦作用下的运动轨迹，给定桌面上的目标点，求轨迹到该点的最短距离。核心思路是**展开法**：将反射运动等价为无限平面上的直线运动，用周期性折叠函数把展开坐标映射回桌面坐标，从而把问题转化为分段二次函数的最小值求解。通过枚举折叠函数的转折点划分线性区间，在每个区间内用顶点公式求距离平方的最小值，最终得到精确到两位小数的答案。算法时间复杂度为 $O(K \log K)$（$K$ 为转折点数），实现简洁、精度可靠。

## 题目描述

在一个长 $a$ 英寸、宽 $b$ 英寸的台球桌上，一个小球从桌面的正中心出发，初始速率为 $v$ 英寸/秒，发射角为 $A$（$0^\circ \le A \le 90^\circ$），方向从水平方向逆时针测量。在第一次反弹之前，小球一直远离桌面的左下角运动。

球与桌边发生完全弹性碰撞（无能量损失），因此每次碰撞后平行于桌边的速度分量保持不变。但由于摩擦，小球以恒定减速度运动，并在 $s > 0$ 秒后完全停止。小球的半径视为零。注意，与普通台球桌不同，本题目中的台球桌没有球袋。

对于每个询问，给定桌面上一个点 $(x, y)$，求小球运动轨迹与该点的最短距离。

## 输入格式

输入包含若干行，每行七个非负整数，依次为：
$a$、$b$、$v$、$A$、$s$、$x$、$y$，满足：
$0 < a \le 100$，$0 < b \le 100$，$0 < v \le 100$，$0 \le A \le 90$，$0 < s \le 200$，$0 \le x \le a$，$0 \le y \le b$。

输入以一行七个零结束。

## 输出格式

对于每组有效输入，输出一行一个实数，表示小球运动轨迹与点 $(x, y)$ 的最短距离，精确到小数点后两位。

## 样例

**输入**
```
100 50 10 90 10 0 0
100 100 10 45 15 0 0
100 100 10 30 200 31 48
0 0 0 0 0 0 0
```

**输出**
```
55.90
70.71
2.04
```

## 题目分析

小球在矩形台球桌内运动，与桌边发生弹性碰撞，因此可以等价为“展开法”：将小球在矩形内的反射运动展开为在无限平面上的直线运动。具体而言，若将矩形反复镜像翻折，则小球在矩形内的轨迹对应为一条从起点出发、沿初始方向的直线，而矩形内的真实位置可由直线上的点沿两个坐标方向分别折叠（$ \text{fold} $）得到。

小球运动过程中同时受到恒定摩擦力，因此速率随时间线性减小，直到停止。由于初始速度为 $v$，减速度为常数，停止时间为 $s$，故总运动路程为 $L = \frac{1}{2} v s$（因为 $v = a_{\text{dec}} s$，路程 $= \frac{1}{2} a_{\text{dec}} s^2 = \frac{1}{2} v s$）。

因此，小球轨迹可参数化为参数 $t$（$0 \le t \le s$）或路径长度 $l$（$0 \le l \le L$）。在任意时刻，小球在展开平面中的位置为：
$$
(X(l), Y(l)) = \left( \frac{a}{2} + l \cos A, \frac{b}{2} + l \sin A \right)
$$
而实际桌面上对应的坐标为：
$$
(f_x(X(l)), f_y(Y(l))) = (\text{fold}(X(l), a), \text{fold}(Y(l), b))
$$
其中 $\text{fold}(z, L)$ 将 $z$ 映射到区间 $[0, L]$，定义为
$$
\text{fold}(z, L) = 
\begin{cases}
z \bmod (2L), & \text{若 } z \bmod (2L) \le L, \\
2L - (z \bmod (2L)), & \text{否则}.
\end{cases}
$$
（当余数恰好等于 $L$ 时，两种表示均可，此时小球在边界上。）

于是问题转化为：求函数
$$
D(l) = \sqrt{ \left( \text{fold}\left(\frac{a}{2} + l \cos A, a\right) - x \right)^2 + \left( \text{fold}\left(\frac{b}{2} + l \sin A, b\right) - y \right)^2 }
$$
在区间 $[0, L]$ 上的最小值。

折叠函数是分段线性的，因此 $D^2(l)$ 在每个由转折点划分的子区间内是一个二次函数（开口向上）。所以最小值只可能出现在子区间端点或该二次函数的顶点处。因此，我们只需找出所有转折点（即展开直线与水平或垂直镜像边界相交的位置），在相邻转折点间检查二次函数的最小值即可。

## 解题思路

### 转折点的确定

展开直线 $X(l)$ 与垂直镜像边界 $X = k a$（$k$ 为整数）相交时，折叠函数的斜率发生改变。同理，$Y(l) = n b$ 处为水平方向的转折点。

对于 $X(l)$，当 $\cos A > 0$ 时（题目中 $A$ 可取 $90^\circ$，此时 $\cos A = 0$，需特殊处理），交点对应的 $l$ 满足
$$
\frac{a}{2} + l \cos A = k a \quad \Rightarrow \quad l = \frac{k a - a/2}{\cos A}.
$$
由于 $l \in [0, L]$，且 $k$ 为整数，只需枚举所有满足 $0 \le l \le L$ 的 $k$ 即可。类似地，对于 $Y(l)$，当 $\sin A > 0$ 时，$l = \frac{n b - b/2}{\sin A}$，$n$ 为整数。

将所有这样的 $l$ 值收集起来，并按升序排序，去重后得到一系列分界点 $p_0 = 0 < p_1 < \dots < p_m = L$（需将 $0$ 和 $L$ 加入）。在每个区间 $[p_i, p_{i+1}]$ 内，$\text{fold}(X(l), a)$ 和 $\text{fold}(Y(l), b)$ 各自是 $l$ 的线性函数（斜率为 $+\cos A$ 或 $-\cos A$ 等），因此 $D^2(l)$ 是一个开口向上的二次函数。

### 二次函数最小值的计算

在区间 $[p_i, p_{i+1}]$ 内，设：
$$
f_x(l) = s_x \cdot (l \cos A) + c_x, \quad f_y(l) = s_y \cdot (l \sin A) + c_y
$$
其中 $s_x, s_y \in \{+1, -1\}$ 为折叠后的斜率符号，$c_x, c_y$ 为常数。于是
$$
D^2(l) = (s_x l \cos A + c_x - x)^2 + (s_y l \sin A + c_y - y)^2.
$$
展开后得：
$$
D^2(l) = (\cos^2 A + \sin^2 A) l^2 + 2 \left[ s_x \cos A (c_x - x) + s_y \sin A (c_y - y) \right] l + \text{const}
= l^2 + 2 B l + C.
$$
其中
$$
B = s_x \cos A (c_x - x) + s_y \sin A (c_y - y).
$$
该二次函数的最小值在 $l_{\text{opt}} = -B$ 处取得。若 $l_{\text{opt}} \in [p_i, p_{i+1}]$，则计算该点处的 $D^2$；否则，最小值在区间端点取得（端点已经在相邻区间或初始时计算）。

### 端点与边界的处理

- 当 $\cos A = 0$ 时，$X(l) = a/2$ 恒定，无 $X$ 方向的转折点，只需处理 $Y$ 方向的转折点即可。此时 $f_x(l)$ 始终为常数，不影响二次项的系数。
- 类似地，当 $\sin A = 0$ 时，只需处理 $X$ 方向的转折点。

- 在转折点处（$l = p_i$），左右两侧的折叠函数可能连续但斜率改变。由于我们检查每个闭区间，转折点的值在相邻区间端点中会被重复计算，不会遗漏。

### 算法步骤

1. 读入每组数据，若全为零则终止。
2. 计算 $L = \frac{1}{2} v s$，起点 $(X_0, Y_0) = (a/2, b/2)$。
3. 构造转折点列表 `breaks`，初始包含 $0$ 和 $L$。
4. 若 $\cos A > \epsilon$（$\epsilon$ 为很小正数），枚举整数 $k$ 满足 $1 \le k \le \lfloor (X_0 + L \cos A)/a \rfloor + 2$，计算 $l = (k a - X_0)/\cos A$，若 $0 \le l \le L$ 则加入。
5. 若 $\sin A > \epsilon$，枚举整数 $n$ 满足 $1 \le n \le \lfloor (Y_0 + L \sin A)/b \rfloor + 2$，计算 $l = (n b - Y_0)/\sin A$，若 $0 \le l \le L$ 则加入。
6. 对 `breaks` 排序并去重（相邻差小于 $10^{-8}$ 视为相同）。
7. 遍历相邻点对 $[p_i, p_{i+1}]$：
   - 取中点 $l_m = (p_i + p_{i+1})/2$，计算 $X_m = X_0 + l_m \cos A$，$Y_m = Y_0 + l_m \sin A$。
   - 确定 $X_m$ 所在折叠区间，得到 $s_x$：若 $X_m$ 折叠后落在 $[0, a)$ 内，则 $s_x = +1$；若在 $(a, 2a]$ 内（展开后），则 $s_x = -1$。更简单的判断方法：比较 $\text{fold}(X_m, a)$ 与 $X_m - 2a\lfloor X_m/(2a)\rfloor$ 的关系，但可直接通过检查 $X_m$ 除以 $2a$ 的余数是否小于 $a$ 来决定。当余数恰为 $a$ 时，此时 $X_m$ 在边界上，但区间内不会包含边界（因为边界已作为分界点），故取任意符号均可，但为了稳定，可令 $s_x = +1$（或 $-1$）不影响最终结果。
   - 同理得到 $s_y$。
   - 计算常数 $c_x = \text{fold}(X_m, a) - s_x \cdot X_m$，$c_y = \text{fold}(Y_m, b) - s_y \cdot Y_m$。由于在区间内折叠函数为线性，该常数在该区间内不变。
   - 计算 $B = s_x \cos A (c_x - x) + s_y \sin A (c_y - y)$，$l_{\text{opt}} = -B$。
   - 若 $l_{\text{opt}}$ 在 $[p_i, p_{i+1}]$ 内，则计算该点处的距离平方；否则取两端点的距离平方。
   - 更新全局最小距离平方。

8. 输出最小距离的平方根，保留两位小数。

### 正确性说明

- 展开法将反射运动等价为直线运动，折叠函数准确给出实际桌面上坐标。
- 折叠函数在每个由镜像边界划分的区间内是线性的，因此目标函数 $D^2(l)$ 在每个区间内为二次函数，其最小值要么在顶点要么在端点。
- 我们枚举了所有可能的转折点，保证了每个线性区间都被覆盖，因此算法能遍历到所有候选最小值点。
- 由于摩擦使速度线性减小，路径长度参数 $l$ 与时间一一对应，且总长度有限，故问题有界。

### 复杂度分析

设总路径长度为 $L$，水平方向和垂直方向的转折点数量约为 $\frac{L \cos A}{a}$ 和 $\frac{L \sin A}{b}$ 量级。由于输入范围较小（$a,b,v,s \le 200$ 以内），$L \le \frac{1}{2} \cdot 100 \cdot 200 = 10000$，因此转折点数不超过 $O(10000)$ 级别。排序去重后，遍历相邻区间，每个区间计算 $O(1)$，总时间复杂度为 $O(K \log K)$，其中 $K$ 为转折点数。实际运行效率极高。

空间复杂度为 $O(K)$。

## 代码实现

```cpp
// Billiard Again
// UVa ID: 10899
// Verdict: Accepted
// Submission Date: 2026-07-13
// UVa Run Time: 0.010s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const double PI = acos(-1.0);
const double EPS = 1e-9;

// 折叠函数：将展开坐标 z 映射回 [0, L] 区间
double fold(double z, double L) {
    double period = 2.0 * L;
    double mod = fmod(z, period);
    if (mod < 0) mod += period;       // 保证非负
    if (mod <= L) return mod;
    return period - mod;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(2);

    int a_int, b_int, v_int, A_int, s_int, x_int, y_int;
    while (cin >> a_int >> b_int >> v_int >> A_int >> s_int >> x_int >> y_int) {
        if (a_int == 0 && b_int == 0 && v_int == 0 && A_int == 0 && s_int == 0 && x_int == 0 && y_int == 0)
            break;

        double a = a_int, b = b_int, v = v_int, s = s_int;
        double x = x_int, y = y_int;
        double A = A_int * PI / 180.0;
        double cosA = cos(A), sinA = sin(A);

        double X0 = a / 2.0, Y0 = b / 2.0;
        double Lmax = v * s / 2.0;          // 总位移长度

        vector<double> bp;
        bp.push_back(0.0);
        bp.push_back(Lmax);

        // x 方向转折点：X0 + l*cosA = k*a
        if (cosA > EPS) {
            double left = X0 / a;           // k 的最小值，k>=1
            int kMin = max(1, (int)ceil(left - EPS));
            double right = (X0 + Lmax * cosA) / a;
            int kMax = (int)floor(right + EPS) + 2; // 多取几个确保覆盖
            for (int k = kMin; k <= kMax; ++k) {
                double l = (k * a - X0) / cosA;
                if (l >= -EPS && l <= Lmax + EPS)
                    bp.push_back(l);
            }
        }

        // y 方向转折点：Y0 + l*sinA = n*b
        if (sinA > EPS) {
            double left = Y0 / b;
            int nMin = max(1, (int)ceil(left - EPS));
            double right = (Y0 + Lmax * sinA) / b;
            int nMax = (int)floor(right + EPS) + 2;
            for (int n = nMin; n <= nMax; ++n) {
                double l = (n * b - Y0) / sinA;
                if (l >= -EPS && l <= Lmax + EPS)
                    bp.push_back(l);
            }
        }

        // 排序去重
        sort(bp.begin(), bp.end());
        vector<double> pts;
        for (double p : bp) {
            if (pts.empty() || p - pts.back() > 1e-8)
                pts.push_back(p);
        }

        double minD2 = 1e100;

        // 遍历每个区间 [pts[i], pts[i+1]]
        for (size_t i = 0; i + 1 < pts.size(); ++i) {
            double l1 = pts[i], l2 = pts[i + 1];
            if (l2 - l1 < EPS) continue;

            double lmid = (l1 + l2) / 2.0;
            double zx = X0 + lmid * cosA;
            double zy = Y0 + lmid * sinA;

            // 确定 x 方向折叠斜率
            double modx = fmod(zx, 2.0 * a);
            if (modx < 0) modx += 2.0 * a;
            int signX = (modx < a || fabs(modx - a) < EPS) ? 1 : -1; // 在转折点附近，但区间内不会正好在转折点

            double mody = fmod(zy, 2.0 * b);
            if (mody < 0) mody += 2.0 * b;
            int signY = (mody < b || fabs(mody - b) < EPS) ? 1 : -1;

            // 计算偏移量，使得 fold = sign * (X0 + l*cosA) + offset
            double foldX_mid = fold(zx, a);
            double foldY_mid = fold(zy, b);
            double offsetX = foldX_mid - signX * (X0 + lmid * cosA);
            double offsetY = foldY_mid - signY * (Y0 + lmid * sinA);

            // 距离平方函数 D2(l) = (signX*(X0+l*cosA)+offsetX - x)^2
            //                        + (signY*(Y0+l*sinA)+offsetY - y)^2
            // 展开为 l^2 + 2*B*l + C
            double B = signX * cosA * (signX * X0 + offsetX - x)
                     + signY * sinA * (signY * Y0 + offsetY - y);
            // 顶点 l_opt = -B (因为二次项系数为1)
            double lOpt = -B;

            // 检查顶点是否在区间内
            double cand_l;
            if (lOpt >= l1 && lOpt <= l2)
                cand_l = lOpt;
            else {
                // 否则取两端点中较小的
                double d1 = pow(fold(X0 + l1 * cosA, a) - x, 2)
                          + pow(fold(Y0 + l1 * sinA, b) - y, 2);
                double d2 = pow(fold(X0 + l2 * cosA, a) - x, 2)
                          + pow(fold(Y0 + l2 * sinA, b) - y, 2);
                minD2 = min(minD2, min(d1, d2));
                continue;
            }

            // 计算候选点的距离平方
            double Xc = X0 + cand_l * cosA;
            double Yc = Y0 + cand_l * sinA;
            double dx = fold(Xc, a) - x;
            double dy = fold(Yc, b) - y;
            double d2 = dx * dx + dy * dy;
            minD2 = min(minD2, d2);
        }

        double ans = sqrt(max(0.0, minD2));
        cout << ans << "\n";
    }

    return 0;
}
```

## 总结

本题是一道经典的反射运动与最值优化问题，核心技巧是**展开法**将碰撞边界转化为周期性折叠函数，从而将轨迹转化为直线段。通过枚举折叠函数的转折点，将连续优化问题简化为分段二次函数的最小值求解，降低了计算难度。

关键点：
- 利用物理规律计算总路程 $L = \frac{1}{2} v s$。
- 折叠函数的定义和转折点枚举方法。
- 在每个线性区间内，距离平方函数为二次函数，可以直接用顶点公式求最小值。
- 注意边界条件（如角度为 $0^\circ$ 或 $90^\circ$）的特殊处理。

该解法时间复杂度低，精度满足题目要求，是一种通用且高效的处理台球反射轨迹最短距离问题的方法。
