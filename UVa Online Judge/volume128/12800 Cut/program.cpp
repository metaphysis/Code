// Cut
// UVa ID: 12800
// Verdict: Accepted
// Submission Date: 2026-07-23
// UVa Run Time: 0.490s

#include <bits/stdc++.h>
using namespace std;

#define MAXN 256
double dp[MAXN][MAXN], distMat[MAXN][MAXN];
int used[MAXN][MAXN];

double computeMinCost(int left, int right) {
    if (used[left][right]) return dp[left][right];
    if (right - left <= 3) return 0;
    used[left][right] = 1;
    double &result = dp[left][right];
    result = 1e+30;
    for (int i = left + 1; i <= right - 1; i += 2) {
        for (int j = i + 1; j <= right - 1; j += 2) {
            result = min(result, computeMinCost(left, i) + computeMinCost(i, j) + computeMinCost(j, right) +
                                 distMat[left][i] + distMat[i][j] + distMat[j][right]);
        }
    }
    return result;
}

int main() {
    int n;
    double xs[MAXN], ys[MAXN];
    while (scanf("%d", &n) == 1) {
        n = n * 2;
        for (int i = 0; i < n; i++) scanf("%lf %lf", &xs[i], &ys[i]);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                distMat[i][j] = hypot(xs[i] - xs[j], ys[i] - ys[j]);
                used[i][j] = 0;
            }
            distMat[i][i + 1] = 0;
        }
        double ans = computeMinCost(0, n - 1);
        printf("%.4lf\n", ans);
    }
    return 0;
}
