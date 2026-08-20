// Number of Battlefields
// UVa ID: 11885
// Verdict: Accepted
// Submission Date: 2026-07-28
// UVa Run Time: 0.010s

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll MOD = 987654321LL;

struct Matrix {
    ll v[2][2];
    Matrix(bool ident = false) {
        memset(v, 0, sizeof(v));
        if (ident) {
            v[0][0] = v[1][1] = 1;
        }
    }
};

Matrix mul(const Matrix& a, const Matrix& b) {
    Matrix c;
    for (int i = 0; i < 2; ++i) {
        for (int k = 0; k < 2; ++k) {
            if (a.v[i][k] == 0) continue;
            for (int j = 0; j < 2; ++j) {
                c.v[i][j] = (c.v[i][j] + a.v[i][k] * b.v[k][j]) % MOD;
            }
        }
    }
    return c;
}

Matrix power(Matrix base, ll exp) {
    Matrix result(true);
    while (exp > 0) {
        if (exp & 1) result = mul(result, base);
        base = mul(base, base);
        exp >>= 1;
    }
    return result;
}

ll calcF(ll n) {
    if (n == 2) return 1;
    if (n == 3) return 2;
    Matrix trans;
    trans.v[0][0] = 3;
    trans.v[0][1] = (MOD - 1) % MOD;
    trans.v[1][0] = 1;
    trans.v[1][1] = 0;
    Matrix mat = power(trans, n - 3);
    ll f_n = (mat.v[0][0] * 2 + mat.v[0][1] * 1) % MOD;
    return f_n;
}

int main() {
    ll p;
    while (scanf("%lld", &p) == 1 && p != 0) {
        if (p % 2 == 1 || p < 6) {
            printf("0\n");
            continue;
        }
        ll n = p / 2;
        ll total = calcF(n);
        ll rect = n - 1;
        ll ans = (total - rect % MOD + MOD) % MOD;
        printf("%lld\n", ans);
    }
    return 0;
}
