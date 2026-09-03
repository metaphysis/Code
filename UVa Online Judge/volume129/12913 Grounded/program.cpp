#include <bits/stdc++.h>
using namespace std;

const long long Mod = 1000000007;
const int MaxN = 1000000;
long long fact[MaxN + 5], invFact[MaxN + 5];

struct TestCase {
    int n, k;
};

long long powMod(long long base, long long exp, long long mod) {
    long long result = 1;
    while (exp > 0) {
        if (exp & 1) result = result * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<TestCase> cases;
    int n, k, maxN = 0;
    while (cin >> n >> k) {
        cases.push_back({n, k});
        maxN = max(maxN, n);
    }
    fact[0] = 1;
    for (int i = 1; i <= maxN; ++i) fact[i] = fact[i - 1] * i % Mod;
    invFact[maxN] = powMod(fact[maxN], Mod - 2, Mod);
    for (int i = maxN; i >= 1; --i) invFact[i - 1] = invFact[i] * i % Mod;
    for (const TestCase &item : cases) {
        long long choose, exp, ways;
        choose = fact[item.n] * invFact[item.k] % Mod * invFact[item.n - item.k] % Mod;
        exp = powMod(2, item.n, Mod - 1);
        exp = (exp - item.n % (Mod - 1) + Mod - 1) % (Mod - 1);
        ways = powMod(2, exp, Mod);
        cout << choose * ways % Mod << '\n';
    }
    return 0;
}
