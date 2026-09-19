#include <bits/stdc++.h>
using namespace std;

const long long mod = 10567201;
vector<long long> fact;

struct TestCase {
    long long n, m, v, r1, r2;
    bool canFirst, canSecond;
};

long long modPow(long long base, long long exp) {
    long long ans = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) ans = ans * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return ans;
}

bool isEnough(long long exp, long long need) {
    if (need == 0) return true;
    if (exp >= 24) return true;
    return (1LL << exp) >= need;
}

long long combination(long long n, long long k) {
    if (k < 0 || k > n) return 0;
    long long invFactK = modPow(fact[k], mod - 2);
    long long invFactNMinusK = modPow(fact[n - k], mod - 2);
    return fact[n] * invFactK % mod * invFactNMinusK % mod;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<TestCase> tests;
    long long n, m, v;
    int maxR = 0;
    while (cin >> n >> m >> v) {
        if (n == 0 && m == 0 && v == 0) break;
        TestCase test;
        test.n = n;
        test.m = m;
        test.v = v;
        test.r1 = modPow(2, n);
        test.r2 = modPow(2, n - 1);
        test.canFirst = isEnough(n, m) && test.r1 >= m;
        test.canSecond = false;
        if (m % 2 == 0) {
            long long k = m / 2;
            test.canSecond = isEnough(n - 1, k) && test.r2 >= k;
        }
        if (test.canFirst) maxR = max(maxR, static_cast<int>(test.r1));
        if (test.canSecond) maxR = max(maxR, static_cast<int>(test.r2));
        tests.push_back(test);
    }
    fact.resize(maxR + 1);
    fact[0] = 1;
    for (int i = 1; i <= maxR; i++) fact[i] = fact[i - 1] * i % mod;
    for (const TestCase &test : tests) {
        long long first = 0, second = 0, value;
        if (test.canFirst) first = combination(test.r1, test.m);
        if (test.canSecond) {
            long long k = test.m / 2;
            second = combination(test.r2, k);
            if (k % 2 == 1) second = (mod - second) % mod;
        }
        if (test.v == 0) {
            value = (first + (test.r1 - 1 + mod) % mod * second) % mod;
        } else {
            value = (first - second + mod) % mod;
        }
        value = value * modPow(test.r1, mod - 2) % mod;
        cout << value << '\n';
    }
    return 0;
}
