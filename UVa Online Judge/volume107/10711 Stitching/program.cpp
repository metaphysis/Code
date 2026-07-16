// Stitching
// UVa ID: 10711
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Point3D {
    double x, y, z;
};

// 计算三角形面积（三维叉积）
double triangleArea(const Point3D& a, const Point3D& b, const Point3D& c) {
    double v1x = b.x - a.x, v1y = b.y - a.y, v1z = b.z - a.z;
    double v2x = c.x - a.x, v2y = c.y - a.y, v2z = c.z - a.z;
    double cx = v1y * v2z - v1z * v2y;
    double cy = v1z * v2x - v1x * v2z;
    double cz = v1x * v2y - v1y * v2x;
    return 0.5 * sqrt(cx * cx + cy * cy + cz * cz);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;
    cout << fixed << setprecision(5);
    while (N--) {
        int m, n;
        double z1;
        cin >> m >> n >> z1;
        vector<Point3D> P(m), Q(n);
        for (int i = 0; i < m; ++i) {
            cin >> P[i].x >> P[i].y;
            P[i].z = 0.0;
        }
        for (int j = 0; j < n; ++j) {
            cin >> Q[j].x >> Q[j].y;
            Q[j].z = z1;
        }
        const double INF = 1e100;
        double ans = INF;
        // 枚举起始偏移 (i0, j0)
        for (int i0 = 0; i0 < m; ++i0) {
            for (int j0 = 0; j0 < n; ++j0) {
                vector<vector<double>> dp(m + 1, vector<double>(n + 1, INF));
                dp[0][0] = 0.0;
                for (int d = 0; d <= m; ++d) {
                    for (int r = 0; r <= n; ++r) {
                        if (d == 0 && r == 0) continue;
                        double best = INF;
                        // 从左边来（向右一步）
                        if (r > 0) {
                            int i = (i0 + d) % m;
                            int jPrev = (j0 + r - 1) % n;
                            int jCur = (j0 + r) % n;
                            double cost = triangleArea(P[i], Q[jPrev], Q[jCur]);
                            best = min(best, dp[d][r - 1] + cost);
                        }
                        // 从上方来（向下一步）
                        if (d > 0) {
                            int iPrev = (i0 + d - 1) % m;
                            int iCur = (i0 + d) % m;
                            int j = (j0 + r) % n;
                            double cost = triangleArea(P[iPrev], P[iCur], Q[j]);
                            best = min(best, dp[d - 1][r] + cost);
                        }
                        dp[d][r] = best;
                    }
                }
                ans = min(ans, dp[m][n]);
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
