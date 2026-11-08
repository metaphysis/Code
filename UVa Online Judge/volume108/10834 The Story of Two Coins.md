
> **摘要**：本文讨论两枚硬币在二维平面上的滚动问题——半径为 $R$ 的定圆与半径为 $r$ 的动圆相切滚动，给定动圆上一点 $T$ 的坐标，求动圆最高点 $P$ 的两个可能位置。文章将滚动分解为公转与自转，把问题转化为两圆交点求解，利用向量点积与垂直向量表达交点、用 $\operatorname{atan2}$ 排序确定时间先后，最终以 $O(1)$ 复杂度给出 $\texttt{C++}$ 实现。

## 题目描述

本题中，有两枚硬币（完美圆形）位于二维平面上。第一枚硬币半径为 $R$，固定不动，其圆心 $Q$ 位于原点 $(0,0)$。第二枚硬币半径为 $r$，像轮子一样沿第一枚硬币的圆周逆时针滚动，同时沿第一枚硬币的表面逆时针移动。当第二枚硬币恰好绕第一枚硬币旋转一周后停止。

开始时，第二枚硬币的圆心 $O$ 位于 $x$ 轴正方向，坐标为 $(R+r,0)$。此时点 $P$ 是第二枚硬币的最高点，坐标为 $(R+r,r)$。随着硬币滚动，$P$ 的位置会因圆周平动和自身旋转而改变。对于第二枚硬币圆周上的任意一点 $T$，给定其坐标 $(x,y)$，需要确定可能存在的两个硬币位置，并分别求出对应位置下 $P$ 的坐标。

## 输入格式

输入文件包含最多 $1000$ 行。每行包含两个正整数 $R$、$r$（$0<|r|\le |R|<1000$）和两个浮点数 $x$、$y$（$0<|x|,|y|<4000.0$）。所有浮点数小数点后均有十五位数字。输入以一行 $R=0$ 且 $r=0$ 结束，该行不应被处理。

## 输出格式

对于每组输入，输出三行或两行。第一行为当前用例的序号，格式为 `Case X:`。接下来两行分别输出两个可能位置下点 $P$ 的坐标。坐标按时间顺序输出（先到达的位置先输出）。若无法找到 $P$ 的坐标，则输出 `IMPOSSIBLE`。所有浮点数四舍五入保留三位小数。

## 样例

输入

```
5 5 10.000000000000000 3.000000000000000
5 5 20.000000000000000 10.000000000000000
0 0 0.000000000000000 0.000000000000000
```

输出

```
Case 1:
2.082 7.076
11.755 2.606
Case 2:
IMPOSSIBLE
```

## 题目分析

第二枚硬币在滚动过程中，其圆心 $O$ 始终位于以原点为圆心、半径为 $a=R+r$ 的圆上。设公转角为 $\theta$（从 $x$ 轴正方向逆时针度量），则圆心坐标为  
$$
O = (a\cos\theta,\; a\sin\theta).
$$

硬币做无滑动滚动，因此自转角速度与公转角速度之比等于 $(R+r)/r$。初始时点 $P$ 相对于圆心的极角为 $\pi/2$，经过公转角 $\theta$ 后，点 $P$ 的绝对极角为  
$$
\alpha = \frac{\pi}{2} + \frac{a}{r}\theta.
$$  
于是 $P$ 的坐标可表示为  
$$
P = O + r(\cos\alpha,\; \sin\alpha).
$$

给定点 $T=(x,y)$，它必须位于动圆上，即满足  
$$
|T-O| = r.
$$  
结合 $|O|=a$，可知 $O$ 是两圆的交点：
- 一个圆以原点为圆心，半径 $a$；
- 另一个圆以 $T$ 为圆心，半径 $r$。

两圆最多有两个交点，每个交点对应一个 $\theta$ 值，从而对应一个 $P$ 的位置。因此，问题转化为求这两个交点并计算对应的 $P$。

## 解题思路

### 1. 几何关系与交点求解

令 $a = R+r$，$d = |T| = \sqrt{x^2+y^2}$。根据两圆交点条件，有  
$$
|O|^2 = a^2,\quad |O-T|^2 = r^2.
$$  
展开第二个式子得  
$$
|O|^2 + |T|^2 - 2O\cdot T = r^2.
$$  
代入 $|O|^2 = a^2$，得到  
$$
O\cdot T = \frac{a^2 + d^2 - r^2}{2} = c.
$$

