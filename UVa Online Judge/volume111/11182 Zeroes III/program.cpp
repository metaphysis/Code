// Zeroes III
// UVa ID: 11182
// Verdict: Accepted
// Submission Date: 2026-01-01
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 质因数分解
vector<pair<int, long long>> primeFactorization(int x) {
    vector<pair<int, long long>> f;
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) {
            long long cnt = 0;
            while (x % i == 0) cnt++, x /= i;
            f.push_back({i, cnt});
        }
    }
    if (x > 1) f.push_back({x, 1});
    return f;
}

// 计算 F2(n) 中质因子 p 的总指数
long long computeTotalExponent(int n, int p) {
    long long total = 0, pk = p;
    while (pk <= n) {
        long long M = n / pk;
        long long L = n - M * pk + 1;
        if (M > 0) {
            // 第一部分：q=1..M-1
            if (M > 1) {
                long long part1 = pk * M * (M - 1) / 2 * (2 * (n + 1) - (pk - 1)) / 2;
                long long part2 = pk * pk * M * (M - 1) * (2 * M - 1) / 6;
                total += part1 - part2;
            }
            // 第二部分：q=M
            total += M * L * (L + 1) / 2;
        }
        if (pk > n / p) break;
        pk *= p;
    }
    return total;
}

int main() {
    int n, b;
    while (cin >> n >> b && b) {
        auto factors = primeFactorization(b);
        long long answer = LLONG_MAX;
        for (auto& [p, expB] : factors) {
            if (p > n) {
                answer = 0;
                break;
            }
            long long totalExp = computeTotalExponent(n, p);
            answer = min(answer, totalExp / expB);
        }
        cout << answer << "\n";
    }
    return 0;
}
