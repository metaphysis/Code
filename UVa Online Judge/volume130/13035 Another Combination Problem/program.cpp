// Another Combination Problem
// UVa ID: 13035
// Verdict: Accepted
// Submission Date: 2025-12-01
// UVa Run Time: 0.030s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1000000007;

// 快速幂取模
ll modPow(ll base, ll exp, ll mod) {
    ll result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) result = (result * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

// 模逆元（费马小定理）
ll modInv(ll x, ll mod) {
    return modPow(x, mod - 2, mod);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    for (int caseId = 1; caseId <= T; ++caseId) {
        ll N;
        cin >> N;
        // 通项公式：S = N * (N+1) * (N+2) / 3
        // 因为要取模，所以改为乘逆元
        ll a = N % MOD;
        ll b = (N + 1) % MOD;
        ll c = (N + 2) % MOD;
        ll inv3 = modInv(3, MOD); // 3的模逆元
        ll ans = (((a * b) % MOD) * c) % MOD;
        ans = (ans * inv3) % MOD;
        cout << "Case " << caseId << ": " << ans << "\n";
    }
    return 0;
}
