// License Plates
// UVa ID: 13257
// Verdict: Accepted
// Submission Date: 2025-12-13
// UVa Run Time: 0.910s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    while (T--) {
        string S;
        cin >> S;
        
        // dp1[i]: 以字母 i 结尾的长度为 1 的子序列数量（实际上只有 0 或 1）
        int dp1[26] = {0};
        // dp2[i][j]: 以字母 i,j 结尾的长度为 2 的子序列数量
        long long dp2[26][26] = {0};
        // dp3[i][j][k]: 以字母 i,j,k 结尾的长度为 3 的子序列数量
        long long dp3[26][26][26] = {0};
        
        for (char ch : S) {
            int c = ch - 'A';
            
            // 更新长度为 3 的子序列
            for (int a = 0; a < 26; ++a) {
                for (int b = 0; b < 26; ++b) {
                    if (dp2[a][b] > 0) {
                        dp3[a][b][c] += dp2[a][b];
                    }
                }
            }
            
            // 更新长度为 2 的子序列
            for (int a = 0; a < 26; ++a) {
                if (dp1[a] > 0) {
                    dp2[a][c] += dp1[a];
                }
            }
            
            // 更新长度为 1 的子序列
            dp1[c] = 1;
        }
        
        // 统计所有不同的长度为 3 的子序列数量
        long long ans = 0;
        for (int a = 0; a < 26; ++a) {
            for (int b = 0; b < 26; ++b) {
                for (int c = 0; c < 26; ++c) {
                    if (dp3[a][b][c] > 0) {
                        ans += 1; // 每个不同的三字母组合只计一次
                    }
                }
            }
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
