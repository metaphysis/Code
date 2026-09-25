#include <bits/stdc++.h>
using namespace std;

const int primeList[3] = {23, 2293, 189613};
vector<long long> fact[3], invFact[3];
long long baseInv[3];

long long powerMod(long long base, long long exp, long long mod) {
    long long res = 1;
    while (exp > 0) {
        if (exp & 1) res = res * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return res;
}

void initComb() {
    long long base = 1;
    for (int i = 0; i < 3; i++) {
        int p = primeList[i];
        fact[i].resize(p);
        invFact[i].resize(p);
        fact[i][0] = 1;
        for (int j = 1; j < p; j++) fact[i][j] = fact[i][j - 1] * j % p;
        invFact[i][p - 1] = powerMod(fact[i][p - 1], p - 2, p);
        for (int j = p - 1; j > 0; j--) invFact[i][j - 1] = invFact[i][j] * j % p;
        baseInv[i] = powerMod(base % p, p - 2, p);
        base *= p;
    }
}

long long lucas(int n, int k, int id) {
    int p = primeList[id], a, b;
    long long res = 1;
    while (n > 0 || k > 0) {
        a = n % p;
        b = k % p;
        if (b > a) return 0;
        res = res * fact[id][a] % p;
        res = res * invFact[id][b] % p;
        res = res * invFact[id][a - b] % p;
        n /= p;
        k /= p;
    }
    return res;
}

long long solve(int n, int m) {
    long long ans = 0, base = 1;
    for (int i = 0; i < 3; i++) {
        int p = primeList[i];
        long long val = lucas(n + m, n, i), step;
        val = val * val % p;
        step = (val - ans % p + p) % p;
        step = step * baseInv[i] % p;
        ans += base * step;
        base *= p;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    initComb();
    while (cin >> n >> m) cout << solve(n, m) << '\n';
    return 0;
}
