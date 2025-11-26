// Matryoshka
// UVa ID: 1579
// Verdict: Accepted
// Submission Date: 2025-11-26
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;
const int MAXN = 512;
int dolls[MAXN];
int dp[MAXN][MAXN];
bool complete[MAXN][MAXN];
int dp2[MAXN];

int main() {
    int n;
    while (cin >> n) {
        // 读取输入数据
        for (int i = 0; i < n; i++) cin >> dolls[i];
        
        // 初始化DP数组
        memset(dp, 0x3f, sizeof(dp));
        for (int i = 0; i < n; i++) dp[i][i] = 0;
        
        // 第一阶段：计算合并任意区间的最小代价
        for (int len = 2; len <= n; len++) {
            for (int l = 0; l + len - 1 < n; l++) {
                int r = l + len - 1;
                for (int k = l; k < r; k++) {
                    int open = 0;
                    int minL = INF, minR = INF;
                    
                    // 找到左右两部分的最小值
                    for (int p = l; p <= k; p++) minL = min(minL, dolls[p]);
                    for (int p = k + 1; p <= r; p++) minR = min(minR, dolls[p]);
                    
                    // 计算需要打开的玩偶数量
                    // 左边部分中大于右边最小值的玩偶都需要打开
                    for (int p = l; p <= k; p++) open += (dolls[p] > minR);
                    // 右边部分中大于左边最小值的玩偶都需要打开
                    for (int p = k + 1; p <= r; p++) open += (dolls[p] > minL);
                    
                    // 更新DP值
                    dp[l][r] = min(dp[l][r], dp[l][k] + dp[k + 1][r] + open);
                }
            }
        }
        
        // 检查哪些区间能形成完整的套娃套装
        memset(complete, 0, sizeof(complete));
        for (int len = 1; len <= n; len++) {
            for (int l = 0; l + len - 1 < n; l++) {
                int r = l + len - 1;
                int m = len; // 套装大小应为区间长度
                vector<bool> used(m + 1, false);
                bool ok = true;
                
                // 检查区间是否包含1到m的每个尺寸恰好一次
                for (int k = l; k <= r && ok; k++) {
                    if (dolls[k] > m) {
                        ok = false;  // 尺寸超出范围
                        break;
                    }
                    if (used[dolls[k]]) {
                        ok = false;  // 重复尺寸
                        break;
                    }
                    used[dolls[k]] = true;
                }
                complete[l][r] = ok;
            }
        }
        
        // 第二阶段：计算全局最优解
        memset(dp2, 0x3f, sizeof(dp2));
        dp2[0] = complete[0][0] ? dp[0][0] : INF;
        
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                if (complete[i][j]) {
                    int cost = dp[i][j];
                    if (i > 0) {
                        if (dp2[i - 1] != INF) {
                            cost += dp2[i - 1];
                        } else {
                            continue;
                        }
                    }
                    dp2[j] = min(dp2[j], cost);
                }
            }
        }
        
        // 输出结果
        if (dp2[n - 1] == INF) cout << "impossible" << endl;
        else cout << dp2[n - 1] << endl;
    }
    return 0;
}
