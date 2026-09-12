#include <bits/stdc++.h>
using namespace std;

struct Point {
    long long x, y;
};

long long cross(const Point &a, const Point &b, const Point &c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, n;
    cin >> t;
    while (t--) {
        cin >> n;
        vector<Point> p(n);
        for (int i = 0; i < n; i++) cin >> p[i].x >> p[i].y;
        sort(p.begin(), p.end(), [](const Point &a, const Point &b) {
            return a.x < b.x;
        });
        vector<vector<char>> topOk(n, vector<char>(n)), botOk(n, vector<char>(n));
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                bool top = true, bot = true;
                for (int k = i + 1; k < j; k++) {
                    long long v = cross(p[i], p[j], p[k]);
                    if (v >= 0) top = false;
                    if (v <= 0) bot = false;
                }
                topOk[i][j] = top;
                botOk[i][j] = bot;
            }
        }
        vector<vector<long long>> dp(n, vector<long long>(n));
        dp[0][0] = 1;
        for (int k = 1; k <= n - 2; k++) {
            for (int i = 0; i < k; i++) {
                for (int j = 0; j < k; j++) {
                    if (max(i, j) != k - 1) continue;
                    if (topOk[i][k]) dp[k][j] += dp[i][j];
                    if (botOk[j][k]) dp[i][k] += dp[i][j];
                }
            }
        }
        long long ans = 0;
        for (int i = 0; i <= n - 2; i++) {
            for (int j = 0; j <= n - 2; j++) {
                if (max(i, j) != n - 2) continue;
                if (topOk[i][n - 1] && botOk[j][n - 1]) ans += dp[i][j];
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
