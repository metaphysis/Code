## 题目描述

在一个二元动态生态系统中，兔子和狐狸的数量变化遵循如下差分方程：

$$
\begin{cases}
h_{y+1} = a \cdot h_y - b \cdot f_y \\
f_{y+1} = d \cdot h_y + c \cdot f_y
\end{cases}
$$

其中 $h_y$ 和 $f_y$ 分别表示第 $y$ 年兔子和狐狸的数量相对于实验开始时的参考值的偏差，它们均为实数。给定系数 $a,b,c,d$ 以及初始偏差 $h_{1998}, f_{1998}$，要求判定该系统的长期演化趋势。

## 输入格式

输入包含 $N$ 个测试用例。第一行为正整数 $N$。接下来每个用例由六个实数 $a,b,c,d,h_{1998},f_{1998}$ 组成，按顺序分三行给出，每行两个数，数字之间用空格分隔。每个数字的文本长度不超过 $10$ 个字符，符合常规实数格式（可选符号、数字序列、可选小数点及可选小数序列）。每个用例后跟一个空行。

## 输出格式

对于每个用例，输出以下句子之一（严格匹配英文原句，包括标点和大小写）：

- `Ecological balance will develop.`  
  表示 $\lim h_y = 0$ 且 $\lim f_y = 0$。

- `Hares will die out while foxes will overgrow.`  
  表示 $\lim h_y = -\infty$ 且 $\lim f_y = +\infty$。

- `Hares will overgrow while foxes will die out.`  
  表示 $\lim h_y = +\infty$ 且 $\lim f_y = -\infty$。

- `Both hares and foxes will die out.`  
  表示 $\lim h_y = -\infty$ 且 $\lim f_y = -\infty$。

- `Both hares and foxes will overgrow.`  
  表示 $\lim h_y = +\infty$ 且 $\lim f_y = +\infty$。

- `Chaos will develop.`  
  表示上述五种情形均不成立。

## 样例

输入

```
2
2 0.5
0.5 0.6
2 3

0.1 1
2 0.1
1 1
```

输出

```
Both hares and foxes will overgrow.
Hares will die out while foxes will overgrow.
```

## 题目分析

将系统写成矩阵形式：

$$
\mathbf{v}_{y+1} = A \mathbf{v}_y, \quad
\mathbf{v}_y = \begin{bmatrix} h_y \\ f_y \end{bmatrix}, \quad
A = \begin{bmatrix} a & -b \\ d & c \end{bmatrix}.
$$

于是 $\mathbf{v}_y = A^y \mathbf{v}_0$，其中 $\mathbf{v}_0 = (h_{1998}, f_{1998})^\mathsf{T}$。系统的长期行为完全由矩阵 $A$ 的特征值 $\lambda_1, \lambda_2$ 决定。

设特征值为 $\lambda$，则其特征多项式为：

$$
\lambda^2 - (a+c)\lambda + (ac + bd) = 0.
$$

记迹 $\tau = a+c$，行列式 $\Delta = ac + bd$，判别式 $D = \tau^2 - 4\Delta$。

- 若 $D < 0$，特征值为共轭复数 $\lambda = \alpha \pm \mathrm{i}\beta$，模长为 $\sqrt{\Delta}$。此时系统表现为旋转与缩放。若模长小于 $1$，则收敛至零（平衡）；否则不会收敛至零也不会发散至无穷，属于混沌。
- 若 $D \ge 0$，特征值为实数。若两个特征值的模都小于 $1$，则系统收敛至零（平衡）。若某个特征值的模大于 $1$，则系统沿该特征向量方向发散。若模等于 $1$，则系统既不收敛也不发散，属于混沌。
- 当两个特征值模均大于 $1$ 时，取模较大的那个作为主导方向。若主导特征值为负数，则序列符号交替，无确定极限，判为混沌。若为正数，则长期极限符号由初始向量在对应特征向量上的投影系数决定。

因此，判定算法的核心是准确计算特征值、特征向量以及投影系数，并处理好各种边界情况（如重根、投影为零、模恰为 $1$ 等）。

## 解题思路

### 特征值计算

对于每个用例，计算 $\tau = a+c$，$\Delta = ac + bd$，$D = \tau^2 - 4\Delta$。

