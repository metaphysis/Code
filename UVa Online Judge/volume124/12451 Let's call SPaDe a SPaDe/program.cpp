// Let's call SPaDe a SPaDe
// UVa ID: 12451
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.010s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 计算整数 x 的十进制位数 (x >= 2)
int digitCount(int x) {
    int cnt = 0;
    while (x > 0) {
        ++cnt;
        x /= 10;
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        string S;
        cin >> S;
        int n = (int)S.size();
        const int INF = 1e9;
        // cost[j][i] 表示子串 S[j..i-1] 整体压缩后的最短长度，若不可压缩则为 INF
        vector<vector<int>> cost(n, vector<int>(n + 1, INF));
        // 枚举起点 j 和周期 p，计算所有可压缩的块
        for (int j = 0; j < n; ++j) {
            // p 至少为 1，且需要至少两个周期，所以 p <= (n-j)/2
            for (int p = 1; p <= (n - j) / 2; ++p) {
                // 计算从 j 开始能连续匹配模式 S[j..j+p-1] 的最大长度 maxLen
                int maxLen = 0;
                while (j + maxLen < n && S[j + maxLen] == S[j + maxLen % p]) {
                    ++maxLen;
                }
                // 枚举重复次数 k (k >= 2)
                for (int k = 2; p * k <= maxLen; ++k) {
                    int len = p * k;
                    int curCost = 2 + p + digitCount(k); // 括号2个 + 子串长度 + 数字位数
                    if (curCost < cost[j][j + len]) {
                        cost[j][j + len] = curCost;
                    }
                }
            }
        }
        // 动态规划：dp[i] 表示前缀 S[0..i-1] 的最短压缩长度
        vector<int> dp(n + 1, INF);
        dp[0] = 0;
        for (int i = 1; i <= n; ++i) {
            // 不压缩当前字符，直接拼接
            dp[i] = dp[i - 1] + 1;
            // 尝试以 i 结尾的压缩块，起点 j
            for (int j = 0; j < i; ++j) {
                if (cost[j][i] != INF) {
                    dp[i] = min(dp[i], dp[j] + cost[j][i]);
                }
            }
        }
        cout << dp[n] << '\n';
    }
    return 0;
}
