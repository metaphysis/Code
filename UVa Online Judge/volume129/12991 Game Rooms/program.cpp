// Game Rooms
// UVa ID: 12991
// Verdict: Accepted
// Submission Date: 2025-10-24
// UVa Run Time: 0.550s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

typedef long long ll;

const ll INF = 1e18;  // 定义无穷大

/**
 * 计算区间 [L, R] 内所有玩家到目标楼层的距离和
 * @param L 区间左端点
 * @param R 区间右端点  
 * @param targetFloor 目标楼层
 * @param countSum 玩家数量的前缀和数组
 * @param weightedSum 玩家数量×楼层号的前缀和数组
 * @return 总距离代价
 */
ll calculateCost(int L, int R, int targetFloor, const vector<ll>& countSum, const vector<ll>& weightedSum) {
    if (L > R) return 0;  // 空区间代价为 0
    ll cnt = countSum[R] - countSum[L - 1];  // 区间内玩家总数
    ll weighted = weightedSum[R] - weightedSum[L - 1];  // 区间内玩家楼层加权和
    return abs(weighted - targetFloor * cnt);  // 计算总距离
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int testCases;
    cin >> testCases;
    for (int caseNum = 1; caseNum <= testCases; caseNum++) {
        int totalFloors;
        cin >> totalFloors;
        
        // 存储每层的乒乓球和台球玩家数量，下标从 1 开始
        vector<ll> tableTennisPlayers(totalFloors + 2, 0);
        vector<ll> poolPlayers(totalFloors + 2, 0);
        for (int i = 1; i <= totalFloors; i++) {
            cin >> tableTennisPlayers[i] >> poolPlayers[i];
        }
        
        // 前缀和数组初始化
        vector<ll> sumTableTennis(totalFloors + 2, 0);  // 乒乓球玩家前缀和
        vector<ll> sumPool(totalFloors + 2, 0);         // 台球玩家前缀和
        vector<ll> sumTableTennisWeighted(totalFloors + 2, 0);  // 乒乓球玩家×楼层号前缀和
        vector<ll> sumPoolWeighted(totalFloors + 2, 0);         // 台球玩家×楼层号前缀和
        
        // 计算前缀和
        for (int i = 1; i <= totalFloors; i++) {
            sumTableTennis[i] = sumTableTennis[i - 1] + tableTennisPlayers[i];
            sumPool[i] = sumPool[i - 1] + poolPlayers[i];
            sumTableTennisWeighted[i] = sumTableTennisWeighted[i - 1] + tableTennisPlayers[i] * i;
            sumPoolWeighted[i] = sumPoolWeighted[i - 1] + poolPlayers[i] * i;
        }
        
        // DP 数组：dp[i][type] 表示前 i 层，第 i 层类型为 type 的最小代价
        vector<vector<ll>> dp(totalFloors + 1, vector<ll>(2, INF));
        dp[0][0] = dp[0][1] = 0;  // 初始化
        
        // 主 DP 循环
        for (int i = 1; i <= totalFloors; i++) {
            for (int currentType = 0; currentType < 2; currentType++) {
                // 根据当前类型选择对应的前缀和数组
                const vector<ll>& otherCount = (currentType == 0) ? sumPool : sumTableTennis;
                const vector<ll>& otherWeighted = (currentType == 0) ? sumPoolWeighted : sumTableTennisWeighted;
                
                // 双指针优化：optimalMid 记录当前最优分割点
                int optimalMid = 0;
                for (int prevEnd = 0; prevEnd < i; prevEnd++) {
                    int L = prevEnd + 1;  // 当前段起始位置
                    int R = i;            // 当前段结束位置
                    
                    // 检查是否整栋楼只有一种类型（无效情况）
                    if (prevEnd == 0 && i == totalFloors) {
                        continue;
                    }
                    
                    ll cost = 0;  // 当前段的代价
                    
                    if (prevEnd == 0) {
                        // 第一段：所有玩家只能去右边的 R+1 层
                        cost = calculateCost(L, R, R + 1, otherCount, otherWeighted);
                    } else if (i == totalFloors) {
                        // 最后一段：所有玩家只能去左边的 prevEnd 层
                        cost = calculateCost(L, R, prevEnd, otherCount, otherWeighted);
                    } else {
                        // 中间段：使用双指针找到最优分割点
                        // 随着 R 增大，optimalMid 单调不减
                        while (optimalMid < R - 1) {
                            // 计算当前分割点的代价
                            ll currentCost = calculateCost(L, optimalMid, prevEnd, otherCount, otherWeighted) +
                                           calculateCost(optimalMid + 1, R, R + 1, otherCount, otherWeighted);
                            // 计算下一个分割点的代价
                            ll nextCost = calculateCost(L, optimalMid + 1, prevEnd, otherCount, otherWeighted) +
                                        calculateCost(optimalMid + 2, R, R + 1, otherCount, otherWeighted);
                            // 如果下一个分割点不更优，则停止移动
                            if (nextCost >= currentCost) break;
                            optimalMid++;
                        }
                        // 使用最优分割点计算总代价
                        cost = calculateCost(L, optimalMid, prevEnd, otherCount, otherWeighted) +
                              calculateCost(optimalMid + 1, R, R + 1, otherCount, otherWeighted);
                    }
                    
                    // 更新 DP 状态
                    dp[i][currentType] = min(dp[i][currentType], 
                                           dp[prevEnd][1 - currentType] + cost);
                }
            }
        }
        
        // 输出结果：取两种类型的较小值
        ll answer = min(dp[totalFloors][0], dp[totalFloors][1]);
        cout << "Case #" << caseNum << ": " << answer << "\n";
    }
    
    return 0;
}
