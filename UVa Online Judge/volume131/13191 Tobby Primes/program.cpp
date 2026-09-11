// Tobby Primes
// UVa ID: 13191
// Verdict: Accepted
// Submission Date: 2026-08-01
// UVa Run Time: 2.370s

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll mulMod(ll a, ll b, ll mod) {
    return (ll)((__int128)a * b % mod);
}

ll powMod(ll a, ll d, ll mod) {
    ll res = 1;
    while (d) {
        if (d & 1) res = mulMod(res, a, mod);
        a = mulMod(a, a, mod);
        d >>= 1;
    }
    return res;
}

bool isPrime(ll n) {
    if (n < 2) return false;
    static ll smallPrimes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    for (ll p : smallPrimes) {
        if (n % p == 0) return n == p;
    }
    ll d = n - 1, s = 0;
    while ((d & 1) == 0) {
        d >>= 1;
        ++s;
    }
    for (ll a : smallPrimes) {
        if (a >= n) continue;
        ll x = powMod(a, d, n);
        if (x == 1 || x == n - 1) continue;
        bool composite = true;
        for (ll r = 1; r < s; ++r) {
            x = mulMod(x, x, n);
            if (x == n - 1) {
                composite = false;
                break;
            }
        }
        if (composite) return false;
    }
    return true;
}

ll pollardRho(ll n) {
    if (n % 2 == 0) return 2;
    if (n % 3 == 0) return 3;
    static mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    while (true) {
        ll c = uniform_int_distribution<ll>(1, n - 1)(rng);
        ll x = uniform_int_distribution<ll>(0, n - 1)(rng);
        ll y = x, d = 1;
        auto f = [&](ll v) { return (mulMod(v, v, n) + c) % n; };
        for (ll iter = 0; d == 1 && iter < 100000; ++iter) {
            x = f(x);
            y = f(f(y));
            ll diff = x > y ? x - y : y - x;
            d = std::__gcd(diff, n);
        }
        if (d > 1 && d < n) return d;
    }
}

const int PRE_SIEVE_CNT = 100;
ll prePrimes[PRE_SIEVE_CNT];

void initPrePrimes() {
    vector<bool> isComp(600, false);
    int cnt = 0;
    for (int i = 2; cnt < PRE_SIEVE_CNT; ++i) {
        if (!isComp[i]) {
            prePrimes[cnt++] = i;
            for (int j = i * i; j < 600; j += i) isComp[j] = true;
        }
    }
}

void factor(ll n, vector<ll>& res) {
    if (n == 1) return;
    for (int i = 0; i < PRE_SIEVE_CNT; ++i) {
        ll p = prePrimes[i];
        if (n % p == 0) {
            while (n % p == 0) {
                res.push_back(p);
                n /= p;
            }
            if (n == 1) return;
        }
    }
    if (isPrime(n)) {
        res.push_back(n);
        return;
    }
    ll d = pollardRho(n);
    factor(d, res);
    factor(n / d, res);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    initPrePrimes();
    int t;
    cin >> t;
    while (t--) {
        ll n;
        cin >> n;
        vector<ll> factors;
        factor(n, factors);
        sort(factors.begin(), factors.end());
        for (size_t i = 0; i < factors.size(); ++i) {
            if (i) cout << ' ';
            cout << factors[i];
        }
        cout << '\n';
    }
    return 0;
}