- 若 $|D| < \epsilon$（$\epsilon$ 为极小阈值），视为重根，$\lambda_1 = \lambda_2 = \tau/2$。
- 否则，若 $D < 0$，按复数处理。
- 否则，计算 $\lambda_{1,2} = \frac{\tau \pm \sqrt{D}}{2}$。

### 判定规则

1. **复数特征值**：模长 $r = \sqrt{\Delta}$。若 $r < 1 - \epsilon$，输出“平衡”；否则输出“混沌”。

2. **实数特征值**：
   - 若 $|\lambda_1| < 1 - \epsilon$ 且 $|\lambda_2| < 1 - \epsilon$，输出“平衡”。
   - 若任一特征值的模在 $[1-\epsilon, 1+\epsilon]$ 内，输出“混沌”（因为无法确定极限）。
   - 若两个模都大于 $1+\epsilon$，则需进一步判断发散方向。

3. **发散方向判断**：
   - 选择模较大的特征值 $\lambda_{\text{dom}}$ 作为主导。
   - 若 $\lambda_{\text{dom}} < 0$，输出“混沌”。
   - 否则，计算主导特征向量 $\mathbf{v}_1$ 和另一个特征向量 $\mathbf{v}_2$。将初始向量 $\mathbf{v}_0$ 表示为 $\mathbf{v}_0 = C_1 \mathbf{v}_1 + C_2 \mathbf{v}_2$。若 $|C_1| < \epsilon$，则退化为次方向，改用 $\mathbf{v}_2$ 和 $C_2$ 作为最终方向。否则使用主导方向。
   - 最终方向向量为 $C \mathbf{v}$，取其两个分量 $h_{\infty}$ 和 $f_{\infty}$ 的符号，根据符号组合输出对应的句子。若任一分量为零，则判为“混沌”。

4. **重根处理**：若 $\lambda_1 = \lambda_2$ 且模大于 $1$，需检查矩阵是否可对角化。若 $A$ 为标量矩阵（即 $A = \lambda I$），则按初始向量符号直接判断；否则存在 $\texttt{Jordan}$ 块，导致线性增长，方向不固定，判为“混沌”。

### 数值稳定性

使用阈值 $\epsilon = 10^{-10}$ 来处理浮点数比较中的舍入误差。所有与 1 的比较均使用 $< 1 - \epsilon$ 和 $> 1 + \epsilon$，中间范围一律视为混沌。判别式 $D$ 接近零时按重根处理，投影系数接近零时退化为次方向。

### 复杂度分析

每个测试用例只需常数次浮点运算（特征值、特征向量、投影系数），时间复杂度 $O(1)$，空间复杂度 $O(1)$。输入规模 $N$ 未明确上界，但每个用例的数值长度不超过 $10$，整体效率极高。

## 代码实现

