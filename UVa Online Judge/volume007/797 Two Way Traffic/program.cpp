// Two Way Traffic
// UVa ID: 797
// Verdict: Accepted
// Submission Date: 2026-07-08
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

using int64 = long long;

// 向下取整除法 (b > 0)
int64 floor_div(int64 a, int64 b) {
    if (a >= 0) return a / b;
    return - ((-a + b - 1) / b);
}

// 向上取整除法 (b > 0)
int64 ceil_div(int64 a, int64 b) {
    if (a >= 0) return (a + b - 1) / b;
    return - ((-a) / b);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int64 d, d1, d2, v1, v2, t1, t2, ti, tf;
    while (cin >> d >> d1 >> d2 >> v1 >> v2 >> t1 >> t2 >> ti >> tf) {
        int64 ans = 0;
        int64 C = d + d1 + d2;                     // d + v1*(d1/v1) + v2*(d2/v2) 的分子
        // k 的范围：ti - d/v1 <= d1/v1 + k*t1 <= tf
        int64 k_min = ceil_div(ti * v1 - d - d1, t1 * v1);
        int64 k_max = floor_div(tf * v1 - d1, t1 * v1);
        for (int64 k = k_min; k <= k_max; ++k) {
            // 时间条件解 j
            int64 time_low_num = ti * (v1 + v2) - C - v1 * t1 * k;
            int64 time_high_num = tf * (v1 + v2) - C - v1 * t1 * k;
            int64 j_time_low = ceil_div(time_low_num, v2 * t2);
            int64 j_time_high = floor_div(time_high_num, v2 * t2);
            // 位置条件解 j
            // 原式： -d*v1 < (d2*v1 - d1*v2) + v1*v2*(j*t2 - k*t1) < d*v2
            int64 A = (d2 * v1 - d1 * v2) - v1 * v2 * k * t1;
            int64 B = v1 * v2 * t2;   // > 0
            // 左边严格大于：A + B*j > -d*v1  =>  j > (-d*v1 - A)/B
            int64 j_pos_low = floor_div(-d * v1 - A, B) + 1;
            // 右边严格小于：A + B*j < d*v2   =>  j < (d*v2 - A)/B
            int64 j_pos_high = ceil_div(d * v2 - A, B) - 1;
            int64 j_low = max(j_time_low, j_pos_low);
            int64 j_high = min(j_time_high, j_pos_high);
            if (j_low <= j_high) ans += j_high - j_low + 1;
        }
        cout << ans << '\n';
    }
    return 0;
}
