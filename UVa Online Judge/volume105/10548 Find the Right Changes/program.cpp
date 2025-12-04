// Find the Right Changes
// UVa ID: 10548
// Verdict: Accepted
// Submission Date: 2025-12-04
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 扩展欧几里得算法，返回 gcd(a,b)，并解出 ax + by = gcd(a,b) 的一组整数解 (x,y)
long long extendedGcd(long long a, long long b, long long& x, long long& y) {
    if (b == 0) { x = 1; y = 0; return a; }
    long long g = extendedGcd(b, a % b, y, x);
    y -= a / b * x;
    return g;
}

// 计算 a>0, b>0, c>0 时方程 ax + by = c 的非负整数解的个数
long long countNonnegSolutions(long long a, long long b, long long c) {
    long long x0, y0;
    long long g = extendedGcd(a, b, x0, y0);
    if (c % g != 0) return 0; // 无整数解
    x0 *= c / g;
    y0 *= c / g;
    long long A = a / g, B = b / g;
    // 通解: x = x0 + k*B, y = y0 - k*A
    // 需要 x >= 0 且 y >= 0
    long long low = ceil((-x0) / (double)B);
    long long high = floor(y0 / (double)A);
    if (low > high) return 0;
    return high - low + 1;
}

int main() {
    int n; scanf("%d", &n);
    while (n--) {
        long long a, b, c; scanf("%lld %lld %lld", &a, &b, &c);
        
        // 情况 1: a>0, b>0
        if (a > 0 && b > 0) {
            if (c < 0) puts("Impossible"); // 左边非负，右边为负，无解
            else {
                long long cnt = countNonnegSolutions(a, b, c);
                if (cnt == 0) puts("Impossible");
                else printf("%lld\n", cnt);
            }
        }
        // 情况 2: a<0, b>0
        else if (a < 0 && b > 0) {
            // 化为正系数方程判断解的存在性
            long long g = __gcd(llabs(a), llabs(b));
            if (c % g == 0) puts("Infinitely many solutions");
            else puts("Impossible");
        }
        // 情况 3: a>0, b<0
        else if (a > 0 && b < 0) {
            long long g = __gcd(llabs(a), llabs(b));
            if (c % g == 0) puts("Infinitely many solutions");
            else puts("Impossible");
        }
        // 情况 4: a<0, b<0 不会出现（题目约束）
    }
    return 0;
}
