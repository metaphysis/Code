// The Soldier's Dilemma
// UVa ID: 12887
// Verdict: Accepted
// Submission Date: 2026-05-27
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;
const int MAXN = 5000;

long long fact[MAXN * 2 + 5], invFact[MAXN * 2 + 5];

long long modPow(long long a, long long e) {
    long long res = 1;
    while (e) {
        if (e & 1) res = res * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return res;
}

void precompute() {
    fact[0] = 1;
    for (int i = 1; i <= 2 * MAXN; ++i)
        fact[i] = fact[i - 1] * i % MOD;
    invFact[2 * MAXN] = modPow(fact[2 * MAXN], MOD - 2);
    for (int i = 2 * MAXN - 1; i >= 0; --i)
        invFact[i] = invFact[i + 1] * (i + 1) % MOD;
}

long long comb(int n, int k) {
    if (k < 0 || k > n) return 0;
    return fact[n] * invFact[k] % MOD * invFact[n - k] % MOD;
}

long long catalan(int n) {
    return comb(2 * n, n) * modPow(n + 1, MOD - 2) % MOD;
}

int main() {
    precompute();
    int T;
    scanf("%d", &T);
    while (T--) {
        int N;
        scanf("%d", &N);
        printf("%lld\n", catalan(N));
    }
    return 0;
}
