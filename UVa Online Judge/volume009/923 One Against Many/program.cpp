#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int g;
    cin >> g;
    while (g--) {
        int oi, r, n;
        cin >> oi >> r >> n;
        vector<int> pri(n);
        for (int i = 0; i < n; ++i)
            cin >> pri[i];
        vector<vector<long long> > dp(oi + 1, vector<long long>(n, -1));
        dp[oi][0] = 0;
        for (int o = oi; o >= 1; --o) {
            for (int s = 0; s < n; ++s) {
                if (dp[o][s] < 0)
                    continue;
                long long cur = dp[o][s];
                long long pay = cur * pri[s] / 100;
                long long base = cur - pay;
                int ns = (s + 1) % n;
                for (int l = 1; l <= o; ++l) {
                    long long gain = static_cast<long long>(r) * l / o;
                    dp[o - l][ns] = max(dp[o - l][ns], base + gain);
                }
            }
        }
        long long ans = 0;
        for (int s = 0; s < n; ++s)
            ans = max(ans, dp[0][s]);
        cout << ans << '\n';
    }
    return 0;
}
