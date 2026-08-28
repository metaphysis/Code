#include <bits/stdc++.h>
using namespace std;

long long modMul(long long a, long long b, long long mod) {
    return (long long)((__int128)a * b % mod);
}

long long modPow(long long a, long long n, long long mod) {
    long long res = 1 % mod;
    a %= mod;
    while (n > 0) {
        if (n & 1) res = modMul(res, a, mod);
        a = modMul(a, a, mod);
        n >>= 1;
    }
    return res;
}

struct Mat {
    long long a00, a01, a10, a11;
};

Mat matMul(Mat a, Mat b, long long mod) {
    Mat c;
    c.a00 = (modMul(a.a00, b.a00, mod) + modMul(a.a01, b.a10, mod)) % mod;
    c.a01 = (modMul(a.a00, b.a01, mod) + modMul(a.a01, b.a11, mod)) % mod;
    c.a10 = (modMul(a.a10, b.a00, mod) + modMul(a.a11, b.a10, mod)) % mod;
    c.a11 = (modMul(a.a10, b.a01, mod) + modMul(a.a11, b.a11, mod)) % mod;
    return c;
}

long long getSeq(long long n, long long k, long long mod) {
    if (n == 0) return 2 % mod;
    if (n == 1) return (mod - 1) % mod;
    Mat res = {1 % mod, 0, 0, 1 % mod};
    Mat bas = {(mod - 1) % mod, (mod - (k - 2) % mod) % mod, 1 % mod, 0};
    long long e = n - 1;
    while (e > 0) {
        if (e & 1) res = matMul(res, bas, mod);
        bas = matMul(bas, bas, mod);
        e >>= 1;
    }
    long long s1 = (mod - 1) % mod, s0 = 2 % mod;
    return (modMul(res.a00, s1, mod) + modMul(res.a01, s0, mod)) % mod;
}

long long getCnt(long long n, long long k, long long mod) {
    if (n <= 2 || k < 3) return 0;
    long long p = modPow((k - 2) % mod, n, mod);
    long long seq = getSeq(n, k, mod);
    long long q = k * (k - 3) / 2 % mod;
    long long val = (p + 1) % mod;
    val = (val + modMul((k - 1) % mod, seq, mod)) % mod;
    if (n % 2 == 0) val = (val + 2 * q) % mod;
    return val;
}

long long getPhi(long long x, vector<long long> ps) {
    long long res = x;
    for (long long p : ps)
        if (x % p == 0) res = res / p * (p - 1);
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    for (int cs = 1; cs <= t; cs++) {
        long long n, k, m;
        cin >> n >> k >> m;
        long long mod = n * m;
        vector<long long> ds, ps;
        for (long long i = 1; i * i <= n; i++)
            if (n % i == 0) {
                ds.push_back(i);
                if (i * i != n) ds.push_back(n / i);
            }
        long long tmp = n;
        for (long long p = 2; p * p <= tmp; p++)
            if (tmp % p == 0) {
                ps.push_back(p);
                while (tmp % p == 0) tmp /= p;
            }
        if (tmp > 1) ps.push_back(tmp);
        long long sum = 0;
        for (long long g : ds) {
            long long phi = getPhi(n / g, ps);
            long long cnt = getCnt(g, k, mod);
            sum = (sum + modMul(phi % mod, cnt, mod)) % mod;
        }
        cout << "Case " << cs << ": " << (sum / n) % m << '\n';
    }
    return 0;
}
