#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll MOD = 1000000007;

// 快速幂取模
ll powMod(ll a, ll e) {
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
    int T; cin >> T;
    for (int cas = 1; cas <= T; ++cas) {
        int C; cin >> C;
        ll n = 1;                 // n 模 MOD
        ll prodF = 1;             // 所有 F(p_i^{a_i}) 的乘积
        ll inv2 = (MOD + 1) / 2;  // 2 的模逆元
        ll inv2k = 1;             // 2^{-k} 的模逆元
        while (C--) {
            ll p, a; cin >> p >> a;
            ll pa = powMod(p, a); // p^a mod MOD
            n = n * pa % MOD;     // 累积计算 n mod MOD

            ll Fi; // 计算 F(p^a) mod MOD
            if (a == 1) {
                // 公式: F(p) = 4p + 2
                Fi = (4 * pa + 2) % MOD;
            } else {
                // 公式: F(p^a) = 2(a+1)p^a + 2(p^a - p)/(p-1) + 2
                ll term1 = 2 * (a + 1) % MOD * pa % MOD;
                // 注意 (p^a - p) 可能为负，先加 MOD
                ll term2 = 2 * (pa - p + MOD) % MOD * powMod(p - 1, MOD - 2) % MOD;
                Fi = (term1 + term2 + 2) % MOD;
            }
            prodF = prodF * Fi % MOD;
            inv2k = inv2k * inv2 % MOD; // 累积 2^{-k}
        }
        ll ans = (n + prodF * inv2k % MOD) % MOD;
        cout << "Case " << cas << ": " << ans << "\n";
    }
    return 0;
}
