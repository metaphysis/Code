// XOR Sequence Revisited
// UVa ID: 13081
// Verdict: Accepted
// Submission Date: 2026-01-07
// UVa Run Time: 0.050s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 根据推导公式计算 A[x]
long long getValue(long long x) {
    if (x == 0) return 1;
    switch (x % 4) {
        case 0: return 1 ^ x;          // 1 XOR x
        case 1: return 0;
        case 2: return 1 ^ (x + 1);    // 1 XOR (x+1)
        case 3: return 1;
    }
    return 0; // 不会执行到这里
}

// 检查在区间 [L, R] 中，是否存在至少一个 i 使得 A[i] 的第 bit 位为 0
bool hasZeroBit(long long L, long long R, int bit) {
    long long mask = 1LL << bit;
    // 枚举模 4 的余数
    for (int r = 0; r < 4; ++r) {
        // 找到第一个 >= L 且模 4 余 r 的数
        long long first = L;
        if (first % 4 != r) first += (r - first % 4 + 4) % 4;
        if (first > R) continue;
        // 找到最后一个 <= R 且模 4 余 r 的数
        long long last = R;
        if (last % 4 != r) last -= (last % 4 - r + 4) % 4;
        if (last < first) continue;
        // 对于余数 r，A[i] 的值是固定的（除了 r=0 时 A_0=1 需要特殊处理）
        // 我们只需检查该余数对应的 A[i] 的第 bit 位是否为 0
        long long val = getValue(first);
        if ((val & mask) == 0) return true; // 存在至少一个使该位为 0 的 A[i]
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        long long L, R;
        cin >> L >> R;
        long long answer = 0;
        // 最多考虑 60 位（因为 10^15 < 2^50）
        for (int bit = 0; bit < 60; ++bit) {
            if (!hasZeroBit(L, R, bit)) answer |= (1LL << bit);
        }
        cout << answer << "\n";
    }
    return 0;
}
