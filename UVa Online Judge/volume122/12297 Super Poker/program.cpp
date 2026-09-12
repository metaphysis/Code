#include <bits/stdc++.h>
using namespace std;

const long long mod = 1000000009LL;
vector<vector<long long>> denPoly(11), numPoly(11);

long long modPow(long long a, long long b) {
    long long res = 1;
    while (b > 0) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

vector<long long> mulPoly(const vector<long long>& a, const vector<long long>& b) {
    vector<long long> res(a.size() + b.size() - 1, 0);
    for (int i = 0; i < (int)a.size(); i++)
        for (int j = 0; j < (int)b.size(); j++)
            res[i + j] = (res[i + j] + a[i] * b[j]) % mod;
    return res;
}

vector<long long> mulFactor(const vector<long long>& a, int pos) {
    vector<long long> res(a.size() + pos, 0);
    for (int i = 0; i < (int)a.size(); i++) {
        res[i] = (res[i] + a[i]) % mod;
        res[i + pos] = (res[i + pos] - a[i] + mod) % mod;
    }
    return res;
}

vector<long long> buildDen(int m) {
    vector<long long> res(1, 1);
    for (int i = 1; i <= m; i++) {
        int cnt = m / i;
        while (cnt--) res = mulFactor(res, i);
    }
    return res;
}

vector<long long> buildMultiplier(int m, int i) {
    vector<long long> res(1, 1);
    for (int j = 1; j <= m; j++) {
        int cnt = m / j - (m - i) / j - (i == j);
        while (cnt--) res = mulFactor(res, j);
    }
    return res;
}

void buildAll() {
    denPoly[0] = vector<long long>(1, 1);
    numPoly[0] = vector<long long>(1, 1);
    for (int m = 1; m <= 10; m++) {
        denPoly[m] = buildDen(m);
        vector<long long> cur(denPoly[m].size(), 0);
        long long invM = modPow(m, mod - 2);
        for (int i = 1; i <= m; i++) {
            vector<long long> mul = buildMultiplier(m, i);
            vector<long long> term = mulPoly(numPoly[m - i], mul);
            vector<long long> shifted(term.size() + i, 0);
            for (int j = 0; j < (int)term.size(); j++)
                shifted[j + i] = term[j] * 4 % mod;
            long long sign = (i & 1) ? 1 : mod - 1;
            for (int j = 0; j < (int)shifted.size(); j++)
                cur[j] = (cur[j] + sign * shifted[j]) % mod;
        }
        for (long long& x : cur) x = (x + mod) % mod * invM % mod;
        numPoly[m] = cur;
    }
}

vector<long long> combine(const vector<long long>& a, const vector<long long>& b, const vector<long long>& rec) {
    int len = rec.size();
    vector<long long> res(2 * len - 1, 0);
    for (int i = 0; i < len; i++)
        for (int j = 0; j < len; j++)
            res[i + j] = (res[i + j] + a[i] * b[j]) % mod;
    for (int i = 2 * len - 2; i >= len; i--) {
        long long val = res[i];
        if (val == 0) continue;
        for (int j = 1; j <= len; j++)
            res[i - j] = (res[i - j] + val * rec[j - 1]) % mod;
    }
    res.resize(len);
    return res;
}

long long linearNth(long long n, const vector<long long>& init, const vector<long long>& rec) {
    int len = rec.size();
    if (n < len) return init[n];
    vector<long long> pol(len, 0), e(len, 0);
    pol[0] = 1;
    if (len == 1) e[0] = rec[0];
    else e[1] = 1;
    while (n > 0) {
        if (n & 1) pol = combine(pol, e, rec);
        e = combine(e, e, rec);
        n >>= 1;
    }
    long long res = 0;
    for (int i = 0; i < len; i++)
        res = (res + pol[i] * init[i]) % mod;
    return res;
}

long long getBaseCoeff(int m, long long n) {
    if (n < 0) return 0;
    const vector<long long>& den = denPoly[m];
    int len = den.size() - 1;
    vector<long long> rec(len), init(len, 0);
    for (int i = 0; i < len; i++)
        rec[i] = (mod - den[i + 1]) % mod;
    init[0] = 1;
    for (int i = 1; i < len; i++) {
        for (int j = 1; j <= i; j++)
            init[i] = (init[i] + den[j] * init[i - j]) % mod;
        init[i] = (mod - init[i]) % mod;
    }
    return linearNth(n, init, rec);
}

long long getWays(int m, long long n) {
    long long res = 0;
    for (int i = 0; i < (int)numPoly[m].size(); i++) {
        if (numPoly[m][i] == 0) continue;
        long long val = getBaseCoeff(m, n - i);
        res = (res + numPoly[m][i] * val) % mod;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    buildAll();
    long long n;
    int k;
    while (cin >> n >> k) {
        if (n == 0 && k == 0) break;
        long long ans = 0;
        for (int m = 1; m <= k; m++)
            ans = (ans + getWays(m, n)) % mod;
        cout << ans << '\n';
    }
    return 0;
}
