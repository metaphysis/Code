
> **摘要**：本题给定一条线段移动前后的端点坐标，要求判断该线段是绕某点逆时针旋转还是沿向量平移，并输出对应的平移向量或旋转中心与角度。核心思路是比较移动前后端点构成的向量：方向不变则为平移（位移为零时输出 `No move.`），方向改变则为旋转，通过叉积与点积求出旋转角度，再由旋转矩阵构造线性方程组解出旋转中心。每组输入仅需常数次运算，时间复杂度 $O(1)$。

## 题目描述

平面上给定一条线段，由其端点 $a = (a_x, a_y)$ 与 $b = (b_x, b_y)$ 确定，且 $a \neq b$。该线段经过一次移动：要么绕平面上某一点进行逆时针旋转，要么沿某一向量平移。已知移动后两端点的坐标分别为 $a' = (a'_x, a'_y)$ 与 $b' = (b'_x, b'_y)$，其中 $a'$ 对应原端点 $a$，$b'$ 对应原端点 $b$。要求判断该线段是被旋转还是平移，并输出相应结果。

## 输入格式

输入包含多行，每行有 $8$ 个浮点数，依次为 $a_x, a_y, a'_x, a'_y, b_x, b_y, b'_x, b'_y$。一行中 $8$ 个数全为 $0$ 时表示输入结束，该行不处理。

## 输出格式

对于每组输入，输出一行结果。浮点数保留 $1$ 位小数。若为平移，输出形如 `Translation by vector <tx,ty>.`；若为旋转，输出形如 `Rotation around (cx,cy) by angle degrees counterclockwise.`。旋转角度应归一化到 $[0, 360^\circ)$。若线段位置完全没有改变，则输出 `No move.`。

## 样例

**输入**
```text
0 2 1 3 2 0 3 1
0 2 2 0 1 3 3 1
2.1 0 0 2.1 3 1 -1 3
2.1 0 2.9238080804 0.7366059011 0 2.1 -0.0347392304 0.9954452513
5 1 2 -2 10 1 2 -7
1 17 1 17 -14 -14 -14 -14
0 0 0 0 0 0 0 0
```

**输出**
```text
Translation by vector <1.0,1.0>.
Translation by vector <2.0,-2.0>.
Rotation around (0.0,0.0) by 90.0 degrees counterclockwise.
Rotation around (1.5,1.5) by 40.0 degrees counterclockwise.
Rotation around (2.0,1.0) by 270.0 degrees counterclockwise.
No move.
```

## 题目分析

本题的核心是通过比较移动前后的端点坐标，推断移动类型。线段在平面中的任何刚性运动（平移或旋转）都保持两点间的距离不变，但平移会保持所有向量的方向不变，而旋转会改变方向。因此可利用移动前后对应端点构成的向量来区分这两种运动。

定义原始向量 $\mathbf{v} = b - a = (v_x, v_y)$，移动后的向量 $\mathbf{v}' = b' - a' = (v'_x, v'_y)$。若线段发生平移，则整个线段沿同一向量移动，因此 $\mathbf{v}'$ 与 $\mathbf{v}$ 完全相同（长度和方向均不变）。若发生旋转（旋转角度非零），则 $\mathbf{v}'$ 的长度不变但方向改变，故 $\mathbf{v}' \neq \mathbf{v}$。特别地，若旋转角度为 $0^\circ$ 或 $360^\circ$，则线段位置不变，可视为未移动，此时亦满足 $\mathbf{v}'=\mathbf{v}$。

因此，首先比较 $\mathbf{v}'$ 与 $\mathbf{v}$ 的差值是否小于阈值。若相等，则属于平移或静止；否则为旋转。

对于平移情形，位移向量即为 $\mathbf{t} = a' - a = (t_x, t_y)$。若 $\mathbf{t}$ 为零向量，则线段未移动；否则输出平移向量。

对于旋转情形，需要计算旋转角度 $\theta$ 以及旋转中心 $c$。旋转角度可由向量 $\mathbf{v}$ 到 $\mathbf{v}'$ 的夹角获得，使用叉积与点积通过 $\operatorname{atan2}$ 函数求得。角度需归一化到非负且小于 $360^\circ$。旋转中心满足方程 $a' - c = R_\theta (a - c)$，其中 $R_\theta$ 为旋转矩阵。整理为线性方程组 $(I - R_\theta)c = a' - R_\theta a$，解此方程组即可得到中心坐标。由于旋转角度非零，系数矩阵可逆，解唯一。

