// Subway
// UVa ID: 10124
// Verdict: Accepted
// Submission Date: 2025-11-30
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    double d, m, a, j;
    
    while (cin >> d >> m >> a >> j) {
        double halfD = d / 2.0;
        double t1, t2, finalSpeed, dist1, dist2, dist3;
        
        // 情况1和2：尝试达到最大速度
        t1 = a / j;  // 加速到最大加速度的时间
        
        // 检查是情况1还是情况2
        if (j * t1 * t1 > m) {
            // 情况1：仅通过加加速度阶段就能达到最大速度
            t1 = sqrt(m / j);
            t2 = t1;
        } else {
            // 情况2：需要匀加速阶段
            t2 = (m - j * t1 * t1) / a + t1;
        }
        
        // 计算最终速度和各段距离
        finalSpeed = j * t1 * t1 / 2.0 + j * t1 * (t2 - t1) + j * t1 * t1 / 2.0;
        dist1 = j * t1 * t1 * t1 / 6.0;
        dist2 = (j * t1 * t1 + j * t1 * (t2 - t1)) * (t2 - t1) / 2.0;
        dist3 = (j * t1 * t1 / 2.0 + j * t1 * (t2 - t1)) * t1 + 
                j * t1 * t1 * t1 / 2.0 - j * t1 * t1 * t1 / 6.0;
        
        double totalTime;
        
        if (dist1 + dist2 + dist3 > halfD) {
            // 情况3：无法达到最大速度
            
            // 先假设仅通过加加速度阶段
            t1 = pow(halfD / j, 1.0 / 3.0);
            t2 = t1;
            
            // 重新计算
            finalSpeed = j * t1 * t1 / 2.0 + j * t1 * (t2 - t1) + j * t1 * t1 / 2.0;
            dist1 = j * t1 * t1 * t1 / 6.0;
            dist2 = (j * t1 * t1 + j * t1 * (t2 - t1)) * (t2 - t1) / 2.0;
            dist3 = (j * t1 * t1 / 2.0 + j * t1 * (t2 - t1)) * t1 + 
                    j * t1 * t1 * t1 / 2.0 - j * t1 * t1 * t1 / 6.0;
            
            if (t1 * j > a) {
                // 需要匀加速阶段但受加速度限制
                t1 = a / j;
                // 解二次方程: a*t2² + b*t2 + c = 0
                double coeffA = j * t1 / 2.0;
                double coeffB = j * t1 * t1 / 2.0;
                double coeffC = -halfD;
                
                t2 = (-coeffB + sqrt(coeffB * coeffB - 4.0 * coeffA * coeffC)) / (2.0 * coeffA);
                
                // 重新计算最终结果
                finalSpeed = j * t1 * t1 / 2.0 + j * t1 * (t2 - t1) + j * t1 * t1 / 2.0;
                dist1 = j * t1 * t1 * t1 / 6.0;
                dist2 = (j * t1 * t1 + j * t1 * (t2 - t1)) * (t2 - t1) / 2.0;
                dist3 = (j * t1 * t1 / 2.0 + j * t1 * (t2 - t1)) * t1 + 
                        j * t1 * t1 * t1 / 2.0 - j * t1 * t1 * t1 / 6.0;
            }
            
            totalTime = t1 + t2 + (halfD - dist1 - dist2 - dist3) / finalSpeed;
        } else {
            // 可以达到最大速度
            totalTime = t1 + t2 + (halfD - dist1 - dist2 - dist3) / m;
        }
        
        // 总时间是前半程时间的2倍
        totalTime *= 2.0;
        totalTime = round(totalTime * 10.0) / 10.0;
        cout << fixed << setprecision(1) << totalTime << endl;
    }
    
    return 0;
}
