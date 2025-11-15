// Conic Distance
// UVa ID: 10495
// Verdict: Accepted
// Submission Date: 2025-11-05
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    double r, h, d1, A1, d2, A2;
    const double PI = acos(-1.0);  // 精确计算π值
    
    // 读取多组测试数据
    while (cin >> r >> h >> d1 >> A1 >> d2 >> A2) {
        // 计算圆锥的母线长度
        double L = sqrt(r * r + h * h);
        
        // 计算展开扇形的圆心角
        double sector_angle = 2.0 * PI * r / L;
        
        // 将角度转换为展开图上的极角
        double psi1 = (A1 / 360.0) * sector_angle;
        double psi2 = (A2 / 360.0) * sector_angle;
        
        // 计算角度差，考虑圆锥的环绕特性
        double delta_psi = fabs(psi1 - psi2);
        delta_psi = min(delta_psi, sector_angle - delta_psi);
        
        // 使用余弦定理计算最短距离
        double dist = sqrt(d1 * d1 + d2 * d2 - 2.0 * d1 * d2 * cos(delta_psi));
        
        // 输出结果，保留两位小数
        cout << fixed << setprecision(2) << dist << endl;
    }
    
    return 0;
}
