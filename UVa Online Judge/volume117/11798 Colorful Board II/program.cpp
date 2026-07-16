// Colorful Board II
// UVa ID: 11798
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.010s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAX_S = 400;
const int MAX_K = 50;
const long long MOD = 1000000007LL;

long long stirling[MAX_S + 1][MAX_S + 1];
long long ways[201][201][MAX_K + 1];
long long factorial[MAX_K + 1];
long long invFactorial[MAX_K + 1];

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
    // 第二类斯特林数
    stirling[0][0] = 1;
    for (int n = 1; n <= MAX_S; ++n) {
        stirling[n][0] = 0;
        for (int k = 1; k <= n; ++k)
            stirling[n][k] = (stirling[n - 1][k - 1] + (long long)k * stirling[n - 1][k]) % MOD;
    }

    // 阶乘
    factorial[0] = 1;
    for (int i = 1; i <= MAX_K; ++i) factorial[i] = factorial[i - 1] * i % MOD;

    // 逆阶乘
    invFactorial[MAX_K] = modPow(factorial[MAX_K], MOD - 2);
    for (int i = MAX_K - 1; i >= 0; --i)
        invFactorial[i] = invFactorial[i + 1] * (i + 1) % MOD;

    // 预处理 g[A][B][t]
    for (int S = 1; S <= MAX_S; ++S) {
        int A = (S + 1) / 2;
        int B = S / 2;
        for (int t = 0; t <= MAX_K; ++t) {
            long long sum = 0;
            for (int e = 0; e <= t; ++e)
                sum = (sum + stirling[A][e] * stirling[B][t - e]) % MOD;
            ways[A][B][t] = sum;
        }
    }
}

int main() {
    precompute();
    int T;
    scanf("%d", &T);
    for (int caseNo = 1; caseNo <= T; ++caseNo) {
        int M, N, K;
        scanf("%d %d %d", &M, &N, &K);
        int total = (M + 1) * (N + 1);
        int A = (total + 1) / 2;
        int B = total / 2;

        long long ans = 0;
        for (int t = 0; t <= K; ++t) {
            long long perm = factorial[K] * invFactorial[K - t] % MOD;
            ans = (ans + perm * ways[A][B][t]) % MOD;
        }
        printf("Case %d: %lld\n", caseNo, ans);
    }
    return 0;
}
