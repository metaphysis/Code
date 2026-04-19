// Trains
// UVa ID: 783
// Verdict: Accepted
// Submission Date: 2026-02-27
// UVa Run Time: 0.010s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    int d, v1, v2, t1, t2, tf;
    while (cin >> d >> v1 >> v2 >> t1 >> t2 >> tf) {
        int cnt = 0;
        double Td1 = static_cast<double>(d) / v1;   // T1到T2单程时间
        double Td2 = static_cast<double>(d) / v2;   // T2到T1单程时间
        
        // 枚举上界，多加2避免边界漏判
        int maxI = (tf + Td1) / t1 + 2;
        int maxJ = (tf + Td2) / t2 + 2;
        
        for (int i = 0; i <= maxI; i++) {
            double a = i * t1;                       // T1出发时刻
            if (a > tf + Td1 + 1e-9) break;          // 出发太晚，后续更晚
            
            for (int j = 0; j <= maxJ; j++) {
                double b = j * t2;                    // T2出发时刻
                if (b > tf + Td2 + 1e-9) break;       // 出发太晚
                
                // 计算相遇时刻
                double t = (d + a * v1 + b * v2) / (v1 + v2);
                
                if (t < -1e-9 || t > tf + 1e-9) continue;   // 相遇时间超出范围
                if (t + 1e-9 < max(a, b)) continue;         // 未出发不能相遇
                
                // 检查是否在轨道上（允许微小浮点误差）
                if (t > a + Td1 + 1e-9) continue;
                if (t > b + Td2 + 1e-9) continue;
                
                cnt++;
            }
        }
        
        cout << cnt << endl;
    }
    return 0;
}
