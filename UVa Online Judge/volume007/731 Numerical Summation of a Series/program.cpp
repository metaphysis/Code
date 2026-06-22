// Numerical Summation of a Series
// UVa ID: 731
// Verdict: Accepted
// Submission Date: 2026-06-22
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 欧拉常数
const long double GAMMA = 0.57721566490153286060651209L;
// pi^2 / 6
const long double PI_SQ_OVER_6 = 1.64493406684822643647241517L;

// 渐近展开计算 digamma(z)，要求 z > 50
long double digammaLargeZ(long double z) {
    long double z2 = z * z;
    long double z4 = z2 * z2;
    long double z6 = z4 * z2;
    long double z8 = z4 * z4;
    long double z10 = z8 * z2;
    long double z12 = z8 * z4;
    long double z14 = z12 * z2;

    long double result = logl(z) - 1.0L / (2.0L * z);
    result -= 1.0L / (12.0L * z2);
    result += 1.0L / (120.0L * z4);
    result -= 1.0L / (252.0L * z6);
    result += 1.0L / (240.0L * z8);
    result -= 1.0L / (132.0L * z10);
    result += 691.0L / (32760.0L * z12);
    result -= 1.0L / (12.0L * z14);
    return result;
}

// 计算任意 z > 0 的 digamma(z)
long double digamma(long double z) {
    const long double THRESHOLD = 50.0L;
    long double sum = 0.0L;
    int n = 0;
    while (z + n < THRESHOLD) {
        sum += 1.0L / (z + n);
        ++n;
    }
    long double val = digammaLargeZ(z + n);
    val -= sum;
    return val;
}

// 计算 psi(x) = sum_{k=1}^∞ 1/(k(k+x))
long double psi(long double x) {
    if (x == 0.0L) return PI_SQ_OVER_6;
    long double z = x + 1.0L;
    long double dig = digamma(z);
    return (dig + GAMMA) / x;
}

int main() {
    // 输出 3001 行，x = 0.0, 0.1, ..., 300.0
    for (int i = 0; i <= 3000; ++i) {
        double x = i * 0.1;               // 输出用 double
        long double psix = psi((long double)x);
        double psixDouble = (double)psix;
        printf("%6.2f%17.12f\n", x, psixDouble);
    }
    return 0;
}
