// Series-Parallel Networks
// UVa ID: 10253
// Verdict: Accepted
// Submission Date: 2025-11-05
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;

/**
 * @brief 计算组合数 C(n, k)
 * @param n 总数
 * @param k 选择数
 * @return 组合数结果
 */
ll combinations(ll n, ll k) {
    if (k > n) return 0;
    if (k == 0 || k == n) return 1;
    
    // 利用对称性 C(n,k) = C(n,n-k) 减少计算量
    if (k > n - k) k = n - k;
    
    ll result = 1;
    for (ll i = 1; i <= k; i++) {
        result = result * (n - i + 1) / i;
    }
    return result;
}

int main() {
    const int MAX_N = 30;
    vector<ll> treeCount(MAX_N + 1, 0);  // treeCount[n]: n个叶子的树的数量
    
    // 基本情况：只有1个叶子的树只有1种（单节点）
    treeCount[1] = 1;
    
    // 计算从2到MAX_N个叶子的树的数量
    for (int leafCount = 2; leafCount <= MAX_N; leafCount++) {
        /**
         * dp[maxSubtreeSize][totalLeaves]: 
         * 使用最大子树大小不超过maxSubtreeSize，总共需要totalLeaves个叶子的方案数
         */
        vector<vector<ll>> dp(leafCount + 1, vector<ll>(leafCount + 1, 0));
        
        // 初始化：没有叶子时只有1种方案（空树）
        for (int i = 0; i <= leafCount; i++) {
            dp[i][0] = 1;
        }
        
        // 动态规划计算
        for (int maxSubtreeSize = 1; maxSubtreeSize < leafCount; maxSubtreeSize++) {
            for (int totalLeaves = 1; totalLeaves <= leafCount; totalLeaves++) {
                // 初始值：不使用大小为maxSubtreeSize的子树
                dp[maxSubtreeSize][totalLeaves] = dp[maxSubtreeSize - 1][totalLeaves];
                
                // 尝试使用p棵大小为maxSubtreeSize的子树
                // 每棵这样的子树有treeCount[maxSubtreeSize]种可能
                for (int subtreeCount = 1; subtreeCount * maxSubtreeSize <= totalLeaves; subtreeCount++) {
                    if (treeCount[maxSubtreeSize] > 0) {
                        // 从treeCount[maxSubtreeSize]种树中选择subtreeCount棵（可重复选择）
                        ll waysToChooseSubtrees = combinations(
                            treeCount[maxSubtreeSize] + subtreeCount - 1, subtreeCount);
                        
                        // 剩余叶子用更小的子树填充
                        ll remainingLeaves = totalLeaves - subtreeCount * maxSubtreeSize;
                        dp[maxSubtreeSize][totalLeaves] += 
                            waysToChooseSubtrees * dp[maxSubtreeSize - 1][remainingLeaves];
                    }
                }
            }
        }
        
        // leafCount个叶子的树数量 = 使用最大子树不超过leafCount-1的情况
        treeCount[leafCount] = dp[leafCount - 1][leafCount];
    }
    
    // 处理输入输出
    int edgeCount;
    while (cin >> edgeCount && edgeCount != 0) {
        if (edgeCount == 1) {
            // 特殊情况：只有1条边，只有1种网络
            cout << 1 << endl;
        } else {
            /**
             * 最终答案 = 树的数量 × 2
             * 因为每个树结构对应两种网络：
             * - 根节点为串联操作
             * - 根节点为并联操作
             */
            cout << treeCount[edgeCount] * 2 << endl;
        }
    }
    
    return 0;
}
