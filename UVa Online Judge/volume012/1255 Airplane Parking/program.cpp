// Airplane Parking
// UVa ID: 1255
// Verdict: Accepted
// Submission Date: 2025-10-10
// UVa Run Time: 0.100s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char* argv[]) {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<pair<int, int>> planes(n);
        vector<int> times;
        // 读取输入并收集所有时间点
        for (int i = 0; i < n; i++) {
            cin >> planes[i].first >> planes[i].second;
            times.push_back(planes[i].first);
            times.push_back(planes[i].second);
        }
        // 离散化
        sort(times.begin(), times.end());
        times.erase(unique(times.begin(), times.end()), times.end());
        int sz = times.size();
        map<int, int> comp;
        for (int i = 0; i < sz; i++) {
            comp[times[i]] = i;
        }
        // 初始化计数数组
        vector<vector<int>> cnt(sz, vector<int>(sz, 0));
        for (int i = 0; i < n; i++) {
            int start = comp[planes[i].first];
            int end = comp[planes[i].second];
            cnt[start][end]++;
        }
        // 区间DP
        vector<vector<int>> dp(sz, vector<int>(sz, 0));
        for (int len = 2; len <= sz; len++) {
            for (int i = 0; i + len <= sz; i++) {
                int j = i + len - 1;
                // 初始值：当前区间端点对应的飞机数量
                dp[i][j] = cnt[i][j];
                // 枚举分割点
                for (int k = i + 1; k < j; k++) {
                    dp[i][j] = max(dp[i][j], dp[i][k] + dp[k][j] + cnt[i][j]);
                }
                // 也考虑不包含端点飞机的情况
                dp[i][j] = max(dp[i][j], dp[i + 1][j]);
                dp[i][j] = max(dp[i][j], dp[i][j - 1]);
            }
        }
        cout << dp[0][sz - 1] << '\n';
    }
    return 0;
}
