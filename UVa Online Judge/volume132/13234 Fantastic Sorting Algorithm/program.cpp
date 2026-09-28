#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while (cin >> n) {
        vector<long long> a(n + 1);
        for (int i = 1; i <= n; ++i) cin >> a[i];
        // 前缀和
        vector<long long> pre(n + 1, 0);
        for (int i = 1; i <= n; ++i) pre[i] = pre[i - 1] + a[i];
        // dp[i]：前 i 个数最多能分成的段数
        vector<int> dp(n + 1, 0);
        // last[i]：在 dp[i] 最大时，最后一段的最小和
        vector<long long> last(n + 1, 0);
        // key[i] = pre[i] + last[i]
        vector<long long> key(n + 1, 0);
        deque<int> q;
        q.push_back(0);
        int best_j = 0;
        for (int i = 1; i <= n; ++i) {
            // 找到满足 key[j] <= pre[i] 的最大 j
            while (!q.empty() && key[q.front()] <= pre[i]) {
                best_j = q.front();
                q.pop_front();
            }
            dp[i] = dp[best_j] + 1;
            last[i] = pre[i] - pre[best_j];
            key[i] = pre[i] + last[i];
            // 维护单调队列（key 递增）
            while (!q.empty() && key[q.back()] >= key[i]) q.pop_back();
            q.push_back(i);
        }
        // 最小操作次数 = n - 最大段数
        cout << n - dp[n] << '\n';
    }
    return 0;
}
