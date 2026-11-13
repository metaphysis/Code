[UVa 203 Running Lights Visibility Calculator](https://blog.csdn.net/metaphysis/article/details/161009036)

## 题目分析

本题是一个船舶航行灯可见性判断与碰撞预警问题。在夜间航行的船舶需要显示航行灯，以便其他船舶判断其位置和运动方向。每艘船舶配备四种航行灯：

- **桅顶灯 ($\texttt{Masthead}$)**：照射 $360^\circ$ 全方向
- **艉灯 ($\texttt{Stern}$)**：照射 $110^\circ$ 至 $250^\circ$ 之间（严格）
- **左舷灯 ($\texttt{Red}$)**：照射 $245^\circ$ 至 $2.5^\circ$ 之间（严格）
- **右舷灯 ($\texttt{Green}$)**：照射 $357.5^\circ$ 至 $115^\circ$ 之间（严格）

所有航行灯的最大可见距离为 $10$ 海里。题目要求：

1. 计算其他船舶相对于本船的相对方位角，并判断可见的灯光配置（从左到右排列）
2. 模拟 $3$ 分钟后的船舶位置，若某船初始可见、距离减小、且相对方位角变化不超过 $2^\circ$，则发出碰撞警告

## 解题思路

### 1. 相对方位角计算

题目定义：从船舶 $A$ 到船舶 $B$ 的**相对方位角**是船舶 $A$ 的航向与向量 $\overrightarrow{AB}$ 之间的顺时针夹角。

计算步骤：
- 计算向量 $\overrightarrow{AB}$ 的方向角（以正北为 $0^\circ$，顺时针增加）
- 减去船舶 $A$ 的航向
- 若结果为负，则加 $360^\circ$

需要注意的是，$\texttt{atan2}$ 函数返回的是与正 $x$ 轴的夹角，需要转换为与正北的夹角。

### 2. 灯光配置判断

根据计算得到的相对方位角，判断从本船观察到的其他船舶的灯光配置。由于灯光照射区域有重叠，需要按照题目给出的区间精确判断。例如：
- 方位角在 $[0^\circ, 2.5^\circ)$ 时，可见灯光为 `Masthead Green Red`
- 方位角在 $[2.5^\circ, 110^\circ]$ 时，可见灯光为 `Masthead Green`
- 等等

当多盏灯在一条直线上时，按字母顺序输出。

### 3. 碰撞预警逻辑

- 初始距离 $\leq 10$ 海里（船舶可见）
- $3$ 分钟后距离减小
- $3$ 分钟后相对方位角变化 $\leq 2^\circ$（考虑 $358^\circ$ 到 $2^\circ$ 的边界情况）

满足以上三个条件则发出碰撞警告，输出船舶名称和 $3$ 分钟后的距离。

### 4. 精度处理

题目要求使用 $\epsilon = 10^{-7}$ 的精度控制浮点数比较。输出时：
- 方位角、距离四舍五入保留两位小数
- 方位角 $\geq 359.995^\circ$ 应输出 $0.00^\circ$
- 转换角度时使用预定义的 $\pi$ 常量

### 5. 运动模拟

船舶速度单位为节（海里/小时），$3$ 分钟为 $1/20$ 小时。位置更新公式：

$$
\begin{aligned}
x_{\text{new}} &= x + \frac{\text{speed}}{20} \cdot \sin(\text{course} \cdot \pi / 180) \\
y_{\text{new}} &= y + \frac{\text{speed}}{20} \cdot \cos(\text{course} \cdot \pi / 180)
\end{aligned}
$$

需要注意的是，航向角以正北为 $0^\circ$，顺时针增加，因此 $x$ 方向使用 $\sin$，$y$ 方向使用 $\cos$。

## 代码实现

```cpp
// Running Lights Visibility Calculator
// UVa ID: 203
// Verdict: Accepted
// Submission Date: 2016-04-20
// UVa Run Time: 0.040s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const double PI = 3.14159265358979323846, EPSILON = 1E-7;

// 船舶结构体
struct ship {
    string name;          // 船名
    double x, y;          // 坐标位置
    double course, speed; // 航向（度）和速度（节）
    double bearing, distance;   // 初始相对方位角和距离
    double bearing1, distance1; // 3分钟后的相对方位角和距离
};

string scenario;          // 当前场景ID
vector<ship> ships;       // 存储所有船舶（下标0为本船）

// 将方位角格式化为保留两位小数的字符串，处理360.00 -> 0.00的情况
string roundedBearing(double bearing) {
    stringstream ss;
    ss << fixed << setprecision(2) << (bearing + EPSILON);
    string number;
    ss >> number;
    if (number == "360.00") number = "0.00";
    return number;
}

// 计算从 other 船到 own 船的相对方位角
// 参数：other - 被观测船，own - 观测船（本船）
double getBearing(ship othership, ship ownship) {
    // 计算向量 from other  to  own 的方向角（与正x轴的夹角，弧度）
    double bearing = atan2(ownship.y - othership.y, ownship.x - othership.x);
    bearing = bearing * 180.0 / PI;

    // 将方向角转换为与正北的夹角（顺时针从正北起算）
    if (bearing < 0.0)
        bearing = -bearing + 90.0;
    else if (bearing > 90.0 && bearing <= 180.0)
        bearing = 270.0 + (180.0 - bearing);
    else if (bearing >= 0.0 && bearing <= 90.0)
        bearing = 90.0 - bearing;

    // 计算相对方位角：目标方向角减去观测船的航向
    if (bearing > othership.course) bearing -= othership.course;
    else bearing = 360.0 - fabs(bearing - othership.course);

    return bearing;
}

// 根据相对方位角判断可见灯光配置（从左到右）
string getLights(double bearing) {
      if(bearing >= 360.0 - EPSILON || bearing <= 0.0 + EPSILON)
        return "Green Masthead Red";
      else if(bearing > 0.0 + EPSILON && bearing < 2.5 - EPSILON)
        return "Masthead Green Red";
      else if(bearing >= 2.5 - EPSILON && bearing <= 110.0 + EPSILON)
        return "Masthead Green";
      else if(bearing > 110.0 + EPSILON && bearing < 115.0 - EPSILON)
        return "Stern Masthead Green";
      else if(bearing >= 115.0 - EPSILON && bearing < 180.0 - EPSILON)
        return "Stern Masthead";
      else if(bearing >= 180.0 - EPSILON && bearing <= 245.0 + EPSILON)
        return "Masthead Stern";
      else if(bearing > 245.0 + EPSILON && bearing < 250.0 - EPSILON)
        return "Red Masthead Stern";
      else if(bearing >= 250.0 - EPSILON && bearing <= 357.5 + EPSILON)
        return "Red Masthead";
      else if(bearing > 357.5 + EPSILON && bearing < 360.0 - EPSILON)
        return "Green Red Masthead";
}

// 计算并输出当前场景的结果
void calculate() {
    // 输出表头
    cout << "Scenario: " << scenario << "\n" << "\n";
    cout << setw(16) << left << "Boat ID";
    cout << setw(7) << right << "Bearing";
    cout << setw(14) << right << "Distance";
    cout << string(3, ' ');;
    cout << "Lights (left to right)" << "\n";
    cout << string(63, '-') << "\n";

    // 计算每艘其他船相对于本船的初始方位角和距离
    for (int i = 1; i < ships.size(); i++) {
        cout << setw(16) << left << ships[i].name;
        ships[i].bearing = getBearing(ships[i], ships[0]);
        ships[i].distance = sqrt(pow(ships[0].x - ships[i].x, 2) + pow(ships[0].y - ships[i].y, 2));
        cout << setw(7) << right <<  fixed << setprecision(2) << roundedBearing(ships[i].bearing);
        cout << setw(12) << right << fixed << setprecision(2) << (ships[i].distance + EPSILON);
        cout << string(5, ' ');

        // 判断灯光是否可见（距离不超过10海里）
        if (ships[i].distance <= (10.0 + EPSILON)) cout << getLights(ships[i].bearing) << "\n";
        else cout << "Lights not visible" << "\n";
    }

    // 模拟3分钟后所有船舶的位置（3分钟 = 1/20小时）
    for (int i = 0; i < ships.size(); i++) {
        ships[i].x += ships[i].speed / 20.0 * sin(ships[i].course * PI / 180.0);
        ships[i].y += ships[i].speed / 20.0 * cos(ships[i].course * PI / 180.0);
    }

    // 重新计算3分钟后的方位角和距离，判断碰撞风险
    for (int i = 1; i < ships.size(); i++) {
        ships[i].bearing1 = getBearing(ships[i], ships[0]);
        ships[i].distance1 = sqrt(pow(ships[0].x - ships[i].x, 2) + pow(ships[0].y - ships[i].y, 2));

        // 条件：初始可见 且 距离减小 且 方位角变化不超过2度
        if (ships[i].distance <= (10.0 + EPSILON) && ships[i].distance1 < (ships[i].distance - EPSILON)) {
            double difference = fabs(ships[i].bearing - ships[i].bearing1);
            // 处理跨越360度边界的情况（如358度到2度）
            if (difference <= 2.0 + EPSILON || difference >= 358.0 + EPSILON)
            cout << "** Collision warning -->" << ships[i].name << ":  Distance =  "
                 << fixed << setprecision(2) << (ships[i].distance1 + EPSILON) << "\n";
        }  
    }
    
    // 输出场景结束分隔线
    cout << string(63, '*') << "\n";
}

int main() {
    cin.tie(0);
    cout.sync_with_stdio(false);

    int shipNumber;
    string line;
    // 循环读取每个测试场景，直到文件结束
    while (getline(cin, scenario)) {
        getline(cin, line);
        shipNumber = stoi(line);

        ships.resize(shipNumber + 1);  // 下标0为本船，下标1~shipNumber为其他船
        for (int i = 0; i < ships.size(); i++) {
            getline(cin, ships[i].name);
            getline(cin, line);
            istringstream iss(line);
            iss >> ships[i].x >> ships[i].y >> ships[i].course >> ships[i].speed;
        }

        calculate();
    }
    
	return 0;
}
```
