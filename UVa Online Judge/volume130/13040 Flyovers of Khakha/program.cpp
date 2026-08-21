#include <bits/stdc++.h>
using namespace std;

const long long inf = (1LL << 62);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, tc;
    cin >> t;
    for (tc = 1; tc <= t; tc++) {
        int n, m;
        cin >> n;
        vector<int> x(n), y(n), deg(n, 0);
        for (int i = 0; i < n; i++) cin >> x[i] >> y[i];
        vector<vector<long long>> dis(n, vector<long long>(n, inf));
        for (int i = 0; i < n; i++) dis[i][i] = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                long long dx = x[i] - x[j], dy = y[i] - y[j];
                dis[i][j] = dis[j][i] = dx * dx + dy * dy;
            }
        }
        cin >> m;
        for (int i = 0; i < m; i++) {
            int a, b;
            cin >> a >> b;
            deg[a]++;
            deg[b]++;
        }
        for (int k = 0; k < n; k++)
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    if (dis[i][j] > dis[i][k] + dis[k][j])
                        dis[i][j] = dis[i][k] + dis[k][j];
        int total = 1 << n, oddMask = 0;
        for (int i = 0; i < n; i++)
            if (deg[i] & 1)
                oddMask |= 1 << i;
        vector<long long> dp(total, inf);
        dp[0] = 0;
        for (int mask = 1; mask < total; mask++) {
            if (__builtin_popcount(mask) & 1) continue;
            int i = __builtin_ctz(mask);
            int rest = mask ^ (1 << i);
            for (int j = i + 1; j < n; j++)
                if (rest & (1 << j))
                    dp[mask] = min(dp[mask], dp[rest ^ (1 << j)] + dis[i][j]);
        }
        long long ans = dp[oddMask];
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                ans = min(ans, dp[oddMask ^ (1 << i) ^ (1 << j)]);
        cout << "Case " << tc << ": " << ans << '\n';
    }
    return 0;
}
