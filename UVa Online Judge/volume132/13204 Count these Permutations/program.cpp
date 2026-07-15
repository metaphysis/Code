// Count these Permutations
// UVa ID: 13204
// Verdict: Accepted
// Submission Date: 2026-07-13
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;
const int MAXN = 1000000;

int main() {
    // 预计算阶乘 fact[i] = i! mod MOD
    static long long fact[MAXN + 1];
    fact[0] = 1;
    for (int i = 1; i <= MAXN; ++i) fact[i] = fact[i - 1] * i % MOD;
    int n;
    // 读取所有输入，直到 EOF
    while (cin >> n) {
        int k = n / 2;                     // 向下取整
        long long ans = fact[k] * fact[k] % MOD;
        if (n & 1)                         // n 为奇数
            ans = ans * n % MOD;
        cout << ans << '\n';
    }
    return 0;
}
