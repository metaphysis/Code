[UVa 217 Radio Direction Finder](https://blog.csdn.net/metaphysis/article/details/161047184)

## 题目分析

本题是一个几何定位问题。一艘装备有定向天线的船可以通过接收已知位置的无线电信标信号来确定自身位置。每个信标发射唯一信号，船通过旋转天线找到信号最强方向，从而获得信标相对于船首方向的相对方位角。

**关键点**：
- 信标位置已知（平面直角坐标系）
- 船的航向 `course` 以度数给出，顺时针从北 $0^\circ$ 开始
- 相对方位角 `angle` 从船首方向顺时针测量
- 天线无法区分信标在左侧还是右侧，即一个相对方位角 $\theta$ 可能对应两个实际方向：$\theta$ 和 $360^\circ - \theta$（或等价地 $\theta$ 和 $180^\circ - \theta$，取决于约定）
- 给定两次信标读数（时间、信标名称、相对方位角）、船的航向和速度，求第二次读数时刻的船位

## 解题思路

### 1. 角度转换

设船的实际航向为 $c$（从北顺时针），相对方位角为 $\alpha$，则信标相对于正北的实际方向角可能为：

$$c + \alpha \quad \text{或} \quad c - \alpha$$

（模 $360^\circ$）

由于题目约定将相对方位角转换为相对于正东方向的角度以便计算直线方程，代码中的 `getAngle` 函数实现了此转换：

- 当输入角度 $\le 90^\circ$：返回 $90^\circ - angle$
- 当输入角度 $\le 270^\circ$：返回 $-(angle - 90^\circ)$
- 否则返回 $180^\circ - (angle - 270^\circ)$

### 2. 几何建模

每次读数时，船的位置与信标位置之间的连线方向是确定的（虽然存在两种可能，但题目保证通过两次读数的组合可以唯一确定）。将这条连线表示为直线方程：

$$ax + by + c = 0$$

其中 $(x, y)$ 是信标坐标，直线方向由转换后的角度决定。

### 3. 运动方程

设第一次读数时刻 $t_1$，船在点 $P_1$；第二次读数时刻 $t_2$，船在点 $P_2$。船速为 $s$，航向为 $c$，则：

$$\overrightarrow{P_1P_2} = (s \cdot \Delta t \cdot \sin c,\; s \cdot \Delta t \cdot \cos c)$$

其中 $\Delta t = t_2 - t_1$（注意：角度 $c$ 从北顺时针，与常规数学坐标系不同，$\sin c$ 对应 $x$ 分量，$\cos c$ 对应 $y$ 分量）。

### 4. 求解位置

设第一次读数的直线为 $L_1: a_1x + b_1y + c_1 = 0$，第二次读数的直线为 $L_2: a_2x + b_2y + c_2 = 0$。$P_1$ 在 $L_1$ 上，$P_2$ 在 $L_2$ 上，且 $P_2 = P_1 + \vec{v}$，其中 $\vec{v} = (s\Delta t \sin c,\; s\Delta t \cos c)$。

联立方程可得 $P_1$ 坐标：

$$a_1x_1 + b_1y_1 + c_1 = 0$$
$$a_2(x_1 + v_x) + b_2(y_1 + v_y) + c_2 = 0$$

解此方程组得到 $P_1$，然后 $P_2 = P_1 + \vec{v}$。

### 5. 不可确定的情况

当两次读数的相对方位角相同或相差 $180^\circ$ 时，两个可能的信标方向直线彼此平行（或重合），无法唯一确定交点，此时输出 `"Position cannot be determined"`。

## 代码实现

```cpp
// Radio Direction Finder
// UVa ID: 217
// Verdict: Accepted
// Submission Date: 2016-06-16
// UVa Run Time: 0.070s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const double PI = 2.0 * acos(0.0), EPSILON = 1E-7;

// 点的结构体
struct point
{
    double x, y;
};

// 直线方程 ax + by + c = 0 的结构体
struct line
{
    double a, b, c;
};

// 船的状态：航向（度数）和速度
struct boat
{
    double course, speed;
};

// 信标读数：信标名称、时间、相对方位角
struct reading
{
    string name;
    double time, angle;
};

map<string, point> beacons;  // 信标名称到坐标的映射
reading reading1, reading2;   // 两次读数
boat mine;                    // 船的航向和速度

// 将相对方位角转换为相对于正东方向的角度，便于计算直线方程
double getAngle(double angle)
{
    if (angle <= 90.0 + EPSILON)
        return (90.0 - angle);
    else if (angle <= 270.0 + EPSILON)
        return -(angle - 90.0);
    else
        return 180.0 - (angle - 270.0);
}

// 根据一次读数，得到信标所在方向的直线方程
line getLine(reading data)
{
    line lr;
    
    // 实际方向角 = 航向 + 相对方位角，再转换到相对于正东的角度
    double angle = getAngle(mine.course + data.angle);
    
    // 处理垂直直线（角度为 ±90°）
    if (fabs(fabs(angle) - 90.0) <= EPSILON)
    {
        lr.a = 1.0;
        lr.b = 0.0;
        lr.c = -beacons[data.name].x;
    }
    else
    {
        // 一般情况：斜率为 tan(angle)，直线方程为 -tan(angle) * x + y + c = 0
        lr.a = -tan(angle * PI / 180.0);
        lr.b = 1.0;
        lr.c = -(lr.a * beacons[data.name].x + lr.b * beacons[data.name].y);
    }
    
    return lr;
}

// 计算并输出第二次读数时刻的船位
void calculate()
{
    // 两次读数之间的行驶距离
    double traveled = (reading2.time - reading1.time) * mine.speed;
    line line1 = getLine(reading1), line2 = getLine(reading2);
    
    // 航向弧度，注意：北为 0°，东为 90°，sin 对应 x 分量，cos 对应 y 分量
    double boatAngle = mine.course * PI / 180.0;
    
    // 联立直线方程求解第一次读数时的船位 P1
    double x1 = line1.c * line2.b - line1.b * line2.c -
        line1.b * line2.b * traveled * cos(boatAngle) -
        line1.b * line2.a * traveled * sin(boatAngle);
    x1 = x1 / (line1.b * line2.a - line1.a * line2.b);
    
    double y1 = line1.c * line2.a - line1.a * line2.c -
        line1.a * line2.a * traveled * sin(boatAngle) -
        line1.a * line2.b * traveled * cos(boatAngle);
    y1 = y1 / (line1.a * line2.b - line1.b * line2.a);
    
    // 输出第二次读数时船的位置：P2 = P1 + 位移向量
    cout << ": Position is (";
    cout << fixed << setprecision(2) << (x1 + traveled * sin(boatAngle)) << ", ";
    cout << fixed << setprecision(2) << (y1 + traveled * cos(boatAngle)) << ")" << endl;
}

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);
    
    int counter, cases = 0;
    while (cin >> counter)
    {
        beacons.clear();
        // 读入信标数据
        for (int i = 1; i <= counter; i++)
        {
            string name;
            double x, y;
            cin >> name >> x >> y;
            
            point location;
            location.x = x;
            location.y = y;
            
            beacons.insert(make_pair(name, location));
        }
        
        // 读入场景数量
        cin >> counter;
        for (int i = 1; i <= counter; i++)
        {
            cin >> mine.course >> mine.speed;
            cin >> reading1.time >> reading1.name >> reading1.angle;
            cin >> reading2.time >> reading2.name >> reading2.angle;
            
            cout << "Scenario " << ++cases;
            
            // 若两次读数的相对方位角相同或相差 180°，无法确定唯一位置
            if (fabs(reading1.angle - reading2.angle) <= EPSILON ||
                fabs(fabs(reading1.angle - reading2.angle) - 180.0) <= EPSILON)
            {
                cout << ": Position cannot be determined" << endl;
                continue;
            }
            
            calculate();
        }
    }
    
	return 0;
}
```

## 总结

本题的关键在于：

1. **角度转换**：正确将船的航向与相对方位角转换为便于几何计算的方向角
2. **直线方程**：每次读数对应一条可能的信标方向直线
3. **运动关系**：利用船的速度和两次读数的时间差，建立两个时刻船位之间的位移关系
4. **特殊情况**：当两条直线平行时无法确定交点，输出无法定位的信息
