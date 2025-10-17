// Cyborg Genes
// UVa ID: 10723
// Verdict: Accepted
// Submission Date: 2025-10-17
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    int T;
    cin >> T;
    cin.ignore(); // 忽略换行符
    
    for (int t = 1; t <= T; t++) {
        string s1, s2;
        getline(cin, s1);
        getline(cin, s2);
        
        int n = s1.length();
        int m = s2.length();
        
        // dp_len[i][j] 表示 s1[0..i-1] 和 s2[0..j-1] 的最短公共超序列长度
        vector<vector<int>> dp_len(n + 1, vector<int>(m + 1, 0));
        // dp_cnt[i][j] 表示对应的不同最短公共超序列的数量
        vector<vector<long long>> dp_cnt(n + 1, vector<long long>(m + 1, 0));
        
        // 初始化：当其中一个字符串为空时
        for (int i = 0; i <= n; i++) {
            dp_len[i][0] = i;  // 超序列就是 s1 的前 i 个字符
            dp_cnt[i][0] = 1;  // 只有一种方式
        }
        for (int j = 0; j <= m; j++) {
            dp_len[0][j] = j;  // 超序列就是 s2 的前 j 个字符
            dp_cnt[0][j] = 1;  // 只有一种方式
        }
        
        // 动态规划填表
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (s1[i - 1] == s2[j - 1]) {
                    // 字符相同，只需在超序列中出现一次
                    dp_len[i][j] = dp_len[i - 1][j - 1] + 1;
                    dp_cnt[i][j] = dp_cnt[i - 1][j - 1];
                } else {
                    // 字符不同，比较两种选择
                    int len1 = dp_len[i - 1][j] + 1; // 取 s1 的当前字符
                    int len2 = dp_len[i][j - 1] + 1; // 取 s2 的当前字符
                    
                    if (len1 < len2) {
                        // 取 s1 的字符更优
                        dp_len[i][j] = len1;
                        dp_cnt[i][j] = dp_cnt[i - 1][j];
                    } else if (len2 < len1) {
                        // 取 s2 的字符更优
                        dp_len[i][j] = len2;
                        dp_cnt[i][j] = dp_cnt[i][j - 1];
                    } else {
                        // 两种选择都能得到最短长度，方案数相加
                        dp_len[i][j] = len1;
                        dp_cnt[i][j] = dp_cnt[i - 1][j] + dp_cnt[i][j - 1];
                    }
                }
            }
        }
        
        // 输出结果
        cout << "Case #" << t << ": " << dp_len[n][m] << " " << dp_cnt[n][m] << endl;
    }
    
    return 0;
}
