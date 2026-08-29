#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll modPow(ll a, ll e, ll m) { ll r = 1; while (e) { if (e & 1) r = r * a % m; a = a * a % m; e >>= 1; } return r; }

vector<int> primeFactors(int n) {
    vector<int> f;
    for (int i = 2; i * i <= n; ++i) if (n % i == 0) { f.push_back(i); while (n % i == 0) n /= i; }
    if (n > 1) f.push_back(n);
    return f;
}

int primitiveRoot(int p) {
    vector<int> fac = primeFactors(p - 1);
    for (int g = 2; ; ++g) {
        bool ok = true;
        for (int pf : fac) if (modPow(g, (p - 1) / pf, p) == 1) { ok = false; break; }
        if (ok) return g;
    }
}

// 大步小步求离散对数 g^x ≡ b (mod p), 返回最小非负解
int bsgs(int g, int b, int p) {
    int m = (int)sqrt(p - 1) + 1;
    map<int, int> mp;
    ll cur = 1;
    for (int j = 0; j < m; ++j) { if (!mp.count((int)cur)) mp[(int)cur] = j; cur = cur * g % p; }
    ll inv = modPow(g, (ll)(p - 1) - (m % (p - 1)), p); // g^{-m} mod p
    cur = b;
    for (int i = 0; i <= m; ++i) {
        auto it = mp.find((int)cur);
        if (it != mp.end()) return i * m + it->second;
        cur = cur * inv % p;
    }
    return -1;
}

// 扩展欧几里得求逆元 (a 与 m 互质)
ll invMod(ll a, ll m) {
    ll m0 = m, y = 0, x = 1;
    if (m == 1) return 0;
    while (a > 1) {
        ll q = a / m;
        ll t = m;
        m = a % m;
        a = t;
        t = y;
        y = x - q * y;
        x = t;
    }
    if (x < 0) x += m0;
    return x;
}

string intToStr(int x) { char buf[5]; sprintf(buf, "%02d", x); return string(buf); }

string toTime(ll x) {
    int y = 2000;
    while (true) {
        bool leap = (y % 400 == 0 || (y % 4 == 0 && y % 100 != 0));
        bool leapSec = (y % 10 == 5 || y % 10 == 8);
        ll normal = (leap ? 366LL : 365LL) * 86400LL;
        ll total = normal + (leapSec ? 1LL : 0LL);
        if (x < total) {
            if (leapSec && x == normal) {
                char buf[64]; sprintf(buf, "%d.12.31 23:59:60", y);
                return string(buf);
            }
            int days[12] = {31, leap ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
            for (int m = 0; m < 12; ++m) {
                ll sec = (ll)days[m] * 86400LL;
                if (x < sec) {
                    int d = (int)(x / 86400) + 1;
                    int rem = (int)(x % 86400);
                    int h = rem / 3600, rem2 = rem % 3600;
                    int min = rem2 / 60, s = rem2 % 60;
                    char buf[64]; sprintf(buf, "%d.%s.%s %s:%s:%s", y, intToStr(m+1).c_str(), intToStr(d).c_str(), intToStr(h).c_str(), intToStr(min).c_str(), intToStr(s).c_str());
                    return string(buf);
                }
                x -= sec;
            }
            return "";
        }
        x -= total;
        ++y;
    }
}

int main() {
    int T; scanf("%d", &T);
    for (int tc = 1; tc <= T; ++tc) {
        int p, q, a; scanf("%d%d%d", &p, &q, &a);
        printf("Case #%d:\n", tc);
        if (a == 0) { printf("%s\n", toTime(0).c_str()); continue; }
        int g = __gcd(q, p - 1);
        if (modPow(a, (p - 1) / g, p) != 1) { printf("Transmission error\n"); continue; }
        int rt = primitiveRoot(p);
        int b = bsgs(rt, a, p);
        if (b == -1) { printf("Transmission error\n"); continue; }
        int qp = q / g, mp = (p - 1) / g, bp = b / g;
        ll invQ = invMod(qp, mp);
        int y0 = (int)((ll)bp * invQ % mp);
        vector<int> sols;
        for (int k = 0; k < g; ++k) {
            int y = y0 + k * mp;
            int x = (int)modPow(rt, y, p);
            sols.push_back(x);
        }
        sort(sols.begin(), sols.end());
        for (int x : sols) printf("%s\n", toTime(x).c_str());
    }
    return 0;
}
