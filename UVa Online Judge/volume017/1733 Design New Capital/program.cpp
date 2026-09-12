#include <bits/stdc++.h>
using namespace std;

const int mod = 7340033, root = 3;
vector<int> fac, ifac;

int modPow(int a, int e) {
    int r = 1;
    while (e > 0) {
        if (e & 1) r = (long long)r * a % mod;
        a = (long long)a * a % mod;
        e >>= 1;
    }
    return r;
}

void initComb(int n) {
    fac.assign(n + 1, 1);
    ifac.assign(n + 1, 1);
    for (int i = 1; i <= n; i++) fac[i] = (long long)fac[i - 1] * i % mod;
    ifac[n] = modPow(fac[n], mod - 2);
    for (int i = n; i >= 1; i--) ifac[i - 1] = (long long)ifac[i] * i % mod;
}

int getComb(int n, int k) {
    if (k < 0 || k > n) return 0;
    return (long long)fac[n] * ifac[k] % mod * ifac[n - k] % mod;
}

void ntt(vector<int>& a, bool inv) {
    int n = a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        int wLen = modPow(root, (mod - 1) / len);
        if (inv) wLen = modPow(wLen, mod - 2);
        for (int i = 0; i < n; i += len) {
            int w = 1, half = len >> 1;
            for (int j = 0; j < half; j++) {
                int u = a[i + j], v = (long long)a[i + j + half] * w % mod;
                a[i + j] = u + v;
                if (a[i + j] >= mod) a[i + j] -= mod;
                a[i + j + half] = u - v;
                if (a[i + j + half] < 0) a[i + j + half] += mod;
                w = (long long)w * wLen % mod;
            }
        }
    }
    if (inv) {
        int invN = modPow(n, mod - 2);
        for (int& x : a) x = (long long)x * invN % mod;
    }
}

vector<int> multiply(vector<int> a, vector<int> b) {
    int need = a.size() + b.size() - 1, n = 1;
    while (n < need) n <<= 1;
    a.resize(n);
    b.resize(n);
    ntt(a, false);
    ntt(b, false);
    for (int i = 0; i < n; i++) a[i] = (long long)a[i] * b[i] % mod;
    ntt(a, true);
    a.resize(need);
    return a;
}

int solve() {
    int n;
    cin >> n;
    int a = 0, b = 0, c = 0, d = 0;
    for (int i = 0, x, y; i < n; i++) {
        cin >> x >> y;
        if (x > 0 && y > 0) a++;
        else if (x < 0 && y > 0) b++;
        else if (x < 0 && y < 0) c++;
        else d++;
    }
    vector<int> p(min(a, c) + 1), q(min(b, d) + 1);
    for (int i = 0; i < (int)p.size(); i++) p[i] = (long long)getComb(a, i) * getComb(c, i) % mod;
    for (int i = 0; i < (int)q.size(); i++) q[i] = (long long)getComb(b, i) * getComb(d, i) % mod;
    vector<int> res = multiply(p, q);
    for (int i = 1; i <= n; i++) {
        if (i > 1) cout << ' ';
        if (i & 1) cout << 0;
        else cout << (i / 2 < (int)res.size() ? res[i / 2] : 0);
    }
    cout << '\n';
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    initComb(100000);
    int t;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cout << "Case " << i << ":\n";
        solve();
    }
    return 0;
}
