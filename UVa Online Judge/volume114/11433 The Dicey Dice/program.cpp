#include <bits/stdc++.h>
using namespace std;

const long long mod = 100000007;
const int maxV = 20010;

long long fac[maxV], invFac[maxV];

long long quickPow(long long a, long long b) {
    long long res = 1;
    while (b > 0) {
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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    fac[0] = 1;
    for (int i = 1; i < maxV; i++) fac[i] = fac[i - 1] * i % mod;
    invFac[maxV - 1] = quickPow(fac[maxV - 1], mod - 2);
    for (int i = maxV - 2; i >= 0; i--) invFac[i] = invFac[i + 1] * (i + 1) % mod;
    int n, k, s;
    while (cin >> n >> k) {
        if (n == 0 && k == 0) break;
        cin >> s;
        int t = s - n;
        if (t < 0 || t > n * (k - 1)) {
            cout << 0 << '\n';
            continue;
        }
        vector<long long> powA(n + 1), powB(n + 1);
        long long baseA = (mod - (k + 1LL) % mod) % mod, baseB = k;
        powA[0] = 1;
        powB[0] = 1;
        for (int i = 1; i <= n; i++) {
            powA[i] = powA[i - 1] * baseA % mod;
            powB[i] = powB[i - 1] * baseB % mod;
        }
        long long ans = 0;
        for (int a = 0; a <= n; a++) {
            int remain = t - k * a;
            if (remain < 0) break;
            long long multiA = comb(n, a);
            for (int b = 0; b <= n - a; b++) {
                int rest = remain - (k + 1) * b;
                if (rest < 0) break;
                int top = 2 * n + rest - 1;
                long long multi = multiA * comb(n - a, b) % mod;
                long long cur = multi * powA[a] % mod * powB[b] % mod;
                cur = cur * comb(top, rest) % mod;
                ans += cur;
                if (ans >= mod) ans -= mod;
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
