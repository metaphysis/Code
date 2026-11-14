[UVa 358 Don't Have A Cow, Dude](https://blog.csdn.net/metaphysis/article/details/161589158)

## 题目描述

老麦克唐纳有一个农场，农场里有一头牛和一个半径为 $100$ 码的圆形围栏。他计划将牛拴在围栏边界上的一根柱子上。他希望牛能够吃到围栏内三分之一面积的草。绳子应该有多长？

你需要解决这个问题的推广形式。

### 输入格式

输入第一行是一个正整数，表示测试用例的数量。每个测试用例包含两个数字：$R$（半径，$1 \leq R \leq 1000$ 的整数）和 $P$（比例，$0.0 \leq P \leq 0.5$ 的实数）。两个测试用例之间有一个空行。

### 输出格式

对于每个测试用例，按样例格式输出一行。$P$ 和答案四舍五入到两位小数。每个测试用例的输出后跟一个空行。

### 样例输入

```
1
100 0.33
```

### 样例输出

```
R = 100, P = 0.33, Rope = 13.24
```

---

## 题目分析

### 问题的本质

这是一个**几何求解**问题。给定一个半径为 $R$ 的圆，在圆周上取一点作为拴牛点，用长度为 $L$ 的绳子将牛拴在该点。牛可以吃到绳子覆盖范围内的草（即半径为 $L$ 的圆与半径为 $R$ 的圆的交集区域）。需要求绳子长度 $L$，使得牛能吃到的草的面积等于给定比例 $P$ 乘以大圆面积。

### 几何关系

设：
- 大圆（牧场）半径 $R$，圆心 $O$
- 拴牛点 $P_0$ 在大圆圆周上
- 绳子长度 $L$，牛的活动区域是以 $P_0$ 为圆心、$L$ 为半径的圆
- 牛能吃到的草是大圆与小圆的交集区域

由于对称性，拴牛点位于圆周上时，交集的形状由两个圆的相交部分决定。

### 数学推导

设两个圆的圆心距离为 $d = R$（拴牛点在大圆上），半径分别为 $R$ 和 $L$。

两圆相交部分的面积公式为：
$$
S = R^2 \cos^{-1}\left(\frac{d^2 + R^2 - L^2}{2dR}\right) + L^2 \cos^{-1}\left(\frac{d^2 + L^2 - R^2}{2dL}\right) - \frac{1}{2} \sqrt{(-d+R+L)(d+R-L)(d-R+L)(d+R+L)}
$$

由于 $d = R$，公式可简化。

设：
- $\alpha = \arccos\left(\frac{2R^2 - L^2}{2R^2}\right)$
- $\beta = \arccos\left(\frac{L}{2R}\right)$

则相交部分面积：
$$
S = R^2 \alpha + L^2 \beta - \frac{1}{2} R L \sin(2\beta)
$$

或者等价形式：
$$
S = R^2 \alpha + L^2 \beta - R^2 \sin \alpha
$$

注意：这里需要验证等式的正确性。实际上，从几何关系可得：
$$
S = R^2 \cos^{-1}\left(1 - \frac{L^2}{2R^2}\right) + L^2 \cos^{-1}\left(\frac{L}{2R}\right) - \frac{L}{2} \sqrt{4R^2 - L^2}
$$

其中 $\sqrt{4R^2 - L^2} = 2R \sin(\alpha/2)$。

### 面积比例

$P$ 是牛能吃到的草占整个牧场的比例：
$$
P = \frac{S}{\pi R^2}
$$

即：
$$
P = \frac{1}{\pi} \left[ \cos^{-1}\left(1 - \frac{L^2}{2R^2}\right) + \frac{L^2}{R^2} \cos^{-1}\left(\frac{L}{2R}\right) - \frac{L}{2R} \sqrt{4 - \frac{L^2}{R^2}} \right]
$$

令 $x = L / R$，则方程简化为：
$$
P = \frac{1}{\pi} \left[ \cos^{-1}\left(1 - \frac{x^2}{2}\right) + x^2 \cos^{-1}\left(\frac{x}{2}\right) - \frac{x}{2} \sqrt{4 - x^2} \right]
$$

### 求解方法

由于方程无法解析求解，需要使用**数值方法**（如二分法）求 $x$，然后得到 $L = xR$。
## 参考代码

```cpp
// Don't Have A Cow, Dude
// UVa ID: 358
// Verdict: Accepted
// Submission Date: 2016-07-06
// UVa Run Time: 0.040s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const double PI = 2.0 * acos(0.0);

int main() {
    ios::sync_with_stdio(false);

    int cases;
    string R, P;
    
    cin >> cases;
    for (int i = 1; i <= cases; i++)
    {
        // 测试用例间输出空行
        if (i > 1) cout << endl;
        cin >> R >> P;
        
        double r = stod(R), p = stod(P);
        double low = 0.0, up = 2.0 * r;  // 绳子长度范围：0 到直径
        
        int iterations = 0;
        // 二分查找
        while (fabs(low - up) >= 1e-7 && iterations++ <= 40)
        {
            double middle = (low + up) / 2.0;
            
            // 计算当前绳子长度下的面积比例
            double a1 = acos((2.0 * r * r - middle * middle) / (2.0 * r * r));
            double a2 = acos(middle / (2.0 * r));
            double next_p = (r * r * a1 + middle * middle * a2 - r * r * sin(a1)) / (PI * r * r);
            
            if (next_p < p)
                low = middle;
            else
                up = middle;
        }
        
        cout << "R = " << R;
        cout << ", P = " << fixed << setprecision(2) << p;
        cout << ", Rope = " << fixed << setprecision(2) << low << endl;
    }
    
    return 0;
}
```
