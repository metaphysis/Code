[UVa 376 More Triangles THE AMBIGUOUS CASE](https://blog.csdn.net/metaphysis/article/details/161642363)


## 题目描述

三角学中的**歧义情况**（$\texttt{ambiguous case}$）是指在已知两边和其中一边的对角时求解三角形。你需要编写一个程序，接收这样的数据并报告所有解。

### 输入格式

每行包含三个实数：前两个表示三角形的两边长度，第三个表示与第二边相对的角（以度为单位）。输入以 `0.0 0.0 0.0` 结束。

### 输出格式

对于每个数据，报告解的数量。如果有解，报告对应的第三边长度（保留两位小数）。如果有两个解，按递减顺序输出。无解时输出 $0$。

### 样例输入

```
2.00 2.00 30.00
2.00 3.00 130.00
1.00 1.00 90.00
698.64 217.77 5.52
0.00 0.00 0.00
```

### 样例输出

```
Case    A      B    THETA  # of    Side   Side
 #     side   side  (deg)  Triags    1      2
   1   2.00   2.00  30.00     1                3.46
   2   2.00   3.00 130.00     1                1.29
   3   1.00   1.00  90.00     0
   4 698.64 217.77   5.52     2      902.54  488.26

END OF REPORT for 4 cases
```

---

## 题目分析

### 问题的本质

这是一个**解三角形**问题。已知两边 $a$、$b$ 和边 $b$ 的对角 $B$，求解第三边 $c$ 的长度。

### 已知条件

- 边 $a$：第一条边的长度
- 边 $b$：第二条边的长度（对角为 $B$）
- 角 $B$：边 $b$ 的对角（以度为单位）

需要求解第三边 $c$ 的可能长度。

### 余弦定理的应用

由余弦定理，边 $b$ 满足：
$$
b^2 = a^2 + c^2 - 2ac\cos B
$$

将其整理为关于 $c$ 的一元二次方程：
$$
c^2 - (2a\cos B) \cdot c + (a^2 - b^2) = 0
$$

记：
$$
\Delta = (2a\cos B)^2 - 4(a^2 - b^2) = 4(b^2 - a^2\sin^2 B)
$$

则方程的解为：
$$
c = a\cos B \pm \sqrt{b^2 - a^2\sin^2 B}
$$

### 歧义情况的分类

根据判别式和根的正负性，解的情况分为以下几类：

#### 情况 1：$B$ 为锐角

- 如果 $b < a\sin B$：$\Delta < 0$，无解
- 如果 $b = a\sin B$：$\Delta = 0$，一个解（直角三角形），此时 $c = a\cos B$
- 如果 $b > a\sin B$：$\Delta > 0$，两个正根：
  - 若 $b \ge a$，两根均为正，但其中一根为 $a\cos B - \sqrt{\cdots}$ 可能为负，需进一步判断，实际只有一个有效解
  - 若 $b < a$，两根均为正，两个有效解

#### 情况 2：$B$ 为钝角

此时 $\cos B < 0$，$a\cos B$ 为负数。两根中 $a\cos B - \sqrt{\cdots}$ 为负，舍去；$a\cos B + \sqrt{\cdots}$ 可能为正也可能为负：
- 如果 $b \le a$：无解
- 如果 $b > a$：一个正解

#### 情况 3：$B = 90^\circ$

此时 $\cos B = 0$，$\sin B = 1$，方程简化为 $c^2 = b^2 - a^2$：
- 如果 $b \le a$：无解
- 如果 $b > a$：一个解 $c = \sqrt{b^2 - a^2}$

---
## 参考代码

```cpp
// More Triangles THE AMBIGUOUS CASE
// UVa ID: 376
// Verdict: Accepted
// Submission Date: 2016-07-08
// UVa Run Time: 0.050s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const double PI = 2.0 * acos(0.0);
const double EPSILON = 1e-7;

int main(int argc, char *argv[]) {
    ios::sync_with_stdio(false);

    int cases = 0;
    double a, b, B;
    vector<tuple<int, double, double, double, double, double>> triangles;
    
    while (cin >> a >> b >> B) {
        if (fabs(a) + fabs(b) + fabs(B) < EPSILON) break;
        
        // B 为 0 或 180 度
        if (fabs(B) <= EPSILON || fabs(B - 180.0) <= EPSILON) {
            triangles.push_back({++cases, a, b, B, a + b, fabs(a - b)});
            continue;
        }
        
        // 零长度边
        if (a < EPSILON || b < EPSILON) {
            triangles.push_back({++cases, a, b, B, -1.0, -1.0});
            continue;
        }
        
        double angle = B;
        double radB = B * PI / 180.0;
        
        if (angle < 90.0 - EPSILON) { // 锐角
            double h = a * sin(radB);
            if (b < h - EPSILON) {
                triangles.push_back({++cases, a, b, angle, -1.0, -1.0});
            } else if (fabs(b - h) <= EPSILON) {
                triangles.push_back({++cases, a, b, angle, a * cos(radB), -1.0});
            } else {
                if (b >= a - EPSILON) {
                    double A = asin(a * sin(radB) / b);
                    double C = PI - A - radB;
                    double c = sqrt(a * a + b * b - 2 * a * b * cos(C));
                    triangles.push_back({++cases, a, b, angle, c, -1.0});
                } else {
                    double offset = sqrt(b * b - a * a * sin(radB) * sin(radB));
                    double c1 = a * cos(radB) + offset;
                    double c2 = a * cos(radB) - offset;
                    if (c1 < c2) swap(c1, c2);
                    triangles.push_back({++cases, a, b, angle, c1, c2});
                }
            }
        } else if (angle > 90.0 + EPSILON) { // 钝角
            if (b < a - EPSILON) {
                triangles.push_back({++cases, a, b, angle, -1.0, -1.0});
            } else {
                double A = asin(a * sin(radB) / b);
                double C = PI - A - radB;
                double c = sqrt(a * a + b * b - 2 * a * b * cos(C));
                triangles.push_back({++cases, a, b, angle, c, -1.0});
            }
        } else { // 直角
            if (b <= a + EPSILON) {
                triangles.push_back({++cases, a, b, angle, -1.0, -1.0});
            } else {
                triangles.push_back({++cases, a, b, angle, sqrt(b * b - a * a), -1.0});
            }
        }
    }

    // 输出表头
    cout << "Case    A      B    THETA  # of    Side   Side" << endl;
    cout << " #     side   side  (deg)  Triags    1      2" << endl;
    
    // 输出结果
    for (auto& t : triangles) {
        int idx = get<0>(t);
        double sideA = get<1>(t);
        double sideB = get<2>(t);
        double theta = get<3>(t);
        double c1 = get<4>(t);
        double c2 = get<5>(t);
        
        cout << setw(4) << right << idx;
        cout << setw(7) << right << fixed << setprecision(2) << sideA;
        cout << setw(7) << right << fixed << setprecision(2) << sideB;
        cout << setw(7) << right << fixed << setprecision(2) << theta;
        cout << setw(6) << right << ((c1 > 0.0) + (c2 > 0.0));
        
        if (c1 > 0.0)
            cout << setw(9) << right << fixed << setprecision(2) << c1;
        if (c2 > 0.0)
            cout << setw(7) << right << fixed << setprecision(2) << c2;
        cout << endl;
    }
    
    cout << endl;
    cout << "END OF REPORT for " << cases << " cases" << endl;
    
    return 0;
}
```
