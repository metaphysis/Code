#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1000000007LL;

vector<long long> multiplyPoly(const vector<long long>& a, const vector<long long>& b, const vector<long long>& d) {
    int L = (int)a.size();
    vector<long long> tmp(2 * L - 1, 0);
    for (int i = 0; i < L; ++i) if (a[i])
        for (int j = 0; j < L; ++j) if (b[j])
            tmp[i + j] = (tmp[i + j] + a[i] * b[j]) % MOD;
    for (int deg = 2 * L - 2; deg >= L; --deg) {
        long long coef = tmp[deg];
        if (coef == 0) continue;
        for (int i = 1; i <= L; ++i)
            tmp[deg - i] = (tmp[deg - i] + coef * d[i - 1]) % MOD;
    }
    vector<long long> res(L);
    for (int i = 0; i < L; ++i) res[i] = tmp[i] % MOD;
    return res;
}

long long linearRec(const vector<long long>& init, const vector<long long>& d, long long n) {
    int L = (int)init.size();
    if (n < L) return init[n] % MOD;
    vector<long long> base(L, 0);
    if (L == 1) base[0] = d[0];
    else base[1] = 1;
    vector<long long> res(L, 0);
    res[0] = 1;
    while (n > 0) {
        if (n & 1) res = multiplyPoly(res, base, d);
        base = multiplyPoly(base, base, d);
        n >>= 1;
    }
    long long ans = 0;
    for (int i = 0; i < L; ++i) ans = (ans + res[i] * init[i]) % MOD;
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    while (T--) {
        int K;
        long long N;
        cin >> K >> N;
        long long minSum = 1LL * K * (K + 1) / 2;
        if (N < minSum) { cout << 0 << "\n"; continue; }
        long long M = N - minSum;
        int L = K * (K + 1) / 2;
        vector<long long> cur(1, 1);
        for (int i = 1; i <= K; ++i) {
            vector<long long> nxt(cur.size() + i, 0);
            for (int j = 0; j < (int)cur.size(); ++j) {
                nxt[j] = (nxt[j] + cur[j]) % MOD;
                nxt[j + i] = (nxt[j + i] - cur[j] + MOD) % MOD;
            }
            cur = nxt;
        }
        vector<long long> d(L);
        for (int j = 1; j <= L; ++j) d[j - 1] = (MOD - cur[j]) % MOD;
        vector<long long> init(L, 0);
        init[0] = 1;
        for (int coin = 1; coin <= K; ++coin)
            for (int s = coin; s < L; ++s)
                init[s] = (init[s] + init[s - coin]) % MOD;
        cout << linearRec(init, d, M) % MOD << "\n";
    }
    return 0;
}
