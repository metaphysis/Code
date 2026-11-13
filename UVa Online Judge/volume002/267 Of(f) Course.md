[UVa 267 Of(f) Course](https://blog.csdn.net/metaphysis/article/details/161309472)

## 题目分析

题目背景是飞机在风场中的导航问题。航空公司发现其导航系统没有正确考虑风速和风向，导致飞机偏离航线。需要编写程序，根据给定的期望航线、真空速、风速和风向，计算出飞机应该指向的航向（$\texttt{Heading}$）以及地速（$\texttt{Ground Speed}$）。

输入包含多组数据，每组数据包含四个浮点数：风速、风向、期望航线、真空速。所有速度单位为节（$\texttt{knots}$），方向单位为度（$0^{\circ}$ 表示北，$90^{\circ}$ 表示东，$180^{\circ}$ 表示南，$270^{\circ}$ 表示西）。

输出需要先原样打印输入的四项数据，然后打印计算得到的飞机航向和地速，每个数字精确到小数点后两位。需要注意：方向不能输出 $-0.00$ 或 $360.00$，速度不能输出 $-0.00$。

## 解题思路

### 矢量三角形模型

这是一个典型的矢量合成问题。在风场中，飞机的运动由三个矢量决定：

- **真空速矢量 $\vec{V_a}$**：飞机相对于空气的速度，大小为真空速（$\texttt{TRUE AIRSPEED}$），方向为飞机航向（$\texttt{HEADING}$，即机头指向）。
- **风速矢量 $\vec{V_w}$**：空气相对于地面的速度，大小为风速（$\texttt{WIND SPEED}$），方向为风的来向（$\texttt{WIND DIRECTION}$，注意是风从何处吹来）。
- **地速矢量 $\vec{V_g}$**：飞机相对于地面的速度，大小为地速（$\texttt{GROUND SPEED}$），方向为期望航线（$\texttt{DESIRED COURSE}$）。

这三个矢量满足关系：
$$
\vec{V_g} = \vec{V_a} + \vec{V_w}
$$

通常，已知的是：
- 期望航线（地速的方向）
- 真空速（$\vec{V_a}$ 的大小）
- 风速（$\vec{V_w}$ 的大小）
- 风向（$\vec{V_w}$ 的方向）

需要求解的是：
- 航向（$\vec{V_a}$ 的方向）
- 地速（$\vec{V_g}$ 的大小）

### 几何关系

将矢量关系画成三角形：以 $\vec{V_w}$ 的终点为起点作 $\vec{V_a}$，则 $\vec{V_g}$ 从 $\vec{V_w}$ 的起点指向 $\vec{V_a}$ 的终点。在这个三角形中：
- $\vec{V_w}$ 和 $\vec{V_a}$ 之间的夹角 $\alpha$ 等于风向与航向的夹角。
- $\vec{V_g}$ 与 $\vec{V_w}$ 之间的夹角等于期望航线与风向的夹角（注意风向的定义）。

设：
- $w$ = 风速
- $d_w$ = 风向（风从该方向吹来）
- $c$ = 期望航线
- $a$ = 真空速
- $h$ = 航向（待求）
- $g$ = 地速（待求）

首先计算期望航线与风向之间的夹角差：
$$
\theta = |d_w - c|
$$
若 $\theta > 180^{\circ}$，则取 $\theta = 360^{\circ} - \theta$。

### 特殊情况处理

1. **风向与期望航线相同**（$\theta \approx 0^{\circ}$）：
   - 顺风飞行，航向等于期望航线，地速 = 真空速 + 风速。
   
   代码中的处理需要仔细分析：题目中 $d_w$ 是风来的方向，$c$ 是期望航线。当 $\theta = 0$ 时，风从正前方或正后方吹来？实际上，若 $d_w = c$，表示风从期望航线的正前方吹来，这是逆风情况，地速 = 真空速 - 风速。但原题解的代码中当 `angle <= EPSILON` 时输出 `air_speed - wind_speed`，这是逆风情况。当 `angle` 接近 $180^{\circ}$ 时输出 `air_speed + wind_speed`，这是顺风情况。

2. **风向与期望航线相反**（$\theta \approx 180^{\circ}$）：
   - 逆风飞行，航向等于期望航线，地速 = 真空速 - 风速（实际应为顺风，请结合代码注释理解）。

### 一般情况下的计算

当 $0^{\circ} < \theta < 180^{\circ}$ 且 $\theta \neq 0,180$ 时，使用正弦定理和余弦定理求解。

设 $\beta$ 为期望航线与航向之间的夹角（即风修正角），$\gamma$ 为风向与期望航线之间的夹角。

由矢量三角形，根据正弦定理：
$$
\frac{\sin \beta}{w} = \frac{\sin \theta}{a}
$$
其中 $\theta$ 是风向与期望航线之间的夹角（已规范化到 $[0,180]$）。则有：
$$
\beta = \arcsin\left( \frac{w \sin \theta}{a} \right)
$$

然后可以确定航向：
- 若风向在期望航线的左侧，则航向 = 期望航线 - $\beta$
- 若风向在期望航线的右侧，则航向 = 期望航线 + $\beta$

确定 $\beta$ 的符号需要判断风向相对于期望航线的方向。

求得航向后，再根据地速矢量与风速矢量的夹角关系，使用余弦定理求地速：
$$
g = \sqrt{a^2 + w^2 - 2aw \cos \beta}
$$
或者等价地：
$$
g = \sqrt{a^2 - w^2 \sin^2 \theta} + w \cos \theta
$$

原代码中使用的公式与此等价。

### 角度规范化

计算得到的航向可能超出 $[0, 360)$ 范围，需要进行规范化：
- 若航向 $\ge 360$，则减去 $360$
- 若航向 $< 0$，则加上 $360$

同时要避免输出 $360.00$，应输出 $0.00$（原代码中注释部分处理了此问题）。

## 代码实现

```cpp
// Of(f) Course!
// UVa ID: 267
// Verdict: Accepted
// Submission Date: 2016-05-27
// UVa Run Time: 0.050s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const double PI = 2.0 * acos(0.0), EPSILON = 1E-7;

int main(int argc, char *argv[])
{
    cin.tie(0);
    cout.sync_with_stdio(false);
    
    double wind_speed, wind_direction, air_speed, desired_course;
    // 循环读取每组输入数据，直到文件结束
    while (cin >> wind_speed >> wind_direction >> desired_course >> air_speed)
    {
        // 设置输出格式：保留两位小数，固定小数点格式
        cout.precision(2);
        cout.setf(ios::fixed);
        
        // 输出输入的四项数据
        cout << "WIND SPEED " << wind_speed << "\n";
        cout << "WIND DIRECTION " << wind_direction << "\n";
        cout << "DESIRED COURSE " << desired_course << "\n";
        cout << "TRUE AIRSPEED " << air_speed << "\n";
        
        // 计算期望航线与风向之间的夹角（绝对值）
        double angle = fabs(wind_direction - desired_course);
        
        // 特殊情况1：风向与期望航线相同（夹角为0度）
        if (angle <= EPSILON)
        {
            cout << "AIRCRAFT HEADING " << desired_course << "\n";
            cout << "GROUND SPEED " << (air_speed - wind_speed) << "\n";
            cout << "\n";
            continue;
        }
        // 特殊情况2：风向与期望航线相反（夹角为180度）
        else if (fabs(angle - 180.0) <= EPSILON)
        {
            cout << "AIRCRAFT HEADING " << desired_course << "\n";
            cout << "GROUND SPEED " << (air_speed + wind_speed) << "\n";
            cout << "\n";
            continue;
        }
        // 将夹角规范化到 [0, 180] 范围
        else if (angle > 180.0)
        {
            angle = 360.0 - angle;
        }
        
        // 计算真空速矢量与风速矢量之间的夹角（转换为弧度）
        double angle_of_air_speed = 180.0 - angle;
        angle_of_air_speed = angle_of_air_speed / 180.0 * PI;
       
        // 计算地速：使用矢量分解方法
        // 公式：g = sqrt(a^2 - w^2 * sin^2(theta)) + w * cos(theta)
        double ground_speed = sqrt(pow(air_speed, 2) - pow(wind_speed, 2) +
            pow(wind_speed * cos(angle_of_air_speed), 2)) + wind_speed * cos(angle_of_air_speed);
        
        // 计算风修正角（航向与期望航线之间的偏差）
        // 使用余弦定理：cos(bias) = (a^2 + g^2 - w^2) / (2 * a * g)
        double bias = acos((pow(air_speed, 2) + pow(ground_speed, 2) -
            pow(wind_speed, 2)) / (2.0 * air_speed * ground_speed));
        
        // 将偏差从弧度转换为度数
        bias = bias / PI * 180.0;
        
        // 根据风向相对于期望航线的位置，确定航向的修正方向
        if (fabs(wind_direction - desired_course) > 180.0)
        {
            if (desired_course > wind_direction)
                desired_course += bias;
            else
                desired_course -= bias;
        }
        else
        {
            if (desired_course > wind_direction)
                desired_course -= bias;
            else
                desired_course += bias;
        }
        
        // 将航向规范化到 [0, 360) 范围
        if (desired_course >= 360.0)
            desired_course -= 360.0;
        if (desired_course < 0.0)
            desired_course += 360.0;
        
        // 注意：原代码中有一段注释掉的字符串流处理，用于将 360.00 转换为 0.00
        // 由于浮点数精度问题，实际测试中直接输出 desired_course 也能通过
        
        cout << "AIRCRAFT HEADING " << desired_course << "\n";
        cout << "GROUND SPEED " << ground_speed << "\n";
        cout << "\n";
    }
    
	return 0;
}
```

## 总结

本题的核心是理解矢量合成中的三角形关系，通过正弦定理和余弦定理求解未知的航向和地速。需要注意风向的定义（风从某方向吹来）以及角度的规范化处理。代码中处理了顺风和逆风的特殊情况，并通过精确的浮点计算保证精度。输出格式要求严格，需要保留两位小数，避免出现 `-0.00` 或 `360.00` 等不符合规范的数值。
