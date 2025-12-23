// The Uxuhul Voting System
// UVa ID: 10654
// Verdict: Accepted
// Submission Date: 2025-12-14
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 8种可能的结果字符串，索引0~7对应状态0~7
const string outcomes[] = {"NNN", "NNY", "NYN", "NYY", "YNN", "YNY", "YYN", "YYY"};

int main() {
    int n;
    cin >> n;
    while (n--) {
        int m;
        cin >> m;
        vector<vector<int>> preferences(m, vector<int>(8));
        // 读取每位祭司的偏好顺序
        for (int i = 0; i < m; i++) for (int j = 0; j < 8; j++) cin >> preferences[i][j];
        
        // dp[i][state] 表示从第i位祭司开始，当前状态为state时，最终结果的编号
        vector<vector<int>> dp(m + 1, vector<int>(8, 0));
        // 边界：最后一位祭司之后，状态即最终结果
        for (int state = 0; state < 8; state++) dp[m][state] = state;
        
        // 逆序DP，从最后一位祭司往前推
        for (int i = m - 1; i >= 0; i--) {
            for (int state = 0; state < 8; state++) {
                int bestPreference = INT_MAX;  // 偏好值越小越好
                int bestOutcome = -1;
                // 尝试翻转三块石头中的一块
                for (int flip = 0; flip < 3; flip++) {
                    int nextState = state ^ (1 << flip);  // 翻转第flip位
                    int finalOutcome = dp[i + 1][nextState];  // 后续祭司的最终结果
                    // 选择对自己最有利的（偏好值最小）
                    if (preferences[i][finalOutcome] < bestPreference) {
                        bestPreference = preferences[i][finalOutcome];
                        bestOutcome = finalOutcome;
                    }
                }
                dp[i][state] = bestOutcome;
            }
        }
        
        // 输出从第一位祭司、初始状态0（NNN）开始的最终结果
        cout << outcomes[dp[0][0]] << endl;
    }
    return 0;
}
