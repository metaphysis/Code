// Trees in a Wood
// UVa ID: 10214
// Verdict: Accepted
// Submission Date: 2025-10-23
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAX_A = 2000; // a 的最大值

vector<int> mobius; // Möbius 函数值
vector<int> primes; // 素数表
vector<bool> isPrime; // 标记是否为素数

// 筛法计算 Möbius 函数
void sieveMobius(int n) {
    mobius.resize(n + 1, 1);
    isPrime.resize(n + 1, true);
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i <= n; i++) {
        if (isPrime[i]) {
            primes.push_back(i);
            mobius[i] = -1;
        }
        for (int p : primes) {
            if (i * p > n) break;
            isPrime[i * p] = false;
            if (i % p == 0) {
                mobius[i * p] = 0;
                break;
            } else {
                mobius[i * p] = -mobius[i];
            }
        }
    }
}

int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    sieveMobius(MAX_A); // 预计算 Möbius 函数
    int a, b;
    while (cin >> a >> b) {
        if (a == 0 && b == 0) break;
        long long visibleCount = 0;
        // 计算第一象限内部可见树数量
        for (int x = 1; x <= a; x++) {
            long long countY = 0;
            // 枚举 x 的所有约数 d
            for (int d = 1; d * d <= x; d++) {
                if (x % d == 0) {
                    countY += mobius[d] * (b / d);
                    int d2 = x / d;
                    if (d2 != d) countY += mobius[d2] * (b / d2);
                }
            }
            visibleCount += countY;
        }
        // 四个象限内部可见树数量乘以 4，加上坐标轴上的 4 棵
        visibleCount = visibleCount * 4 + 4;
        // 计算总树数量
        long long totalTrees = (long long)(2 * a + 1) * (2 * b + 1) - 1;
        double ratio = (double)visibleCount / totalTrees;
        cout << fixed << setprecision(7) << ratio << '\n';
    }
    return 0;
}
