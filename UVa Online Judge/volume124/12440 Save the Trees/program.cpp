// Save the Trees
// UVa ID: 12440
// Verdict: Accepted
// Submission Date: 2026-05-19
// UVa Run Time: 0.300s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010;
const long long INF = 1e18;

int main() {
    int T;
    scanf("%d", &T);
    for (int cas = 1; cas <= T; cas++) {
        int n;
        scanf("%d", &n);
        
        vector<int> type(n + 1), height(n + 1);
        for (int i = 1; i <= n; i++) 
            scanf("%d %d", &type[i], &height[i]);
        
        map<int, int> lastPos;  // 记录每个 type 最后出现的位置
        vector<long long> dp(n + 1, INF);
        dp[0] = 0;
        
        deque<int> dq;  // 单调队列，存储下标
        int L = 0;      // 当前合法的左边界
        
        for (int i = 1; i <= n; i++) {
            // 更新左边界 L = max(L, lastPos[type[i]])
            if (lastPos.find(type[i]) != lastPos.end())
                L = max(L, lastPos[type[i]]);
            lastPos[type[i]] = i;
            
            // 移除队列中下标 <= L 的元素（这些左边界已经不合法）
            while (!dq.empty() && dq.front() <= L) 
                dq.pop_front();
            
            // 维护单调递减队列：移除队尾高度 <= 当前高度的元素
            while (!dq.empty() && height[dq.back()] <= height[i]) 
                dq.pop_back();
            
            // 将当前树加入队列
            dq.push_back(i);
            
            // 遍历队列计算 dp[i]
            dp[i] = INF;
            // 情况1：第一段直接从 L+1 开始（即左边界为 L 的情况）
            dp[i] = min(dp[i], dp[L] + height[dq.front()]);
            
            // 情况2：对于队列中相邻的两个元素
            for (size_t j = 1; j < dq.size(); j++) {
                int pos = dq[j];      // 当前段的最大值位置
                int prevPos = dq[j-1]; // 上一个位置
                dp[i] = min(dp[i], dp[prevPos] + height[pos]);
            }
        }
        
        printf("Case %d: %lld\n", cas, dp[n]);
    }
    return 0;
}
