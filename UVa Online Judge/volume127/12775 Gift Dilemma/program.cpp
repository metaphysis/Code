// 
// UVa ID: 
// Verdict: Accepted
// Submission Date: 2025-10-
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
// 计算最大公约数
long long computeGcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
// 扩展欧几里得算法，求解 ax + by = gcd(a, b)
void extendedGcd(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return;
    }
    extendedGcd(b, a % b, y, x);
    y -= a / b * x;
}
// 计算 a 在模 m 下的逆元，要求 gcd(a, m) = 1
long long modularInverse(long long a, long long m) {
    long long x, y;
    extendedGcd(a, m, x, y);
    return (x % m + m) % m;
}
int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int testCases; cin >> testCases;
    for (int caseNum = 1; caseNum <= testCases; caseNum++) {
        long long priceA, priceB, priceC, totalPrice;
        cin >> priceA >> priceB >> priceC >> totalPrice;
        // 计算最大公约数并检查是否有解
        long long gcdABC = computeGcd(computeGcd(priceA, priceB), priceC);
        if (totalPrice % gcdABC != 0) {
            cout << "Case " << caseNum << ": 0\n";
            continue;
        }
        // 归一化处理
        priceA /= gcdABC; priceB /= gcdABC; priceC /= gcdABC; totalPrice /= gcdABC;
        // 计算 A 和 B 的最大公约数
        long long gcdAB = computeGcd(priceA, priceB);
        long long normalizedA = priceA / gcdAB, normalizedB = priceB / gcdAB;
        // 预处理逆元
        long long inverseA = modularInverse(normalizedA, normalizedB);
        long long solutionCount = 0;
        // 枚举 z 的可能取值
        for (long long z = 0; z * priceC <= totalPrice; z++) {
            long long remaining = totalPrice - z * priceC;
            // 检查剩余金额是否能被 gcdAB 整除
            if (remaining % gcdAB != 0) continue;
            long long reducedRemaining = remaining / gcdAB;
            // 计算特解 x0
            long long remainder = reducedRemaining % normalizedB;
            long long x0 = (remainder * inverseA) % normalizedB;
            // 计算 x 的最大可能值
            long long maxX = reducedRemaining / normalizedA;
            // 如果特解超出范围，则无解
            if (x0 > maxX) continue;
            // 计算解的数量
            long long count = (maxX - x0) / normalizedB + 1;
            if (count > 0) solutionCount += count;
        }
        cout << "Case " << caseNum << ": " << solutionCount << "\n";
    }
    return 0;
}
