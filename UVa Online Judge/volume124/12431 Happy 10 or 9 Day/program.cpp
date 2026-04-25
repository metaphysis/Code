// Happy 10/9 Day
// UVa ID: 12431
// Verdict: Accepted
// Submission Date: 2026-04-23
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// 快速幂取模：计算 (a^b) % mod，使用 __int128 避免乘法溢出
ll powMod(ll a, ll b, ll mod) {
    ll res = 1 % mod;
    a %= mod;
    while (b > 0) {
        if (b & 1) res = (ll)((__int128)res * a % mod);
        a = (ll)((__int128)a * a % mod);
        b >>= 1;
    }
    return res;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int caseNo = 1; caseNo <= T; ++caseNo) {
        ll n, b, d, M;
        scanf("%lld %lld %lld %lld", &n, &b, &d, &M);
        
        if (M == 1) {
            printf("Case %d: 0\n", caseNo);
            continue;
        }
        
        // 模数扩大 (b-1) 倍
        ll mod = M * (b - 1);
        ll bn = powMod(b, n, mod);
        ll numerator = (bn - 1 + mod) % mod;  // (b^n - 1) mod (M*(b-1))
        
        // 整除 (b-1) 得到等比数列和
        ll sum = numerator / (b - 1);
        ll ans = (d % M) * (sum % M) % M;
        
        printf("Case %d: %lld\n", caseNo, ans);
    }
    return 0;
}
