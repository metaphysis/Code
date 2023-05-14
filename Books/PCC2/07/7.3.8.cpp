const int BASE = 16777213, MOD = 2147483647;

long long h[1000100];

long long getHash(string &s) {
    h[0] = 0;
    int n = s.length();
    for (int i = 1; i <= n; i++)
        h[i] = (h[i - 1] * BASE + s[i - 1]) % MOD;
    return h[n];
}

int prepared = 0;

int getHash(string &s, int L, int R) {
    if (!prepared) {
        getHash(s);
        prepared = 1;
    }
    long long b = 1;
    for (int i = L; i <= R; i++) b = b * BASE % MOD;
    return (h[R + 1] - h[L + 1] * b % MOD + MOD) % MOD;
}
