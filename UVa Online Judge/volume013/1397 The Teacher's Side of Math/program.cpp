#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>

using namespace std;
using boost::multiprecision::cpp_int;

struct Poly {
    vector<cpp_int> c;
};

void trim(Poly &p) {
    while (!p.c.empty() && p.c.back() == 0) p.c.pop_back();
}

Poly makeConst(long long x) {
    Poly p;
    if (x != 0) p.c.push_back(x);
    return p;
}

void addTo(Poly &a, const Poly &b, int sg) {
    if (a.c.size() < b.c.size()) a.c.resize(b.c.size());
    for (int i = 0; i < (int)b.c.size(); i++) a.c[i] += sg * b.c[i];
    trim(a);
}

Poly mul(const Poly &a, const Poly &b) {
    Poly r;
    if (a.c.empty() || b.c.empty()) return r;
    r.c.assign(a.c.size() + b.c.size() - 1, 0);
    for (int i = 0; i < (int)a.c.size(); i++)
        for (int j = 0; j < (int)b.c.size(); j++) r.c[i + j] += a.c[i] * b.c[j];
    trim(r);
    return r;
}

long long comb(int n, int k) {
    long long r = 1;
    for (int i = 1; i <= k; i++) r = r * (n - i + 1) / i;
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int a, m, b, n;
    while (cin >> a >> m >> b >> n) {
        if (a == 0 && m == 0 && b == 0 && n == 0) break;
        int sz = m + n, all = 1 << sz;
        vector<Poly> p(m + 1), q(n + 1);
        p[0] = makeConst(-a);
        p[m] = makeConst(1);
        for (int k = 0; k <= n; k++) {
            q[k].c.assign(n - k + 1, 0);
            q[k].c[n - k] = (k & 1) ? -comb(n, k) : comb(n, k);
        }
        q[0].c[0] -= b;
        vector<vector<Poly>> mat(sz, vector<Poly>(sz));
        for (int i = 0; i < n; i++)
            for (int j = 0; j <= m; j++) mat[i][i + j] = p[m - j];
        for (int i = 0; i < m; i++)
            for (int j = 0; j <= n; j++) mat[n + i][i + j] = q[n - j];
        vector<Poly> dp(all);
        dp[0] = makeConst(1);
        for (int mask = 0; mask < all; mask++) {
            int row = __builtin_popcount((unsigned)mask);
            if (row == sz || dp[mask].c.empty()) continue;
            for (int col = 0; col < sz; col++) {
                if (mask & (1 << col)) continue;
                if (mat[row][col].c.empty()) continue;
                Poly cur = mul(dp[mask], mat[row][col]);
                int inv = __builtin_popcount((unsigned)(mask >> (col + 1)));
                addTo(dp[mask | (1 << col)], cur, (inv & 1) ? -1 : 1);
            }
        }
        Poly ans = dp[all - 1];
        for (int i = m * n; i >= 0; i--) {
            if (i != m * n) cout << ' ';
            if (i < (int)ans.c.size()) cout << ans.c[i];
            else cout << 0;
        }
        cout << '\n';
    }
    return 0;
}
