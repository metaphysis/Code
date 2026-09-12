#include <bits/stdc++.h>
using namespace std;

const long long mod = 10000;

long long getDigitCnt(long long n) {
    long long ans = 0, p = 1;
    while (p <= n) {
        ans = (ans + n - p + 1) % mod;
        if (p > n / 10) break;
        p *= 10;
    }
    return ans;
}

long long powMod(long long a, long long b) {
    long long ans = 1;
    while (b > 0) {
        if (b & 1) ans = ans * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long n, d, s, p1, p2, ans;
    int cas = 0;
    while (cin >> n && n) {
        d = getDigitCnt(n);
        s = (n + d) % mod;
        p1 = powMod(2, n - 1);
        p2 = p1 * 2 % mod;
        ans = (n % mod + d - 1 + s * p1 + p2 + 2 * (n % mod) - 3) % mod;
        if (ans < 0) ans += mod;
        cout << "Case " << ++cas << ": " << ans << '\n';
    }
    return 0;
}
