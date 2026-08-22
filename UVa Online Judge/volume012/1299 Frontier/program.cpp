#include <bits/stdc++.h>
using namespace std;

const double inf = 1e100;

struct Point {
    long long x, y;
};

long long cross(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

double dis(Point a, Point b) {
    long long dx = a.x - b.x, dy = a.y - b.y;
    return sqrt((double)dx * dx + (double)dy * dy);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    while (cin >> n >> m) {
        vector<Point> guard(n), mark(m);
        for (int i = 0; i < n; i++)
            cin >> guard[i].x >> guard[i].y;
        for (int i = 0; i < m; i++)
            cin >> mark[i].x >> mark[i].y;
        vector<vector<bool>> good(n, vector<bool>(n, false));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j)
                    continue;
                good[i][j] = true;
                for (int k = 0; k < m; k++) {
                    if (cross(guard[i], guard[j], mark[k]) >= 0) {
                        good[i][j] = false;
                        break;
                    }
                }
            }
        }
        double ans = inf;
        for (int s = 0; s < n; s++) {
            for (int k = s + 1; k < s + n - 1; k++) {
                int u = s % n, v = k % n;
                if (!good[u][v])
                    continue;
                vector<double> dp(s + n, inf);
                dp[k] = dis(guard[u], guard[v]);
                for (int i = k; i < s + n - 1; i++) {
                    if (dp[i] >= inf)
                        continue;
                    for (int j = i + 1; j < s + n; j++) {
                        int a = i % n, b = j % n;
                        if (!good[a][b])
                            continue;
                        if (i == k && cross(guard[u], guard[v], guard[b]) == 0)
                            continue;
                        dp[j] = min(dp[j], dp[i] + dis(guard[a], guard[b]));
                    }
                }
                for (int i = k + 1; i < s + n; i++) {
                    int a = i % n;
                    if (dp[i] < inf && good[a][u])
                        ans = min(ans, dp[i] + dis(guard[a], guard[u]));
                }
            }
        }
        cout << fixed << setprecision(2) << ans << '\n';
    }
    return 0;
}
