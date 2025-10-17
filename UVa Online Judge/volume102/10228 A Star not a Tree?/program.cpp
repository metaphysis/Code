// A Star not a Tree?
// UVa ID: 10228
// Verdict: Accepted
// Submission Date: 2025-10-16
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;
// 点结构体，表示二维坐标
struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
};
// 计算两点间的欧几里得距离
double distance(const Point& a, const Point& b) {
    return hypot(a.x - b.x, a.y - b.y);
}
// 使用Weiszfeld算法计算几何中位数
Point geometricMedian(const vector<Point>& points, int maxIterations = 200) {
    int n = points.size();
    // 初始点设为所有点的质心（平均值）
    Point median;
    for (const auto& p : points) {
        median.x += p.x;
        median.y += p.y;
    }
    median.x /= n;
    median.y /= n;
    // Weiszfeld算法迭代
    for (int iter = 0; iter < maxIterations; iter++) {
        Point numerator(0, 0);  // 分子部分
        double denominator = 0; // 分母部分
        // 计算加权平均的分子和分母
        for (const auto& p : points) {
            double dist = distance(median, p);
            if (dist < 1e-12) {
                // 如果距离太小（接近某个数据点），跳过避免除零
                continue;
            }
            numerator.x += p.x / dist;
            numerator.y += p.y / dist;
            denominator += 1.0 / dist;
        }
        // 如果分母为零，说明几何中位数与某个数据点重合
        if (denominator == 0) {
            break;
        }
        // 计算新的几何中位数估计
        Point newMedian(numerator.x / denominator, numerator.y / denominator);
        // 检查是否收敛（位置变化很小）
        if (distance(newMedian, median) < 1e-12) {
            break;
        }
        // 更新几何中位数
        median = newMedian;
    }
    return median;
}
int main() {
    int cases;
    cin >> cases;
    bool firstCase = true;
    while (cases--) {
        int n;
        cin >> n;
        vector<Point> computers(n);
        for (int i = 0; i < n; i++) {
            cin >> computers[i].x >> computers[i].y;
        }
        // 计算几何中位数（最优集线器位置）
        Point hub = geometricMedian(computers);
        // 计算总电缆长度
        double totalLength = 0;
        for (const auto& computer : computers) {
            totalLength += distance(hub, computer);
        }
        // 输出结果（四舍五入到最近的整数）
        if (!firstCase) {
            cout << endl;
        }
        firstCase = false;
        cout << static_cast<int>(round(totalLength)) << endl;
    }
    return 0;
}
