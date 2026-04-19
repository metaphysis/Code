// Pirate Chest
// UVa ID: 1580
// Verdict: Accepted
// Submission Date: 2026-02-27
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int a, b, m, n;
    while (cin >> a >> b >> m >> n) {
        vector<vector<int>> depth(m, vector<int>(n));
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                cin >> depth[i][j];

        ll totalArea = (ll)m * n;
        ll maxVol = 0;

        // 枚举所有可能的矩形底面尺寸，考虑旋转
        vector<pair<int, int>> sizes;
        for (int p = 1; p <= a; p++)
            for (int q = 1; q <= b; q++)
                sizes.emplace_back(p, q);
        for (int p = 1; p <= b; p++)
            for (int q = 1; q <= a; q++)
                if (p != a || q != b)
                    sizes.emplace_back(p, q);
        sort(sizes.begin(), sizes.end());
        sizes.erase(unique(sizes.begin(), sizes.end()), sizes.end());

        for (auto &sz : sizes) {
            int rows = sz.first, cols = sz.second;
            if (rows > m || cols > n) continue;

            for (int r1 = 0; r1 + rows <= m; r1++) {
                for (int c1 = 0; c1 + cols <= n; c1++) {
                    int minDepth = INT_MAX;
                    for (int i = r1; i < r1 + rows; i++)
                        for (int j = c1; j < c1 + cols; j++)
                            minDepth = min(minDepth, depth[i][j]);

                    ll k = (ll)rows * cols;
                    if (k >= totalArea) continue;  // 箱子不能覆盖整个池塘

                    // 最大高度 H_max = floor(minDepth * totalArea / (totalArea - k))
                    ll H_max = (minDepth * totalArea - 1) / (totalArea - k);
                    if (H_max < 1) continue;

                    ll vol = k * H_max;
                    if (vol > maxVol) maxVol = vol;
                }
            }
        }

        cout << maxVol << "\n";
    }
    return 0;
}
