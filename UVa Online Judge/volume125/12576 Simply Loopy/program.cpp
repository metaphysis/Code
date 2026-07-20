// Simply Loopy
// UVa ID: 12576
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;
const ull MOD = 7477777ULL;

// 计算 sum_{i=1}^{x} i^2，使用 __int128 防溢出
static inline __int128 getS2(int x) {
    __int128 a = x;
    return a * (a + 1) * (2 * a + 1) / 6;
}

// 计算 sum_{i=1}^{x} i^3
static inline __int128 getS3(int x) {
    __int128 a = x;
    __int128 t = a * (a + 1) / 2;
    return t * t;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    vector<int> queries(T);
    int maxN = 0;
    for (int i = 0; i < T; ++i) {
        cin >> queries[i];
        if (queries[i] > maxN) maxN = queries[i];
    }
    // 预计算 H(n) 数组，下标从 1 开始
    vector<ull> hVal(maxN + 2, 0);
    for (int n = 3; n <= maxN - 1; ++n) {
        int x = n - 2;                // x >= 1
        __int128 s2 = getS2(x);
        __int128 s3 = getS3(x);
        __int128 val = (__int128)(n - 1) * s2 - s3;   // 恒为正
        hVal[n] = (ull)(val % MOD);
    }
    // fVal[n] = F(n), gVal[n] = G(n)
    vector<ull> fVal(maxN + 2, 0), gVal(maxN + 2, 0);
    // 递推
    for (int n = 1; n < maxN; ++n) {
        fVal[n + 1] = (fVal[n] + (5ULL * gVal[n]) % MOD) % MOD;
        gVal[n + 1] = (gVal[n] + hVal[n]) % MOD;
    }
    // 输出结果
    for (int i = 0; i < T; ++i) {
        int n = queries[i];
        cout << "Case " << (i + 1) << ": " << fVal[n] << '\n';
    }
    return 0;
}
