// DNA Regions
// UVa ID: 1392
// Verdict: Accepted
// Submission Date: 2026-01-30
// UVa Run Time: 0.030s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, p;
    while (cin >> n >> p) {
        if (n == 0) break;
        string s1, s2;
        cin >> s1 >> s2;
        // 特殊情况：如果 p = 100，整个序列都是保守区域
        if (p == 100) {
            cout << n << "\n";
            continue;
        }
        // 计算前缀和：pre[i] 表示前 i 个位置的不同字符数
        vector<int> pre(n + 1, 0);
        for (int i = 0; i < n; ++i) pre[i + 1] = pre[i] + (s1[i] != s2[i]);
        // 计算 f[i] = 100 * pre[i] - p * i
        vector<long long> f(n + 1, 0);
        for (int i = 0; i <= n; ++i) f[i] = 100LL * pre[i] - 1LL * p * i;
        // 存储 (-f[i], i) 对，并按 -f[i] 排序（即按 f[i] 降序）
        vector<pair<long long, int>> pairs;
        for (int i = 0; i <= n; ++i) pairs.emplace_back(-f[i], i);
        sort(pairs.begin(), pairs.end());
        int r = 0;
        int minIndex = n + 1;  // 维护到当前位置为止的最小索引
        // 遍历排序后的数组
        for (int idx = 0; idx <= n; ++idx) {
            int currentIndex = pairs[idx].second;
            // 如果之前有更小的索引，可以形成区间
            if (minIndex < currentIndex) {
                int length = currentIndex - minIndex;
                if (length > r) r = length;
            }
            // 更新最小索引
            if (currentIndex < minIndex) minIndex = currentIndex;
        }
        // 输出结果
        if (r == 0) cout << "No solution.\n";
        else cout << r << "\n";
    }
    return 0;
}
