#include <bits/stdc++.h>
using namespace std;

const long long mod = 1000000007;
const int maxVal = 100000;
long long fac[maxVal + 1], invFac[maxVal + 1], pw[maxVal + 1];

long long qpow(long long a, long long b) {
    long long res = 1;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

long long comb(int n, int k) {
    if (k > n) return 0;
    return fac[n] * invFac[k] % mod * invFac[n - k] % mod;
}

void init() {
    fac[0] = invFac[0] = pw[0] = 1;
    for (int i = 1; i <= maxVal; i++) {
        fac[i] = fac[i - 1] * i % mod;
        pw[i] = pw[i - 1] * 2 % mod;
    }
    invFac[maxVal] = qpow(fac[maxVal], mod - 2);
    for (int i = maxVal; i >= 1; i--) invFac[i - 1] = invFac[i] * i % mod;
}

pair<long long, long long> solve(int n, long long c, int k, int a, int b, int d) {
    vector<int> cnt(maxVal + 1);
    vector<long long> allCnt(maxVal + 1), kCnt(maxVal + 1);
    long long p0 = a, p1 = b, cur, ans1 = 0, ans2 = 0;
    cnt[p0]++;
    if (n >= 2) cnt[p1]++;
    for (int i = 2; i < n; i++) {
        cur = 1 + (1LL * a * p0 + 1LL * b * p1 + d) % maxVal;
        cnt[cur]++;
        p0 = p1;
        p1 = cur;
    }
    for (int i = 1; i <= maxVal; i++) {
        int sum = 0;
        for (int j = i; j <= maxVal; j += i) sum += cnt[j];
        allCnt[i] = (pw[sum] - 1 + mod) % mod;
        kCnt[i] = comb(sum, k);
    }
    for (int i = maxVal; i >= 1; i--) {
        for (int j = i + i; j <= maxVal; j += i) {
            allCnt[i] = (allCnt[i] - allCnt[j] + mod) % mod;
            kCnt[i] = (kCnt[i] - kCnt[j] + mod) % mod;
        }
        long long ways = (c / i) % mod;
        ans1 = (ans1 + allCnt[i] * ways) % mod;
        ans2 = (ans2 + kCnt[i] * ways) % mod;
    }
    return make_pair(ans1, ans2);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int t;
    cin >> t;
    for (int tc = 1; tc <= t; tc++) {
        int n, k, a, b, d;
        long long c;
        cin >> n >> c >> k;
        cin >> a >> b >> d;
        pair<long long, long long> ans = solve(n, c, k, a, b, d);
        cout << "Case " << tc << ": " << ans.first << " " << ans.second << '\n';
    }
    return 0;
}
