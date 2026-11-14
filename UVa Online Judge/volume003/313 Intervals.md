[UVa 313 Intervals](https://blog.csdn.net/metaphysis/article/details/161476834)

## 题目描述

在新开发大楼的地下室天花板上安装了一个光源。不幸的是，地板材料对光非常敏感，其预期寿命会急剧下降。为了避免这种情况，当局决定用遮光罩覆盖光敏区域，但只能覆盖那些没有被管道遮挡的地板部分。

为了简化问题，将三维空间简化为二维模型：
- $x$ 轴与地板水平对齐
- 光源是一个点光源，坐标为整数 $[b_x, b_y]$
- 管道用圆表示，圆心 $[c_{i,x}, c_{i,y}]$ 和半径 $r_i$ 都是整数
- 管道是实心材料，不能反射光，光不能穿过管道
- 管道之间不会重叠
- 所有管道都位于光源下方：$c_{i,y} + r_i < b_y$

要求：确定 $x$ 轴上由于管道遮挡而没有光照射的**非重叠区间**。

### 输入格式

输入文件由多个数据块组成，每个数据块描述一个场景：
- 第一行：正整数 $N < 500$，表示管道数量
- 第二行：两个整数 $b_x$ 和 $b_y$，光源坐标
- 接下来 $N$ 行：每行三个整数 $c_{i,x}$、$c_{i,y}$、$r_i$，表示管道圆心和半径

最后一个数据块以 $N = 0$ 结束。

### 输出格式

输出文件包含与输入块对应的数据块（最后一个除外）。每个数据块输出若干行，每行两个实数，表示无光区间的左右端点（保留两位小数，按 $x$ 坐标升序排列）。每个数据块后输出一个空行。

### 样例输入

```
6
300 450
70 50 30
120 20 20
270 40 10
250 85 20
220 30 30
380 100 100
1
300 300
300 150 90
1
300 300
390 150 90
0
```

### 样例输出

```
0.72 78.86
88.50 133.94
181.04 549.93

75.00 525.00

300.00 862.50
```

---

## 题目分析

### 问题的本质

这是一个**光的直线传播与遮挡**问题。点光源发出的光线沿直线传播，当遇到圆形管道时，光线被遮挡，在地板（$x$ 轴）上形成阴影区间。

关键要点：
- 光源是点光源，位于 $(b_x, b_y)$
- 管道是圆，位于光源下方
- 光沿直线传播，不能穿过管道
- 需要找出 $x$ 轴上所有被阴影覆盖的区间

### 几何模型

对于每个管道（圆），从光源向圆作两条切线，这两条切线与 $x$ 轴的交点之间形成一个阴影区间。所有管道的阴影区间的并集即为无光区域。

因此，问题转化为：
1. 对于每个圆，计算其切线与 $x$ 轴的交点
2. 合并所有区间（求并集）
3. 输出合并后的区间

### 切线的数学推导

设光源为 $L(b_x, b_y)$，圆心为 $C(c_x, c_y)$，半径为 $r$。

从点 $L$ 向圆作切线。设切线与 $x$ 轴的交点为 $P(x, 0)$。连接 $P$ 和 $L$ 的直线为：
$$
y = m(x - b_x) + b_y
$$
其中 $m$ 是斜率。

该直线与圆相切的条件是：圆心到直线的距离等于半径 $r$。

圆心 $C$ 到直线 $y = m(x - b_x) + b_y$ 的距离公式为：
$$
distance = \frac{|m(c_x - b_x) - c_y + b_y|}{\sqrt{m^2 + 1}} = r
$$

平方后得：
$$
[m(c_x - b_x) - (c_y - b_y)]^2 = r^2 (m^2 + 1)
$$

展开：
$$
m^2 (c_x - b_x)^2 - 2m(c_x - b_x)(c_y - b_y) + (c_y - b_y)^2 = r^2 m^2 + r^2
$$

整理成关于 $m$ 的二次方程：
$$
[(c_x - b_x)^2 - r^2] m^2 - 2(c_x - b_x)(c_y - b_y) m + [(c_y - b_y)^2 - r^2] = 0
$$

令：
- $\Delta x = c_x - b_x$
- $\Delta y = c_y - b_y$

则有：
$$
(\Delta x^2 - r^2) m^2 - 2 \Delta x \Delta y \cdot m + (\Delta y^2 - r^2) = 0
$$

这就是代码中的系数：
- $a = \Delta x^2 - r^2$
- $b = -2 \Delta x \Delta y$（注意符号）
- $c = \Delta y^2 - r^2$

### 求直线与 $x$ 轴的交点

已知直线斜率为 $m$，经过点 $L(b_x, b_y)$，其方程为：
$$
y - b_y = m(x - b_x)
$$

令 $y = 0$，解得 $x$ 坐标：
$$
x = b_x - \frac{b_y}{m}
$$

---

## 解题思路

### 步骤一：读取输入

对于每个数据块，读取 $N$、光源坐标，然后读取 $N$ 个管道的信息。

### 步骤二：计算每个管道的阴影区间

对于每个管道，计算二次方程的系数：
```cpp
double dx = pipe.x - light.x;
double dy = pipe.y - light.y;
double a = dx * dx - pipe.r * pipe.r;
double b = 2 * dx * dy;  // 注意：实际应为 -2*dx*dy
double c = dy * dy - pipe.r * pipe.r;
```

然后判断判别式：
```cpp
double delta = b * b - 4 * a * c;
if (delta > EPSILON) {
    // 有两个不同的斜率，对应两个切点
}
```

**情况 1**：$a \neq 0$，两个不同的斜率
```cpp
double m1 = (-b + sqrt(delta)) / (2 * a);
double m2 = (-b - sqrt(delta)) / (2 * a);
double left = light.x - light.y / m1;
double right = light.x - light.y / m2;
if (left > right) swap(left, right);
intervals.push_back({left, right});
```

**情况 2**：$a = 0$，一次方程，只有一个斜率（切线与垂直相关）
```cpp
else {
    double m = -c / b;
    double x_intersection = light.x - light.y / m;
    intervals.push_back({min(x_intersection, light.x), max(x_intersection, light.x)});
}
```

### 步骤三：合并区间

将所有区间按左端点排序，然后合并重叠或相邻的区间。

### 步骤四：输出

每个区间输出两个实数，保留两位小数。每个数据块后输出一个空行。

---

## 算法复杂度分析

### 时间复杂度

- 每个管道：$O(1)$ 计算
- 排序：$O(N \log N)$，$N < 500$
- 合并：$O(N)$
- 总复杂度：$O(N \log N)$，完全可行

### 空间复杂度

- 存储区间：$O(N)$
- 存储管道信息：$O(N)$

---

## 正确性证明

**引理 1**：从点光源到圆的切线与 $x$ 轴的交点之间的区域恰好是圆在 $x$ 轴上投影的阴影区域。

证明：光线沿直线传播，从光源出发的每条光线要么直接照射到 $x$ 轴，要么被圆遮挡。切线是“恰好擦过”圆的光线，切线之间的光线都被圆遮挡。因此，切线与 $x$ 轴的交点之间的区域即为阴影区域。$\square$

**引理 2**：二次方程的解给出了切线的斜率。

证明：圆心到直线的距离等于半径是相切的条件，推导出的二次方程的解即为切线的斜率。$\square$

**引理 3**：区间合并的正确性。

证明：按左端点排序后，依次合并重叠或相邻的区间，得到的就是所有阴影区间的并集。$\square$

---

## 参考代码

```cpp
// Intervals
// UVa ID: 313
// Verdict: Accepted
// Submission Date: 2016-07-09
// UVa Run Time: 0.040s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const double HALF_PI = acos(0.0);
const double EPSILON = 1E-7;

struct point
{
    double x, y;
};

struct pipe
{
    double x, y, r;
};

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    int n;
    while (cin >> n, n)
    {
        point light;
        vector<pipe> pipes;

        cin >> light.x >> light.y;

        for (int i = 1; i <= n; i++)
        {
            pipe aPipe;
            cin >> aPipe.x >> aPipe.y >> aPipe.r;
            pipes.push_back(aPipe);
        }

        // 存储所有阴影区间
        vector<pair<double, double>> intervals;
        double a, b, c, left, right;

        for (int i = 0; i < pipes.size(); i++)
        {
            // 计算二次方程系数: a*m^2 + b*m + c = 0
            double dx = pipes[i].x - light.x;
            double dy = pipes[i].y - light.y;
            double r = pipes[i].r;
            
            a = dx * dx - r * r;
            b = 2 * dx * dy;
            c = dy * dy - r * r;
            
            double delta = b * b - 4 * a * c;
            if (delta > EPSILON)  // 存在两条切线
            {
                if (fabs(a) >= EPSILON)  // a != 0，两个不同的斜率
                {
                    double m1 = (-b + sqrt(delta)) / (2 * a);
                    double m2 = (-b - sqrt(delta)) / (2 * a);
                    
                    // 计算与 x 轴的交点
                    left = light.x - light.y / m1;
                    right = light.x - light.y / m2;
                    
                    if (left >= right)
                        swap(left, right);
                    intervals.push_back(make_pair(left, right));
                }
                else  // a == 0，一次方程
                {
                    double m = -c / b;
                    double x_intersection = light.x - light.y / m;
                    left = min(x_intersection, light.x);
                    right = max(x_intersection, light.x);
                    intervals.push_back(make_pair(left, right));
                }
            }
        }

        // 按左端点排序
        sort(intervals.begin(), intervals.end());

        // 合并重叠区间
        double coverL = intervals[0].first;
        double coverR = intervals[0].second;
        
        for (int i = 1; i < intervals.size(); i++)
        {
            if (intervals[i].first <= coverR + EPSILON)  // 区间重叠或相邻
                coverR = max(coverR, intervals[i].second);
            else
            {
                cout << fixed << setprecision(2) << coverL << " " << coverR << endl;
                coverL = intervals[i].first;
                coverR = intervals[i].second;
            }
        }
        cout << fixed << setprecision(2) << coverL << " " << coverR << endl;
        cout << endl;  // 数据块后空行
    }

    return 0;
}
```

---

## 总结

本题的核心在于：
1. **几何建模**：将光的遮挡问题转化为圆的两条切线与 $x$ 轴的交点问题
2. **代数求解**：利用点到直线的距离公式推导二次方程
3. **区间合并**：将多个阴影区间合并为不重叠的区间

### 关键点回顾

| 知识点 | 说明 |
|--------|------|
| 光源 | 点光源，位于管道上方 |
| 管道 | 圆形，实心，不透明 |
| 切线 | 从光源向圆作切线 |
| 阴影区间 | 切线与 $x$ 轴的交点之间 |
| 二次方程 | 距离公式推导 |
| 区间合并 | 排序后合并重叠区间 |

### 注意事项

1. **浮点精度**：使用 `EPSILON = 1E-7` 处理比较
2. **特殊情况**：当 $a = 0$ 时，二次方程退化为一次方程
3. **输出格式**：保留两位小数，每个数据块后空行

这种“几何 + 代数 + 区间合并”的解题模式，在计算几何和光线追踪领域具有典型性。
