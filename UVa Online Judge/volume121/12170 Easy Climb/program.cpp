// Easy Climb
// UVa ID: 12170
// Verdict: Accepted
// Submission Date: 2025-10-13
// UVa Run Time: 0.740s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const long long INF = (1LL << 60);

long long dynamicProgramming() {
    int n;
    long long d;
    cin >> n >> d;
    vector<long long> h(n);
    for (int i = 0; i < n; i++) cin >> h[i];
    // 可行性检查：如果起点终点高度差过大，直接返回不可能
    if (abs(h[0] - h[n - 1]) > (n - 1) * d) return -1;
    // 生成候选高度集合
    set<long long> candidate_set;
    for (int i = 0; i < n; i++) {
        for (int delta = -n; delta <= n; delta++) {
            long long candidate = h[i] + (long long)delta * d;
            if (candidate >= 0) candidate_set.insert(candidate);
        }
    }
    // 转换为有序向量
    vector<long long> candidates(candidate_set.begin(), candidate_set.end());
    int m = candidates.size();
    // DP数组：dp[i][j]表示第i个石堆高度为candidates[j]时的最小调整量
    vector<vector<long long>> dp(n, vector<long long>(m, INF));
    // 初始化第一个石堆
    for (int j = 0; j < m; j++) {
        if (candidates[j] == h[0]) {
            dp[0][j] = 0;
            break;
        }
    }
    // 动态规划：使用滑动窗口优化
    for (int i = 1; i < n; i++) {
        deque<int> dq;  // 双端队列维护滑动窗口最小值
        int k = 0;      // 窗口右边界指针
        for (int j = 0; j < m; j++) {
            // 扩展窗口：将所有candidates[k] <= candidates[j] + d的加入队列
            while (k < m && candidates[k] <= candidates[j] + d) {
                // 维护队列单调性：队尾大于等于当前值的出队
                while (!dq.empty() && dp[i - 1][dq.back()] >= dp[i - 1][k]) {
                    dq.pop_back();
                }
                dq.push_back(k);
                k++;
            }
            // 收缩窗口：移除candidates[dq.front()] < candidates[j] - d的
            while (!dq.empty() && candidates[dq.front()] < candidates[j] - d) {
                dq.pop_front();
            }
            // 状态转移
            if (!dq.empty()) {
                long long minVal = dp[i - 1][dq.front()];
                if (minVal < INF) {
                    dp[i][j] = minVal + abs(candidates[j] - h[i]);
                }
            }
        }
    }
    // 提取结果：最后一个石堆高度为h[n - 1]的最小调整量
    long long answer = INF;
    for (int j = 0; j < m; j++)
        if (candidates[j] == h[n - 1] && dp[n - 1][j] < answer)
            answer = dp[n - 1][j];
    return answer;
}

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int cases;
    cin >> cases;
    while (cases--) {
        long long result = dynamicProgramming();
        if (result == -1 || result >= INF) cout << "impossible" << endl;
        else cout << result << '\n';
    }
    return 0;
}
