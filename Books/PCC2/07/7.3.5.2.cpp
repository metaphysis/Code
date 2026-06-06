// 扩展欧几里得算法，用于求逆元
ll exgcd(ll a, ll b, ll& x, ll& y) {
    if (b == 0) { x = 1; y = 0; return a; }
    ll g = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return g;
}

// 求逆元，要求 gcd(a, mod) = 1
ll invMod(ll a, ll mod) {
    ll x, y;
    exgcd(a, mod, x, y);
    return (x % mod + mod) % mod;
}

// 快速幂
ll powMod(ll a, ll b, ll mod) {
    ll r = 1 % mod;
    a %= mod;
    while (b) {
        if (b & 1) r = (r + a) % mod;
        a = (a + a) % mod;
        b >>= 1;
    }
    return r;
}

// 扩展小步大步法，适用于任意模数
ll exBSGS(ll a, ll b, ll p) {
    a %= p; b %= p;
    if (p == 1) return (b == 0) ? 0 : -1;
    if (b == 1) return 0;
    ll g = __gcd(a, p);
    if (g == 1) return bsgs(a, b, p);
    if (b % g != 0) return -1;
    ll na = a / g, nb = b / g, np = p / g;
    ll invNa = invMod(na, np);
    ll newB = powMod(nb, invNa, np);
    ll r = exBSGS(a, newB, np);
    if (r == -1) return -1;
    return r + 1;
}
