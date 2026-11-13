[UVa 241 Sail Race](https://blog.csdn.net/metaphysis/article/details/161143475)

## 题目描述

大西洋海岸水手帆船俱乐部需要开发一个比赛时间估计工具。给定一系列标位（最多 $10$ 个）、恒定的风速和风向、以及帆船的航行性能参数，要求计算帆船完成比赛的最短时间。

### 关键规则

1. **坐标系**：正北为 $y$ 轴正方向，正东为 $x$ 轴正方向，单位为海里（$\texttt{nm}$）。
2. **风向**：用 $000.0^\circ \sim 359.9^\circ$ 表示，$000.0^\circ$ 为正北，顺时针增加。
3. **航行限制**：帆船不能驶入与风向夹角小于“顶风角”（$\texttt{point angle}$）的区域。  
   - 如果目标方向与风向的夹角 $\alpha \ge$ 顶风角，可以直接航行。
   - 否则，必须通过换舷（$\texttt{tack}$）来回航行：先沿顶风角方向行驶一段，再换到另一侧顶风角方向行驶，从而间接到达目标点。
4. **速度计算**：速度 = 风速 × 速度比，速度比取决于“与风夹角”（$\texttt{angle off wind}$）所在的区间：
   - 顶风区（$\texttt{point angle}$ $\le \alpha <$ $\texttt{reach angle}$）：使用 $\texttt{point speed ratio}$
   - 横风区（$\texttt{reach angle}$ $\le \alpha <$ $\texttt{downwind angle}$）：使用 $\texttt{reach speed ratio}$
   - 顺风区（$\alpha \ge$ $\texttt{downwind angle}$）：使用 $\texttt{downwind speed ratio}$
5. **罚时**：每次换舷或经过标位（起点除外）都会产生一次罚时，罚时时间固定（输入给出）。
6. **最优化要求**：每段赛程（两个标位之间）必须以 **最少换舷次数** 和 **最短航行距离** 完成。

## 题目分析与解题思路

### 核心难点

本题的核心在于“最少换舷次数”与“最短距离”的同时满足。这实际上是一个几何问题：

- 可行航行方向只有两个（对称于风向）：$\phi_1 = windDir + pointAngle$ 和 $\phi_2 = windDir- pointAngle$。
- 任意航向必须是这两个方向的线性组合（因为不能直接驶入禁止区）。
- 由起点到终点的向量 $\vec{D}$ 可以表示为：
$$
  \vec{D} = a \cdot \vec{u}_1 + b \cdot \vec{u}_2
$$
  其中 $\vec{u}_1, \vec{u}_2$ 分别是 $\phi_1, \phi_2$ 方向的单位向量。
- 解出 $a, b$ 后，如果 $a, b \ge 0$，则最少换舷次数为 $1$（两段航行），否则不可达（但题目保证可达）。  
  **注意**：此时的分段数（$\texttt{tack legs}$）为 $2$，换舷事件次数为 $1$。
- 如果目标方向 $\alpha \ge pointAngle$，则可以直接航行（$a = |\vec{D}|, b = 0$），分段数为 $1$，换舷事件次数为 $0$。

因此，我们只需对每一段赛程判断是否直接航行，否则解线性方程组即可。

### 关键计算步骤

#### 1. 方向角与夹角

给定起点 $(x_1, y_1)$ 和终点 $(x_2, y_2)$：

- 位移向量：$\Delta x = x_2 - x_1,\ \Delta y = y_2 - y_1$。
- 距离：$d = \sqrt{\Delta x^2 + \Delta y^2}$。
- 目标方向（单位：度，从正北顺时针）：
 $$
  targetDir = \text{atan2}(\Delta x, \Delta y)
 $$
  返回值范围 $(-\pi, \pi]$，需要转换到 $[0, 360)$。

- 与风向夹角：
 $$
  \alpha = \min(|targetDir - windDir|,\ 360 - |targetDir - windDir|)
 $$

#### 2. 速度计算

设风速为 $ws$，与风夹角为 $\alpha$，速度比由 $\alpha$ 所在区间决定：

$$
\text{ratio} =
\begin{cases}
p_r & \text{if } \alpha \in [p_a, r_a) \\
r_r & \text{if } \alpha \in [r_a, d_a) \\
d_r & \text{if } \alpha \ge d_a
\end{cases}
$$
其中 $p_a, r_a, d_a$ 分别表示 $\texttt{point angle}$、$\texttt{reach angle}$、$\texttt{downwind angle}$，$p_r, r_r, d_r$ 是对应的速度比。

则船速 $v = ratio \times ws$。

#### 3. 分段航行（必须换舷时）

设两个可行方向：
$$
\phi_1 = windDir + pointAngle,\quad \phi_2 = windDir - pointAngle
$$
将角度转换为弧度，计算单位向量：
$$
\vec{u}_1 = (\cos\phi_1, \sin\phi_1),\quad \vec{u}_2 = (\cos\phi_2, \sin\phi_2)
$$
解线性方程组：
$$
\begin{cases}
a \cos\phi_1 + b \cos\phi_2 = \Delta x \\
a \sin\phi_1 + b \sin\phi_2 = \Delta y
\end{cases}
$$
使用克莱姆法则：
$$
\Delta = \sin\phi_1 \cos\phi_2 - \sin\phi_2 \cos\phi_1 \\
a = \frac{\Delta x \cos\phi_2 - \Delta y \sin\phi_2}{\Delta},\quad
b = \frac{\Delta y \sin\phi_1 - \Delta x \cos\phi_1}{\Delta}
$$
理论上 $a, b \ge 0$，若出现微小负数可视为 $0$。

#### 4. 总段数与罚时

- 直接航行：该赛程贡献 $1$ 个航段（$\texttt{tack leg}$）。
- 两段航行：贡献 $2$ 个航段。
- 总航段数 $S = \sum$ 每个赛程的航段数。
- 罚时次数 = $S - 1$（因为第一次航行前无罚时，此后每新开始一段航程罚一次）。
- 总罚时时间 = $(S - 1) \times tackPenalty$。

#### 5. 总时间

总航行时间 = $\sum \frac{\text{各航段距离}}{\text{各航段速度}}$  
总比赛时间 = 总航行时间 + 总罚时时间。

### 输入输出处理

- 多组测试数据，以 `0 0 0 0` 结束。
- 输出格式需严格按照题目要求：先输出 `Race` 信息，再输出 `layout` 长度，然后逐 `Leg` 输出，最后输出汇总。
- 每组数据之间用空行隔开。

## 代码实现

```cpp
// Sail Race
// UVa ID: 241
// Verdict: Accepted
// Submission Date: 2026-05-16
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 角度转弧度
double toRadians(double deg) { return deg * M_PI / 180.0; }
// 弧度转角度
double toDegrees(double rad) { return rad * 180.0 / M_PI; }

// 将角度归一化到 [0, 360)
double normalizeAngle(double a) {
    a = fmod(a, 360.0);
    if (a < 0) a += 360.0;
    return a;
}

// 计算两个角度之间的最小夹角 (0~180)
double angleDiff(double a, double b) {
    double d = fabs(a - b);
    if (d > 180) d = 360 - d;
    return d;
}

// 根据与风夹角计算船速
double boatSpeed(double ws, double off, double pa, double pr,
                 double ra, double rr, double da, double dr) {
    if (off < pa - 1e-9) return 0;          // 不可航行（理论上不会发生）
    if (off < ra) return pr * ws;
    if (off < da) return rr * ws;
    return dr * ws;
}

int main() {
    int raceNum = 0;
    double windDir, windSpeed, tackPenalty;
    int n;

    while (cin >> windDir >> windSpeed >> tackPenalty >> n) {
        if (windDir == 0 && windSpeed == 0 && tackPenalty == 0 && n == 0) break;
        raceNum++;

        // 读取第二行：6 个航行性能参数
        double pointAngle, pointRatio, reachAngle, reachRatio, downwindAngle, downwindRatio;
        cin >> pointAngle >> pointRatio >> reachAngle >> reachRatio >> downwindAngle >> downwindRatio;

        // 读取 n 个标位信息
        vector<tuple<string, double, double>> marks(n);
        for (int i = 0; i < n; i++) {
            cin >> get<0>(marks[i]) >> get<1>(marks[i]) >> get<2>(marks[i]);
        }

        // 预先计算 layout 总长度（各段直线距离之和）
        double layoutLen = 0;
        for (int i = 0; i < n - 1; i++) {
            auto [name1, x1, y1] = marks[i];
            auto [name2, x2, y2] = marks[i + 1];
            double dx = x2 - x1, dy = y2 - y1;
            layoutLen += sqrt(dx * dx + dy * dy);
        }

        // 输出 race 标题和 layout 长度
        cout << "Race " << raceNum << " has " << n - 1 << " legs\n";
        cout << "The race layout is " << fixed << setprecision(2) << layoutLen << " nm long\n\n";

        double totalDist = 0, totalTime = 0;
        int totalSegments = 0, tackSeq = 0;

        // 处理每个 Leg（两个相邻标位之间）
        for (int i = 0; i < n - 1; i++) {
            auto [name1, x1, y1] = marks[i];
            auto [name2, x2, y2] = marks[i + 1];
            double dx = x2 - x1, dy = y2 - y1;
            double directDist = sqrt(dx * dx + dy * dy);
            double targetDir = normalizeAngle(toDegrees(atan2(dx, dy)));

            cout << "Leg " << i + 1 << " from Mark " << name1 << " to " << name2
                 << ": direction = " << fixed << setprecision(1) << targetDir
                 << ", distance = " << fixed << setprecision(2) << directDist << " nm\n";

            double alpha = angleDiff(targetDir, windDir);

            // 情况1：可以直接航行
            if (alpha >= pointAngle) {
                double speed = boatSpeed(windSpeed, alpha, pointAngle, pointRatio,
                                         reachAngle, reachRatio, downwindAngle, downwindRatio);
                totalDist += directDist;
                totalTime += directDist / speed;
                totalSegments++;
                cout << "Tack " << ++tackSeq << ": speed = " << fixed << setprecision(1) << speed
                     << ", direction = " << fixed << setprecision(1) << targetDir
                     << ", distance = " << fixed << setprecision(2) << directDist << " nm\n";
            }
            // 情况2：必须换舷，两段航行
            else {
                double phi1 = normalizeAngle(windDir + pointAngle);
                double phi2 = normalizeAngle(windDir - pointAngle);

                double rad1 = toRadians(phi1), rad2 = toRadians(phi2);
                double sin1 = sin(rad1), cos1 = cos(rad1);
                double sin2 = sin(rad2), cos2 = cos(rad2);

                // 解线性方程组求两段距离 a, b
                double det = sin1 * cos2 - sin2 * cos1;
                double a = (dx * cos2 - dy * sin2) / det;
                double b = (dy * sin1 - dx * cos1) / det;

                // 两段速度相同（因为与风夹角 = pointAngle）
                double speed = boatSpeed(windSpeed, pointAngle, pointAngle, pointRatio,
                                         reachAngle, reachRatio, downwindAngle, downwindRatio);

                totalDist += a + b;
                totalTime += a / speed + b / speed;
                totalSegments += 2;

                cout << "Tack " << ++tackSeq << ": speed = " << fixed << setprecision(1) << speed
                     << ", direction = " << fixed << setprecision(1) << phi1
                     << ", distance = " << fixed << setprecision(2) << a << " nm\n";
                cout << "Tack " << ++tackSeq << ": speed = " << fixed << setprecision(1) << speed
                     << ", direction = " << fixed << setprecision(1) << phi2
                     << ", distance = " << fixed << setprecision(2) << b << " nm\n";
            }
            cout << '\n';
        }

        // 罚时计算：总航段数 - 1
        int penaltyCount = totalSegments - 1;
        double totalPenalty = penaltyCount * tackPenalty;

        cout << "Race " << raceNum << " was " << fixed << setprecision(2) << totalDist
             << " nm long with " << totalSegments << " tack legs\n";
        cout << "Estimated Race Duration is " << fixed << setprecision(2) << totalTime + totalPenalty
             << " hours with " << fixed << setprecision(2) << totalPenalty << " hours of Tack Penalty\n\n";
    }

    return 0;
}
```

## 总结

本题的关键在于将帆船航行约束转化为向量分解问题，通过解线性方程组得到最少换舷次数下的最短路径。在实现时需要注意：

- 角度归一化与夹角的正确计算。
- 速度比的分段查找。
- 罚时次数与航段数的关系：罚时次数 = 总航段数 $−$  $1$。
- 多组输入的处理与严格的输出格式。
- **特别注意：题目描述中的输出格式和在线测试数据的输出格式并不一致，需要适当更改（以下为正确的输出格式）。**

```cpp
Race 1 has 5 legs
The race layout is 58.48 nm long

Leg 1 from Mark M1 to M2: direction = 45.0, distance = 14.14 nm
Tack 1: speed = 5.0, direction = 90.0, distance = 10.00 nm
Tack 2: speed = 5.0, direction = 0.0, distance = 10.00 nm

Leg 2 from Mark M2 to M3: direction = 343.3, distance = 10.44 nm
Tack 3: speed = 5.0, direction = 343.3, distance = 10.44 nm

Leg 3 from Mark M3 to M4: direction = 253.6, distance = 17.72 nm
Tack 4: speed = 6.7, direction = 253.6, distance = 17.72 nm

Leg 4 from Mark M4 to M5: direction = 153.4, distance = 11.18 nm
Tack 5: speed = 7.5, direction = 153.4, distance = 11.18 nm

Leg 5 from Mark M5 to M6: direction = 180.0, distance = 5.00 nm
Tack 6: speed = 6.7, direction = 180.0, distance = 5.00 nm

Race 1 was 64.34 nm long with 6 tack legs
Estimated Race Duration is 11.47 hours with 0.50 hours of Tack Penalty

```

掌握以上要点后，即可顺利通过本题。
