#include <bits/stdc++.h>
using namespace std;

const long long mod = 1000000007LL;

long long modPow(long long a, long long b) {
    long long res = 1;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

long long getSum(long long n, int k, const vector<long long>& ys, const vector<long long>& invFac) {
    int d = k + 1;
    long long x = n % mod;
    vector<long long> pre(d + 2), suf(d + 2);
    if (x <= d) return ys[(int)x];
    pre[0] = 1;
    for (int i = 0; i <= d; ++i) pre[i + 1] = pre[i] * (x - i + mod) % mod;
    suf[d + 1] = 1;
    for (int i = d; i >= 0; --i) suf[i] = suf[i + 1] * (x - i + mod) % mod;
    long long res = 0;
    for (int i = 0; i <= d; ++i) {
        long long cur = ys[i] * pre[i] % mod * suf[i + 1] % mod;
        cur = cur * invFac[i] % mod * invFac[d - i] % mod;
        if ((d - i) & 1) cur = (mod - cur) % mod;
        res = (res + cur) % mod;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, maxK = 2500;
    cin >> t;
    vector<long long> ns(t), ans(t), fac(maxK + 2), invFac(maxK + 2);
    vector<int> ks(t);
    vector<vector<pair<long long, int>>> qs(maxK + 1);
    fac[0] = 1;
    for (int i = 1; i <= maxK + 1; ++i) fac[i] = fac[i - 1] * i % mod;
    invFac[maxK + 1] = modPow(fac[maxK + 1], mod - 2);
    for (int i = maxK; i >= 0; --i) invFac[i] = invFac[i + 1] * (i + 1) % mod;
    for (int i = 0; i < t; ++i) {
        cin >> ns[i] >> ks[i];
        qs[ks[i]].push_back({ns[i], i});
    }
    for (int k = 2; k <= maxK; ++k) {
        if (qs[k].empty()) continue;
        int d = k + 1;
        vector<long long> ys(d + 1);
        for (int i = 1; i <= d; ++i) ys[i] = (ys[i - 1] + modPow(i, k)) % mod;
        for (auto item : qs[k]) {
            long long n = item.first, x = n % mod;
            long long sum = n % mod * ((n + 1) % mod) % mod * ((mod + 1) / 2) % mod;
            long long total = modPow(sum, k);
            long long cube = getSum(n, k, ys, invFac);
            ans[item.second] = (total - cube + mod) % mod;
        }
    }
    for (int i = 0; i < t; ++i) cout << ans[i] << '\n';
    return 0;
}
