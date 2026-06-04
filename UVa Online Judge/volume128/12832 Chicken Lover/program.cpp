// Chicken Lover
// UVa ID: 12832
// Verdict: Accepted
// Submission Date: 2026-06-04
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

long long gcd(long long a, long long b) {
    while (b) { long long t = b; b = a % b; a = t; }
    return a;
}

int main() {
    int T; scanf("%d", &T);
    for (int caseNum = 1; caseNum <= T; caseNum++) {
        int m; scanf("%d", &m);
        long long numerator = 0, denominator = 1;
        for (int i = 0; i < m; i++) {
            int n, k; scanf("%d %d", &n, &k);
            // 当前项 = k / n
            // 分数加法： numerator/denominator + k/n
            long long newNumerator = numerator * n + k * denominator;
            long long newDenominator = denominator * n;
            numerator = newNumerator;
            denominator = newDenominator;
            // 约分，防止溢出
            long long g = gcd(numerator, denominator);
            numerator /= g; denominator /= g;
        }
        printf("Case %d: %lld/%lld\n", caseNum, numerator, denominator);
    }
    return 0;
}
