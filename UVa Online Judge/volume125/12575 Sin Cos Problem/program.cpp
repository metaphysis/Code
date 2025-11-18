// Sin Cos Problem
// UVa ID: 12575
// Verdict: Accepted
// Submission Date: 2025-11-15
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net


#include <bits/stdc++.h>
using namespace std;

const double PI = acos(-1.0);

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        double a, b;
        scanf("%lf %lf", &a, &b);
        double r = sqrt(a * a + b * b);
        
        if (r == 0) {
            // 当 A 和 B 都为 0 时，任何 θ 都得到最大值 0
            // 取最小非负 θ = 0
            printf("0.00 0.00\n");
        } else {
            double phi = atan2(b, a);
            double theta = PI / 2 - phi;
            
            // 确保 theta 在 [0, 2π) 范围内
            if (theta < 0) theta += 2 * PI;
            if (theta >= 2 * PI) theta -= 2 * PI;
            
            printf("%.2lf %.2lf\n", theta, r);
        }
    }
    return 0;
}
