// A Shooting Game
// UVa ID: 11884
// Verdict: Accepted
// Submission Date: 2026-07-30
// UVa Run Time: 0.020s

#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-8;
double dp[7][7][7][7][7][7];

bool isZero(int h0, int h1, int h2, int h3, int h4, int h5) {
    return h0 == 0 && h1 == 0 && h2 == 0 && h3 == 0 && h4 == 0 && h5 == 0;
}

double dfs(int h0, int h1, int h2, int h3, int h4, int h5) {
    double &res = dp[h0][h1][h2][h3][h4][h5];
    if (res > EPS) return res;
    if (isZero(h0, h1, h2, h3, h4, h5)) return res = 0.0;
    double best = 0.0;
    for (int row = 1; row <= 6; ++row) {
        double leftExpect = 0.0;
        for (int power = 1; power <= 3; ++power) {
            int v0 = h0, v1 = h1, v2 = h2, v3 = h3, v4 = h4, v5 = h5;
            int k = power;
            if (v0 >= row && k > 0) { --v0; --k; }
            if (v1 >= row && k > 0) { --v1; --k; }
            if (v2 >= row && k > 0) { --v2; --k; }
            if (v3 >= row && k > 0) { --v3; --k; }
            if (v4 >= row && k > 0) { --v4; --k; }
            if (v5 >= row && k > 0) { --v5; --k; }
            if (k == power) continue;
            leftExpect += (1.0 / 3.0) * (1.0 - dfs(v0, v1, v2, v3, v4, v5));
        }
        best = max(best, leftExpect);
        double rightExpect = 0.0;
        for (int power = 1; power <= 3; ++power) {
            int v0 = h0, v1 = h1, v2 = h2, v3 = h3, v4 = h4, v5 = h5;
            int k = power;
            if (v5 >= row && k > 0) { --v5; --k; }
            if (v4 >= row && k > 0) { --v4; --k; }
            if (v3 >= row && k > 0) { --v3; --k; }
            if (v2 >= row && k > 0) { --v2; --k; }
            if (v1 >= row && k > 0) { --v1; --k; }
            if (v0 >= row && k > 0) { --v0; --k; }
            if (k == power) continue;
            rightExpect += (1.0 / 3.0) * (1.0 - dfs(v0, v1, v2, v3, v4, v5));
        }
        best = max(best, rightExpect);
    }
    return res = best;
}

int main() {
    int n;
    while (scanf("%d", &n) == 1 && n != 0) {
        int h[6] = {0, 0, 0, 0, 0, 0};
        for (int i = 0; i < n; ++i) scanf("%d", &h[i]);
        memset(dp, 0, sizeof(dp));
        double ans = dfs(h[0], h[1], h[2], h[3], h[4], h[5]);
        printf("%.6f\n", ans);
    }
    return 0;
}
