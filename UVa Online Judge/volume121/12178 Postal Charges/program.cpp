// Postal Charges
// UVa ID: 12178
// Verdict: Accepted
// Submission Date: 2026-07-30
// UVa Run Time: 0.310s

#include <bits/stdc++.h>
using namespace std;

// 计算两个已排序数组之间所有元素绝对差之和
double crossAbsSum(const vector<double>& a, const vector<double>& b) {
    double total = 0.0;
    size_t i = 0, j = 0;
    long long cntX = 0, cntY = 0;
    double sumX = 0.0, sumY = 0.0;
    while (i < a.size() || j < b.size()) {
        if (j == b.size() || (i < a.size() && a[i] <= b[j])) {
            double v = a[i];
            total += cntY * v - sumY;   // 当前X与之前所有Y的差
            ++cntX;
            sumX += v;
            ++i;
        } else {
            double v = b[j];
            total += cntX * v - sumX;   // 当前Y与之前所有X的差
            ++cntY;
            sumY += v;
            ++j;
        }
    }
    return total;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    while (cin >> n) {
        // 10x10 个行会，坐标范围 [0,10)
        long long cnt[10][10] = {};
        vector<double> xs[10][10], ys[10][10];

        for (int k = 0; k < n; ++k) {
            double x, y;
            cin >> x >> y;
            int i = (int)x;          // 0 <= x < 10
            int j = (int)y;
            ++cnt[i][j];
            xs[i][j].push_back(x);
            ys[i][j].push_back(y);
        }

        // 对每个行会内的坐标排序
        for (int i = 0; i < 10; ++i)
            for (int j = 0; j < 10; ++j) {
                sort(xs[i][j].begin(), xs[i][j].end());
                sort(ys[i][j].begin(), ys[i][j].end());
            }

        long long totalPairs = 0;
        double totalDist = 0.0;

        // 枚举所有满足 i1 < i2 且 j1 < j2 的行会对
        for (int i1 = 0; i1 < 10; ++i1)
            for (int j1 = 0; j1 < 10; ++j1) {
                if (cnt[i1][j1] == 0) continue;
                for (int i2 = i1 + 1; i2 < 10; ++i2)
                    for (int j2 = j1 + 1; j2 < 10; ++j2) {
                        if (cnt[i2][j2] == 0) continue;
                        long long cA = cnt[i1][j1], cB = cnt[i2][j2];
                        totalPairs += cA * cB;
                        // x 方向距离和 + y 方向距离和
                        totalDist += crossAbsSum(xs[i1][j1], xs[i2][j2]);
                        totalDist += crossAbsSum(ys[i1][j1], ys[i2][j2]);
                    }
            }

        double ans = totalDist / (double)totalPairs;
        cout << fixed << setprecision(8) << ans << '\n';
    }
    return 0;
}
