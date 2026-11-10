#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef __int128 i128;

// 扩展欧几里得
ll exgcd(ll a, ll b, ll& x, ll& y) {
    if (b == 0) { x = 1; y = 0; return a; }
    ll g = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return g;
}

// 逆元（要求 gcd(a, mod) = 1）
ll invMod(ll a, ll mod) {
    ll x, y;
    exgcd(a, mod, x, y);
    return (x % mod + mod) % mod;
}

// 乘法取模（防溢出）
ll mulMod(ll a, ll b, ll mod) {
    return (ll)((i128)a * b % mod);
}

// 快速幂
ll powMod(ll a, ll b, ll mod) {
    ll r = 1 % mod;
    a %= mod;
    while (b) {
        if (b & 1) r = mulMod(r, a, mod);
        a = mulMod(a, a, mod);
        b >>= 1;
    }
    return r;
}

// 普通 BSGS，要求 gcd(a, p) = 1
ll bsgs(ll a, ll b, ll p) {
    a %= p; b %= p;
    if (p == 1) return b == 0 ? 0 : -1;
    if (b == 1) return 0;

    ll m = (ll)sqrt((long double)p) + 1;
    unordered_map<ll, ll> mp;
    mp.reserve((size_t)(2 * m));

    // mp[a^j] = j
    ll cur = 1 % p;
    for (ll i = 0; i < m; i++) {
        if (!mp.count(cur)) mp[cur] = i;
        cur = mulMod(cur, a, p);
    }

    ll am = powMod(a, m, p);
    ll invAm = invMod(am, p);   // gcd(a,p)=1 保证存在

    // 查 b * a^{-im}
    cur = b;
    for (ll i = 0; i <= m; i++) {
        if (mp.count(cur)) return i * m + mp[cur];
        cur = mulMod(cur, invAm, p);
    }
    return -1;
}

int main() {
    int a, b, p;
    while (cin >> a >> b >> p)  cout << bsgs(a, b, p) << '\n';
    return 0;
}
