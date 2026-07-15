// Elliptic Athletics Track
// UVa ID: 12475
// Verdict: Accepted
// Submission Date: 2026-07-13
// UVa Run Time: 0.010s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 被积函数：sqrt(1 - e^2 * sin^2(theta))
double integrand(double theta, double e) {
    return sqrt(1.0 - e * e * sin(theta) * sin(theta));
}

// 复合辛普森积分，区间 [0, pi/2]，等分数 N
double simpsonIntegral(double e, int N = 10000) {
    double a = 0.0, b = M_PI / 2.0;
    double h = (b - a) / N;
    double sum = 0.0;
    for (int i = 0; i <= N; ++i) {
        double theta = a + i * h;
        double fv = integrand(theta, e);
        if (i == 0 || i == N) sum += fv;
        else if (i % 2 == 0) sum += 2.0 * fv;
        else sum += 4.0 * fv;
    }
    return sum * h / 3.0;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int cs = 1; cs <= T; ++cs) {
        int bInt, aInt;
        scanf("%d %d", &bInt, &aInt);
        double a = (double)aInt;
        double b = (double)bInt;
        double e = sqrt(1.0 - (b * b) / (a * a));   // 离心率
        double integral = simpsonIntegral(e);       // 第二类完全椭圆积分 E(e)
        double circumference = 4.0 * a * integral;  // 椭圆周长
        printf("Case %d: %.6f\n", cs, circumference);
    }
    return 0;
}
