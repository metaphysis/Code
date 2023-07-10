const int MAXN = 1000100;
const int BASE = 16777213, MOD = 2147483647;

long long h[MAXN], b[MAXN];

int getHash(string &s) {
    h[0] = 0;
    int n = s.length();
    for (int i = 1; i <= n; i++)
        h[i] = (h[i - 1] * BASE + s[i - 1]) % MOD;
    return h[n];
}

int prepared = 0;

int getHash(string &s, int L, int R) {
    if (!prepared) {
        h[0] = 0, b[0] = 1;
        int n = s.length();
        for (int i = 1; i <= n; i++) {
            h[i] = (h[i - 1] * BASE + s[i - 1]) % MOD;
            b[i] = b[i - 1] * BASE % MOD;
        }
        prepared = 1;
    }
    return (h[R + 1] - h[L] * b[R - L + 1] % MOD + MOD) % MOD;
}
