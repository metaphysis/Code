// Maximum
// UVa ID: 1319
// Verdict: Accepted
// Submission Date: 2026-07-16
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int m, p, a, b;
    while (cin >> m >> p >> a >> b) {
        long double sqrtA = sqrtl((long double)a);
        long double L = -1.0L / sqrtA;          // 下限
        long double U = sqrtA;                  // 上限
        long double total = (long double)b * sqrtA;
        long double ans = -1.0e100L;
        const long double eps = 1e-9L;
        // 1) 全部取端点：t个U，其余L
        for (int t = 0; t <= m; ++t) {
            long double sum = t * U + (m - t) * L;
            if (fabsl(sum - total) <= eps) {
                long double val = t * powl(U, p) + (m - t) * powl(L, p);
                if (val > ans) ans = val;
            }
        }
        // 2) 一个内部变量z，其余取端点
        for (int t = 0; t < m; ++t) {
            long double z = total - t * U - (m - t - 1) * L;
            if (z >= L - eps && z <= U + eps) {
                long double val = t * powl(U, p) + powl(z, p) + (m - t - 1) * powl(L, p);
                if (val > ans) ans = val;
            }
        }
        // 四舍五入到最接近整数
        long long result = llroundl(ans);
        cout << result << '\n';
    }
    return 0;
}
