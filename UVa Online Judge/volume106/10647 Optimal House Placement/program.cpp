
// Optimal House Placement
// UVa ID: 10647
// Verdict: Accepted
// Submission Date: 2026-02-07
// UVa Run Time: 0.020s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-10;
const int MAXN = 10010;

int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int n;
    double p[MAXN], gap[MAXN], leftE[MAXN], rightE[MAXN];
    while (scanf("%d", &n) == 1 && n) {
        // 读入位置
        for (int i = 0; i < n; i++) scanf("%lf", &p[i]);
        // 计算相邻两个朋友家需要消耗的能量
        for (int i = 1; i < n; i++) gap[i] = (p[i] - p[i - 1]) * (p[i] - p[i - 1]);
        leftE[0] = 0;
        for (int i = 1; i < n; i++) leftE[i] = leftE[i - 1] + i * gap[i];
        rightE[n - 1] = 0;
        for (int i = n - 2; i >= 0; i--) rightE[i] = rightE[i + 1] + (n - i - 1) * gap[i + 1];
        double bestX = p[0], minE = 1e18, x, E;
        // 从左至右考虑所有可能的最佳候选位置
        for (int i = 0; i < n - 1; i++) {
            int leftCnt = i + 1, rightCnt = n - i - 1;
            x = (leftCnt * p[i] + rightCnt * p[i + 1]) / n;
            E = leftE[i] + rightE[i + 1]
                          + leftCnt * (x - p[i]) * (x - p[i])
                          + rightCnt * (p[i + 1] - x) * (p[i + 1] - x);
            if (E < minE - EPS) {
                minE = E;
                bestX = x;
            }
        }
        printf("%.3f\n", bestX);
    }
    return 0;
}
