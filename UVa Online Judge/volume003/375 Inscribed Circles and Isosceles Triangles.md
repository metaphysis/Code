[UVa 375 Inscribed Circles and Isosceles Triangles](https://blog.csdn.net/metaphysis/article/details/161642353)

## 题目描述

给定两个实数：
- $B$：等腰三角形底边的宽度（英寸）
- $H$：等腰三角形的高（英寸）

计算一系列内切圆的周长之和，这些圆从底边到顶部依次堆叠：
- 最低的内切圆与底边和两腰相切
- 下一个更高的内切圆与下方的内切圆和两腰相切
- 依此类推，直到最小圆的半径小于 $0.000001$

### 输入格式

第一行是一个正整数 $n$，表示测试用例的数量。每个测试用例一行，包含两个正实数 $B$ 和 $H$。

### 输出格式

对于每个测试用例，输出一个实数（$12$ 位有效数字，其中 $6$ 位小数），表示所有内切圆周长之和。

### 样例输入

```
1

0.263451 0.263451
```

### 样例输出

```
    0.827648
```

---

## 题目分析

### 问题的本质

这是一个**几何级数求和**问题。在等腰三角形中，从底边开始依次向上堆叠内切圆，每个圆都与两腰相切，并与下方的圆相切。需要计算所有圆的周长之和。

### 几何关系

等腰三角形的底边 $B$，高 $H$，腰长 $L = \sqrt{(B/2)^2 + H^2}$。

**第一个圆**（最低）：
- 内切于等腰三角形，圆心在角平分线交点上
- 半径 $r_1 = \frac{B \times H}{B + \sqrt{4H^2 + B^2}}$

**后续圆**：
- 每个新的圆都内切于上方剩余的小等腰三角形
- 新三角形与原三角形相似
- 半径递减比例恒定

### 半径递推关系

设第 $i$ 个圆的半径为 $r_i$，其对应的等腰三角形高为 $H_i$，底边为 $B_i$。由相似性：
$$
\frac{r_{i+1}}{r_i} = \frac{H_i - 2r_i}{H_i + 2r_i}
$$

### 迭代终止条件

当 $r < 0.000001$ 时停止。

---
## 参考代码

```cpp
// Inscribed Circles and Isosceles Triangles
// UVa ID: 375
// Verdict: Accepted
// Submission Date: 2016-07-03
// UVa Run Time: 0.040s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const double PI = 2 * acos(0.0);

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);
    
    double n, B, H, sumOfR, r;
    cin >> n;
    
    cout << fixed << setprecision(6);
    
    for (int i = 1; i <= n; i++)
    {
        cin >> B >> H;
        
        // 测试用例间空行
        if (i > 1) cout << endl;
        
        sumOfR = 0.0;
        // 第一个内切圆半径
        r = H * B / (B + sqrt(4 * H * H + B * B));
        
        // 累加半径直到小于阈值
        while (r >= 0.000001)
        {
            sumOfR += r;
            H -= 2 * r;                              // 剩余三角形高度
            r = r * H / (H + 2 * r);                 // 下一个圆的半径
        }
    
        // 输出周长之和，右对齐 13 位
        cout << right << setw(13) << (2.0 * PI * sumOfR) << endl;
    }
    
    return 0;
}
```
