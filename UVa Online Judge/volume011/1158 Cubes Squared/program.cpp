// Cubes Squared
// UVa ID: 1158
// Verdict: Accepted
// Submission Date: 2026-01-03
// UVa Run Time: 0.030s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 400000;
const int INF = 1e9;

vector<int> cubes;       // 所有立方数（i³）
vector<int> pyramids;    // 所有平方金字塔数（1²+2²+...+i²）
int dp[MAX_N + 1];       // dp[x] 表示堆放 x 个 hcube 所需的最少堆数

// 预处理所有可能的立方数和平方金字塔数
void preprocess() {
    // 立方数：i³ ≤ MAX_N
    for (int i = 1; i * i * i <= MAX_N; i++) cubes.push_back(i * i * i);
    // 平方金字塔数：1²+2²+...+i² ≤ MAX_N
    for (int i = 1; i * i <= MAX_N; i++) {
        int sum = i * (i + 1) * (2 * i + 1) / 6;  // 平方和公式
        if (sum > MAX_N) break;
        pyramids.push_back(sum);
    }
    // 初始化 dp 数组为无穷大
    fill(dp, dp + MAX_N + 1, INF);
    dp[0] = 0;  // 堆放 0 个 hcube 需要 0 堆
    // 完全背包动态规划
    for (int num : cubes)
        for (int j = num; j <= MAX_N; j++)
            if (dp[j - num] != INF) dp[j] = min(dp[j], dp[j - num] + 1);
    for (int num : pyramids)
        for (int j = num; j <= MAX_N; j++)
            if (dp[j - num] != INF) dp[j] = min(dp[j], dp[j - num] + 1);
}

int main() {
    preprocess();  // 预处理所有结果
    int n;
    while (cin >> n and n != -1) cout << dp[n] << endl;
    return 0;
}