```cpp
// Hares and Foxes
// UVa ID: 720
// Verdict: Accepted
// Submission Date: 2026-07-08
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-10;

int sgn(double x) {
    if (x > EPS) return 1;
    if (x < -EPS) return -1;
    return 0;
}

void eigenVector(double a, double b, double c, double d, double lam, double &vx, double &vy) {
    double e11 = a - lam, e12 = -b;
    double e21 = d, e22 = c - lam;
    if (fabs(e11) > fabs(e21)) {
        vx = e12;
        vy = -e11;
    } else {
        vx = e22;
        vy = -e21;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;
    while (N--) {
        double a, b, c, d, h0, f0;
        cin >> a >> b >> c >> d >> h0 >> f0;
        double tr = a + c;
        double det = a * c + b * d;
        double disc = tr * tr - 4 * det;
        if (fabs(disc) < EPS) {
            double lam = tr / 2;
            double m = fabs(lam);
            if (m < 1 - EPS) cout << "Ecological balance will develop.\n";
            else if (m > 1 + EPS) {
                if (lam < 0) {
                    cout << "Chaos will develop.\n";
                } else {
                    bool isScalar = (fabs(a - lam) < EPS && fabs(c - lam) < EPS &&
                                     fabs(b) < EPS && fabs(d) < EPS);
                    if (!isScalar) {
                        cout << "Chaos will develop.\n";
                    } else {
                        int hs = sgn(h0), fs = sgn(f0);
                        if (hs == 0 || fs == 0) cout << "Chaos will develop.\n";
                        else if (hs > 0 && fs > 0) cout << "Both hares and foxes will overgrow.\n";
                        else if (hs < 0 && fs < 0) cout << "Both hares and foxes will die out.\n";
                        else if (hs > 0 && fs < 0) cout << "Hares will overgrow while foxes will die out.\n";
                        else cout << "Hares will die out while foxes will overgrow.\n";
                    }
                }
            } else cout << "Chaos will develop.\n";
            continue;
        }
        if (disc < 0) {
            double r = sqrt(det);
            if (r < 1 - EPS) cout << "Ecological balance will develop.\n";
            else cout << "Chaos will develop.\n";
            continue;
        }
        double sqrtDisc = sqrt(disc);
        double lam1 = (tr + sqrtDisc) / 2;
        double lam2 = (tr - sqrtDisc) / 2;
        double m1 = fabs(lam1), m2 = fabs(lam2);
        if (m1 < 1 - EPS && m2 < 1 - EPS) {
            cout << "Ecological balance will develop.\n";
            continue;
        }
        if ((m1 >= 1 - EPS && m1 <= 1 + EPS) || (m2 >= 1 - EPS && m2 <= 1 + EPS)) {
            cout << "Chaos will develop.\n";
            continue;
        }
        double lamDom, lamSub, mDom, mSub;
        if (m1 > m2) {
            lamDom = lam1; mDom = m1;
            lamSub = lam2; mSub = m2;
        } else {
            lamDom = lam2; mDom = m2;
            lamSub = lam1; mSub = m1;
        }
        if (lamDom < 0) {
            cout << "Chaos will develop.\n";
            continue;
        }
        double v1x, v1y, v2x, v2y;
        eigenVector(a, b, c, d, lamDom, v1x, v1y);
        eigenVector(a, b, c, d, lamSub, v2x, v2y);
        double detV1V2 = v1x * v2y - v1y * v2x;
        if (fabs(detV1V2) < EPS) {
            cout << "Chaos will develop.\n";
            continue;
        }
        double detV0V2 = h0 * v2y - f0 * v2x;
        double Cdom = detV0V2 / detV1V2;
        double usedLam, usedVx, usedVy, usedC;
        if (fabs(Cdom) < EPS) {
            if (mSub < 1 + EPS) {
                if (mSub < 1 - EPS) cout << "Ecological balance will develop.\n";
                else cout << "Chaos will develop.\n";
                continue;
            }
            if (lamSub < 0) {
                cout << "Chaos will develop.\n";
                continue;
            }
            usedLam = lamSub;
            usedVx = v2x; usedVy = v2y;
            double detV0V1 = h0 * v1y - f0 * v1x;
            usedC = -detV0V1 / detV1V2;
        } else {
            usedLam = lamDom;
            usedVx = v1x; usedVy = v1y;
            usedC = Cdom;
        }
        if (usedLam < 0) {
            cout << "Chaos will develop.\n";
            continue;
        }
        double hFinal = usedC * usedVx;
        double fFinal = usedC * usedVy;
        int hs = sgn(hFinal), fs = sgn(fFinal);
        if (hs == 0 || fs == 0) cout << "Chaos will develop.\n";
        else if (hs > 0 && fs > 0) cout << "Both hares and foxes will overgrow.\n";
        else if (hs < 0 && fs < 0) cout << "Both hares and foxes will die out.\n";
        else if (hs > 0 && fs < 0) cout << "Hares will overgrow while foxes will die out.\n";
        else cout << "Hares will die out while foxes will overgrow.\n";
    }
    return 0;
}
```

## 总结

本题本质上是一个二维线性差分方程的稳定性与长期符号判定问题，核心工具是线性代数中的**特征值**与**特征向量**。解题的关键在于：

- 准确计算特征值并判断其模长与 $1$ 的关系，区分平衡、发散和混沌。
- 当发散时，通过投影系数确定最终方向符号，并正确处理重根、投影为零等退化情形。
- 数值实现中必须谨慎处理浮点数误差，采用适当的阈值（$\epsilon$）将临界情况统一归为混沌，避免因舍入误差导致的误判。

本题提醒我们，在计算几何或数值分析类问题中，对边界情况的鲁棒处理往往比算法主体更为重要，合理的阈值选择可以直接决定提交是否通过。
