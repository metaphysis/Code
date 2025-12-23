#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1005;
const int MAX_S = 25;
const int INF = 0x3f3f3f3f;

int dp[MAX_N][MAX_S];

// 预处理所有 dp[n][s] 的值
void precompute() {
    // 初始化：没有数字需要猜的情况
    for (int s = 0; s < MAX_S; ++s) dp[0][s] = 0;
    // 初始化：不能承受任何 strike 的情况
    for (int n = 1; n < MAX_N; ++n) dp[n][0] = n;
    
    // 动态规划递推
    for (int n = 1; n < MAX_N; ++n) {
        for (int s = 1; s < MAX_S; ++s) {
            int best = INF;
            // 尝试所有可能的猜测位置 k
            for (int k = 0; k < n; ++k) {
                int strikePart = dp[k][s - 1];      // 猜大后的情况
                int smilePart = dp[n - k - 1][s];   // 猜小后的情况
                int worst = 1 + max(strikePart, smilePart);
                if (worst < best) best = worst;
            }
            dp[n][s] = best;
        }
    }
}

int main() {
    precompute();  // 预先计算
    int c, n, S;
    cin >> c;
    while (c--) {
        cin >> n >> S;
        int s = S - 1;  // Bob 最多能承受的 strike 次数
        if (s < 0) s = 0;  // 安全处理边界
        cout << dp[n][s] << endl;
    }
    return 0;
}
