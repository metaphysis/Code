// Forming Teams
// UVa ID: 13085
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.020s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MAXN = 1000000;
const ll MOD = 1000000007LL;

ll fact[MAXN + 5], invfact[MAXN + 5];

ll modPow(ll a, ll b) {
    ll res = 1;
    a %= MOD;
    while (b) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

int main() {
    fact[0] = 1;
    for (int i = 1; i <= MAXN; ++i) fact[i] = fact[i - 1] * i % MOD;
    invfact[MAXN] = modPow(fact[MAXN], MOD - 2);
    for (int i = MAXN; i >= 1; --i) invfact[i - 1] = invfact[i] * i % MOD;

    int T;
    scanf("%d", &T);
    for (int tc = 1; tc <= T; ++tc) {
        int N;
        scanf("%d", &N);
        ll ans = 0;
        for (int k = 1; k * k <= N; ++k) {
            if (N % k == 0) {
                int d1 = k, d2 = N / k;
                int m1 = N / d1;
                ll term1 = fact[N] * modPow(invfact[d1], m1) % MOD * invfact[m1] % MOD;
                ans = (ans + term1) % MOD;
                if (d2 != d1) {
                    int m2 = N / d2;
                    ll term2 = fact[N] * modPow(invfact[d2], m2) % MOD * invfact[m2] % MOD;
                    ans = (ans + term2) % MOD;
                }
            }
        }
        printf("Case %d: %lld\n", tc, ans);
    }
    return 0;
}
