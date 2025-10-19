// Folding
// UVa ID: 1630
// Verdict: Accepted
// Submission Date: 2025-10-19
// UVa Run Time: 0.110s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

string fold(const string& s) {
    int n = s.size();
    vector<vector<string>> dp(n, vector<string>(n));
    
    // 初始化：长度为1的子串
    for (int i = 0; i < n; i++) {
        dp[i][i] = s[i];
    }
    
    // 枚举所有子串长度
    for (int len = 2; len <= n; len++) {
        for (int i = 0; i + len - 1 < n; i++) {
            int j = i + len - 1;
            // 初始化为原子串
            dp[i][j] = s.substr(i, len);
            
            // 1. 尝试分割点
            for (int k = i; k < j; k++) {
                string candidate = dp[i][k] + dp[k+1][j];
                if (candidate.size() < dp[i][j].size()) {
                    dp[i][j] = candidate;
                }
            }
            
            // 2. 尝试重复模式
            for (int l = 1; l < len; l++) {
                if (len % l == 0) {
                    bool repeat_ok = true;
                    // 检查是否满足重复条件
                    for (int pos = i; pos <= j; pos++) {
                        if (s[pos] != s[i + (pos - i) % l]) {
                            repeat_ok = false;
                            break;
                        }
                    }
                    if (repeat_ok) {
                        int times = len / l;
                        string candidate = to_string(times) + "(" + dp[i][i+l-1] + ")";
                        if (candidate.size() < dp[i][j].size()) {
                            dp[i][j] = candidate;
                        }
                    }
                }
            }
        }
    }
    return dp[0][n-1];
}

int main() {
    string line;
    while (getline(cin, line)) {
        if (line.empty()) continue;
        cout << fold(line) << endl;
    }
    return 0;
}
