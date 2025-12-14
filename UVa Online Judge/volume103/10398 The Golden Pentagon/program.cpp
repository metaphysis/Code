// The Golden Pentagon
// UVa ID: 10398
// Verdict: Accepted
// Submission Date: 2025-12-07
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 使用牛顿法求解方程 a^5 - a^4 - 1 = 0 的正实数根
double findGrowthRatio() {
    double a = 1.5;  // 初始猜测值
    double epsilon = 1e-12;
    for (int iter = 0; iter < 100; iter++) {
        double f = pow(a, 5) - pow(a, 4) - 1;
        double df = 5 * pow(a, 4) - 4 * pow(a, 3);
        double newA = a - f / df;
        if (fabs(newA - a) < epsilon) break;
        a = newA;
    }
    return a;
}

int main() {
    // 预先计算增长比例
    double a = findGrowthRatio();
    double log10A = log10(a);
    
    double s;
    int i;
    while (scanf("%lf %d", &s, &i) == 2) {
        if (i == 1) {
            // 第一个三角形
            long long len = (long long)floor(s);
            if (len < 1000000000) printf("%lld\n", len);
            else {
                int digits = (int)floor(log10(len)) + 1;
                printf("%d\n", digits);
            }
        } else {
            // 计算 log10(L) = log10(S) + (I-1)*log10(a)
            double log10L = log10(s) + (i - 1) * log10A;
            
            if (log10L < 9.0) {  // 10^9 = 1e9
                // 直接计算 L
                double L = s * pow(a, i - 1);
                long long len = (long long)floor(L);
                printf("%lld\n", len);
            } else {
                // 计算位数 D = floor(log10L) + 1
                int digits = (int)floor(log10L) + 1;
                printf("%d\n", digits);
            }
        }
    }
    return 0;
}
