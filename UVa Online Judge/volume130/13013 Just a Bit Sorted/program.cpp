#include <bits/stdc++.h>
using namespace std;

const long long mod = 1000000007LL;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    while (cin >> n >> q) {
        vector<long long> dp(n + 1), pre(n + 1);
        dp[1] = 1;
        for (int len = 2; len <= n; ++len) {
            for (int m = len; m >= 2; --m)
                dp[m] = (m * dp[m] + (len - m + 1) * dp[m - 1]) % mod;
        }
        for (int m = 1; m <= n; ++m)
            pre[m] = (pre[m - 1] + dp[m]) % mod;
        for (int i = 0; i < q; ++i) {
            long long k;
            cin >> k;
            if (i) cout << ' ';
            cout << pre[min(k, (long long)n)];
        }
        cout << '\n';
    }
    return 0;
}
