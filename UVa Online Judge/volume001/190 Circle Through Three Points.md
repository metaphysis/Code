[UVa 190 Circle Through Three Points](https://blog.csdn.net/metaphysis/article/details/160911389)

## 题目分析

本题给定平面直角坐标系中不共线的三个点的坐标，要求求出经过这三个点的圆的方程，并以两种形式输出：

1. 标准形式：$(x - h)^2 + (y - k)^2 = r^2$
2. 一般形式：$x^2 + y^2 + cx + dy - e = 0$

输入包含多组测试数据，每组数据给出 $A_x, A_y, B_x, B_y, C_x, C_y$ 六个实数，输出需要将 $h, k, r, c, d, e$ 保留三位小数，并按照指定格式处理正负号。

## 解题思路

### 圆心坐标的推导

设圆心坐标为 $(h, k)$，半径为 $r$。根据圆上任意一点到圆心的距离等于半径，对于三个点 $A(x_1, y_1)$，$B(x_2, y_2)$，$C(x_3, y_3)$ 有：

$$(x_1 - h)^2 + (y_1 - k)^2 = (x_2 - h)^2 + (y_2 - k)^2$$

$$(x_1 - h)^2 + (y_1 - k)^2 = (x_3 - h)^2 + (y_3 - k)^2$$

展开并整理得到关于 $h$ 和 $k$ 的线性方程组：

$$2(x_2 - x_1)h + 2(y_2 - y_1)k = x_2^2 - x_1^2 + y_2^2 - y_1^2$$

$$2(x_3 - x_1)h + 2(y_3 - y_1)k = x_3^2 - x_1^2 + y_3^2 - y_1^2$$

使用克莱姆法则（Cramer’s Rule）求解得到 $h$ 和 $k$ 的表达式：

$$h = \frac{(x_1^2 - x_2^2 + y_1^2 - y_2^2)(y_1 - y_3) - (x_1^2 - x_3^2 + y_1^2 - y_3^2)(y_1 - y_2)}{2[(y_1 - y_3)(x_1 - x_2) - (y_1 - y_2)(x_1 - x_3)]}$$

$$k = \frac{(x_1^2 - x_2^2 + y_1^2 - y_2^2)(x_1 - x_3) - (x_1^2 - x_3^2 + y_1^2 - y_3^2)(x_1 - x_2)}{2[(y_1 - y_2)(x_1 - x_3) - (y_1 - y_3)(x_1 - x_2)]}$$

### 半径的计算

$$r = \sqrt{(x_1 - h)^2 + (y_1 - k)^2}$$

### 一般形式参数的转换

将标准形式展开：

$$(x - h)^2 + (y - k)^2 = r^2$$

$$x^2 - 2hx + h^2 + y^2 - 2ky + k^2 = r^2$$

$$x^2 + y^2 - 2hx - 2ky + (h^2 + k^2 - r^2) = 0$$

整理得到：

$$x^2 + y^2 + cx + dy - e = 0$$

其中：

$$c = -2h, \quad d = -2k, \quad e = r^2 - h^2 - k^2$$

### 格式处理注意事项

- 当 $h$ 或 $k$ 的绝对值小于 $10^{-3}$ 时，视为 $0$，此时输出不包含括号形式
- 符号处理需要避免出现两个连续符号（如 `- -`）
- 当 $c$、$d$、$e$ 为 $0$ 时不输出对应项

## 代码实现

```cpp
// Circle Through Three Points
// UVa ID: 190
// Verdict: Accepted
// Submission Date: 2016-03-14
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net
//
// 当参数为 0 时忽略输出，但是题目描述中并未提到这一点。很容易让人 Wrong Answer。

#include <bits/stdc++.h>
using namespace std;

const double EPSILON = 10E-3;   // 精度阈值，用于判断浮点数是否为0

int main(int argc, char *argv[]) {
    double ax, ay, bx, by, cx, cy;  // 三个点的坐标
    double h, k, r;                  // 圆心坐标和半径
    double c, d, e;                  // 一般形式的参数
    double temp;                     // 临时变量，用于存储绝对值
    
    // 循环读取每组测试数据，直到文件末尾
    while (cin >> ax >> ay >> bx >> by >> cx >> cy) {
        // 使用克莱姆法则求解圆心坐标 h 和 k
        // 分子：第一个部分
        h = (ax * ax - bx * bx + ay * ay - by * by) * (ay - cy);
        // 减去第二个部分
        h -= (ax * ax - cx * cx + ay * ay - cy * cy) * (ay - by);
        // 除以分母
        h /= (2 * (ay - cy) * (ax - bx) - 2 * (ay - by) * (ax - cx));

        // 计算 k 的分子
        k = (ax * ax - bx * bx + ay * ay - by * by) * (ax - cx);
        k -= (ax * ax - cx * cx + ay * ay - cy * cy) * (ax - bx);
        // 除以分母
        k /= (2 * (ay - by) * (ax - cx) - 2 * (ay - cy) * (ax - bx));
        
        // 计算半径：圆心到任意一个点的距离
        r = sqrt(pow(ax - h, 2) + pow(ay - k, 2));
        
        // 输出标准形式：(x - h)^2 + (y - k)^2 = r^2
        // 处理 x 部分
        // h 接近 0，直接输出 x^2
        if (fabs(h) < EPSILON) {
            cout << "x^2";
        }  else {
            cout << "(x ";
            // 注意符号处理：因为公式中是 (x - h)，所以当 h > 0 时显示减号
            cout << (h < 0 ? "+" : "-");
            temp = h < 0 ? -h : h;   // 取绝对值
            cout << " " << fixed << setprecision(3) << temp << ")^2";
        }

        cout << " + ";
        
        // 处理 y 部分
        // k 接近 0，直接输出 y^2
        if (fabs(k) < EPSILON) {
            cout << "y^2";
        } else {
            cout << "(y ";
            cout << (k < 0 ? "+" : "-");
            temp = k < 0 ? -k : k;
            cout << " " << fixed << setprecision(3) << temp << ")^2";
        }
        
        // 输出半径部分
        cout << " = ";
        cout << fixed << setprecision(3) << r << "^2";
        cout << "\n";
        
        // 输出一般形式：x^2 + y^2 + cx + dy - e = 0
        cout << "x^2 + y^2 ";
        
        // 计算并输出 cx 项：c = -2h
        c = h < 0 ? -2 * h : 2 * h;
        // 只有非零时才输出
        if (fabs(c) > EPSILON) {
            // 注意公式中是 +cx，而实际 c = -2h
            // 若 h > 0，则 c 为正，显示 +；若 h < 0，则 c 为负，显示 -
            cout << (h < 0 ? "+" : "-");
            cout << " " << fixed << setprecision(3) << c << "x ";
        }

        // 计算并输出 dy 项：d = -2k
        d = k < 0 ? -2 * k : 2 * k;
        if (fabs(d) > EPSILON) {
            cout << (k < 0 ? "+" : "-");
            cout << " " << fixed << setprecision(3) << d << "y ";
        }
        
        // 计算并输出常数项 e = h^2 + k^2 - r^2
        e = h * h + k * k - r * r;
        if (fabs(e) > EPSILON) {
            // 公式中是 -e，因此移项后显示相反符号
            cout << (e < 0 ? "-" : "+");
            e = e < 0 ? -e : e;
            cout << " " << fixed << setprecision(3) << e << " ";
        }
        
        cout << "= 0";
        
        // 每组测试数据之间输出一个空行
        cout << "\n\n";
    }
    
    return 0;
}
```
