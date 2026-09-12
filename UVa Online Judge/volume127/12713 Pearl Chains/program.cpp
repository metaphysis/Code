#include <bits/stdc++.h>
using namespace std;

const int mod = 1000003;

long long qpow(long long a, long long b) {
    long long r = 1;
    while (b > 0) {
        if (b & 1) r = r * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<int> fact(mod), invFact(mod), inv(mod);
    fact[0] = 1;
    for (int i = 1; i < mod; i++) fact[i] = 1LL * fact[i - 1] * i % mod;
    invFact[mod - 1] = qpow(fact[mod - 1], mod - 2);
    for (int i = mod - 1; i >= 1; i--) invFact[i - 1] = 1LL * invFact[i] * i % mod;
    inv[1] = 1;
    for (int i = 2; i < mod; i++) inv[i] = mod - 1LL * (mod / i) * inv[mod % i] % mod;
    int t;
    cin >> t;
    while (t--) {
        long long a, b, x, y, z;
        cin >> a >> b >> x >> y >> z;
        x %= mod;
        y %= mod;
        z %= mod;
        long long ans = 1;
        while (a > 0 || b > 0) {
            int ai = a % mod, bi = b % mod;
            int left = max(0, ai + bi - mod + 1), right = min(ai, bi);
            long long sum = 0;
            bool ok = true, hasZero = false;
            int fixedK = -1;
            if (x == 0) {
                hasZero = true;
                fixedK = ai;
            }
            if (y == 0) {
                hasZero = true;
                if (fixedK == -1) fixedK = bi;
                else if (fixedK != bi) ok = false;
            }
            if (z == 0) {
                hasZero = true;
                if (fixedK == -1) fixedK = 0;
                else if (fixedK != 0) ok = false;
            }
            if (hasZero) {
                if (ok && fixedK >= left && fixedK <= right) {
                    int n = ai + bi - fixedK;
                    sum = 1LL * fact[n] * invFact[ai - fixedK] % mod;
                    sum = sum * invFact[bi - fixedK] % mod;
                    sum = sum * invFact[fixedK] % mod;
                    sum = sum * qpow(x, ai - fixedK) % mod;
                    sum = sum * qpow(y, bi - fixedK) % mod;
                    sum = sum * qpow(z, fixedK) % mod;
                }
            } else if (left <= right) {
                int k = left, n = ai + bi - k;
                long long term = 1LL * fact[n] * invFact[ai - k] % mod;
                term = term * invFact[bi - k] % mod;
                term = term * invFact[k] % mod;
                term = term * qpow(x, ai - k) % mod;
                term = term * qpow(y, bi - k) % mod;
                term = term * qpow(z, k) % mod;
                for (; k <= right; k++) {
                    sum += term;
                    if (sum >= mod) sum -= mod;
                    if (k == right) break;
                    term = term * (ai - k) % mod;
                    term = term * (bi - k) % mod;
                    term = term * z % mod;
                    term = term * inv[k + 1] % mod;
                    term = term * inv[ai + bi - k] % mod;
                    term = term * inv[x] % mod;
                    term = term * inv[y] % mod;
                }
            }
            ans = ans * sum % mod;
            a /= mod;
            b /= mod;
        }
        cout << ans << '\n';
    }
    return 0;
}
