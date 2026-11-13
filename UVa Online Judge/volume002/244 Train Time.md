[UVa 244 Train Time](https://blog.csdn.net/metaphysis/article/details/161247689)

## 题目分析

本题要求模拟两列火车在同一线路相向而行，计算它们相遇的时间和地点。题目给出了一个简化的火车运行模型，其中包含以下关键假设：

1. 火车在每个车站停留固定时间 $m$ 分钟
2. 火车以恒定加速度 $s$ 英尺/分钟² 加速和减速，且具有相同的最大速度 $v$ 英尺/分钟
3. 火车从车站出发时初速度为 $0$，到达车站时末速度为 $0$。相邻车站距离足够远，使得火车可以加速到最大速度后再减速
4. 两列火车同时出发：一列从地铁中心（$\texttt{Metro Center}$）向外行驶，另一列从最外端车站向地铁中心行驶
5. 每条线路最多有 $31$ 个车站
6. 相遇时间不会恰好发生在某列火车从车站出发的时刻

### 输入格式

每个测试场景的数据格式如下：
- 一系列距离值（单位为英里），表示各车站到地铁中心的距离，按升序排列，以 $0.0$ 结束
- 最大速度 $v$（英尺/分钟）
- 加速度 $s$（英尺/分钟²）
- 车站停留时间 $m$（分钟）

输入以 $-1.0$ 结束。

### 输出格式

对于每个场景，输出：
1. 场景编号（从 $\texttt{Scenario \#1}$ 开始）
2. 相遇时间（分钟，保留 $1$ 位小数）
3. 相遇地点到地铁中心的距离（英里，保留 $3$ 位小数），如果相遇在车站，则标注车站编号

## 解题思路

### 1. 距离单位转换

输入中车站距离以英里为单位，而速度和加速度以英尺为单位，因此需要统一单位。题目给出 $1$ 英里 = $5280$ 英尺，所以在计算时需要将英里转换为英尺，或将英尺转换为英里。

### 2. 相邻车站间的行程时间分析

火车从车站 $i$ 到车站 $i+1$ 的运动过程分为三个阶段：

1. **加速阶段**：从静止加速到最大速度 $v$，所需时间为 $t_{acc} = v/s$，行驶距离为 $\frac{1}{2} s t_{acc}^2 = \frac{v^2}{2s}$

2. **匀速阶段**：以最大速度 $v$ 匀速行驶，设两站间距离为 $D$（英尺），则匀速行驶距离为 $D - v^2/s$，时间为 $(D - v^2/s)/v$

3. **减速阶段**：从最大速度减速到 $0$，与加速阶段对称，时间也为 $t_{acc}$，距离也为 $\frac{v^2}{2s}$

因此，从车站 $i$ 到车站 $i+1$ 的总行程时间为：

$$T_{travel} = \frac{v}{s} + \frac{D}{v} = \frac{D}{v} + \frac{v}{s}$$

注意：这里 $\frac{v}{s}$ 是加速时间，但由于减速时间相同，总时间中加速和减速各贡献 $\frac{v}{s}$，但 $\frac{v}{s}$ 出现在公式中两次？实际上：

$$T_{travel} = t_{acc} + \frac{D - v^2/s}{v} + t_{acc} = \frac{2v}{s} + \frac{D}{v} - \frac{v}{s} = \frac{D}{v} + \frac{v}{s}$$

所以 $\frac{v}{s}$ 是加速和减速总时间的一半，这是一个简化后的公式。

### 3. 车站时刻表计算

我们需要为两列火车分别计算到达和离开每个车站的时间。

**左行列车**（从地铁中心向外行驶）：
- 起点（车站 $0$，即地铁中心）：到达时间 = 出发时间 = $0$
- 对于车站 $i$（$i \ge 1$）：到达时间 = 上一车站出发时间 + 行程时间；出发时间 = 到达时间 + $m$

**右行列车**（从最外端车站向地铁中心行驶）：
- 最外端车站（设为车站 $n$）：到达时间 = 出发时间 = $0$
- 从外向内计算，将时刻表反向存储

### 4. 相遇情况分类

两列火车相遇可能有三种情况：

#### 情况一：在车站相遇

如果某列火车到达车站的时间落在另一列火车在该车站的停靠时间区间内（包括到达和离开时间，但不包括恰好出发的时刻，因为题目保证不会发生），则两车在该车站相遇。

设左车在车站 $i$ 的到达时间为 $L_{arr}[i]$，离开时间为 $L_{dep}[i]$；右车在该站的到达时间为 $R_{arr}[i]$，离开时间为 $R_{dep}[i]$。

相遇条件为：
$$L_{arr}[i] \in [R_{arr}[i], R_{dep}[i]] \quad \text{或} \quad R_{arr}[i] \in [L_{arr}[i], L_{dep}[i]]$$

#### 情况二：在两站之间的路段相遇

当两车都在行驶过程中（不在车站停留）时，它们可能在两站之间的路段上相遇。判断条件是：
- 左车从车站 $i$ 出发后（$L_{dep}[i] < R_{arr}[i]$），且
- 右车从车站 $i+1$ 出发后（$R_{dep}[i+1] < L_{arr}[i+1]$）

### 5. 路段相遇时的距离计算

当确定相遇发生在车站 $i$ 和 $i+1$ 之间后，需要计算相遇点到地铁中心的距离。

设左车离开车站 $i$ 的时间为 $t_{left\_dep} = L_{dep}[i]$，右车离开车站 $i+1$ 的时间为 $t_{right\_dep} = R_{dep}[i+1]$。

两车从各自车站出发的时间可能不同，需要确定它们是否同时开始相向行驶。实际上，由于题目设定两车同时从起点出发，经过不同数量的车站后，到达当前路段的时间可能不同。

我们需要计算从两车都开始行驶的时刻起，到它们相遇的时间间隔。然后根据这个时间间隔，判断相遇发生在加速段、匀速段还是减速段。

设 $t_0 = \max(L_{dep}[i], R_{dep}[i+1])$，即两车都离开车站的时间点。

在路段 $i$ 到 $i+1$ 上，左车的运动方程为：
- 加速段（$0 \le t \le v/s$）：位置 = $\frac{1}{2} s t^2$
- 匀速段（$v/s < t \le D/v$）：位置 = $\frac{v^2}{2s} + v(t - v/s)$
- 减速段（$D/v < t \le D/v + v/s$）：位置 = $D - \frac{1}{2} s (D/v + v/s - t)^2$

右车的运动方向相反，但计算方式类似。

通过联立方程可以求解相遇时间，但代码采用了一种更直接的方法：计算相遇位置，然后根据时间差判断位于哪个阶段。

### 6. 特殊情况：只有一站

如果地铁中心和最外端车站之间没有中间车站（即只有一站，$n=1$），那么两列火车直接从两端向中间行驶。此时相遇时间计算为：

$$t_{meet} = \frac{1}{2} \left( \frac{D}{v} + \frac{v}{s} \right)$$

其中 $D$ 为两站间距离（英尺），相遇地点为 $D/2$。

## 代码注释

```cpp
// Train Time
// UVa ID: 244
// Verdict: Accepted
// Submission Date: 2016-06-09
// UVa Run Time: 0.010s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int cases = 0;                              // 场景计数器
vector<double> distances_from_start;        // 各站到地铁中心的距离（英里）
double v, s, m;                             // 最大速度、加速度、停留时间

// 车站信息结构体
struct station
{
    double arrived_time, departure_time;    // 到达时间和出发时间
};

void process()
{
    // 场景间输出空行
    if (cases > 0)
        cout << endl;

    cout << "Scenario #" << ++cases << ":" << endl;
    
    // 特殊情况：只有两个车站（地铁中心和最外端车站）
    if (distances_from_start.size() == 1)
    {
        double meet_time = distances_from_start.front() * 5280.0 / v + v / s;
        cout << "   Meeting time: ";
        cout << fixed << setprecision(1) << meet_time / 2.0 << " minutes" << endl;
        cout << "   Meeting distance: ";
        cout << fixed << setprecision(3) << distances_from_start.front() / 2.0;
        cout << " miles from metro center hub" << endl;
        return;
    }

    // 计算相邻车站间的距离（英尺）
    vector<double> distances(distances_from_start);
    distances.insert(distances.begin(), 0.0);
    for (int i = 0; i < distances.size() - 1; i++)
        distances[i] = (distances[i + 1] - distances[i]) * 5280.0;
    distances.erase(distances.end() - 1);

    // 插入地铁中心（距离为0）
    distances_from_start.insert(distances_from_start.begin(), 0.0);

    // 计算每个区间所需的行程时间
    vector<double> schedule;
    for (int i = 0; i < distances.size(); i++)
        schedule.push_back(distances[i] / v + v / s);

    // 左行列车（从地铁中心向外）的时刻表
    vector<station> left_train, right_train;

    // 起点：地铁中心（车站0）
    left_train.push_back((station){0.0, 0.0});
    double time_elapsed = 0.0;
    for (int i = 0; i < schedule.size(); i++)
    {
        station aStation;
        aStation.arrived_time = time_elapsed + schedule[i];     // 到达时间
        aStation.departure_time = aStation.arrived_time + m;    // 出发时间
        left_train.push_back(aStation);
        time_elapsed = aStation.departure_time;
    }

    // 右行列车（从最外端向地铁中心）的时刻表
    right_train.push_back((station){0.0, 0.0});                 // 起点：最外端车站
    time_elapsed = 0.0;
    for (int i = schedule.size() - 1; i >= 0; i--)
    {
        station aStation;
        aStation.arrived_time = time_elapsed + schedule[i];     // 到达时间
        aStation.departure_time = aStation.arrived_time + m;    // 出发时间
        right_train.insert(right_train.begin(), aStation);      // 从外向内插入
        time_elapsed = aStation.departure_time;
    }

    // 情况一：检查是否在车站相遇
    for (int i = 0; i < left_train.size(); i++)
    {
        // 左车到达时右车正在车站停留
        if (left_train[i].arrived_time >= right_train[i].arrived_time &&
            left_train[i].arrived_time <= right_train[i].departure_time)
        {
            cout << "   Meeting time: ";
            cout << fixed << setprecision(1) << left_train[i].arrived_time << " minutes" << endl;
            cout << "   Meeting distance: ";
            cout << fixed << setprecision(3) << distances_from_start[i];
            cout << " miles from metro center hub, in station " << i << endl;
            return;
        }

        // 右车到达时左车正在车站停留
        if (right_train[i].arrived_time >= left_train[i].arrived_time &&
            right_train[i].arrived_time <= left_train[i].departure_time)
        {
            cout << "   Meeting time: ";
            cout << fixed << setprecision(1) << right_train[i].arrived_time << " minutes" << endl;
            cout << "   Meeting distance: ";
            cout << fixed << setprecision(3) << distances_from_start[i];
            cout << " miles from metro center hub, in station " << i << endl;
            return;
        }
    }

    // 情况二：检查是否在两站之间的路段相遇
    for (int i = 0; i < left_train.size() - 1; i++)
    {
        // 左车已离开车站i，右车已离开车站i+1，两车都在行驶中
        if (left_train[i].departure_time < right_train[i].arrived_time &&
            right_train[i + 1].departure_time < left_train[i + 1].arrived_time)
        {
            // 计算相遇位置和时间的复杂公式
            double distance_traveled =
                (fabs(left_train[i].departure_time - right_train[i + 1].departure_time) -
                v / s) * v + 2.0 * v * v / s;
            double traveled_time = v / s + (distances[i] - distance_traveled) / (2.0 * v);
            cout << "   Meeting time: ";
            double meet_time =
                max(left_train[i].departure_time,
                right_train[i + 1].departure_time) + traveled_time;
            cout << fixed << setprecision(1) << meet_time << " minutes" << endl;
            cout << "   Meeting distance: ";

            // 根据时间差判断相遇发生在加速段、匀速段还是减速段
            time_elapsed = meet_time - left_train[i].departure_time;
            double accelerate_time = v / s;
            double meet_distance = distances_from_start[i];

            if (time_elapsed <= accelerate_time)                    // 加速阶段
            {
                meet_distance += s * time_elapsed * time_elapsed / 10560.0;
            }
            else if (time_elapsed <= (schedule[i] - accelerate_time))  // 匀速阶段
            {
                meet_distance += v * v / s / 10560.0;
                meet_distance += (time_elapsed - accelerate_time) * v / 5280.0;
            }
            else                                                    // 减速阶段
            {
                time_elapsed = schedule[i] - time_elapsed;
                meet_distance =
                    distances_from_start[i + 1] - s * time_elapsed * time_elapsed / 10560.0;
            }

            cout << fixed << setprecision(3) << meet_distance;
            cout << " miles from metro center hub" << endl;
            return;
        }
    }
}

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    double d;
    while (cin >> d, d > 0.0)
    {
        distances_from_start.clear();
        distances_from_start.push_back(d);
        // 读取该场景的所有车站距离，以0.0结束
        while (cin >> d, d > 0.0)
            distances_from_start.push_back(d);
        // 读取最大速度、加速度、停留时间
        cin >> v >> s >> m;
        process();
    }

    return 0;
}
```

## 要点总结

1. **单位转换**：注意输入距离为英里，速度与加速度为英尺单位，计算时需统一
2. **时刻表计算**：正确计算两车到达和离开每个车站的时间
3. **相遇情况分类**：在车站相遇和路段相遇分别处理
4. **运动阶段判断**：路段相遇时需根据时间判断位于加速、匀速还是减速阶段
5. **边界条件**：考虑只有两个车站的特殊情况
