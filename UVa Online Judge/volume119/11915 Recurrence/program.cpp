#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1000000009LL;

long long qPow(long long a, long long b) {
    long long r = 1;
    while (b > 0) {
        if (b & 1) r = r * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return r;
}

int solve() {
    int t;
    cin >> t;
    vector<vector<int> > alls(t);
    vector<int> ns(t);
    int maxSum = 0;
    for (int k = 0; k < t; k++) {
        int n, sum = 0;
        cin >> n;
        ns[k] = n;
        alls[k].resize(n);
        for (int i = 0; i < n; i++) {
            cin >> alls[k][i];
            sum += alls[k][i];
        }
        maxSum = max(maxSum, sum);
    }
    int lim = max(maxSum, 2000);
    vector<long long> fac(lim + 1), ifac(lim + 1);
    fac[0] = 1;
    for (int i = 1; i <= lim; i++) fac[i] = fac[i - 1] * i % MOD;
    ifac[lim] = qPow(fac[lim], MOD - 2);
    for (int i = lim; i >= 1; i--) ifac[i - 1] = ifac[i] * i % MOD;
    for (int k = 0; k < t; k++) {
        int n = ns[k], sum = 0;
        vector<int> p = alls[k];
        for (int x : p) sum += x;
        long long ans = fac[sum];
        for (int i = 0; i < n; i++) {
            ans = ans * ifac[p[i] + n - 1 - i] % MOD;
            for (int j = i + 1; j < n; j++)
                ans = ans * (p[i] - p[j] + j - i) % MOD;
        }
        cout << "Case " << k + 1 << ": " << ans << '\n';
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return solve();
}
