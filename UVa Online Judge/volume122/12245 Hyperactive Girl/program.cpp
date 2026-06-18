// Hyperactive Girl
// UVa ID: 12245
// Verdict: Accepted
// Submission Date: 2026-06-17
// UVa Run Time: 0.040s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MOD = 100000000;

struct Interval {
    int s, f;
};

int main() {
    int M, N;
    while (cin >> M >> N && (M != 0 || N != 0)) {
        vector<Interval> acts(N);
        for (int i = 0; i < N; ++i)
            cin >> acts[i].s >> acts[i].f;
        
        // 按左端点排序，便于保证左端点严格递增的条件
        sort(acts.begin(), acts.end(), [](const Interval& a, const Interval& b) {
            if (a.s != b.s) return a.s < b.s;
            return a.f < b.f;
        });
        
        // dp[i][j]：以 i 和 j 为最后两个区间的极小覆盖路径数
        vector<vector<int>> dp(N, vector<int>(N, 0));
        int r = 0;
        
        // 初始化：只有两个区间的路径
        for (int i = 0; i < N; ++i) {
            if (acts[i].s != 0) continue;  // 第一个区间必须从0开始
            for (int j = 0; j < N; ++j) {
                if (i == j) continue;
                if (acts[i].s < acts[j].s &&          // 左端点严格递增
                    acts[i].f >= acts[j].s &&         // 能接上
                    acts[i].f < acts[j].f) {          // 右端点严格递增
                    dp[i][j] = 1;
                }
            }
        }
        
        // DP 转移
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (dp[i][j] == 0) continue;
                for (int k = 0; k < N; ++k) {
                    if (k == i || k == j) continue;
                    // 左端点严格递增
                    if (acts[j].s >= acts[k].s) continue;
                    // 能接上
                    if (acts[j].f < acts[k].s) continue;
                    // 右端点严格递增
                    if (acts[j].f >= acts[k].f) continue;
                    // 极小性条件：区间 j 必须必要，即 F[i] < S[k]
                    if (acts[i].f >= acts[k].s) continue;
                    
                    dp[j][k] += dp[i][j];
                    if (dp[j][k] >= MOD) dp[j][k] -= MOD;
                }
            }
        }
        
        // 统计答案：所有 F[j] >= M 的路径
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (acts[j].f >= M) {
                    r += dp[i][j];
                    r %= MOD;
                }
            }
        }
        
        // 特殊情况：单个区间就能覆盖 [0, M]
        for (int i = 0; i < N; ++i) {
            if (acts[i].s == 0 && acts[i].f >= M) {
                r += 1;
                r %= MOD;
            }
        }
        
        cout << r % MOD << endl;
    }
    return 0;
}
