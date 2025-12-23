// Moogle
// UVa ID: 11370
// Verdict: Accepted
// Submission Date: 2025-12-20
// UVa Run Time: 0.040s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

double solve() {
    int h, c;
    cin >> h >> c;
    vector<double> loc(h);
    for (int i = 0; i < h; i++) cin >> loc[i];
    
    // 计算误差矩阵：error[i][j] 表示存储点 i 和 j 之间（不包括 i, j）的误差和
    vector<vector<double>> error(h, vector<double>(h, 0.0));
    for (int i = 0; i < h; i++) {
        for (int j = i + 1; j < h; j++) {
            double sum = 0.0;
            for (int k = i + 1; k < j; k++) {
                // 计算房屋 k 的插值位置
                double interp = loc[i] + (loc[j] - loc[i]) * (k - i) / double(j - i);
                sum += fabs(interp - loc[k]); // 累加绝对误差
            }
            error[i][j] = sum;
        }
    }
    
    // dp[i][k]: 以房屋 i 作为第 k 个存储点的最小误差和
    vector<vector<double>> dp(h, vector<double>(c + 1, 1e30));
    dp[0][1] = 0.0; // 第一个房屋是第一个存储点，误差为0
    
    // 动态规划
    for (int i = 0; i < h; i++) {
        for (int k = 1; k <= c; k++) {
            if (dp[i][k] > 1e29) continue; // 不可达状态
            // 尝试将 i 作为当前最后一个存储点，选择下一个存储点 j
            for (int j = i + 1; j < h; j++) {
                if (k + 1 <= c) {
                    dp[j][k + 1] = min(dp[j][k + 1], dp[i][k] + error[i][j]);
                }
            }
        }
    }
    
    // 最后一个房屋必须是第 c 个存储点
    return dp[h - 1][c] / h;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(4);
    
    int t;
    cin >> t;
    while (t--) cout << solve() << "\n";
    
    return 0;
}
