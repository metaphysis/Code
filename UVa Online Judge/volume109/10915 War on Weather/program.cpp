// War on Weather
// UVa ID: 10915
// Verdict: Accepted
// Submission Date: 2025-11-05
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// 地球半径，根据周长40,000km计算
const double R = 40000.0 / (2 * M_PI);

// 三维点结构体
struct Point {
    double x, y, z;
    Point(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}
    
    // 点积运算
    double dot(const Point& p) const {
        return x * p.x + y * p.y + z * p.z;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int k, m;
    
    // 处理多个测试用例，直到遇到 0 0
    while (cin >> k >> m && (k != 0 || m != 0)) {
        vector<Point> satellites(k);
        vector<Point> targets(m);

        // 读取卫星坐标
        for (int i = 0; i < k; i++) {
            cin >> satellites[i].x >> satellites[i].y >> satellites[i].z;
        }
        
        // 读取目标坐标
        for (int i = 0; i < m; i++) {
            cin >> targets[i].x >> targets[i].y >> targets[i].z;
        }

        int count = 0;  // 可击中目标计数器
        
        // 检查每个目标是否能被至少一个卫星击中
        for (const Point& target : targets) {
            bool can_hit = false;
            
            // 遍历所有卫星，检查视线
            for (const Point& satellite : satellites) {
                // 使用点积判断是否存在视线
                // 添加容差 1e-8 处理边界情况
                if (satellite.dot(target) >= R * R - 1e-8) {
                    can_hit = true;
                    break;  // 找到一个可见卫星即可
                }
            }
            
            if (can_hit) {
                count++;
            }
        }

        // 输出当前测试用例的结果
        cout << count << "\n";
    }

    return 0;
}
