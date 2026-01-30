// Digit Blocks
// UVa ID: 11394
// Verdict: Accepted
// Submission Date: 2026-01-19
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

long long C[20][20];

void initialize() {
    for (int i = 0; i < 20; i++) {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; j++)
            C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
    }
}

// 将十六进制字符转换为数值
int hexCharToInt(char c) {
    if (isdigit(c)) return c - '0';
    return c - 'A' + 10;
}

long long solve(const string& blocks) {
    int n = blocks.size();
    // 统计每种数字的出现次数（1-15）
    vector<int> cnt(16, 0);
    for (char c : blocks) cnt[hexCharToInt(c)]++;
    // dp[j][k] = 当前和模5为j，选了k个数字的排列总数
    vector<vector<long long>> dp(5, vector<long long>(n + 1, 0));
    dp[0][0] = 1;
    // 处理每种数字
    for (int d = 1; d <= 15; d++) {
        if (cnt[d] == 0) continue;
        // 临时数组
        vector<vector<long long>> newDp(5, vector<long long>(n + 1, 0));
        // 遍历当前所有状态
        for (int r = 0; r < 5; r++) {
            for (int k = 0; k <= n; k++) {
                if (dp[r][k] == 0) continue;
                // 对于这种数字，可以选择t个（0 <= t <= cnt[d]）
                int maxT = min(cnt[d], n - k);
                for (int t = 0; t <= maxT; t++) {
                    int newR = (r + d * t) % 5;
                    int newK = k + t;
                    // 在newK个位置中选t个位置放数字d
                    newDp[newR][newK] += dp[r][k] * C[newK][t];
                }
            }
        }
        dp = move(newDp);
    }
    // 计算答案：所有模5为0且至少选1个数字的情况
    long long r = 0;
    for (int k = 1; k <= n; k++) r += dp[0][k];
    return r;
}

int main() {
    initialize(); // 预处理组合数
    string line;
    while (getline(cin, line)) {
        if (line == "#") break;
        cout << solve(line) << '\n';
    }
    return 0;
}
