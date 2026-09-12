#include <bits/stdc++.h>
using namespace std;

const long long mod = 21092013;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<int> mu(51), primes;
    vector<bool> comp(51, false);
    mu[1] = 1;
    for (int i = 2; i <= 50; i++) {
        if (!comp[i]) {
            primes.push_back(i);
            mu[i] = -1;
        }
        for (int p : primes) {
            if (i * p > 50) break;
            comp[i * p] = true;
            if (i % p == 0) {
                mu[i * p] = 0;
                break;
            }
            mu[i * p] = -mu[i];
        }
    }
    int t, n;
    cin >> t;
    for (int tc = 1; tc <= t; tc++) {
        cin >> n;
        vector<vector<int>> adj(n + 1);
        vector<int> low(n + 1), high(n + 1), par(n + 1, 0), ord;
        for (int i = 1, u, v; i < n; i++) {
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        for (int i = 1; i <= n; i++) cin >> low[i];
        for (int i = 1; i <= n; i++) cin >> high[i];
        ord.reserve(n);
        ord.push_back(1);
        for (int i = 0; i < n; i++) {
            int u = ord[i];
            for (int v : adj[u]) {
                if (v == par[u]) continue;
                par[v] = u;
                ord.push_back(v);
            }
        }
        vector<long long> all(51, 0), dp(n + 1);
        for (int d = 1; d <= 50; d++) {
            long long total = 0;
            fill(dp.begin(), dp.end(), 0);
            for (int i = n - 1; i >= 0; i--) {
                int u = ord[i];
                long long sumVal = 0, pairVal = 0;
                for (int v : adj[u]) {
                    if (par[v] != u) continue;
                    pairVal = (pairVal + sumVal * dp[v]) % mod;
                    sumVal = (sumVal + dp[v]) % mod;
                }
                long long ways = high[u] / d - (low[u] - 1) / d;
                total = (total + ways * ((1 + sumVal + pairVal) % mod)) % mod;
                dp[u] = ways * ((1 + sumVal) % mod) % mod;
            }
            all[d] = total;
        }
        cout << "Case " << tc << ":\n";
        for (int g = 1; g <= 50; g++) {
            long long ans = 0;
            for (int k = 1; g * k <= 50; k++) ans += mu[k] * all[g * k];
            ans %= mod;
            if (ans < 0) ans += mod;
            cout << g << ": " << ans << '\n';
        }
    }
    return 0;
}
