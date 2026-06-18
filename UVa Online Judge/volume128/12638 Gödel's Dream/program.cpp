// Gödel's Dream
// UVa ID: 12638
// Verdict: Accepted
// Submission Date: 2026-06-17
// UVa Run Time: 0.210s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    string s;
    while (cin >> s) {
        int n = (int)s.size();
        vector<int> dp(n + 1, -1);
        dp[0] = 0;
        
        for (int i = 0; i < n; ++i) {
            if (dp[i] == -1) continue;
            int L = 1, R = 1; // 当前可能的 need 值区间 [L, R]
            for (int j = i; j < n; ++j) {
                char ch = s[j];
                bool canZero = false;
                int newL, newR;
                
                if (ch == '1') {
                    // 遇到 '1'：need 增加 1
                    newL = L + 1;
                    newR = R + 1;
                    canZero = false;
                } else if (ch == '0') {
                    // 遇到 '0'：need 减少 1
                    if (L == 1) canZero = true; // need=1 减 1 得 0
                    else canZero = false;
                    
                    if (L <= 1) {
                        // need=1 会变成 0，只有 need>=2 才能保留为正整数
                        if (R >= 2) {
                            newL = 1;
                            newR = R - 1;
                        } else {
                            newL = INF;
                            newR = -INF; // 空状态
                        }
                    } else {
                        newL = L - 1;
                        newR = R - 1;
                    }
                } else { // ch == '?'
                    // '?' 可以选择变成 '0' 或 '1'
                    canZero = (L == 1); // 若 need=1，选择 '0' 可得 0
                    
                    // 计算选择 '0'（减 1）的部分
                    int left1, right1;
                    if (L >= 2) {
                        left1 = L - 1;
                        right1 = R - 1;
                    } else {
                        // L == 1，need=1 减 1 得 0，不保留
                        if (R >= 2) {
                            left1 = 1;
                            right1 = R - 1;
                        } else {
                            left1 = INF;
                            right1 = -INF;
                        }
                    }
                    
                    // 计算选择 '1'（加 1）的部分
                    int left2 = L + 1;
                    int right2 = R + 1;
                    
                    // 合并两个区间
                    if (left1 <= right1) {
                        newL = min(left1, left2);
                        newR = max(right1, right2);
                    } else {
                        newL = left2;
                        newR = right2;
                    }
                }
                
                // 如果 0 可达，说明当前子串 s[i..j] 可以成为一个 h 序列
                if (canZero) {
                    dp[j + 1] = max(dp[j + 1], dp[i] + 1);
                }
                
                L = newL;
                R = newR;
                
                // 状态为空，无法继续扩展
                if (L > R) break;
            }
        }
        
        cout << (dp[n] == -1 ? 0 : dp[n]) << '\n';
    }
    return 0;
}
