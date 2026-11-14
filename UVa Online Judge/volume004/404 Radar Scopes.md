[UVa 404 Radar Scopes](https://blog.csdn.net/metaphysis/article/details/157261893)

## 题目分析

### 问题背景
这是一个空中交通管制系统的仿真问题，需要通过处理两次雷达扫描数据来检测飞机的异常情况，并生成相应的警告信息。系统需要处理以下六种警告类型：

1. **设备警告** ：当飞机两次扫描中指示的空速平均值与基于位置变化计算的实际速度相差超过 $10\%$ 时触发。
2. **新入侵警告** ：当一架在第一次扫描中不存在的飞机出现在第二次扫描中，且其指示空速（加上 $10\%$ 余量）足以让它在 $5$ 秒内从雷达边界外飞到当前位置时触发。
3. **新起飞警告** ：当一架在第一次扫描中不存在的飞机出现在第二次扫描中，但其速度不足以在 $5$ 秒内从边界外飞到当前位置时触发（意味着飞机是在雷达范围内刚刚起飞的）。
4. **离开范围警告** ：当一架在第一次扫描中存在的飞机在第二次扫描中消失，且其指示空速（加上 $10\%$ 余量）足以让它在 $5$ 秒内飞出雷达范围时触发。
5. **范围丢失警告** ：当一架在第一次扫描中存在的飞机在第二次扫描中消失，但其速度不足以在 $5$ 秒内飞出雷达范围时触发（意味着飞机可能已降落或坠毁）。

### 关键数据
- 雷达范围：半径 $10$ 英里
- 扫描间隔： $5$ 秒
- 飞机数量：每次扫描 $0$ 到 $100$ 架
- 应答机编码： $1$ 到 $5$ 位数字的字符串（需要保留前导零）
- 方位角： $000.000$ 到 $359.999$ 度（北为 $0$ 度，东为 $90$ 度）
- 距离： $000.000$ 到 $010.000$ 英里
- 地速： $000.000$ 到 $999.999$ 英里/小时

## 解题思路

### 1. 数据存储与匹配
由于应答机编码是包含前导零的字符串（如 `"013"` ），我们需要将其作为字符串存储，以确保正确匹配和输出。我们可以使用两个 `map<string, Plane>` 来分别存储两次扫描中的飞机数据，以便快速查找匹配。

### 2. 速度计算与比较
对于两次扫描中都出现的飞机，我们需要计算它们基于位置变化的实际速度：
1. 将极坐标（方位角、距离）转换为直角坐标
2. 计算两次扫描间的直线距离
3. 实际速度 = 距离 / 时间（ $5$ 秒 = $5/3600$ 小时）
4. 比较指示空速的平均值与实际速度是否在 $10\%$ 误差范围内

### 3. 警告判断逻辑

#### 情况1：飞机出现在两次扫描中
- 计算实际速度并比较指示空速平均值
- 如果超出 $10\%$ 误差范围，生成设备警告

#### 情况2：飞机只出现在第一次扫描
- 计算最大可能飞行距离： $d_{\text{max}} = d_1 + v_1 \times 1.1 \times (5/3600)$
- 如果 $d_{\text{max}} \geq 10$ ，说明飞机可能飞出了雷达范围 → 离开范围警告
- 否则，飞机可能降落或坠毁 → 范围丢失警告

#### 情况3：飞机只出现在第二次扫描
- 计算从边界到当前位置的最短距离： $d_{\text{need}} = 10 - d_2$
- 计算所需最小速度： $v_{\text{need}} = d_{\text{need}} / (5/3600)$
- 如果 $v_2 \times 1.1 \geq v_{\text{need}}$ ，说明飞机可能从边界外飞入 → 新入侵警告
- 否则，飞机可能是刚刚起飞 → 新起飞警告

### 4. 排序与输出
- 按应答机编码的数值大小排序（注意：需要将字符串转换为整数比较，但输出时保留字符串格式）
- 使用 `printf("%5s")` 实现右对齐并保留前导零
- 严格按照要求的格式输出警告信息

## 时间复杂度分析
- 每次扫描最多 $100$ 架飞机
- 使用 `map` 进行查找和匹配： $O(n \log n)$
- 总时间复杂度： $O(n \log n)$ ，对于 $n \leq 200$ 完全可以接受
- 空间复杂度： $O(n)$ ，用于存储两次扫描的数据

## 注意事项
1. 单位转换： $5$ 秒需要转换为小时（ $5/3600$ ）
2. 角度转换：需要将度转换为弧度才能使用三角函数
3. 误差处理：比较时需要同时考虑上界和下界
4. 字符串处理：应答机编码需要作为字符串处理以保留前导零
5. 排序比较：虽然存储为字符串，但排序时需要按数值大小排序

## 代码实现

```cpp
// Radar Scopes
// UVa ID: 404
// Verdict: Accepted
// Submission Date: 2026-01-22
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 飞机数据结构
struct Plane {
    string squawk;  // 应答机编码（保留前导零）
    double azimuth, distance, speed;
};

// 警告信息结构
struct Warning {
    string squawk;
    string type;
    // 按数值大小排序（字符串转整数比较）
    bool operator<(const Warning& other) const { return stoi(squawk) < stoi(other.squawk); }
};

// 角度转弧度
double degToRad(double deg) { return deg * M_PI / 180.0; }

// 计算两架飞机位置间的直线距离
double calcDistance(double a1, double d1, double a2, double d2) {
    a1 = degToRad(a1), a2 = degToRad(a2);
    double x1 = d1 * sin(a1), y1 = d1 * cos(a1);
    double x2 = d2 * sin(a2), y2 = d2 * cos(a2);
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

int main() {
    int scenarioNum = 0;
    int n1;
    // 处理多个场景，直到文件结束
    while (cin >> n1) {
        scenarioNum++;
        vector<Plane> sweep1(n1);
        map<string, Plane> map1;  // 用于快速查找第一次扫描的飞机
        // 读取第一次扫描数据
        for (int i = 0; i < n1; i++) {
            cin >> sweep1[i].squawk >> sweep1[i].azimuth >> sweep1[i].distance >> sweep1[i].speed;
            map1[sweep1[i].squawk] = sweep1[i];
        }
        int n2;
        cin >> n2;
        vector<Plane> sweep2(n2);
        map<string, Plane> map2;  // 用于快速查找第二次扫描的飞机
        // 读取第二次扫描数据
        for (int i = 0; i < n2; i++) {
            cin >> sweep2[i].squawk >> sweep2[i].azimuth >> sweep2[i].distance >> sweep2[i].speed;
            map2[sweep2[i].squawk] = sweep2[i];
        }
        vector<Warning> warnings;  // 存储所有警告
        // 处理在两次扫描中都出现的飞机
        for (auto& p1 : sweep1)
            if (map2.count(p1.squawk)) {
                Plane p2 = map2[p1.squawk];
                // 计算基于位置变化的实际速度
                double dist = calcDistance(p1.azimuth, p1.distance, p2.azimuth, p2.distance);
                double radarSpeed = dist / (5.0 / 3600.0);  // 英里/小时
                double avgSpeed = (p1.speed + p2.speed) / 2.0;
                // 检查是否超出10%误差范围
                if (avgSpeed < 0.9 * radarSpeed || avgSpeed > 1.1 * radarSpeed)
                    warnings.push_back({p1.squawk, "equipment warning"});
            } else {
                // 第一次有，第二次没有的飞机
                double maxDist = p1.distance + p1.speed * 1.1 * (5.0 / 3600.0);
                if (maxDist >= 10.0) warnings.push_back({p1.squawk, "domain exited"});
                else warnings.push_back({p1.squawk, "domain loss"});
            }
        // 处理只在第二次扫描中出现的飞机
        for (auto& p2 : sweep2) {
            if (!map1.count(p2.squawk)) {
                double maxDist = 10.0 - p2.distance;  // 从边界到当前位置的距离
                double requiredSpeed = maxDist / (5.0 / 3600.0);
                if (p2.speed * 1.1 >= requiredSpeed)
                    warnings.push_back({p2.squawk, "new intrusion"});
                else
                    warnings.push_back({p2.squawk, "new aloft"});
            }
        }
        // 按应答机编码排序
        sort(warnings.begin(), warnings.end());
        // 输出结果
        cout << "Scenario # " << scenarioNum << endl;
        for (auto& w : warnings)
            printf("%5s -- %s\n", w.squawk.c_str(), w.type.c_str());
        cout << endl;
    }
    return 0;
}
```

## 总结

本题主要考察以下几点：
1. 复杂逻辑的梳理与实现能力
2. 极坐标与直角坐标的转换
3. 字符串与数值的混合处理
4. 物理计算与误差分析
5. 数据结构的合理选择与使用

通过使用 `map` 存储飞机数据，我们可以高效地匹配两次扫描中的飞机，然后根据不同的情况应用相应的判断逻辑。注意处理应答机编码的前导零是本题的一个关键细节，需要在存储、比较和输出时都特别注意。