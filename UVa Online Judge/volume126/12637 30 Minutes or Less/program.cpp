// 30 Minutes or Less
// UVa ID: 12637
// Verdict: Accepted
// Submission Date: 2026-02-25
// UVa Run Time: 0.020s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

// 计算曼哈顿距离
int manhattan(pair<int, int> a, pair<int, int> b) {
    return abs(a.first - b.first) + abs(a.second - b.second);
}

// 匈牙利算法求最小权匹配
int hungarian(const vector<vector<int>>& cost) {
    int n = cost.size();      // 左部节点数（订单数）
    int m = cost[0].size();   // 右部节点数（餐厅数）
    
    // u[i] 左部顶标，v[j] 右部顶标
    // p[j] 右部节点匹配的左部节点
    // way[j] 记录增广路径
    vector<int> u(n + 1), v(m + 1), p(m + 1), way(m + 1);
    
    for (int i = 1; i <= n; ++i) {
        p[0] = i;
        int j0 = 0;
        vector<int> minv(m + 1, INF);
        vector<bool> used(m + 1, false);
        
        do {
            used[j0] = true;
            int i0 = p[j0];
            int delta = INF;
            int j1;
            
            // 更新所有未访问右部节点的 minv
            for (int j = 1; j <= m; ++j) {
                if (!used[j]) {
                    int cur = cost[i0 - 1][j - 1] - u[i0] - v[j];
                    if (cur < minv[j]) {
                        minv[j] = cur;
                        way[j] = j0;
                    }
                    if (minv[j] < delta) {
                        delta = minv[j];
                        j1 = j;
                    }
                }
            }
            
            // 更新顶标
            for (int j = 0; j <= m; ++j) {
                if (used[j]) {
                    u[p[j]] += delta;
                    v[j] -= delta;
                } else {
                    minv[j] -= delta;
                }
            }
            
            j0 = j1;
        } while (p[j0] != 0);
        
        // 回溯更新匹配
        do {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while (j0);
    }
    
    // 最小权值即为 -v[0]
    return -v[0];
}

int main() {
    int R, N;
    while (cin >> R >> N) {
        vector<pair<int, int>> restaurants(R), orders(N);
        
        // 读入餐厅坐标
        for (int i = 0; i < R; ++i) {
            cin >> restaurants[i].first >> restaurants[i].second;
        }
        
        // 读入订单坐标
        for (int i = 0; i < N; ++i) {
            cin >> orders[i].first >> orders[i].second;
        }
        
        // 构建成本矩阵：订单 i 到餐厅 j 的距离
        vector<vector<int>> cost(R, vector<int>(N));
        for (int i = 0; i < R; ++i) {
            for (int j = 0; j < N; ++j) {
                cost[i][j] = manhattan(restaurants[i], orders[j]);
            }
        }
        
        // 转置矩阵，使左部为订单，右部为餐厅
        // 这样左部节点数 N <= 右部节点数 R，满足匈牙利算法的要求
        vector<vector<int>> transposedCost(N, vector<int>(R));
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < R; ++j) {
                transposedCost[i][j] = cost[j][i];
            }
        }
        
        // 求解最小权匹配
        int ans = hungarian(transposedCost);
        cout << ans << endl;
    }
    
    return 0;
}
