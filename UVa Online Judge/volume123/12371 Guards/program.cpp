// Guards
// UVa ID: 12371
// Verdict: Accepted
// Submission Date: 2026-07-28
// UVa Run Time: 0.080s

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1000000007LL;
int main() {
    int T;
    scanf("%d", &T);
    vector<pair<int,int>> queries(T);
    int maxN = 0, maxK = 0;
    for (int i = 0; i < T; ++i) {
        int N, K;
        scanf("%d %d", &N, &K);
        queries[i] = {N, K};
        maxN = max(maxN, N);
        maxK = max(maxK, K);
    }
    vector<ll> fact(maxN + 1);
    fact[0] = 1;
    for (int i = 1; i <= maxN; ++i) fact[i] = fact[i - 1] * i % MOD;
    vector<ll> inv(maxN + 2);
    inv[1] = 1;
    for (int i = 2; i <= maxN + 1; ++i)
        inv[i] = MOD - (MOD / i) * inv[MOD % i] % MOD;
    ll inv2 = (MOD + 1) / 2;
    vector<vector<ll>> f(maxN + 1, vector<ll>(maxK + 1, 0));
    f[0][0] = 1;
    for (int n = 1; n < maxN; ++n) {
        for (int k = 1; k <= maxK; ++k) {
            ll val = ((ll)n * f[n][k] % MOD + inv2 * f[n-1][k-1] % MOD) % MOD;
            f[n+1][k] = val * inv[n+1] % MOD;
        }
    }
    for (int tc = 1; tc <= T; ++tc) {
        int N = queries[tc-1].first;
        int K = queries[tc-1].second;
        ll ans = fact[N] * fact[N] % MOD * f[N][K] % MOD;
        printf("Case %d: %lld\n", tc, ans);
    }
    return 0;
}
