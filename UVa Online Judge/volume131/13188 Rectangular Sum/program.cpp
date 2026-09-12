#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const ll mod = 1000000007;
const ll inv2 = 500000004;
const ll inv6 = 166666668;

ll mul(ll a, ll b) {
    return a * b % mod;
}

ll calcF(ll x) {
    x %= mod;
    return mul(mul(x, (x + mod - 1) % mod), (x + 1) % mod) * inv6 % mod;
}

ll solve(ll n) {
    ll h, w, sum, ans;
    h = (n + 1) / 2;
    w = n + 1 - h;
    sum = (calcF(n) - calcF(w - 1) + mod) % mod;
    ans = mul(w % mod, sum);
    ans = (ans + mul(mul(h % mod, w % mod), (n + 1) % mod) * inv2) % mod;
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, i;
    ll n;
    cin >> t;
    for (i = 1; i <= t; i++) {
        cin >> n;
        cout << "Case #" << i << ": " << solve(n) << '\n';
    }
    return 0;
}
