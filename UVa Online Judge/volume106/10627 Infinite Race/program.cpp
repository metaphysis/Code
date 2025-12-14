// Infinite Race
// UVa ID: 10627
// Verdict: Accepted
// Submission Date: 2025-12-14
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    long long L, u, v, t;
    while (cin >> L >> u >> v >> t) {
        if (L == 0) break;
        if (u == 0 && v == 0) {
            cout << 0 << endl;
            continue;
        }
        // 确保 u >= v
        if (u < v) swap(u, v);
        long long ans = 0;
        // 迎面相遇次数
        ans += ((u + v) * t + L) / (2 * L);
        // 同向超越次数
        ans += ((u - v) * t + L) / (2 * L);
        // 减去重复计算的端点相遇
        long long d = __gcd(u, v);
        if ((u - v) / d % 2 != 0) ans -= (d * t + L) / (2 * L);
        cout << ans << endl;
    }
    return 0;
}
