// How Many in 3D
// UVa ID: 12446
// Verdict: Accepted
// Submission Date: 2026-01-11
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MOD = 1000000007;
// f数组存储f(0)到f(1000000)
ll f[1000010] = {1, 2, 9, 32}; // 初始化前4项

int main() {
    // 预计算所有f(n)
    for (int i = 4; i <= 1000000; i++) {
        // 递推公式：f(n) = 3f(n-1) + 3f(n-2) - f(n-3)
        f[i] = (3 * f[i - 1] + 3 * f[i - 2] - f[i - 3]) % MOD;
        // 处理负数
        if (f[i] < 0) f[i] += MOD;
    }
    int T, n;
    cin >> T;
    while (T--) {
        cin >> n;
        cout << f[n] << '\n';
    }
    return 0;
}
