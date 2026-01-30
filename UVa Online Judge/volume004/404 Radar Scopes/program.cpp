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
