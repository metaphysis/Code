#include <bits/stdc++.h>
using namespace std;

const long long mod = 10567201;

struct TestCase {
    int n, m, v;
};

long long modPow(long long a, long long b) {
    long long ans = 1;
    while (b > 0) {
        if (b & 1) ans = ans * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return ans;
}

long long comb(long long n, int k, int exp, const vector<long long>& invFact) {
    long long ans = 1;
    int i;
    if (exp <= 10 && (1LL << exp) < k) return 0;
    for (i = 0; i < k; ++i) ans = ans * ((n - i + mod) % mod) % mod;
    return ans * invFact[k] % mod;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<TestCase> tests;
    int n, m, v, maxM = 0;
    while (cin >> n >> m >> v && (n != 0 || m != 0 || v != 0)) {
        tests.push_back({n, m, v});
        maxM = max(maxM, m);
    }
    vector<long long> fact(maxM + 1), invFact(maxM + 1);
    int i;
    fact[0] = 1;
    for (i = 1; i <= maxM; ++i) fact[i] = fact[i - 1] * i % mod;
    invFact[maxM] = modPow(fact[maxM], mod - 2);
    for (i = maxM; i >= 1; --i) invFact[i - 1] = invFact[i] * i % mod;
    for (const TestCase& cur : tests) {
        long long p2 = modPow(2, cur.n);
        long long pHalf = modPow(2, cur.n - 1);
        long long first = comb(p2, cur.m, cur.n, invFact);
        long long second = 0;
        if (cur.m % 2 == 0) {
            second = comb(pHalf, cur.m / 2, cur.n - 1, invFact);
            if ((cur.m / 2) % 2 == 1) second = (mod - second) % mod;
        }
        long long coef = cur.v == 0 ? (p2 - 1 + mod) % mod : mod - 1;
        long long ans = (first + coef * second) % mod;
        ans = ans * modPow(p2, mod - 2) % mod;
        cout << ans << '\n';
    }
    return 0;
}
