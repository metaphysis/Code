// Binomial Coefficients
// UVa ID: 1649
// Verdict: Accepted
// Submission Date: 2025-12-26
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const double EPS = 1e-12;  // 更小的误差阈值

int main() {
    int t; cin >> t;
    while (t--) {
        ll m; cin >> m;
        vector<pair<ll, ll>> answer;
        // 加入边界解
        answer.push_back({m, 1});
        answer.push_back({m, m - 1});
        // 预先计算 log(2), log(3), ..., log(60)
        vector<double> log_fact(61, 0);
        for (int i = 2; i <= 60; i++) log_fact[i] = log_fact[i - 1] + log(i);
        double log_m = log(m);
        // 枚举 k 从 2 到 60
        for (ll k = 2; k <= 60; k++) {
            // 计算 log(m × k!) = log(m) + log(k!)
            double target_log = log_m + log_fact[k];
            // 计算 (m × k!)^(1/k) = exp(target_log / k)
            double target_root = exp(target_log / k);
            // 估算 n：n ≈ target_root + (k-1)/2
            ll est = llround(target_root) + (k - 1) / 2;
            if (est < k) break;
            // 搜索范围：在估计值附近小范围搜索
            // 因为浮点数估计通常很准确
            ll left = max(k, est - 3), right = est + 3;
            for (ll n = left; n <= right; n++) {
                // 快速计算 log(n × (n-1) × ... × (n-k+1))
                // 这等于 log(n!) - log((n-k)!)
                double product_log = 0.0;
                for (ll i = 0; i < k; i++) product_log += log(n - i);
                // 浮点数匹配检查
                if (fabs(product_log - target_log) < EPS) {
                    answer.push_back({n, k});
                    if (k != n - k) answer.push_back({n, n - k});
                    break;
                }
            }
        }
        // 排序去重
        sort(answer.begin(), answer.end());
        answer.erase(unique(answer.begin(), ans.end()), ans.end());
        // 输出
        cout << ans.size() << "\n";
        if (!ans.empty()) {
            for (size_t i = 0; i < ans.size(); i++) {
                cout << "(" << ans[i].first << "," << ans[i].second << ")";
                if (i + 1 < ans.size()) cout << " ";
            }
            cout << "\n";
        } else cout << "\n";
    }
    return 0;
}
