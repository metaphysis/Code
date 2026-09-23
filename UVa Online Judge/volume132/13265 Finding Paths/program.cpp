#include <bits/stdc++.h>
using namespace std;

const long long mod = 1000000007;
vector<long long> fact, invFact, weight;

struct Query {
    int n, m, k;
};

long long modPow(long long base, long long exp) {
    long long result = 1;
    while (exp > 0) {
        if (exp & 1) result = result * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return result;
}

long long combination(int n, int k) {
    if (k < 0 || k > n) return 0;
    return fact[n] * invFact[k] % mod * invFact[n - k] % mod;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<Query> queries;
    int n, m, k, maxD = 0;
    while (cin >> n >> m >> k) {
        queries.push_back({n, m, k});
        maxD = max(maxD, n + m + k);
    }
    if (queries.empty()) return 0;
    fact.resize(maxD + 2);
    invFact.resize(maxD + 2);
    weight.resize(maxD + 1);
    fact[0] = 1;
    for (int i = 1; i <= maxD + 1; ++i) fact[i] = fact[i - 1] * i % mod;
    invFact[maxD + 1] = modPow(fact[maxD + 1], mod - 2);
    for (int i = maxD + 1; i >= 1; --i) invFact[i - 1] = invFact[i] * i % mod;
    weight[maxD] = 1;
    for (int t = maxD; t >= 1; --t) {
        long long term = combination(maxD + 1, t);
        if ((maxD + 1 - t) & 1) term = (mod - term) % mod;
        weight[t - 1] = (2 * weight[t] + term) % mod;
    }
    for (const Query &query : queries) {
        int start = max(query.n, max(query.m, query.k));
        long long total = 0, term, invalid;
        for (int t = start; t <= maxD; ++t) {
            term = weight[t] * combination(t, query.n) % mod;
            term = term * combination(t, query.m) % mod;
            term = term * combination(t, query.k) % mod;
            total = (total + term) % mod;
        }
        invalid = fact[query.n + query.m + query.k] * invFact[query.n] % mod;
        invalid = invalid * invFact[query.m] % mod;
        invalid = invalid * invFact[query.k] % mod;
        cout << (total - invalid + mod) % mod << '\n';
    }
    return 0;
}
