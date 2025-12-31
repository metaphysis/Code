// National Bomb Defusing Squad
// UVa ID: 13150
// Verdict: Accepted
// Submission Date: 2025-12-26
// UVa Run Time: 2.410s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    while (cin >> n >> q, n || q) {
        vector<pair<int, int>> points(n);
        for (int i = 0; i < n; ++i) cin >> points[i].first >> points[i].second;

        // 对每个点，存储到其他点的距离平方
        vector<vector<int>> distSq(n);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                int dx = points[i].first - points[j].first;
                int dy = points[i].second - points[j].second;
                distSq[i].push_back(dx * dx + dy * dy);
            }
            sort(distSq[i].begin(), distSq[i].end()); // 便于二分查找
        }

        while (q--) {
            int r;
            cin >> r;
            long long total = 0;
            int rSq = r * r;
            for (int i = 0; i < n; ++i) {
                // 使用 upper_bound 找到第一个 > rSq 的位置，其索引即为 ≤ rSq 的数量
                int cnt = upper_bound(distSq[i].begin(), distSq[i].end(), rSq) - distSq[i].begin();
                total += cnt;
            }
            double expected = total * 1.0 / n;
            cout << fixed << setprecision(2) << expected << "\n";
        }
        cout << "\n"; // 每个测试用例后输出空行
    }

    return 0;
}
