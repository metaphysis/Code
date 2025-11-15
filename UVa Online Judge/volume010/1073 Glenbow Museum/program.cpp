// Glenbow Museum
// UVa ID: 1073
// Verdict: Accepted
// Submission Date: 2025-11-06
// UVa Run Time: 0.120s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net


#include <iostream>
#include <cstring>
using namespace std;

long long dp[1010][1010][2]; // dp[pos][r_count][last_is_O]

long long solve(int L) {
    if (L < 4 || L % 2 != 0) return 0;
    
    int R_count = (L + 4) / 2;
    int O_count = (L - 4) / 2;
    
    if (R_count < 0 || O_count < 0) return 0;
    
    long long result = 0;
    
    // 情况1：以 R 开头
    memset(dp, 0, sizeof(dp));
    dp[1][1][0] = 1;
    
    for (int i = 1; i < L; i++) {
        for (int r = 0; r <= i; r++) {
            for (int lastO = 0; lastO <= 1; lastO++) {
                if (dp[i][r][lastO] == 0) continue;
                
                int o_used = i - r;
                
                // 下一个是 R
                if (r + 1 <= R_count) {
                    dp[i + 1][r + 1][0] += dp[i][r][lastO];
                }
                
                // 下一个是 O（不能连续两个 O）
                if (!lastO && o_used + 1 <= O_count) {
                    dp[i + 1][r][1] += dp[i][r][lastO];
                }
            }
        }
    }
    
    // 以 R 开头，结尾可以是 R 或 O
    long long case1 = 0;
    for (int lastO = 0; lastO <= 1; lastO++) {
        case1 += dp[L][R_count][lastO];
    }
    
    // 情况2：以 O 开头
    if (O_count > 0) {
        memset(dp, 0, sizeof(dp));
        dp[1][0][1] = 1;
        
        for (int i = 1; i < L; i++) {
            for (int r = 0; r <= i; r++) {
                for (int lastO = 0; lastO <= 1; lastO++) {
                    if (dp[i][r][lastO] == 0) continue;
                    
                    int o_used = i - r;
                    
                    // 下一个是 R
                    if (r + 1 <= R_count) {
                        dp[i + 1][r + 1][0] += dp[i][r][lastO];
                    }
                    
                    // 下一个是 O（不能连续两个 O）
                    if (!lastO && o_used + 1 <= O_count) {
                        dp[i + 1][r][1] += dp[i][r][lastO];
                    }
                }
            }
        }
        
        // 以 O 开头，必须以 R 结尾
        long long case2 = dp[L][R_count][0];
        result = case1 + case2;
    } else {
        result = case1;
    }
    
    return result;
}

int main() {
    int L;
    int caseNum = 1;
    
    while (cin >> L && L != 0) {
        long long ans = solve(L);
        cout << "Case " << caseNum << ": " << ans << endl;
        caseNum++;
    }
    
    return 0;
}
