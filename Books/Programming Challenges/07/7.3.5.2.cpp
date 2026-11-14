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

// 乘法取模（防溢出）
ll mulMod(ll a, ll b, ll mod) {
    return (ll)((i128)a * b % mod);
}

// 逆元（要求 gcd(a, mod) = 1）
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

// 扩展 BSGS，任意模数
ll exBSGS(ll a, ll b, ll p) {
    a %= p; b %= p;
    if (p == 1) return (b == 0) ? 0 : -1;
    if (b == 1) return 0;

    ll g = __gcd(a, p);
    if (g == 1) return bsgs(a, b, p);
    if (b % g != 0) return -1;

    ll na = a / g, nb = b / g, np = p / g;
    ll invNa = invMod(na, np);
    ll newB = mulMod(nb % np, invNa, np);   // (b/g) * (a/g)^{-1} mod (p/g)

    ll r = exBSGS(a, newB, np);
    if (r == -1) return -1;
    return r + 1;
}

// ==================================================
//                       测试
// ==================================================
int main() {
    cout << "========= Test 1: exgcd / invMod =========" << endl;
    bool ok1 = true;
    for (ll a = 1; a <= 30; a++) {
        for (ll m = 1; m <= 30; m++) {
            if (__gcd(a, m) != 1) continue;
            ll inv = invMod(a, m);
            if (mulMod(a, inv, m) != 1 % m) {
                cout << "  FAIL invMod: a=" << a << " m=" << m << endl;
                ok1 = false;
            }
        }
    }
    for (ll a = 1; a <= 30; a++) {
        for (ll b = 1; b <= 30; b++) {
            ll x, y;
            ll g = exgcd(a, b, x, y);
            if (a * x + b * y != g || g != __gcd(a, b)) {
                cout << "  FAIL exgcd: a=" << a << " b=" << b << endl;
                ok1 = false;
            }
        }
    }
    cout << (ok1 ? "  ✅ Passed" : "  ❌ Failed") << endl;

    cout << "========= Test 2: powMod =========" << endl;
    bool ok2 = true;
    for (ll a = 0; a <= 10; a++) {
        for (ll b = 0; b <= 15; b++) {
            for (ll m = 1; m <= 20; m++) {
                ll expected = 1 % m;
                for (ll i = 0; i < b; i++) expected = mulMod(expected, a, m);
                ll got = powMod(a, b, m);
                if (got != expected) {
                    cout << "  FAIL powMod(" << a << "," << b << "," << m
                         << ") = " << got << " expected " << expected << endl;
                    ok2 = false;
                }
            }
        }
    }
    cout << (ok2 ? "  ✅ Passed" : "  ❌ Failed") << endl;

    cout << "========= Test 3: bsgs (gcd(a,p)=1) =========" << endl;
    bool ok3 = true;
    for (ll a = 2; a <= 6; a++) {
        for (ll p = 2; p <= 40; p++) {
            if (__gcd(a, p) != 1) continue;
            for (ll b = 0; b < p; b++) {
                ll expected = -1, cur = 1 % p;
                for (ll x = 0; x <= p; x++) {
                    if (cur == b) { expected = x; break; }
                    cur = mulMod(cur, a, p);
                }
                ll got = bsgs(a, b, p);
                if (got != expected) {
                    cout << "  FAIL bsgs(" << a << "," << b << "," << p
                         << ") = " << got << " expected " << expected << endl;
                    ok3 = false;
                }
            }
        }
    }
    cout << (ok3 ? "  ✅ Passed" : "  ❌ Failed") << endl;

    cout << "========= Test 4: exBSGS (任意模数) =========" << endl;
    bool ok4 = true;
    for (ll a = 0; a <= 10; a++) {
        for (ll p = 1; p <= 40; p++) {
            for (ll b = 0; b < p; b++) {
                ll expected = -1, cur = 1 % p;
                for (ll x = 0; x <= 2 * p + 10; x++) {
                    if (cur == b) { expected = x; break; }
                    cur = mulMod(cur, a, p);
                }
                ll got = exBSGS(a, b, p);
                if (got != expected) {
                    cout << "  FAIL exBSGS(" << a << "," << b << "," << p
                         << ") = " << got << " expected " << expected << endl;
                    ok4 = false;
                }
            }
        }
    }
    cout << (ok4 ? "  ✅ Passed" : "  ❌ Failed") << endl;

    cout << "========= Test 5: 随机大数交叉验证 =========" << endl;
    bool ok5 = true;
    mt19937_64 rng(12345);
    for (int t = 0; t < 500; t++) {
        ll p = rng() % 1000000 + 2;
        ll a = rng() % 100 + 2;
        ll x = rng() % 200;
        ll b = powMod(a, x, p);
        ll got = exBSGS(a, b, p);
        if (got == -1 || got > x || powMod(a, got, p) != b) {
            cout << "  FAIL exBSGS(" << a << "," << b << "," << p
                 << ") = " << got << "  (a^x=b with x=" << x << ")" << endl;
            ok5 = false;
        }
    }
    cout << (ok5 ? "  ✅ Passed" : "  ❌ Failed") << endl;

    // ============ 手工验证示例 ============
    cout << "========= 已知样例 =========" << endl;
    cout << "3^x ≡ 2 (mod 5) : x = " << exBSGS(3, 2, 5) << "  (expect 3)" << endl;
    cout << "2^x ≡ 4 (mod 8) : x = " << exBSGS(2, 4, 8) << "  (expect 2)" << endl;
    cout << "2^x ≡ 0 (mod 8) : x = " << exBSGS(2, 0, 8) << "  (expect 3)" << endl;
    cout << "2^x ≡ 3 (mod 8) : x = " << exBSGS(2, 3, 8) << "  (expect -1, 无解)" << endl;
    cout << "2^x ≡ 6 (mod 100) : x = " << exBSGS(2, 6, 100) << endl;
    // 2^6=64, 2^7=128≡28, 2^8=56, 2^9=112≡12, 2^10=24, ... 周期内是否出现 6？用暴力验一下：
    {
        ll cur = 1, ans = -1;
        for (ll x = 0; x <= 200; x++) {
            if (cur == 6) { ans = x; break; }
            cur = cur * 2 % 100;
        }
        cout << "  (暴力结果: " << ans << ")" << endl;
    }

    // ============ 交互模式 ============
    cout << "========= 交互模式 =========" << endl;
    cout << "输入 a b p，求最小的 x 使 a^x ≡ b (mod p)。输入 0 0 0 退出。" << endl;
    ll a, b, p;
    while (cin >> a >> b >> p) {
        if (a == 0 && b == 0 && p == 0) break;
        ll ans = exBSGS(a, b, p);
        if (ans == -1) cout << "  无解" << endl;
        else cout << "  最小 x = " << ans << endl;
    }
    return 0;
}
