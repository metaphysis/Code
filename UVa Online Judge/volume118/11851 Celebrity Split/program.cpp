// Celebrity Split
// UVa ID: 11851
// Verdict: Accepted
// Submission Date: 2026-05-25
// UVa Run Time: 0.680s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Node {
    int diff, mask, sum1;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n && n != 0) {
        vector<int> a(n);
        int total = 0;
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
            total += a[i];
        }
        
        int n1 = n / 2, n2 = n - n1;
        
        // 枚举左半所有不相交子集对 (L1, L2)
        int limit1 = 1;
        for (int i = 0; i < n1; ++i) limit1 *= 3;
        vector<Node> left;
        left.reserve(limit1);
        
        for (int state = 0; state < limit1; ++state) {
            int sum1 = 0, sum2 = 0, mask = 0, tmp = state;
            for (int i = 0; i < n1; ++i) {
                int t = tmp % 3;
                tmp /= 3;
                if (t == 1) {
                    sum1 += a[i];
                    mask |= (1 << i);
                } else if (t == 2) {
                    sum2 += a[i];
                    mask |= (1 << i);
                }
            }
            left.push_back({sum1 - sum2, mask, sum1});
        }
        
        // 枚举右半所有不相交子集对 (R1, R2)
        int limit2 = 1;
        for (int i = 0; i < n2; ++i) limit2 *= 3;
        vector<Node> right;
        right.reserve(limit2);
        
        for (int state = 0; state < limit2; ++state) {
            int sum1 = 0, sum2 = 0, mask = 0, tmp = state;
            for (int i = 0; i < n2; ++i) {
                int t = tmp % 3;
                tmp /= 3;
                if (t == 1) {
                    sum1 += a[n1 + i];
                    mask |= (1 << i);
                } else if (t == 2) {
                    sum2 += a[n1 + i];
                    mask |= (1 << i);
                }
            }
            right.push_back({sum1 - sum2, mask, sum1});
        }
        
        // 对右半按 diff 排序
        sort(right.begin(), right.end(), [](const Node& x, const Node& y) {
            return x.diff < y.diff;
        });
        
        // 压缩右半：每个 diff 只保留最大的 sum1
        vector<pair<int, int>> rightBest;
        for (size_t i = 0; i < right.size(); ) {
            int curDiff = right[i].diff;
            int maxSum1 = 0;
            while (i < right.size() && right[i].diff == curDiff) {
                if (right[i].sum1 > maxSum1) maxSum1 = right[i].sum1;
                ++i;
            }
            rightBest.emplace_back(curDiff, maxSum1);
        }
        
        // 匹配左半与右半
        int maxSameSum = 0;
        for (const Node& node : left) {
            int target = -node.diff;
            auto it = lower_bound(rightBest.begin(), rightBest.end(), make_pair(target, 0));
            if (it != rightBest.end() && it->first == target) {
                maxSameSum = max(maxSameSum, node.sum1 + it->second);
            }
        }
        
        cout << total - 2 * maxSameSum << '\n';
    }
    return 0;
}
