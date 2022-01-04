#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100010, MAXB = 320, MOD = 10007;

int n, s, a[MAXN], link[MAXN];
long long added[MAXB], multiplied[MAXB];

int query(int L) {
    int p = link[L];    
    return (a[L] * multiplied[p] % MOD + added[p]) % MOD;
}

void add(int L, int R, int x) {
    int p = link[L], q = link[R];
    for (int i = (p - 1) * s + 1; i <= min(n, p * s); i++)
        a[i] = (a[i] * multiplied[p] % MOD + added[p]) % MOD;
    for (int i = L; i <= min(R, p * s); i++) a[i] += x, a[i] %= MOD;
    added[p] = 0, multiplied[p] = 1;
    for (int i = p + 1; i < q; i++) added[i] += x, added[i] %= MOD;
    if (p != q) {
        for (int i = (q - 1) * s + 1; i <= min(n, q * s); i++)
            a[i] = (a[i] * multiplied[q] % MOD + added[q]) % MOD;
        for (int i = (q - 1) * s + 1; i <= R; i++) a[i] += x, a[i] %= MOD;
        added[q] = 0, multiplied[q] = 1;
    }
}

void multiply(int L, int R, int x) {
    int p = link[L], q = link[R];
    for (int i = (p - 1) * s + 1; i <= min(n, p * s); i++)
        a[i] = (a[i] * multiplied[p] % MOD + added[p]) % MOD;
    for (int i = L; i <= min(R, p * s); i++) a[i] *= x, a[i] %= MOD;
    added[p] = 0, multiplied[p] = 1;
    for (int i = p + 1; i < q; i++) {
        added[i] *= x, added[i] %= MOD;
        multiplied[i] *= x, multiplied[i] %= MOD;
    }
    if (p != q) {
        for (int i = (q - 1) * s + 1; i <= min(n, q * s); i++)
            a[i] = (a[i] * multiplied[q] % MOD + added[q]) % MOD;
        for (int i = (q - 1) * s + 1; i <= R; i++) a[i] *= x, a[i] %= MOD;
        added[q] = 0, multiplied[q] = 1;
    }
}

int main(int argc, char *argv[]) {
    cin >> n;
    s = sqrt(n) + 1;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        link[i] = (i - 1) / s + 1;
    }
    for (int i = 1; i <= s; i++) multiplied[i] = 1;
    int c, L, R, x;
    for (int i = 0; i < n; i++) {
        cin >> c >> L >> R >> x;
        if (c == 0) add(L, R, x);
        else if (c == 1) multiply(L, R, x);
        else cout << query(R) << '\n';
    }
    return 0;
}
