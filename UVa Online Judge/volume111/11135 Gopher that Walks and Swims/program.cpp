#include <bits/stdc++.h>
using namespace std;

const long double inf = 1e100L;

int getCell(long double x, long double d) {
    return (int)floor(x / d + 1e-12L);
}

long double getDist(long double dx, long double dy) {
    return sqrtl(dx * dx + dy * dy);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long double d, l, xs, ys, xt, yt;
    while (cin >> d >> l >> xs >> ys >> xt >> yt) {
        if (d == 0) break;
        int sxCell = getCell(xs, d), txCell = getCell(xt, d);
        int syCell = getCell(ys, d), tyCell = getCell(yt, d);
        int v = txCell - sxCell, h = syCell - tyCell;
        long double swim = 2.0L * l * (v * sqrtl(2.0L) + h - v);
        long double walk = 0.0L;
        if (v == 0) {
            long double dy = ys - yt - 2.0L * l * h;
            walk = getDist(xt - xs, dy);
        } else {
            vector<vector<long double>> dp(v, vector<long double>(h, inf));
            for (int j = 0; j < h; j++) {
                long double x = (sxCell + 1) * d - l;
                long double y = (syCell - j) * d + l;
                long double dx = x - xs;
                long double dy = ys - y - 2.0L * l * j;
                dp[0][j] = getDist(dx, dy);
            }
            for (int i = 1; i < v; i++) {
                for (int j = i; j < h; j++) {
                    long double x1 = (sxCell + i) * d + l;
                    long double y1;
                    for (int k = i - 1; k < j; k++) {
                        long double x2 = (sxCell + i + 1) * d - l;
                        long double y2 = (syCell - j) * d + l;
                        y1 = (syCell - k) * d - l;
                        long double dx = x2 - x1;
                        long double dy = y1 - y2 - 2.0L * l * (j - k - 1);
                        dp[i][j] = min(dp[i][j], dp[i - 1][k] + getDist(dx, dy));
                    }
                }
            }
            for (int j = v - 1; j < h; j++) {
                long double x = (sxCell + v) * d + l;
                long double y = (syCell - j) * d - l;
                long double dx = xt - x;
                long double dy = y - yt - 2.0L * l * (h - j - 1);
                walk = max(walk, dp[v - 1][j] + getDist(dx, dy));
            }
            long double best = inf;
            for (int j = v - 1; j < h; j++) {
                long double x = (sxCell + v) * d + l;
                long double y = (syCell - j) * d - l;
                long double dx = xt - x;
                long double dy = y - yt - 2.0L * l * (h - j - 1);
                best = min(best, dp[v - 1][j] + getDist(dx, dy));
            }
            walk = best;
        }
        cout << fixed << setprecision(2);
        cout << "The gopher has to swim " << (double)swim;
        cout << " meters and walk " << (double)walk << " meters.\n";
    }
    return 0;
}
