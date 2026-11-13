[UVa 237 Monitoring Wheelchair Patients](https://blog.csdn.net/metaphysis/article/details/152667327)

## 题目描述

本题要求监控电动轮椅在限定区域内的运动轨迹。轮椅只能在停止时改变方向，记录设备会记录每个运动时间段的速度和罗盘方位角。需要分析数据以确定：

1. 患者是否离开限定区域，如果离开，找出第一次离开的时间和位置
2. 如果未离开，计算患者到达的最远点距离门的距离
3. 患者行驶的总距离

## 问题分析

### 坐标系和初始条件
- 限定区域：$200ft × 400ft$ 的矩形区域
- 坐标系：西南角为 $(0,0)$，东北角为 $(400,200)$
- 入口：南边界中心点 $(200,0)$
- 初始方向：北（$0°$）

### 输入格式
- 每个数据集第一行：记录的行数
- 后续每行：开始时间、结束时间、速度、方位角
- 以行数为 $0$ 结束输入

### 运动模型
- 在每个时间段内，轮椅保持恒定速度和方向
- 方向用罗盘方位角表示：$0°=$北，$90°=$东，$180°=$南，$270°=$西

## 算法思路

### 关键点
1. **位置计算**：
   - 使用向量运算计算轮椅位置
   - 将方位角转换为弧度，计算方向向量
   - 位置 = 起点 + 方向向量 × 速度 × 时间

2. **边界检测**：
   - 检查位置是否在矩形区域内
   - 使用二分查找精确定位穿越边界的时间点

3. **距离计算**：
   - 总距离：各时间段距离之和
   - 最远距离：各位置到入口点的欧几里得距离的最大值

### 核心步骤
1. **初始化**：从入口点 $(200,0)$ 开始
2. **处理每个时间段**：
   - 计算方向向量
   - 更新终点位置
   - 累加行驶距离
   - 检查是否越界
3. **输出结果**：按要求格式输出

## 代码实现

```cpp
// Monitoring Wheelchair Patients
// UVa ID: 237
// Verdict: Accepted
// Submission Date: 2025-10-05
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const double PI = 2.0 * acos(0.0), EPSILON = 1E-10;

// 点结构体，表示二维坐标点
struct point {
    double x, y;
    point (double x = 0, double y = 0): x(x), y(y) {}
    // 向量加法
    point operator + (point p) { return point(x + p.x, y + p.y); }
    // 向量减法
    point operator - (point p) { return point(x - p.x, y - p.y); }
    // 向量数乘
    point operator * (double u) { return point(x * u, y * u); }
    // 向量数除
    point operator / (double u) { return point(x / u, y / u); }
    // 向量旋转（逆时针旋转alpha弧度）
    point rotate(double alpha) {
        return point(x * cos(alpha) - y * sin(alpha), x * sin(alpha) + y * cos(alpha));
    }
    // 计算向量的模长（距离原点的距离）
    double norm() { return sqrt(x * x + y * y); }
};

// 浮点数比较函数，避免精度问题
int dcmp(double x) {
    if (abs(x) <= EPSILON) return 0;  // 相等
    return x > 0 ? 1 : -1;           // 大于或小于
}

// 判断点是否在限定区域内（矩形区域：0<x<400, 0<y<200）
bool isInBox(point p) {
    return dcmp(p.x) > 0 && dcmp(p.x - 400) < 0 && dcmp(p.y) > 0 && dcmp(p.y - 200) < 0;
}

int main(int argc, char *argv[]) {
    int lines, cases = 0;  // lines: 记录的行数，cases: 测试用例编号
    
    // 循环处理每个测试用例
    while (cin >> lines) {
        if (lines == 0) break;  // 输入0表示结束
        
        int out = 0;           // 标记是否离开限定区域
        point start(200, 0);   // 起始位置（入口点）
        point outP;            // 离开边界时的位置
        double t1, t2, speed, bearing;  // 时间区间、速度、方位角
        double totalD = 0;     // 总行驶距离
        double maxD = 0;       // 距离入口点的最远距离
        double outT;           // 离开边界的时间
        
        // 处理每个时间段的记录
        for (int i = 1; i <= lines; i++) {
            cin >> t1 >> t2 >> speed >> bearing;
            
            // 计算方向向量：将北方向(0,1)旋转-bearing角度（转换为弧度）
            // 注意：bearing是罗盘方位角，0°=北，90°=东
            point scale = point(0, 1).rotate(-bearing / 180 * PI) * speed;
            
            // 计算当前时间段结束时的位置
            point now = start + scale * (t2 - t1);
            
            // 累加行驶距离：速度 × 时间
            totalD += speed * (t2 - t1);
            
            // 如果之前没有离开过限定区域，且当前位置不在区域内
            if (!out && !isInBox(now)) {
                out = 1;  // 标记为已离开
                int cnt = 0;
                double left = t1, right = t2, middle;
                
                // 使用二分查找精确定位离开边界的时间点
                // 迭代50次确保足够的精度（约2^-50的误差）
                while (cnt++ <= 50) {
                    middle = (left + right) / 2;           // 取中点时间
                    point tmp = start + scale * (middle - t1);  // 计算中点时间的位置
                    
                    if (isInBox(tmp)) 
                        left = middle;   // 如果还在区域内，搜索右半区间
                    else 
                        right = middle;  // 如果已离开，搜索左半区间
                }
                
                // 记录离开边界时的位置和时间
                outP = start + scale * (middle - t1);
                outT = middle;
            }
            
            // 更新起始位置为当前位置，准备处理下一个时间段
            start = now;
            
            // 更新距离入口点的最远距离
            maxD = max(maxD, (start - point(200, 0)).norm());
        }
        
        // 输出结果
        cout << "Case Number " << ++cases << '\n';
        cout.precision(1);  // 设置输出精度为1位小数
        cout << fixed;      // 固定小数格式
        
        if (out) {
            // 如果离开了限定区域
            cout << "Left restricted area at point (" << outP.x;
            cout << "," << outP.y << ") and time " << outT;
            cout << " sec." << '\n';
        } else {
            // 如果未离开限定区域
            cout << "No departure from restricted area" << '\n';
            cout << "Maximum distance patient traveled from door was ";
            cout << maxD << " feet" << '\n';
        }
        
        // 输出总行驶距离
        cout << "Total distance traveled was ";
        cout << totalD << " feet" << '\n';
        
        // 输出分隔线
        cout << "***************************************" << '\n';
    }
    
    return 0;
}
```

## 技术要点详解

### 1. 几何计算核心
- **点结构体**：封装了坐标点和基本的向量运算，便于几何计算
- **旋转操作**：将标准北方向向量 $(0,1)$ 按方位角旋转，得到实际运动方向
- **向量运算**：通过向量加法和数乘实现位置更新

### 2. 边界检测优化
- **二分查找原理**：当发现某个时间段内从区域内运动到区域外时，使用二分法在时间区间内搜索精确的穿越时刻
- **精度控制**：迭代 $50$ 次确保时间精度足够高（约$10^{-15}$ 秒）
- **效率平衡**：在保证精度的同时避免过度计算

### 3. 数值处理技巧
- **浮点比较**：使用 `dcmp` 函数避免直接比较浮点数，防止精度误差导致的错误判断
- **输出格式化**：使用 `fixed` 和 `precision` 控制输出格式，确保符合题目要求

### 4. 算法流程控制
- **状态标记**：使用 `out` 变量记录是否已离开区域，避免重复计算
- **增量更新**：在循环中逐步更新位置和距离，避免存储所有中间点
- **边界条件**：正确处理完全在区域内和跨越边界的情况

## 总结

本题通过几何向量运算和二分查找的结合，高效解决了轮椅运动轨迹的监控问题。关键创新点在于：

1. **向量化位置计算**：将运动分解为方向向量和时间参数的乘积
2. **精确边界检测**：使用二分法定位穿越时刻，避免近似误差
3. **实时距离跟踪**：在运动过程中动态更新最远距离

这种解法既保证了计算精度，又具有良好的时间复杂度，适用于大规模数据输入。
