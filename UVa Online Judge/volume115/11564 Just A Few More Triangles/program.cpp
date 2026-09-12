#include <bits/stdc++.h>
using namespace std;

struct Val {
    long long r, e, f, z, h, w;
};

long long powll(long long a, int b) {
    long long res = 1;
    while (b--) res *= a;
    return res;
}

Val calcLocal(int p, int k) {
    long long r, e, f, z, h, w, p2;
    z = powll(p, k / 2);
    if (p == 2) {
        vector<long long> rv(k + 1), ev(k + 1);
        rv[0] = 1;
        if (k >= 1) rv[1] = 4;
        for (int i = 2; i <= k; i++) rv[i] = (1LL << (2 * i)) + 8 * rv[i - 2];
        ev[0] = 1;
        if (k >= 1) ev[1] = 2;
        if (k >= 2) ev[2] = 8;
        for (int i = 3; i <= k; i++) ev[i] = (1LL << (i + 1)) + 4 * ev[i - 2];
        r = rv[k];
        e = ev[k];
        f = 1LL << k;
        h = 1LL << k;
        w = 1LL << ((k + 1) / 2);
    } else {
        vector<long long> rv(k + 1);
        p2 = 1LL * p * p;
        rv[0] = 1;
        if (k >= 1) rv[1] = p2;
        for (int i = 2; i <= k; i++) rv[i] = (p2 - 1) * powll(p, 2 * i - 2) + p2 * p * rv[i - 2];
        r = rv[k];
        e = powll(p, k - 1) * (p + 1LL * k * (p - 1));
        if (p % 4 == 1) f = e;
        else f = z * z;
        if (p % 8 == 1 || p % 8 == 7) h = e;
        else h = z * z;
        w = z;
    }
    return {r, e, f, z, h, w};
}

long long solve(int n, const vector<int>& spf) {
    long long r = 1, e = 1, f = 1, z = 1, h = 1, w = 1, t, d;
    int x = n;
    while (x > 1) {
        int p = spf[x], k = 0;
        Val cur;
        while (x % p == 0) {
            x /= p;
            k++;
        }
        cur = calcLocal(p, k);
        r *= cur.r;
        e *= cur.e;
        f *= cur.f;
        z *= cur.z;
        h *= cur.h;
        w *= cur.w;
    }
    t = r - 2 * e - f + 3 * z - 1;
    d = h - z - w + 1;
    return (t + d) / 2;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<int> nums;
    int n, mx = 2;
    while (cin >> n) {
        nums.push_back(n);
        mx = max(mx, n);
    }
    vector<int> spf(mx + 1);
    for (int i = 2; i <= mx; i++) {
        if (spf[i]) continue;
        spf[i] = i;
        if (1LL * i * i > mx) continue;
        for (int j = i * i; j <= mx; j += i)
            if (!spf[j]) spf[j] = i;
    }
    for (int x : nums) cout << solve(x, spf) << '\n';
    return 0;
}
