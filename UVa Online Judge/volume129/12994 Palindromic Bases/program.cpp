#include <bits/stdc++.h>
using namespace std;

using u64 = unsigned long long;
using u128 = __uint128_t;

u64 mulMod(u64 a, u64 b, u64 mod) {
    return (u128)a * b % mod;
}

u64 powMod(u64 a, u64 n, u64 mod) {
    u64 res = 1;
    while (n > 0) {
        if (n & 1) res = mulMod(res, a, mod);
        a = mulMod(a, a, mod);
        n >>= 1;
    }
    return res;
}

bool isPrime(u64 n) {
    if (n < 2) return false;
    for (u64 p : {2ULL, 3ULL, 5ULL, 7ULL, 11ULL, 13ULL, 17ULL, 19ULL, 23ULL, 29ULL, 31ULL, 37ULL}) {
        if (n % p == 0) return n == p;
    }
    u64 d = n - 1, s = 0;
    while ((d & 1) == 0) {
        d >>= 1;
        s++;
    }
    for (u64 a : {2ULL, 3ULL, 5ULL, 7ULL, 11ULL, 13ULL, 17ULL}) {
        if (a >= n) continue;
        u64 x = powMod(a, d, n);
        if (x == 1 || x == n - 1) continue;
        bool ok = false;
        for (u64 r = 1; r < s; r++) {
            x = mulMod(x, x, n);
            if (x == n - 1) {
                ok = true;
                break;
            }
        }
        if (!ok) return false;
    }
    return true;
}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

u64 getFactor(u64 n) {
    if (n % 2 == 0) return 2;
    while (true) {
        u64 c = rng() % (n - 1) + 1, x = rng() % (n - 2) + 2, y = x, d = 1;
        auto f = [&](u64 v) { return (mulMod(v, v, n) + c) % n; };
        while (d == 1) {
            x = f(x);
            y = f(f(y));
            u64 diff = x > y ? x - y : y - x;
            d = __gcd(diff, n);
        }
        if (d != n) return d;
    }
}

void factor(u64 n, map<u64, int> &fac) {
    if (n == 1) return;
    if (isPrime(n)) {
        fac[n]++;
        return;
    }
    u64 d = getFactor(n);
    factor(d, fac);
    factor(n / d, fac);
}

void makeDiv(int pos, u64 cur, const vector<pair<u64, int>> &items, vector<u64> &divs) {
    if (pos == (int)items.size()) {
        divs.push_back(cur);
        return;
    }
    u64 p = items[pos].first;
    int cnt = items[pos].second;
    for (int i = 0; i <= cnt; i++) {
        makeDiv(pos + 1, cur, items, divs);
        cur *= p;
    }
}

bool isPal(u64 n, u64 base) {
    vector<u64> dig;
    while (n > 0) {
        dig.push_back(n % base);
        n /= base;
    }
    int len = dig.size();
    if (len < 4 || len % 2 != 0) return false;
    for (int i = 0; i < len / 2; i++)
        if (dig[i] != dig[len - i - 1]) return false;
    return true;
}

u64 getCube(u64 n) {
    u64 left = 0, right = 100000;
    while (left < right) {
        u64 mid = (left + right + 1) / 2;
        if ((u128)mid * mid * mid <= n) left = mid;
        else right = mid - 1;
    }
    return left;
}

long long solve(u64 n) {
    map<u64, int> fac;
    factor(n, fac);
    vector<pair<u64, int>> items(fac.begin(), fac.end());
    vector<u64> divs;
    makeDiv(0, 1, items, divs);
    long long ans = 0;
    for (u64 a : divs) {
        u64 d = n / a;
        if ((u128)a * a + a < n && d >= 3 && a < d - 1) ans++;
    }
    for (u64 base = 2; base <= getCube(n); base++)
        if (isPal(n, base)) ans++;
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    for (int cs = 1; cs <= t; cs++) {
        u64 n;
        cin >> n;
        cout << "Case " << cs << ": ";
        if (n == 0) cout << "0\n";
        else cout << solve(n) << '\n';
    }
    return 0;
}
