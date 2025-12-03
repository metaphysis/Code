// Thinking Backward
// UVa ID: 10623
// Verdict: Accepted
// Submission Date: 2025-12-03
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 计算区域数的函数
long long computeRegions(long long m, long long n, long long p) {
    return 2 * m * m - 2 * m + n * n - n + 3 * p * p - 3 * p + 6 * m * p + 4 * m * n + 6 * n * p + 2;
}

int main() {
    unsigned int N;
    int caseNo = 1;
    while (cin >> N && N != -1) {
        cout << "Case " << caseNo++ << ":\n";
        if (N == 1) {
            cout << "0 0 0\n";
            continue;
        }
        vector<tuple<int, int, int>> solutions;
        // 枚举m和p
        for (int m = 0; m < 100; ++m)
            for (int p = 0; p < 100; ++p) {
                // 二次方程系数
                // n² + (4m+6p-1)n + (2m²-2m+3p²-3p+6mp+2-N) = 0
                long long A = 1;
                long long B = 4 * m + 6 * p - 1;
                long long C = 2LL * m * m - 2 * m + 3LL * p * p - 3 * p + 6LL * m * p + 2 - N;
                // 判别式
                long long discriminant = B * B - 4 * A * C;
                if (discriminant < 0) continue;
                // 求平方根
                long long sqrt_disc = sqrt(discriminant);
                if (sqrt_disc * sqrt_disc != discriminant) continue;
                // 解1: n = (-B + sqrt_disc) / 2
                if ((-B + sqrt_disc) % 2 == 0) {
                    long long n = (-B + sqrt_disc) / 2;
                    if (n >= 0 && n < 20000)
                        solutions.push_back(make_tuple(m, n, p));
                }
            }
        // 排序：按m升序，然后按n升序
        sort(solutions.begin(), solutions.end());
        if (solutions.empty()) cout << "Impossible.\n";
        else {
            for (const auto& sol : solutions)
                cout << get<0>(sol) << ' ' << get<1>(sol) << ' ' << get<2>(sol) << '\n';
        }
    }
    return 0;
}
