// Palindrome
// UVa ID: 12960
// Verdict: Accepted
// Submission Date: 2025-10-09
// UVa Run Time: 0.310s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char* argv[]) {
    // 加速输入输出
    cin.tie(0), cout.tie(0), ios_base::sync_with_stdio(false);

    string s;
    while (cin >> s) {
        int n = s.length();
        int N;
        cin >> N;
        
        // 标记特殊位置（从0开始索引）
        vector<bool> special(n, false);
        for (int i = 0; i < N; i++) {
            int pos;
            cin >> pos;
            special[pos - 1] = true;  // 输入位置从1开始，转换为从0开始
        }
        
        // dp[i][j] = (特殊位置数量, 回文子序列长度)
        vector<vector<pair<int, int>>> dp(n, vector<pair<int, int>>(n, {0, 0}));
        
        // 初始化：长度为1的子串
        for (int i = 0; i < n; i++) {
            dp[i][i] = {special[i] ? 1 : 0, 1};  // 单个字符本身就是回文
        }
        
        // 处理长度为2的子串
        for (int i = 0; i < n - 1; i++) {
            if (s[i] == s[i + 1]) {
                // 两端字符相同，可以形成长度为2的回文
                int cnt = special[i] + special[i + 1];  // 统计特殊位置数量
                dp[i][i + 1] = {cnt, 2};
            } else {
                // 两端字符不同，取左右单个字符中较优的
                dp[i][i + 1] = max(dp[i][i], dp[i + 1][i + 1]);
            }
        }
        
        // 处理长度从3到n的子串
        for (int len = 3; len <= n; len++) {
            for (int i = 0; i + len - 1 < n; i++) {
                int j = i + len - 1;  // 子串结束位置
                
                // 情况1：不包含左端字符
                // 情况2：不包含右端字符
                dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
                
                // 情况3：两端字符相同，可以包含两端
                if (s[i] == s[j]) {
                    // 获取内部子串的最优解
                    pair<int, int> inside = (i + 1 <= j - 1) ? dp[i + 1][j - 1] : make_pair(0, 0);
                    // 计算两端新增的特殊位置数量
                    int add_special = (special[i] ? 1 : 0) + (special[j] ? 1 : 0);
                    // 构建候选解：长度+2，特殊位置数量相应增加
                    pair<int, int> candidate = {inside.first + add_special, inside.second + 2};
                    // 更新最优解
                    dp[i][j] = max(dp[i][j], candidate);
                }
            }
        }
        
        // 输出整个字符串的最优回文子序列长度
        cout << dp[0][n - 1].second << "\n";
    }
    
    return 0;
}

