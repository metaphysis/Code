// Dance Dance Revolution
// UVa ID: 1291
// Verdict: Accepted
// Submission Date: 2025-12-01
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;
int cost[5][5]; // 预计算体力消耗表

// 初始化体力消耗表
void initCost() {
    // 初始化全部为0
    for (int i = 0; i < 5; i++) 
        for (int j = 0; j < 5; j++) 
            cost[i][j] = 0;
    
    // 中心点到边点：2
    for (int i = 1; i <= 4; i++) 
        cost[0][i] = cost[i][0] = 2;
    
    // 相邻边点：3
    cost[1][2] = cost[2][1] = 3;
    cost[2][3] = cost[3][2] = 3;
    cost[3][4] = cost[4][3] = 3;
    cost[4][1] = cost[1][4] = 3;
    
    // 相对边点：4
    cost[1][3] = cost[3][1] = 4;
    cost[2][4] = cost[4][2] = 4;
    
    // 原地踩踏：1
    for (int i = 0; i < 5; i++) 
        cost[i][i] = 1;
}

int main() {
    initCost(); // 初始化体力消耗表
    vector<int> steps; // 存储当前指令序列
    int step;
    
    while (cin >> step) {
        if (step == 0) {
            // 遇到0表示一组数据结束
            if (steps.empty()) 
                break; // 单独0表示输入结束
            
            // dp[l][r]表示当前左脚在l、右脚在r的最小体力
            vector<vector<int>> dp(5, vector<int>(5, INF));
            dp[0][0] = 0; // 初始状态：双脚在中心点
            
            // 处理每个指令
            for (int s : steps) {
                vector<vector<int>> ndp(5, vector<int>(5, INF));
                for (int l = 0; l < 5; l++) {
                    for (int r = 0; r < 5; r++) {
                        if (dp[l][r] != INF) {
                            // 尝试移动左脚到s
                            if (r != s) // 右脚不能在目标点上
                                ndp[s][r] = min(ndp[s][r], dp[l][r] + cost[l][s]);
                            // 尝试移动右脚到s
                            if (l != s) // 左脚不能在目标点上
                                ndp[l][s] = min(ndp[l][s], dp[l][r] + cost[r][s]);
                        }
                    }
                }
                dp = move(ndp); // 滚动更新
            }
            
            // 寻找最小消耗
            int ans = INF;
            for (int l = 0; l < 5; l++) 
                for (int r = 0; r < 5; r++) 
                    ans = min(ans, dp[l][r]);
            
            cout << ans << endl;
            steps.clear(); // 清空，准备下一组数据
        } else {
            steps.push_back(step); // 添加指令到序列
        }
    }
    
    return 0;
}
