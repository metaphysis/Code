// Surveillance
// UVa ID: 1707
// Verdict: Accepted
// Submission Date: 2025-12-05
// UVa Run Time: 2.800s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e6 + 10; // 注意：2 * n 可能达到 2e6
const int LOG = 22;        // 2^21 > 2e6

int n, k;
int maxReach[2 * MAXN]; // maxReach[i] = 从 ≤ i 的位置开始能覆盖到的最远位置
int dp[2 * MAXN][LOG];  // 倍增表

int main() {
    while (scanf("%d %d", &n, &k) == 2) {
        // 初始化
        for (int i = 1; i <= 2 * n; ++i)
            maxReach[i] = i;
        
        // 处理每个摄像头
        for (int i = 0; i < k; ++i) {
            int a, b;
            scanf("%d %d", &a, &b);
            if (a <= b) {
                // 区间 [a, b]
                maxReach[a] = max(maxReach[a], b);
                // 在链的复制部分也要更新
                if (a + n <= 2 * n)
                    maxReach[a + n] = max(maxReach[a + n], b + n);
            } else {
                // 区间 [a, b+n]（在环上覆盖了a到n和1到b）
                maxReach[a] = max(maxReach[a], b + n);
            }
        }
        
        // 计算前缀最大值
        for (int i = 2; i <= 2 * n; ++i)
            maxReach[i] = max(maxReach[i], maxReach[i - 1]);
        
        // 构建倍增表
        for (int i = 1; i <= 2 * n; ++i)
            dp[i][0] = maxReach[i] + 1; // 注意：+1是为了方便，表示选择这个区间后能到达的下一个位置
        
        // 如果dp[i][0]超过边界，设为2*n+1
        for (int i = 1; i <= 2 * n; ++i)
            if (dp[i][0] > 2 * n) dp[i][0] = 2 * n + 1;
        
        // 构建倍增表
        for (int j = 1; j < LOG; ++j)
            for (int i = 1; i <= 2 * n; ++i)
                if (dp[i][j - 1] <= 2 * n)
                    dp[i][j] = dp[dp[i][j - 1]][j - 1];
                else
                    dp[i][j] = 2 * n + 1;
        
        int ans = k + 1;
        
        // 检查每个起点
        for (int start = 1; start <= n; ++start) {
            int current = start;
            int steps = 0;
            
            // 使用倍增找到覆盖[start, start+n-1]所需的最小步数
            for (int j = LOG - 1; j >= 0; --j) {
                if (dp[current][j] < start + n) {
                    current = dp[current][j];
                    steps += (1 << j);
                }
            }
            
            // 再走一步
            current = dp[current][0];
            steps++;
            
            if (current <= start + n) {
                ans = min(ans, steps);
            }
        }
        
        if (ans > k)
            printf("impossible\n");
        else
            printf("%d\n", ans);
    }
    
    return 0;
}
