// John's Tree
// UVa ID: 12749
// Verdict: Accepted
// Submission Date: 2026-06-18
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll MOD = 1000000007LL;

ll modPow(ll a, ll e, ll mod) {
    ll r = 1;
    a %= mod;
    while (e > 0) {
        if (e & 1) r = (r * a) % mod;
        a = (a * a) % mod;
        e >>= 1;
    }
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    for (int cs = 1; cs <= T; ++cs) {
        ll D, V;
        cin >> D >> V;
        ll r;
        if (D == 0) r = 1;
        else if (D == 1) r = (V + 1) % MOD;
        else if (V == 1) {
            cout << "Case " << cs << ": -1\n";
            continue;
        } else if (V == 2) r = (2 * (D % MOD) + 1) % MOD;
        else {
            ll a = (V - 1) % MOD;
            ll p = modPow(a, D, MOD);
            ll numerator = (p - 1 + MOD) % MOD;
            ll denom = (V - 2) % MOD;
            ll invMod = modPow(denom, MOD - 2, MOD);
            ll sum = (V % MOD) * numerator % MOD * invMod % MOD;
            r = (1 + sum) % MOD;
        }
        cout << "Case " << cs << ": " << r << "\n";
    }
    return 0;
}
