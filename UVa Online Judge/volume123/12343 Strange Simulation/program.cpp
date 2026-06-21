// Strange Simulation
// UVa ID: 12343
// Verdict: Accepted
// Submission Date: 2026-06-21
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;

// 返回 x 的二进制位数（不含前导零）
int bitlen(ull x) {
    int len = 0;
    while (x) { ++len; x >>= 1; }
    return len;
}

// 计算 0 ^ 1 ^ ... ^ n
ull xorPrefix(ull n) {
    switch (n % 4) {
        case 0: return n;
        case 1: return 1;
        case 2: return n + 1;
        default: return 0;
    }
}

int main() {
    int T;
    scanf("%d", &T);
    for (int tc = 1; tc <= T; ++tc) {
        ull p, q;
        scanf("%llu %llu", &p, &q);

        int L = bitlen(q);          // 最大位数
        ull ans = 0;

        for (int k = 1; k <= L; ++k) {
            ull low  = 1ULL << (k - 1);                 // 2^(k-1)
            ull high = (k == 63) ? ~0ULL : ((1ULL << k) - 1); // 2^k - 1

            ull left  = max(p, low);
            ull right = min(q, high);

            if (left <= right) {
                ull xorRange = xorPrefix(right) ^ xorPrefix(left - 1);
                int shift = L - k;
                ans ^= (xorRange << shift);
            }
        }

        printf("Case %d: %llu\n", tc, ans);
    }
    return 0;
}