## 解题思路

规则 $\texttt{1}$. 读入每组 $8$ 个浮点数，若全为零则终止。  
规则 $\texttt{2}$. 计算原始向量 $\mathbf{v} = (b_x - a_x,\ b_y - a_y)$ 和新向量 $\mathbf{v}' = (b'_x - a'_x,\ b'_y - a'_y)$，以及位移 $\mathbf{t} = (a'_x - a_x,\ a'_y - a_y)$。  
规则 $\texttt{3}$. 若 $\|\mathbf{v}' - \mathbf{v}\| < 10^{-8}$，则判定为平移或静止。进一步判断 $\|\mathbf{t}\| < 10^{-8}$，若成立则输出 `No move.`，否则输出平移向量。  
规则 $\texttt{4}$. 否则判定为旋转。计算叉积 $\text{cross} = v_x v'_y - v_y v'_x$ 与点积 $\text{dot} = v_x v'_x + v_y v'_y$，求得 $\theta = \operatorname{atan2}(\text{cross},\text{dot})$。将弧度转换为角度，若为负则加 $360^\circ$。  
规则 $\texttt{5}$. 计算旋转矩阵元素 $\cos\theta$ 与 $\sin\theta$，构造 $d = a' - R_\theta a$ 以及系数矩阵 $M = I - R_\theta$。解二元一次方程组 $M c = d$，得到中心 $(c_x, c_y)$。  
规则 $\texttt{6}$. 对中心坐标进行零值修正（绝对值小于 $10^{-8}$ 置零），以避免输出 `-0.0`。  
规则 $\texttt{7}$. 按格式输出结果。

复杂度分析：每组输入仅涉及常数次算术运算，时间复杂度为 $O(1)$，空间复杂度为 $O(1)$。

## 代码实现

```cpp
// Translation or Rotation
// UVa ID: 10760
// Verdict: Accepted
// Submission Date: 2026-07-17
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-8;

bool isZero(double x) {
    return fabs(x) < EPS;
}

int main() {
    double ax, ay, apx, apy, bx, by, bpx, bpy;
    while (scanf("%lf%lf%lf%lf%lf%lf%lf%lf", &ax, &ay, &apx, &apy, &bx, &by, &bpx, &bpy) == 8) {
        if (isZero(ax) && isZero(ay) && isZero(apx) && isZero(apy) &&
            isZero(bx) && isZero(by) && isZero(bpx) && isZero(bpy)) break;
        double vx = bx - ax, vy = by - ay;
        double vpx = bpx - apx, vpy = bpy - apy;
        double tx = apx - ax, ty = apy - ay;
        if (fabs(vx - vpx) < EPS && fabs(vy - vpy) < EPS) {
            if (fabs(tx) < EPS && fabs(ty) < EPS) printf("No move.\n");
            else printf("Translation by vector <%.1f,%.1f>.\n", tx, ty);
        } else {
            double cross = vx * vpy - vy * vpx;
            double dot = vx * vpx + vy * vpy;
            double angleRad = atan2(cross, dot);
            double angleDeg = angleRad * 180.0 / acos(-1.0);
            if (angleDeg < 0.0) angleDeg += 360.0;
            double cosA = cos(angleRad), sinA = sin(angleRad);
            double d_x = apx - (cosA * ax - sinA * ay);
            double d_y = apy - (sinA * ax + cosA * ay);
            double det = (1.0 - cosA) * (1.0 - cosA) + sinA * sinA;
            double c_x = ((1.0 - cosA) * d_x - sinA * d_y) / det;
            double c_y = (sinA * d_x + (1.0 - cosA) * d_y) / det;
            if (fabs(c_x) < EPS) c_x = 0.0;
            if (fabs(c_y) < EPS) c_y = 0.0;
            printf("Rotation around (%.1f,%.1f) by %.1f degrees counterclockwise.\n", c_x, c_y, angleDeg);
        }
    }
    return 0;
}
```

## 总结

本题是计算几何中的基础分类问题，核心在于利用向量长度与方向在平移与旋转中的不同表现来区分运动类型。处理浮点数时需注意精度阈值的设定，以及角度与中心坐标的归一化与误差修正。旋转中心的求解利用了旋转矩阵的代数性质，将几何问题转化为线性方程组的解析解，避免了迭代或复杂几何构造。输出格式的严格要求（保留一位小数、句点结尾）亦需细心处理。该解法简洁高效，适用于所有合法输入。
