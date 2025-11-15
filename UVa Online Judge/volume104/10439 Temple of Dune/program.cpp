// Temple of Dune
// UVa ID: 10439
// Verdict: Accepted
// Submission Date: 2025-11-05
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

const double PI = acos(-1.0);  // 定义圆周率
const double EPS = 1e-4;       // 浮点数比较容差

// 点结构体
struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
};

// 计算三角形外心（外接圆圆心）
Point circumcenter(Point A, Point B, Point C) {
    double D = 2 * (A.x * (B.y - C.y) + B.x * (C.y - A.y) + C.x * (A.y - B.y));
    double Ux = ((A.x * A.x + A.y * A.y) * (B.y - C.y) +
                 (B.x * B.x + B.y * B.y) * (C.y - A.y) +
                 (C.x * C.x + C.y * C.y) * (A.y - B.y)) / D;
    double Uy = ((A.x * A.x + A.y * A.y) * (C.x - B.x) +
                 (B.x * B.x + B.y * B.y) * (A.x - C.x) +
                 (C.x * C.x + C.y * C.y) * (B.x - A.x)) / D;
    return Point(Ux, Uy);
}

// 计算点的极角
double angle(Point p) {
    return atan2(p.y, p.x);
}

// 角度归一化到 [0, 2π) 范围
double normalize(double a) {
    while (a < 0) a += 2 * PI;
    while (a >= 2 * PI) a -= 2 * PI;
    return a;
}

int main() {
    int nCases;
    cin >> nCases;
    
    while (nCases--) {
        Point p[3];
        // 读入三个点的坐标
        for (int i = 0; i < 3; i++) {
            cin >> p[i].x >> p[i].y;
        }
        
        // 计算外接圆圆心
        Point center = circumcenter(p[0], p[1], p[2]);
        
        // 计算三个点相对于圆心的极角
        vector<double> angles;
        for (int i = 0; i < 3; i++) {
            double dx = p[i].x - center.x;
            double dy = p[i].y - center.y;
            angles.push_back(atan2(dy, dx));
        }
        
        // 对极角排序
        sort(angles.begin(), angles.end());
        
        // 计算相邻点之间的角度差（取小于 π 的值）
        vector<double> diffs;
        for (int i = 0; i < 3; i++) {
            double diff = angles[(i + 1) % 3] - angles[i];
            if (diff < 0) diff += 2 * PI;  // 处理负角度差
            if (diff > PI) diff = 2 * PI - diff;  // 取较小的弧
            diffs.push_back(diff);
        }
        
        // 枚举可能的顶点数 n，从 3 到 200
        int ans = 200;  // 初始化为最大值
        for (int n = 3; n <= 200; n++) {
            double unit = 2 * PI / n;  // 单位角度
            bool ok = true;
            
            // 检查每个角度差是否是单位角度的整数倍
            for (double d : diffs) {
                double k = d / unit;  // 计算倍数
                // 检查 k 是否接近整数（考虑浮点误差）
                double r = fabs(k - round(k));
                if (r > EPS && fabs(k - round(k) - 1) > EPS && fabs(k - round(k) + 1) > EPS) {
                    ok = false;
                    break;
                }
            }
            
            // 如果满足条件，更新答案并退出循环
            if (ok) {
                ans = n;
                break;
            }
        }
        
        cout << ans << endl;
    }
    
    return 0;
}
