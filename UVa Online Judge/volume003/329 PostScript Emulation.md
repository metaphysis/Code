[UVa 329 PostScript Emulation](https://blog.csdn.net/metaphysis/article/details/161513947)

## 题目描述

$\texttt{PostScript}$ 是一种广泛用于激光打印机的页面描述语言。$\texttt{PostScript}$ 中的基本测量单位是点（$\texttt{point}$），每英寸恰好有 $72$ 点。$\texttt{PostScript}$ 程序开始时使用的默认坐标系是熟悉的笛卡尔坐标系，原点（$x$ 和 $y$ 坐标均为 $0$ 的点）位于页面的左下角。

本题要求识别 $\texttt{PostScript}$ 语言的一小部分。具体来说，需要识别以下命令。所有命令均为小写字母。当命令描述中出现 `number` 时，输入数据中将出现一个浮点数值（可选符号和小数点）。当命令中出现两个数字时，第一个表示 $x$ 坐标，第二个表示 $y$ 坐标。为简单起见，每个命令独占一行，命令的每个组件之间用一个空格分隔。换行符紧跟在每个命令之后。以第一列为星号（`*`）的行终止输入。

需要保留操作顺序。

### 命令说明

| 命令 | 格式 | 说明 |
|------|------|------|
| `rotate` | `number rotate` | 将坐标系绕当前原点逆时针旋转指定角度（度）。不影响已经绘制在页面上的线条。 |
| `translate` | `number number translate` | 将坐标系原点移动到指定位置。数值相对于当前原点解释。 |
| `scale` | `number number scale` | 将给定的缩放因子应用于 $x$ 和 $y$ 坐标。缩放会影响该方向上的所有内容，无论之后如何旋转。 |
| `moveto` | `number number moveto` | 将当前点移动到指定坐标。 |
| `rmoveto` | `number number rmoveto` | 类似于 `moveto`，但指定的是相对于当前位置的坐标。 |
| `lineto` | `number number lineto` | 从当前位置到指定位置绘制一条线。当前位置变为命令中指定的位置。 |
| `rlineto` | `number number rlineto` | 类似于 `lineto`，但指定的是相对于当前位置的坐标。 |

### 任务

读取一个小的 $\texttt{PostScript}$ 程序，输出一个**产生相同效果但不使用 `rotate`、`translate` 或 `scale` 命令**的程序。即，输入程序中的 `moveto`、`rmoveto`、`lineto` 和 `rlineto` 命令应该出现在输出中（很可能带有修改后的数值），但输入中的 `rotate`、`translate` 和 `scale` 命令不得出现在输出中。

假设程序开始时使用默认坐标系。输出程序中的数字必须至少精确到两位小数。

### 样例输入

```
300 300 moveto
0 72 rlineto
2 1 scale
36 0 rlineto
1 -4 scale
0 18 rlineto
1 -0.25 scale
0.5 1 scale
300 300 translate
90 rotate
0 0 moveto
0 72 rlineto
2 1 scale
36 0 rlineto
1 -4 scale
0 18 rlineto
*
```

### 样例输出

```
300 300 moveto
0 72 rlineto
72 0 rlineto
0 -72 rlineto
300 300 moveto
-72 0 rlineto
0 72 rlineto
72 0 rlineto
```

---

## 题目分析

### 问题的本质

这是一个**坐标变换合成**问题。`rotate`、`translate` 和 `scale` 命令改变坐标系，而 `moveto`、`lineto` 等命令在当前坐标系下指定坐标。我们需要消除这些变换命令，将所有坐标变换的累积效果直接应用到绘图命令的坐标上。

换句话说，我们需要：
1. 维护当前坐标系相对于原始坐标系的变换矩阵
2. 遇到 `rotate`、`translate`、`scale` 时，更新变换矩阵
3. 遇到绘图命令时，将命令中的坐标通过当前变换矩阵转换回原始坐标系，然后输出转换后的数值

### 二维仿射变换的矩阵表示

在二维空间中，旋转、平移、缩放都可以用 $3 \times 3$ 的齐次坐标矩阵表示：

- **平移** `(tx, ty)`：
  $$
  \begin{bmatrix}
  1 & 0 & tx \\
  0 & 1 & ty \\
  0 & 0 & 1
  \end{bmatrix}
  $$

- **旋转** `angle`（逆时针，弧度制）：
  $$
  \begin{bmatrix}
  \cos\theta & -\sin\theta & 0 \\
  \sin\theta & \cos\theta & 0 \\
  0 & 0 & 1
  \end{bmatrix}
  $$

- **缩放** `(sx, sy)`：
  $$
  \begin{bmatrix}
  sx & 0 & 0 \\
  0 & sy & 0 \\
  0 & 0 & 1
  \end{bmatrix}
  $$

### 变换的累积

当连续应用多个变换时，变换矩阵是这些变换矩阵的乘积（按应用顺序从左到右相乘）。

设当前变换矩阵为 $M$。对于命令中的点 $(x, y)$，其在原始坐标系中的实际位置为：
$$
\begin{bmatrix} x' \\ y' \\ 1 \end{bmatrix} = M \cdot \begin{bmatrix} x \\ y \\ 1 \end{bmatrix}
$$

### 命令的转换

1. **绝对坐标命令**（`moveto`、`lineto`）：$(x, y)$ 是当前坐标系下的坐标，需要转换为原始坐标后再输出
2. **相对坐标命令**（`rmoveto`、`rlineto`）：$(\Delta x, \Delta y)$ 是相对于当前点的偏移量。需要转换为原始坐标系下的偏移量，即：
   - 当前点在原始坐标系中的位置为 $P_1 = M \cdot (cx, cy)$
   - 新点在当前坐标系中的位置为 $(cx + \Delta x, cy + \Delta y)$，在原始坐标系中为 $P_2 = M \cdot (cx + \Delta x, cy + \Delta y)$
   - 原始坐标系下的偏移量为 $P_2 - P_1$

---

## 解题思路

### 步骤一：维护变换矩阵

使用 $3 \times 3$ 矩阵 `im` 表示从当前坐标系到原始坐标系的变换。初始为单位矩阵。

对于每个变换命令：
- `translate tx ty`：构造平移矩阵 $T$，执行 `im = im * T`
- `rotate angle`：构造旋转矩阵 $R$（角度转换为弧度），执行 `im = im * R`
- `scale sx sy`：构造缩放矩阵 $S$，执行 `im = im * S`

### 步骤二：维护当前点坐标

为了处理相对命令，需要维护当前点在当前坐标系下的坐标 `(cx, cy)`。初始为 `(0, 0)`。

当遇到变换命令时，`(cx, cy)` 也需要相应变换：
- `translate tx ty`：`cx -= tx, cy -= ty`（因为原点移动了，当前点相对于新原点的坐标需要调整）
- `rotate angle`：将 `(cx, cy)` 旋转 `-angle`（因为坐标系旋转了，当前点在新坐标系中的坐标需要调整）
- `scale sx sy`：`cx /= sx, cy /= sy`

### 步骤三：处理绝对坐标命令

对于 `moveto` 和 `lineto`：
1. 将当前点 `(cx, cy)` 更新为命令中的坐标
2. 将命令中的坐标通过变换矩阵转换到原始坐标系
3. 输出转换后的坐标和命令类型

### 步骤四：处理相对坐标命令

对于 `rmoveto` 和 `rlineto`：
1. 计算当前点在原始坐标系中的位置 `(x1, y1) = transform(cx, cy)`
2. 更新当前点：`cx += dx, cy += dy`
3. 计算新点在原始坐标系中的位置 `(x2, y2) = transform(cx, cy)`
4. 原始坐标系下的偏移量为 `(dx', dy') = (x2 - x1, y2 - y1)`
5. 输出 `dx' dy'` 和命令类型

---
## 参考代码

```cpp
// PostScript Emulation
// UVa ID: 329
// Verdict: Accepted
// Submission Date: 2019-11-03
// UVa Run Time: 0.140s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

// 当前变换矩阵（3x3），将当前坐标转换为原始坐标
double im[3][3] = {
    {1, 0, 0},
    {0, 1, 0},
    {0, 0, 1}
};

// 将矩阵 rm 左乘到当前矩阵上：im = im * rm
void multiply(double rm[3][3])
{
    double tmp[3][3];
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++) {
            tmp[i][j] = 0;
            for (int k = 0; k < 3; k++)
                tmp[i][j] += im[i][k] * rm[k][j];
        }
    memcpy(im, tmp, sizeof(tmp));
}

// 将当前坐标系下的点 (x, y) 转换为原始坐标系下的坐标
pair<double, double> restore(double x, double y)
{
    double nx = im[0][0] * x + im[0][1] * y + im[0][2];
    double ny = im[1][0] * x + im[1][1] * y + im[1][2];
    return make_pair(nx, ny);
}

const double PI = 2.0 * acos(0);

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string line, parameter;
    double cx = 0, cy = 0;  // 当前点在当前坐标系下的坐标

    while (getline(cin, line), line != "*") {
        vector<string> cmd;
        istringstream iss(line);
        while (iss >> parameter) cmd.push_back(parameter);

        string command = cmd.back();
        
        if (command == "translate") {
            double tx = stod(cmd[0]);
            double ty = stod(cmd[1]);
            // 构造平移矩阵
            double rm[3][3] = {
                {1, 0, tx},
                {0, 1, ty},
                {0, 0, 1}
            };
            multiply(rm);
            // 更新当前点坐标
            cx -= tx, cy -= ty;
        } 
        else if (command == "rotate") {
            double alpha = stod(cmd.front()) * PI / 180.0;
            // 构造旋转矩阵
            double rm[3][3] = {
                {cos(alpha), -sin(alpha), 0},
                {sin(alpha), cos(alpha), 0},
                {0, 0, 1}
            };
            multiply(rm);
            // 更新当前点坐标（逆旋转）
            double nextx = cx * cos(alpha) + cy * sin(alpha);
            double nexty = -cx * sin(alpha) + cy * cos(alpha);
            cx = nextx, cy = nexty;
        } 
        else if (command == "scale") {
            double sx = stod(cmd[0]);
            double sy = stod(cmd[1]);
            // 构造缩放矩阵
            double rm[3][3] = {
                {sx, 0, 0},
                {0, sy, 0},
                {0, 0, 1}
            };
            multiply(rm);
            // 更新当前点坐标
            cx /= sx, cy /= sy;
        } 
        else if (command == "moveto" || command == "lineto") {
            // 绝对坐标命令
            cx = stod(cmd[0]);
            cy = stod(cmd[1]);
            pair<double, double> r = restore(cx, cy);
            cout << fixed << setprecision(6) << r.first << ' ';
            cout << fixed << setprecision(6) << r.second << ' ';
            cout << command << '\n';
        } 
        else if (command == "rmoveto" || command == "rlineto") {
            // 相对坐标命令
            double dx = stod(cmd[0]);
            double dy = stod(cmd[1]);
            // 当前点在原始坐标系中的位置
            pair<double, double> r1 = restore(cx, cy);
            // 更新当前点
            cx += dx;
            cy += dy;
            // 新点在原始坐标系中的位置
            pair<double, double> r2 = restore(cx, cy);
            // 输出原始坐标系下的偏移量
            cout << fixed << setprecision(6) << (r2.first - r1.first) << ' ';
            cout << fixed << setprecision(6) << (r2.second - r1.second) << ' ';
            cout << command << '\n';
        }
    }
    return 0;
}
```

---

## 总结

本题的核心在于：
1. **仿射变换的矩阵表示**：使用 $3 \times 3$ 齐次坐标矩阵统一表示平移、旋转、缩放
2. **变换累积**：矩阵乘法按顺序累积所有变换
3. **坐标转换**：将变换后的坐标还原到原始坐标系
4. **当前点维护**：正确处理相对坐标命令

### 关键点回顾

| 知识点 | 说明 |
|--------|------|
| 变换矩阵 | $3 \times 3$ 齐次坐标矩阵 |
| 矩阵乘法 | 按执行顺序左乘 |
| 平移 | `[1 0 tx; 0 1 ty; 0 0 1]` |
| 旋转 | `[cosθ -sinθ 0; sinθ cosθ 0; 0 0 1]` |
| 缩放 | `[sx 0 0; 0 sy 0; 0 0 1]` |
| 绝对坐标 | 直接变换后输出 |
| 相对坐标 | 变换前后点坐标之差 |

### 坐标变换的数学原理

当坐标系经过一系列变换后，点在新坐标系下的坐标 $(x, y)$ 与在原始坐标系下的坐标 $(x', y')$ 之间的关系为：

$$
\begin{bmatrix} x' \\ y' \\ 1 \end{bmatrix} = M_n \cdot M_{n-1} \cdots M_1 \cdot \begin{bmatrix} x \\ y \\ 1 \end{bmatrix}
$$

其中 $M_i$ 是第 $i$ 个变换的矩阵。本题正是通过累积这些矩阵，将绘图命令中的坐标还原到原始坐标系中。