设 $\mathbf{u} = T/d$ 为 $T$ 方向的单位向量，$\mathbf{v} = (-u_y,\; u_x)$ 为垂直于 $\mathbf{u}$ 的单位向量。则满足上述点积条件的点 $O$ 可表示为  
$$
O = \frac{c}{d}\mathbf{u} \pm h\,\mathbf{v},
$$  
其中  
$$
h = \sqrt{a^2 - \left(\frac{c}{d}\right)^2}.
$$  
若 $h^2 < 0$（即 $\left|\frac{c}{d}\right| > a$），则两圆无交点，输出 `IMPOSSIBLE`。

### 2. 角度排序与时间顺序

每个交点 $O_i$ 对应一个公转角 $\theta_i = \operatorname{atan2}(O_{i_y}, O_{i_x})$。由于硬币沿逆时针方向滚动，公转角随时间单调增加，因此时间顺序即 $\theta$ 递增顺序。将两个 $\theta$ 归一化到 $[0,2\pi)$ 后按升序排列，即可确定先后顺序。

### 3. 计算点 $P$ 的坐标

对于每个有效交点 $O_i$ 及其对应的 $\theta_i$，计算  
$$
\alpha_i = \frac{\pi}{2} + \frac{a}{r}\theta_i,
$$  
$$
P_i = O_i + r(\cos\alpha_i,\; \sin\alpha_i).
$$  
输出时保留三位小数。

### 4. 精度与边界

题目保证输入不会出现只有一个交点的情况（即两圆不相切），也避免因精度误差导致输出歧义。使用双精度浮点数计算即可。圆周率取 $\pi = 2\cos^{-1}(0)$。

### 复杂度分析

每组输入仅进行常数次三角函数、开方和四则运算，时间复杂度 $O(1)$。空间复杂度 $O(1)$。

## 代码实现

```cpp
// The Story of Two Coins
// UVa ID: 10834
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const double PI = acos(-1.0);

// 将角度归一化到 [0, 2*PI)
double normAngle(double th) {
    while (th < 0) th += 2 * PI;
    while (th >= 2 * PI) th -= 2 * PI;
    return th;
}

int main() {
    int R, r;
    double x, y;
    int caseNo = 0;
    while (cin >> R >> r >> x >> y) {
        if (R == 0 && r == 0) break;
        ++caseNo;
        double a = R + r;               // 圆心轨迹半径
        double d = hypot(x, y);         // |T|
        // 计算 c = O·T
        double c = (a * a + d * d - r * r) / 2.0;
        double p = c / d;               // O 在 T 方向上的投影长度
        double h2 = a * a - p * p;
        if (h2 < -1e-12) {              // 无解
            cout << "Case " << caseNo << ":\n";
            cout << "IMPOSSIBLE\n";
            continue;
        }
        double h = sqrt(max(0.0, h2));
        double ux = x / d, uy = y / d;
        double vx = -uy, vy = ux;       // 垂直单位向量
        // 两个圆心
        double Ox1 = p * ux + h * vx, Oy1 = p * uy + h * vy;
        double Ox2 = p * ux - h * vx, Oy2 = p * uy - h * vy;
        // 对应的角度
        double theta1 = normAngle(atan2(Oy1, Ox1));
        double theta2 = normAngle(atan2(Oy2, Ox2));
        // 按时间顺序（角度升序）排列
        if (theta1 > theta2) {
            swap(theta1, theta2);
            swap(Ox1, Ox2);
            swap(Oy1, Oy2);
        }
        double ratio = a / r;           // (R+r)/r
        // 计算P
        auto calcP = [&](double theta, double Ox, double Oy) {
            double alpha = PI / 2.0 + ratio * theta;
            double Px = Ox + r * cos(alpha);
            double Py = Oy + r * sin(alpha);
            return make_pair(Px, Py);
        };
        auto p1 = calcP(theta1, Ox1, Oy1);
        auto p2 = calcP(theta2, Ox2, Oy2);
        cout << "Case " << caseNo << ":\n";
        cout << fixed << setprecision(3) << p1.first << " " << p1.second << "\n";
        cout << fixed << setprecision(3) << p2.first << " " << p2.second << "\n";
    }
    return 0;
}
```

## 总结

本题核心是几何建模与坐标变换。通过将硬币的滚动分解为公转和自转，将问题转化为两圆交点求解。关键技巧包括：
- 利用向量点积和垂直向量表达交点；
- 使用 $\operatorname{atan2}$ 获得角度并按序输出；
- 注意浮点数误差处理。

该解法简洁高效，复杂度为 $O(1)$，适用于题目限制的数据规模。
