// Casino Advantage
// UVa ID: 12448
// Verdict: Accepted
// Submission Date: 2026-06-23
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// 计算组合数 C(n, k)
ll comb(int n, int k) {
    if (k < 0 || k > n) return 0;
    if (k > n - k) k = n - k;
    ll res = 1;
    for (int i = 1; i <= k; ++i) {
        res = res * (n - i + 1) / i;
    }
    return res;
}

// 快速幂计算 a^b
ll powll(ll a, int b) {
    ll res = 1;
    while (b) {
        if (b & 1) res *= a;
        a *= a;
        b >>= 1;
    }
    return res;
}

// 最大公约数
ll gcdll(ll a, ll b) {
    while (b) { ll t = a % b; a = b; b = t; }
    return a;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int N, M, K;
        scanf("%d %d %d", &N, &M, &K);
        // 不可能的情况
        if (K > N || K > M) {
            printf("0\n");
            continue;
        }
        // 计算容斥和：sum_{i=0}^{K} (-1)^i * C(K,i) * (K-i)^M
        ll sum = 0;
        for (int i = 0; i <= K; ++i) {
            ll term = comb(K, i) * powll(K - i, M);
            if (i & 1) sum -= term;
            else sum += term;
        }
        // 分子 = C(N,K) * sum
        ll numerator = comb(N, K) * sum;
        ll denominator = powll(N, M);
        // 约分
        if (numerator == 0) {
            printf("0\n");
            continue;
        }
        ll g = gcdll(numerator, denominator);
        numerator /= g;
        denominator /= g;
        if (denominator == 1) printf("%lld\n", numerator);
        else printf("%lld/%lld\n", numerator, denominator);
    }
    return 0;
}
