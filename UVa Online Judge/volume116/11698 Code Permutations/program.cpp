// Code Permutations
// UVa ID: 11698
// Verdict: Accepted
// Submission Date: 2026-07-30
// UVa Run Time: 0.020s

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll MOD = 2147483647LL;

ll modPow(ll a, ll e) {
    ll r = 1;
    while (e) {
        if (e & 1) r = r * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int N;
        ll K;
        cin >> N >> K;
        if (K == 1) {
            cout << 1 << "\n";
            continue;
        }
        // 分解 K
        vector<pair<ll, int>> fac;
        ll tmp = K;
        for (ll p = 2; p * p <= tmp; ++p) {
            if (tmp % p == 0) {
                int cnt = 0;
                while (tmp % p == 0) { tmp /= p; ++cnt; }
                fac.push_back({p, cnt});
            }
        }
        if (tmp > 1) fac.push_back({tmp, 1});
        int M = fac.size();
        bool ok = true;
        for (auto &pe : fac) {
            ll pp = 1;
            for (int i = 0; i < pe.second; ++i) pp *= pe.first;
            if (pp > N) { ok = false; break; }
        }
        if (!ok) {
            cout << 0 << "\n";
            continue;
        }
        // 生成有效长度 l (2..N) 且 l 整除 K，并计算 mask
        vector<pair<int, int>> lengths;
        for (int l = 2; l <= N; ++l) {
            if (K % l != 0) continue;
            int mask = 0;
            for (int i = 0; i < M; ++i) {
                ll p = fac[i].first;
                int e = fac[i].second;
                int cnt = 0;
                ll x = l;
                while (x % p == 0) { x /= p; ++cnt; }
                if (cnt == e) mask |= (1 << i);
            }
            lengths.push_back({l, mask});
        }
        if (lengths.empty()) {
            cout << 0 << "\n";
            continue;
        }
        // 预计算阶乘与逆元
        vector<ll> fact(N + 1), invfact(N + 1);
        fact[0] = 1;
        for (int i = 1; i <= N; ++i) fact[i] = fact[i - 1] * i % MOD;
        invfact[N] = modPow(fact[N], MOD - 2);
        for (int i = N; i >= 1; --i) invfact[i - 1] = invfact[i] * i % MOD;
        // DP
        int fullMask = (1 << M) - 1;
        vector<vector<ll>> dp(N + 1, vector<ll>(1 << M, 0));
        dp[0][0] = 1;
        for (auto &pr : lengths) {
            int l = pr.first;
            int lMask = pr.second;
            vector<vector<ll>> ndp = dp; // 不选当前长度的方案
            ll invL = modPow(l, MOD - 2);
            vector<ll> factor((N / l) + 1, 1);
            ll cur = 1;
            for (int c = 1; c <= N / l; ++c) {
                cur = cur * invL % MOD;
                factor[c] = cur * invfact[c] % MOD;
            }
            for (int s = 0; s <= N; ++s) {
                for (int mask = 0; mask <= fullMask; ++mask) {
                    ll val = dp[s][mask];
                    if (!val) continue;
                    int maxC = (N - s) / l;
                    for (int c = 1; c <= maxC; ++c) {
                        int ns = s + c * l;
                        int nmask = mask | lMask;
                        ndp[ns][nmask] = (ndp[ns][nmask] + val * factor[c]) % MOD;
                    }
                }
            }
            dp.swap(ndp);
        }
        ll ans = 0;
        for (int s = 0; s <= N; ++s) {
            ll ways = dp[s][fullMask];
            if (!ways) continue;
            ans = (ans + ways * fact[N] % MOD * invfact[N - s]) % MOD;
        }
        cout << ans << "\n";
    }
    return 0;
}
