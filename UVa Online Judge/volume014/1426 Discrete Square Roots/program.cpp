// Discrete Square Roots
// UVa ID: 1426
// Verdict: Accepted
// Submission Date: 2026-07-16
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) { x = 1; y = 0; return a; }
    ll x1, y1;
    ll g = exgcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

ll modInverse(ll a, ll m) {
    if (m == 1) return 0;
    ll x, y;
    exgcd(a, m, x, y);
    return (x % m + m) % m;
}

vector<pair<ll, int>> factorize(ll n) {
    vector<pair<ll, int>> fac;
    for (ll p = 2; p * p <= n; ++p) {
        if (n % p == 0) {
            int e = 0;
            while (n % p == 0) { n /= p; ++e; }
            fac.push_back({p, e});
        }
    }
    if (n > 1) fac.push_back({n, 1});
    return fac;
}

void genDivs(int idx, ll cur, const vector<pair<ll, int>> &fac, vector<ll> &divs) {
    if (idx == (int)fac.size()) { divs.push_back(cur); return; }
    ll p = fac[idx].first;
    int e = fac[idx].second;
    ll mul = 1;
    for (int i = 0; i <= e; ++i) {
        genDivs(idx + 1, cur * mul, fac, divs);
        mul *= p;
    }
}

ll gcd(ll a, ll b) {
    while (b) { ll t = a % b; a = b; b = t; }
    return a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll x, N, r;
    int caseNo = 1;
    while (cin >> x >> N >> r) {
        if (x == 0 && N == 0 && r == 0) break;

        vector<pair<ll, int>> fac = factorize(N);
        vector<ll> divs;
        genDivs(0, 1, fac, divs);

        vector<ll> ans;
        for (ll d : divs) {
            ll m = N / d;
            ll g = gcd(d, m);
            if ((2 * r) % g != 0) continue;

            ll c = ((-2 * r) % m + m) % m;
            ll a = d / g;
            ll b = m / g;
            ll c2 = c / g;

            ll inv = modInverse(a, b);
            ll t0 = (c2 * inv) % b;
            ll L = N / g;
            ll s0 = (r + d * t0) % L;

            for (ll k = 0; k < g; ++k) {
                ll s = s0 + k * L;
                ans.push_back(s);
            }
        }

        sort(ans.begin(), ans.end());
        ans.erase(unique(ans.begin(), ans.end()), ans.end());

        cout << "Case " << caseNo++ << ":";
        for (ll v : ans) cout << " " << v;
        cout << "\n";
    }
    return 0;
}
