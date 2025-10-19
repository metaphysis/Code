// Color Length
// UVa ID: 1625
// Verdict: Accepted
// Submission Date: 2025-10-19
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 5005;
const int INF = 0x3f3f3f3f;

int dp[MAXN][MAXN];
int firstA[26], lastA[26], firstB[26], lastB[26];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;
    while (T--) {
        string A, B;
        cin >> A >> B;
        int n = A.length(), m = B.length();

        // 初始化 first 和 last 数组
        for (int c = 0; c < 26; c++) {
            firstA[c] = firstB[c] = INF;
            lastA[c] = lastB[c] = -1;
        }

        // 预处理 A 中每种颜色的第一次和最后一次出现位置
        for (int i = 0; i < n; i++) {
            int ch = A[i] - 'A';
            if (firstA[ch] == INF) firstA[ch] = i;
            lastA[ch] = i;
        }
        
        // 预处理 B 中每种颜色的第一次和最后一次出现位置
        for (int i = 0; i < m; i++) {
            int ch = B[i] - 'A';
            if (firstB[ch] == INF) firstB[ch] = i;
            lastB[ch] = i;
        }

        // DP 数组初始化
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= m; j++) {
                dp[i][j] = INF;
            }
        }
        dp[0][0] = 0;

        // 动态规划主循环
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= m; j++) {
                if (i == 0 && j == 0) continue;

                // 计算 cost: 已经开始但未结束的颜色数量
                int cost = 0;
                for (int c = 0; c < 26; c++) {
                    bool started = false;  // 颜色是否已经开始
                    bool ended = true;     // 颜色是否已经结束

                    // 检查颜色是否已经开始
                    // 在 A 的前 i 个字符中出现过，或在 B 的前 j 个字符中出现过
                    if (i > 0 && firstA[c] != INF && firstA[c] < i) started = true;
                    if (j > 0 && firstB[c] != INF && firstB[c] < j) started = true;
                    
                    // 检查颜色是否已经结束
                    // 在 A 的剩余部分或 B 的剩余部分还会出现
                    if (i < n && lastA[c] != -1 && lastA[c] >= i) ended = false;
                    if (j < m && lastB[c] != -1 && lastB[c] >= j) ended = false;
                    
                    // 如果已经开始但未结束，则计入代价
                    if (started && !ended) cost++;
                }

                // 状态转移：从左边（A 串）取一个字符
                if (i > 0) {
                    dp[i][j] = min(dp[i][j], dp[i - 1][j] + cost);
                }
                // 状态转移：从上边（B 串）取一个字符
                if (j > 0) {
                    dp[i][j] = min(dp[i][j], dp[i][j - 1] + cost);
                }
            }
        }

        // 输出结果
        cout << dp[n][m] << "\n";
    }

    return 0;
}
