// Equations
// UVa ID: 11266
// Verdict: Accepted
// Submission Date: 2026-06-19
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MOD = 200003;

long long modPow(long long a, long long e) {
    long long r = 1;
    while (e) {
        if (e & 1) r = r * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return r;
}

long long fact[15], invFact[15];

long long comb(long long M, int k) {
    if (M < 0 || k < 0 || k > M) return 0;
    if (k == 0) return 1;
    long long num = 1;
    for (int i = 0; i < k; ++i) num = num * ((M - i) % MOD) % MOD;
    return num * invFact[k] % MOD;
}

int main() {
    fact[0] = 1;
    for (int i = 1; i <= 10; ++i) fact[i] = fact[i-1] * i % MOD;
    invFact[10] = modPow(fact[10], MOD - 2);
    for (int i = 9; i >= 0; --i) invFact[i] = invFact[i+1] * (i+1) % MOD;

    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        long long s;
        scanf("%d %lld", &n, &s);
        vector<long long> A(n), B(n), C(n);
        long long sumA = 0;
        for (int i = 0; i < n; ++i) {
            scanf("%lld %lld", &A[i], &B[i]);
            sumA += A[i];
            C[i] = B[i] - A[i];
        }
        long long S = s - sumA;
        long long ans = 0;
        int total = 1 << n;
        for (int mask = 0; mask < total; ++mask) {
            long long t = S;
            int bits = 0;
            for (int i = 0; i < n; ++i) if (mask & (1 << i)) {
                t -= (C[i] + 1);
                ++bits;
            }
            if (t < 0) continue;
            long long term = comb(t + n - 1, n - 1);
            if (bits & 1) ans = (ans - term) % MOD;
            else ans = (ans + term) % MOD;
        }
        ans = (ans % MOD + MOD) % MOD;
        printf("%lld\n", ans);
    }
    return 0;
}
