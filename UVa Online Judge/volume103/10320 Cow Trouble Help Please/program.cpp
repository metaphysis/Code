// Cow Trouble Help Please
// UVa ID: 10320
// Verdict: Accepted
// Submission Date: 2025-11-11
// UVa Run Time: 0.010s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>

using namespace std;

const double PI = acos(-1.0);

int main() {
    double L, W, R;
    
    while (cin >> L >> W >> R) {
        double area = 0.0;
        
        // 确保L是长边，W是短边
        if (L < W) swap(L, W);
        
        // 四分之三圆的基础面积
        area = 0.75 * PI * R * R;
        
        if (R <= W) {
            cout << fixed << setprecision(10) << area << endl;
            continue;
        }
        
        // 添加两个额外的四分之一圆面积
        if (W < R && R <= L) {
            area += 0.25 * PI * (R - W) * (R - W);
        } else {
            if (L < R && R <= L + W) {
                area += 0.25 * PI * ((R - L) * (R - L) + (R - W) * (R - W));
            } else if (L + W < R) {
                area += 0.25 * PI * ((R - L) * (R - L) + (R - W) * (R - W));
                
                double R1 = R - L;  // 绕过长边的圆的半径
                double R2 = R - W;  // 绕过宽边的圆的半径
                double d = sqrt(L * L + W * W);  // 两圆心距离
                
                // 计算两个圆心连线与水平线的夹角
                double alpha = atan2(L, W);
                
                // 利用余弦定理计算两个圆心到交点的连线夹角
                double angle1 = acos((R1 * R1 + d * d - R2 * R2) / (2 * R1 * d)) - alpha;
                double angle2 = acos((R2 * R2 + d * d - R1 * R1) / (2 * R2 * d)) - (PI / 2 - alpha);
                
                // 重叠区域面积 = 两个扇形面积之和
                double sector1 = R1 * R1 * angle1 / 2.0;
                double sector2 = R2 * R2 * angle2 / 2.0;
                
                // 四边形面积（两个三角形面积之和）
                double triangleArea = 0.5 * R1 * W * sin(angle1) + 0.5 * R2 * L * sin(angle2);
                
                area -= sector1 + sector2 - triangleArea;
            }
        }
        
        cout << fixed << setprecision(10) << area << endl;
    }
    
    return 0;
}
