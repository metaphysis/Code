#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n, l, sx, sy;
        cin >> n >> l;
        cin >> sx >> sy;
        vector<vector<int>> a(n, vector<int>(n));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) cin >> a[i][j];
        const long long neg = -(1LL << 60);
        vector<vector<long long>> dp(n, vector<long long>(n, neg));
        dp[sy][sx] = 0;
        int dx[4] = {1, 1, -1, -1}, dy[4] = {1, -1, 1, -1};
        while (l--) {
            vector<vector<long long>> ndp(n, vector<long long>(n, neg));
            for (int y = 0; y < n; y++) {
                for (int x = 0; x < n; x++) {
                    if (dp[y][x] == neg) continue;
                    for (int d = 0; d < 4; d++) {
                        int nx = x + dx[d], ny = y + dy[d];
                        while (nx >= 0 && nx < n && ny >= 0 && ny < n) {
                            ndp[ny][nx] = max(ndp[ny][nx], dp[y][x] + a[ny][nx]);
                            nx += dx[d];
                            ny += dy[d];
                        }
                    }
                }
            }
            dp.swap(ndp);
        }
        long long ans = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) ans = max(ans, dp[i][j]);
        cout << ans << '\n';
    }
    return 0;
}
