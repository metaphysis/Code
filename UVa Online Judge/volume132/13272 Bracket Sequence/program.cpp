// Bracket Sequence
// UVa ID: 13272
// Verdict: Accepted
// Submission Date: 2025-11-29
// UVa Run Time: 0.020s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 检查两个字符是否匹配
bool isMatch(char left, char right) {
    return (left == '(' && right == ')') ||
           (left == '[' && right == ']') ||
           (left == '{' && right == '}') ||
           (left == '<' && right == '>');
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    cin.ignore(); // 忽略换行符
    
    for (int caseNum = 1; caseNum <= t; caseNum++) {
        string s;
        getline(cin, s);
        int n = s.length();
        
        vector<int> dp(n + 1, 0); // dp[i]表示从位置i开始的最长平衡序列长度
        
        // 从右向左处理
        for (int i = n - 1; i >= 0; i--) {
            // 如果是右括号，不能作为平衡序列的开头
            if (s[i] == ')' || s[i] == ']' || s[i] == '}' || s[i] == '>') {
                dp[i] = 0;
                continue;
            }
            
            // 对于左括号，检查是否能匹配
            int j = i + 1 + dp[i + 1]; // 跳过中间平衡部分后的位置
            
            if (j < n && isMatch(s[i], s[j])) {
                // 当前匹配的2个字符 + 中间部分 + 匹配后的部分
                dp[i] = 2 + dp[i + 1] + dp[j + 1];
            } else {
                dp[i] = 0;
            }
        }
        
        // 输出结果
        cout << "Case " << caseNum << ":\n";
        for (int i = 0; i < n; i++) {
            cout << dp[i] << "\n";
        }
    }
    
    return 0;
}
