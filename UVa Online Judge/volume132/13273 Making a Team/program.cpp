// Making a Team
// UVa ID: 13273
// Verdict: Accepted
// Submission Date: 2026-07-30
// UVa Run Time: 0.000s

#include <bits/stdc++.h>
using namespace std;

const long long MOD = 100000007;
long long inv2, inv6, inv24;

long long modPow(long long a, long long e) {
    long long res = 1;
    while (e) {
        if (e & 1) res = res * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return res;
}

long long modInv(long long a) {
    long long b = MOD, u = 1, v = 0;
    while (b) {
        long long t = a / b;
        a -= t * b; swap(a, b);
        u -= t * v; swap(u, v);
    }
    return (u % MOD + MOD) % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    inv2 = modInv(2);
    inv6 = modInv(6);
    inv24 = modInv(24);

    long long n;
    while (cin >> n && n) {
        long long ans = 0;

        long long term1 = (n % MOD) * modPow(2, n - 1) % MOD;
        ans = (ans + term1) % MOD;

        if (n >= 2) {
            long long c2 = (n % MOD) * ((n - 1) % MOD) % MOD * inv2 % MOD;
            long long term2 = c2 * 14 % MOD * modPow(2, n - 2) % MOD;
            ans = (ans + term2) % MOD;
        }

        if (n >= 3) {
            long long c3 = (n % MOD) * ((n - 1) % MOD) % MOD * ((n - 2) % MOD) % MOD * inv6 % MOD;
            long long term3 = c3 * 36 % MOD * modPow(2, n - 3) % MOD;
            ans = (ans + term3) % MOD;
        }

        if (n >= 4) {
            long long c4 = (n % MOD) * ((n - 1) % MOD) % MOD * ((n - 2) % MOD) % MOD * ((n - 3) % MOD) % MOD * inv24 % MOD;
            long long term4 = c4 * 24 % MOD * modPow(2, n - 4) % MOD;
            ans = (ans + term4) % MOD;
        }

        cout << ans << '\n';
    }
    return 0;
}
