[UVa 407 Gears on a Board](https://blog.csdn.net/metaphysis/article/details/161737098)

## 题目描述

题目模拟了一个二维平面上的齿轮系统。齿轮安装在 $300 \times 300$ 的网格点上（坐标范围 $1$ 到 $300$），每个齿轮有内半径（靠近板面）和外半径（远离板面）。齿轮绕其中心旋转，当两个齿轮接触时（内半径相切或外半径相切），它们会以相等的线速度驱动对方。

系统中有一个马达齿轮（$\texttt{motor gear}$），是唯一的动力来源，以给定的转速（$\texttt{RPM}$）旋转。需要计算其他齿轮的旋转方向和转速，并检测以下错误和警告：

- **重叠错误（$\texttt{Error -- Overlapping Gears}$）** ：两个或更多齿轮在内半径或外半径处发生重叠（即圆心距小于两半径之和）。
- **冲突错误（$\texttt{Error -- Conflicting Gear Rotation}$）** ：某个齿轮被两个不同的转速驱动（即通过不同路径到达同一齿轮时，计算出的转速不一致）。
- **空闲警告（$\texttt{Warning -- Idle Gear}$）** ：某个齿轮的转速为零（未被驱动）。

## 输入格式

输入包含多组配置，每组配置的格式如下：
- 第一行包含六个整数：马达的 $x$、$y$ 坐标，内半径 $ir$、外半径 $or$，转速 $AV$（负数表示逆时针，正数表示顺时针），以及齿轮数量 $NG$（$1 \le NG \le 20$，不包括马达）。
- 接下来 $NG$ 行，每行包含四个整数：齿轮的 $x$、$y$ 坐标，内半径 $ir$ 和外半径 $or$。

所有坐标和半径均为整数，范围 $1$ 到 $300$（坐标）或 $1$ 到 $100$（半径），转速绝对值 $1$ 到 $1000$。

## 输出格式

对于每组配置，首先输出一行 `Simulation #X`，其中 $X$ 从 $1$ 开始递增，左对齐从第 $13$ 列开始。

如果没有错误：
- 输出 $NG$ 行（不包括马达），每行格式为：齿轮编号（右对齐占 $2$ 列）、冒号（第 $3$ 列）、方向（第 $5$ 列，`L` 表示逆时针，`R` 表示顺时针）、转速（从第 $7$ 列开始左对齐，保留两位小数）。
- 如果某齿轮转速为零，输出 `Warning -- Idle Gear`（从第 $5$ 列到第 $24$ 列）。

如果有错误：
- 只输出两行：第一行为 `Simulation #X`，第二行为错误信息（左对齐从第 $1$ 列开始）。重叠错误优先于冲突错误。

每组输出后跟一个空行。

## 样例

输入

```
20 100 5 5 -300 5
43 100 18 10
43 74 8 4
71 100 10 15
94 100 3 8
122 100 25 6
20 100 5 5 -300 5
43 100 18 10
43 74 8 4
71 100 10 10
89 100 3 8
105 100 25 6
20 100 5 5 -300 5
43 100 18 10
43 74 8 4
71 100 10 10
89 100 3 8
125 100 25 6
```

输出

```
Simulation #1
 1: R 83.33
 2: L 187.50
 3: L 150.00
 4: R 281.25
 5: L 33.75

Simulation #2
Error -- Overlapping Gears

Simulation #3
 1: R 83.33
 2: L 187.50
 3: L 150.00
 4: R 187.50
 5: Warning -- Idle Gear

```

## 题目分析

本题的核心是建立齿轮之间的接触关系图，然后从马达齿轮开始进行广度优先遍历（$\texttt{BFS}$），计算每个齿轮的转速和方向，同时检测重叠、冲突和空闲情况。

### 齿轮接触判定

两个齿轮 $i$ 和 $j$ 的圆心距为：
$$
d = \sqrt{(x_i - x_j)^2 + (y_i - y_j)^2}
$$

接触条件：
- **内半径接触**：$d = ir_i + ir_j$（精度允许 $10^{-6}$ 误差）
- **外半径接触**：$d = or_i + or_j$

如果 $d < ir_i + ir_j$ 或 $d < or_i + or_j$，则发生重叠错误。

### 转速计算

当两个齿轮接触时，接触点的线速度相等。设齿轮 $i$ 的转速为 $v_i$（$\texttt{RPM}$），半径为 $r_i$（接触时使用的半径），则线速度为 $v_i \times r_i$。对于齿轮 $j$，有：
$$
v_i \times r_i = v_j \times r_j
$$
因此：
$$
v_j = \frac{r_i}{r_j} \times v_i
$$

接触类型决定了使用的半径：
- 内半径接触：使用内半径 $ir$
- 外半径接触：使用外半径 $or$

### 方向规则

当两个齿轮通过内半径接触时，旋转方向相反；通过外半径接触时，旋转方向也相反。因此无论哪种接触，相邻齿轮的方向始终相反。

设马达的转速符号为负表示逆时针（$\texttt{L}$），正表示顺时针（$\texttt{R}$）。遍历时，每经过一条边，方向取反。

### 冲突检测

如果某个齿轮已经被访问过，再次通过另一条路径到达时：
- 新计算出的方向必须与已记录的方向一致
- 新计算出的转速（绝对值）必须与已记录的转速相等（误差 $10^{-6}$ 内）

若任一条件不满足，则产生冲突错误。

### 重叠错误的优先级

题目明确指出，重叠错误优先于冲突错误。因此检测顺序为：先检查所有齿轮对是否存在重叠，若有则直接输出重叠错误，不再进行后续的转速计算。

### 空闲齿轮

遍历结束后，转速为零的齿轮（未被任何齿轮驱动，或虽然被驱动但计算出的转速为零）应输出空闲警告。注意马达齿轮本身不输出。

## 代码实现

```cpp
// Gears on a Board
// UVa ID: 407
// Verdict: Accepted
// Submission Date: 2016-08-06
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const double epsilon = 1e-6;

struct gear
{
    int index;
    double x, y, gir, gor;
    bool is_rotate_left;
    double velocity;
};

struct adjacent
{
    int index;
    bool ir_touched, or_touched;
};

int cases = 0, ng;
vector<gear> gears;
vector<vector<adjacent>> edges;

void run()
{
    cout << "Simulation #" << ++cases << '\n';
    
    edges.assign(ng, vector<adjacent>());
        
    for (int i = 0; i < ng; i++)
        for (int j = i + 1; j < ng; j++)
        {
            adjacent edge;
            edge.index = j, edge.ir_touched = false, edge.or_touched = false;

            double d = sqrt(pow(gears[i].x - gears[j].x, 2) + pow(gears[i].y - gears[j].y, 2));
            
            if (d < gears[i].gir + gears[j].gir - epsilon ||
                d < gears[i].gor + gears[j].gor - epsilon)
            {
                cout << "Error -- Overlapping Gears\n\n";
                return;
            }
            
            if (fabs(d - gears[i].gir - gears[j].gir) < epsilon)
                edge.ir_touched = true;
            
            if (fabs(d - gears[i].gor - gears[j].gor) < epsilon)
                edge.or_touched = true;
            
            if (edge.ir_touched || edge.or_touched)
            {
                edges[i].push_back(edge);
                edge.index = i;
                edges[j].push_back(edge);
            }
        }
        
    vector<bool> visited(ng, false);
    
    queue<int> unvisited;
    unvisited.push(0);
    visited[0] = true;
    
    while (unvisited.empty() == false)
    {
        int current = unvisited.front();
        unvisited.pop();
        
        bool is_rotate_left = !gears[current].is_rotate_left;

        for (auto edge : edges[current])
        {
            double final_velocity, ir_velocity = -1.0, or_velocity = -1.0;
            if (edge.ir_touched)
            {
                ir_velocity = gears[current].gir / gears[edge.index].gir * gears[current].velocity;
                final_velocity = ir_velocity;
            }

            if (edge.or_touched)
            {
                or_velocity = gears[current].gor / gears[edge.index].gor * gears[current].velocity;
                final_velocity = or_velocity;
            }
            
            if (ir_velocity > 0 && or_velocity > 0 && fabs(ir_velocity - or_velocity) > epsilon)
            {
                cout << "Error -- Conflicting Gear Rotation\n\n";
                return;
            }
            
            if (visited[edge.index] == false)
            {
                gears[edge.index].is_rotate_left = is_rotate_left;
                gears[edge.index].velocity = final_velocity;
                visited[edge.index] = true;
                unvisited.push(edge.index);
            }
            else
            {
                if (gears[edge.index].is_rotate_left != is_rotate_left ||
                    fabs(gears[edge.index].velocity - final_velocity) > epsilon)
                {
                    cout << "Error -- Conflicting Gear Rotation\n\n";
                    return;
                }
            }
        }
    }
    
    for (int i = 1; i < ng; i++)
    {
        cout << ' ' << i << ": ";
        
        if (fabs(gears[i].velocity) < epsilon)
        {
            cout << "Warning -- Idle Gear\n";
            continue;
        }

        cout << (gears[i].is_rotate_left ? 'L' : 'R');
        cout << ' ' << fixed << setprecision(2) << gears[i].velocity;
        cout << '\n';
    }
    cout << '\n';
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    double x, y, gir, gor, velocity;
    gear motor;
    
    while (cin >> motor.x >> motor.y >> motor.gir >> motor.gor >> motor.velocity >> ng)
    {
        gears.clear();

        motor.is_rotate_left = motor.velocity < 0;
        motor.velocity = fabs(motor.velocity);
        gears.push_back(motor);

        for (int i = 1; i <= ng; i++)
        {
            cin >> x >> y >> gir >> gor;
            gears.push_back((gear){i, x, y, gir, gor, false, 0.0});
        }
        
        ng++;
        
        run();
    }
    
    return 0;
}
```