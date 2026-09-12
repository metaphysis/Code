#include <bits/stdc++.h>
using namespace std;

const long long mod = 1000000007;
long long fac[10005], invFac[10005];

long long modPow(long long a, long long b) {
    long long res = 1;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

long long comb(int n, int k) {
    if (k < 0 || k > n) return 0;
    return fac[n] * invFac[k] % mod * invFac[n - k] % mod;
}

long long countWays(int n, int m, int k, int a, int b) {
    long long res = 0;
    for (int i = 0; i <= a; i++) {
        for (int j = 0; j <= b; j++) {
            long long cur = comb(a, i) * comb(b, j) % mod * comb((n - i) * (m - j), k) % mod;
            if ((i + j) & 1) res = (res - cur + mod) % mod;
            else res = (res + cur) % mod;
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    fac[0] = 1;
    for (int i = 1; i <= 10000; i++) fac[i] = fac[i - 1] * i % mod;
    invFac[10000] = modPow(fac[10000], mod - 2);
    for (int i = 10000; i >= 1; i--) invFac[i - 1] = invFac[i] * i % mod;
    int t;
    cin >> t;
    for (int tc = 1; tc <= t; tc++) {
        int n, m, k, rowCnt, colCnt;
        cin >> n >> m >> k;
        rowCnt = (n == 1 ? 1 : 2);
        colCnt = (m == 1 ? 1 : 2);
        long long ans = countWays(n, m, k, rowCnt, colCnt);
        ans = (ans + countWays(n, m, k, 0, m) - countWays(n, m, k, rowCnt, m)) % mod;
        ans = (ans + countWays(n, m, k, n, 0) - countWays(n, m, k, n, colCnt)) % mod;
        ans = (ans + mod) % mod;
        cout << "Case " << tc << ": " << ans << '\n';
    }
    return 0;
}
