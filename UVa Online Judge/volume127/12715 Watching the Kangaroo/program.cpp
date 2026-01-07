// Watching the Kangaroo
// UVa ID: 12715
// Verdict: Accepted
// Submission Date: 2026-01-07
// UVa Run Time: 0.090s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    for (int caseNo = 1; caseNo <= T; ++caseNo) {
        int n, m;
        cin >> n >> m;
        vector<pair<int, int>> screens(n);
        for (int i = 0; i < n; ++i) cin >> screens[i].first >> screens[i].second;
        vector<int> queries(m);
        for (int i = 0; i < m; ++i) cin >> queries[i];
        // 准备左半部分和右半部分的数据
        vector<pair<int, int>> leftEvents;  // (sum, 2L) 其中 sum = L+R
        vector<pair<int, int>> rightEvents; // (sum, 2R) 其中 sum = L+R
        for (auto& screen : screens) {
            int L = screen.first, R = screen.second, sum = L + R;
            leftEvents.emplace_back(sum, 2 * L);
            rightEvents.emplace_back(sum, 2 * R);
        }
        // 左半部分：按 sum 降序排序
        sort(leftEvents.begin(), leftEvents.end(), greater<pair<int, int>>());
        // 预处理左半部分：对于每个位置，维护最小的 2L
        vector<int> minDoubleL(leftEvents.size());
        if (!leftEvents.empty()) {
            minDoubleL[0] = leftEvents[0].second;
            for (int i = 1; i < (int)leftEvents.size(); ++i)
                minDoubleL[i] = min(minDoubleL[i - 1], leftEvents[i].second);
        }
        // 右半部分：按 sum 升序排序
        sort(rightEvents.begin(), rightEvents.end());
        // 预处理右半部分：对于每个位置，维护最大的 2R
        // 由于我们需要前缀最大值（从开始到当前位置的最大值）
        vector<int> prefixMaxR(rightEvents.size());
        if (!rightEvents.empty()) {
            prefixMaxR[0] = rightEvents[0].second;
            for (int i = 1; i < (int)rightEvents.size(); ++i)
                prefixMaxR[i] = max(prefixMaxR[i - 1], rightEvents[i].second);
        }
        cout << "Case " << caseNo << ":\n";
         for (int x : queries) {
            int y = 2 * x;
            int answer = 0;
            // 处理左半部分：找到所有 sum >= y 的区间
            if (!leftEvents.empty()) {
                // 二分查找：找到第一个 sum < y 的位置
                // 由于是降序排列，所有 sum >= y 的区间在 [0, idx)
                auto it = lower_bound(leftEvents.begin(), leftEvents.end(), 
                                     make_pair(y, INT_MIN), greater<pair<int, int>>());
                int idx = it - leftEvents.begin();
                if (idx > 0) {
                    int minL = minDoubleL[idx - 1];
                    if (minL <= y) answer = max(answer, y - minL);
                }
            }
            // 处理右半部分：找到所有 sum <= y 的区间
            if (!rightEvents.empty()) {
                // 二分查找：找到最后一个 sum <= y 的位置
                auto it = upper_bound(rightEvents.begin(), rightEvents.end(), 
                                     make_pair(y, INT_MAX));
                if (it != rightEvents.begin()) {
                    --it;
                    int idx = it - rightEvents.begin();
                    int maxR = prefixMaxR[idx];
                    if (maxR >= y) answer = max(answer, maxR - y);
                }
            }
            cout << answer / 2 << '\n';
        }
    }
    return 0;
}
