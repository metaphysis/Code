// Hybrid Salientia
// UVa ID: 11919
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.190s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Stone {
    char type;
    double x, y, r;
};

// 计算圆与圆的最短距离
double distCircleCircle(const Stone& a, const Stone& b) {
    double dx = a.x - b.x, dy = a.y - b.y;
    double d = sqrt(dx*dx + dy*dy);
    return max(0.0, d - a.r - b.r);
}

// 计算点到轴对齐矩形的最短距离（矩形内部为0）
double pointToRect(double px, double py, double rx, double ry, double s) {
    double lx = rx, rx2 = rx + s;
    double by = ry, ty = ry + s;
    double dx = max({lx - px, 0.0, px - rx2});
    double dy = max({by - py, 0.0, py - ty});
    return sqrt(dx*dx + dy*dy);
}

// 计算圆与正方形的最短距离
double distCircleSquare(const Stone& c, const Stone& s) {
    double d = pointToRect(c.x, c.y, s.x, s.y, s.r);
    return max(0.0, d - c.r);
}

// 计算两个正方形的最短距离
double distSquareSquare(const Stone& a, const Stone& b) {
    double l1 = a.x, r1 = a.x + a.r, b1 = a.y, t1 = a.y + a.r;
    double l2 = b.x, r2 = b.x + b.r, b2 = b.y, t2 = b.y + b.r;
    double dx = 0.0, dy = 0.0;
    if (r1 < l2) dx = l2 - r1;
    else if (r2 < l1) dx = l1 - r2;
    if (t1 < b2) dy = b2 - t1;
    else if (t2 < b1) dy = b1 - t2;
    return sqrt(dx*dx + dy*dy);
}

double distBetween(const Stone& a, const Stone& b) {
    if (a.type == 'C' && b.type == 'C') return distCircleCircle(a, b);
    if (a.type == 'C' && b.type == 'S') return distCircleSquare(a, b);
    if (a.type == 'S' && b.type == 'C') return distCircleSquare(b, a);
    return distSquareSquare(a, b);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    // 预计算 0.9 的幂，最大指数为 N-1 <= 14
    double pow09[20];
    pow09[0] = 1.0;
    for (int i = 1; i < 20; ++i) pow09[i] = pow09[i-1] * 0.9;

    cout << fixed << setprecision(10);
    while (T--) {
        int N;
        cin >> N;
        vector<Stone> stones(N);
        for (int i = 0; i < N; ++i) {
            cin >> stones[i].type >> stones[i].x >> stones[i].y >> stones[i].r;
        }

        vector<vector<double>> dist(N, vector<double>(N, 0.0));
        for (int i = 0; i < N; ++i)
            for (int j = i+1; j < N; ++j) {
                double d = distBetween(stones[i], stones[j]);
                dist[i][j] = dist[j][i] = d;
            }

        int full = (1 << N) - 1;
        const double INF = 1e100;
        vector<vector<double>> dp(1 << N, vector<double>(N, INF));
        dp[1 << 0][0] = 0.0;

        for (int mask = 0; mask < (1 << N); ++mask) {
            if ((mask & 1) == 0) continue;   // 必须包含起点
            int cnt = __builtin_popcount((unsigned)mask); // 已访问石头数
            int k = cnt;  // 下一次跳跃是第 k 次（k从1开始）
            for (int i = 0; i < N; ++i) if (mask & (1 << i)) {
                double cur = dp[mask][i];
                if (cur >= INF/2) continue;
                for (int j = 0; j < N; ++j) if (!(mask & (1 << j))) {
                    double d = dist[i][j];
                    double need = d / pow09[k-1];
                    double nxt = max(cur, need);
                    int nmask = mask | (1 << j);
                    if (nxt < dp[nmask][j]) dp[nmask][j] = nxt;
                }
            }
        }

        double ans = INF;
        for (int i = 0; i < N; ++i) ans = min(ans, dp[full][i]);
        cout << ans << '\n';
    }
    return 0;
}
