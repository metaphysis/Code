// Magic Bitstrings
// UVa ID: 10866
// Verdict: Accepted
// Submission Date: 2026-01-09
// UVa Run Time: 0.100s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 快速幂取模：计算 (a^b) % mod
long long powMod(long long a, long long b, long long mod) {
    long long result = 1;
    while (b > 0) {
        if (b & 1) result = result * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return result;
}

// 判断是否存在并构造魔法比特串
string solve(int p) {
    // 根据数论结论，当 p = 2 时是特殊情况，没有非平凡的魔法串
    if (p == 2) return "Impossible";
    string result(p - 1, '0'); // 初始化全0串
    // 根据原根的性质，当 p 为奇素数时，存在非平凡的魔法串
    // 构造方法：result[i] = (powMod(i+1, p-2, p) > 1) ? '0' : '1'
    // 但这里采用更直接的构造：对于 i 从 1 到 p-1，如果 i 是模 p 的二次剩余，则对应位置为 0，否则为 1
    // 而 1 总是二次剩余，所以 result[0] 固定为 0
    result[0] = '0';
    for (int i = 2; i <= p - 1; i++) {
        // 利用勒让德符号判断 i 是否为模 p 的二次剩余
        // 当 i^((p-1)/2) % p == 1 时，i 是二次剩余，对应位为 0
        if (powMod(i, (p - 1) / 2, p) == 1) result[i - 1] = '0';
        else result[i - 1] = '1';
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int p;
    while (cin >> p and p != 0) cout << solve(p) << "\n";
    return 0;
}
