// Map
// UVa ID: 10713
// Verdict: Accepted
// Submission Date: 2025-11-25
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-10;  // 浮点数比较精度阈值
const double sqrt2 = sqrt(2.0);  // 根号2的预计算值
const double PI = acos(-1.0);    // 圆周率

// 八个方向的单位向量
const pair<double, double> dirs[8] = {
    {0, 1},     // north - 北方向
    {0, -1},    // south - 南方向
    {1, 0},     // east  - 东方向
    {-1, 0},    // west  - 西方向
    {1/sqrt2, 1/sqrt2},   // northeast - 东北方向
    {-1/sqrt2, 1/sqrt2},  // northwest - 西北方向
    {1/sqrt2, -1/sqrt2},  // southeast - 东南方向
    {-1/sqrt2, -1/sqrt2}  // southwest - 西南方向
};

// 八个方向的名称，与dirs数组一一对应
const string dirNames[8] = {
    "north", "south", "east", "west",
    "northeast", "northwest", "southeast", "southwest"
};

// 检查点是否在圆内（包括边界）
bool isPointInCircle(double r, double x, double y) {
    return x * x + y * y <= r * r + eps;  // 距离圆心距离小于等于半径
}

// 将位移向量分解为两个最接近的方向组合
vector<pair<int, double>> decomposeToDirections(double dx, double dy) {
    double targetAngle = atan2(dy, dx);  // 计算目标方向的角度
    
    // 将八个方向的角度排序，便于查找最接近的方向
    vector<pair<double, int>> angles;
    for (int i = 0; i < 8; i++) {
        double angle = atan2(dirs[i].second, dirs[i].first);  // 计算每个方向的角度
        angles.push_back({angle, i});  // 存储角度和方向索引
    }
    sort(angles.begin(), angles.end());  // 按角度排序
    
    // 找到目标角度所在的两个相邻方向区间
    int idx1 = -1, idx2 = -1;
    for (int i = 0; i < 8; i++) {
        int next = (i + 1) % 8;  // 下一个方向（循环处理）
        double a1 = angles[i].first, a2 = angles[next].first;
        
        // 处理角度环绕问题（从-PI到PI的跳变）
        if (a2 < a1) a2 += 2 * PI;
        if (targetAngle < a1) targetAngle += 2 * PI;
        
        // 如果目标角度在当前区间内，记录这两个方向
        if (a1 <= targetAngle && targetAngle <= a2) {
            idx1 = angles[i].second, idx2 = angles[next].second;
            break;
        }
    }
    assert(idx1 != -1 && idx2 != -1);  // 确保找到了两个方向
    
    // 解线性方程组：将位移向量分解为两个方向向量的线性组合
    double a1x = dirs[idx1].first, a1y = dirs[idx1].second;
    double a2x = dirs[idx2].first, a2y = dirs[idx2].second;
    double det = a1x * a2y - a1y * a2x;  // 行列式值
    double a = (dx * a2y - dy * a2x) / det, b = (a1x * dy - a1y * dx) / det;
    
    // 构建结果向量，只包含距离大于0的方向
    vector<pair<int, double>> result;
    if (a > eps) result.push_back({idx1, a});
    if (b > eps) result.push_back({idx2, b});
    return result;
}

int main() {
    double r, x, y, X, Y;
    bool firstCase = true;  // 标记是否为第一个测试用例，用于控制空行输出
    
    while (cin >> r) {
        if (r < 0) break;  // 输入-1时结束
        
        // 控制测试用例间的空行：第一个用例前不空行，后续用例前空行
        if (firstCase) firstCase = false;
        else cout << '\n';
        
        cin >> x >> y >> X >> Y;  // 读取起点和终点坐标
        double dx = X - x, dy = Y - y;  // 计算位移向量
        
        // 将位移向量分解为两个最接近的方向
        auto instructions = decomposeToDirections(dx, dy);
        
        // 如果有两条指令，需要检查路径是否在圆内
        if (instructions.size() > 1) {
            // 计算执行第一条指令后的转折点坐标
            auto pr = instructions.front();
            double turnx = x + pr.second * dirs[pr.first].first;
            double turny = y + pr.second * dirs[pr.first].second;
            
            // 如果转折点在圆外，颠倒两条指令的顺序
            // 由于圆的凸性，颠倒顺序后的路径一定在圆内
            if (!isPointInCircle(r, turnx, turny)) 
                reverse(instructions.begin(), instructions.end());
        }
        
        // 输出结果，距离精确到小数点后10位
        cout << fixed << setprecision(10);
        for (auto& inst : instructions)
            cout << dirNames[inst.first] << " " << inst.second << '\n';
    }
    return 0;
}
