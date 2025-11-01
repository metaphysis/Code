// Robots(II)
// UVa ID: 10599
// Verdict: Accepted
// Submission Date: 2025-10-31
// UVa Run Time: 0.010s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct Cell {
    int row, col, index;
    Cell(int r, int c, int idx) : row(r), col(c), index(idx) {}
    
    bool operator<(const Cell& other) const {
        if (row != other.row) return row < other.row;
        return col < other.col;
    }
};

int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int R, C, testCase = 1;
    
    while (cin >> R >> C) {
        if (R == -1 && C == -1) break;
        
        vector<Cell> garbage;
        int r, c;
        
        // 读取垃圾位置
        while (cin >> r >> c) {
            if (r == 0 && c == 0) break;
            // 计算单元格编号：行优先顺序
            int index = (r - 1) * C + c;
            garbage.emplace_back(r, c, index);
        }
        
        // 如果没有垃圾
        if (garbage.empty()) {
            cout << "CASE#" << testCase++ << ": 0 0" << endl;
            continue;
        }
        
        // 按行和列排序
        sort(garbage.begin(), garbage.end());
        
        int n = garbage.size();
        vector<int> dp(n, 1);    // dp[i]: 以第i个垃圾结尾的最大清理数量
        vector<long long> count(n, 1); // count[i]: 达到dp[i]的路径数量
        vector<int> prev(n, -1); // 前驱节点
        
        int maxClean = 1;
        
        // 动态规划
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                // 检查是否可以转移：行和列都不递减
                if (garbage[j].row <= garbage[i].row && 
                    garbage[j].col <= garbage[i].col) {
                    
                    if (dp[j] + 1 > dp[i]) {
                        dp[i] = dp[j] + 1;
                        count[i] = count[j];
                        prev[i] = j;
                    } else if (dp[j] + 1 == dp[i]) {
                        count[i] += count[j];
                    }
                }
            }
            maxClean = max(maxClean, dp[i]);
        }
        
        // 计算总路径数和找到一条路径
        long long totalWays = 0;
        vector<int> path;
        
        for (int i = 0; i < n; i++) {
            if (dp[i] == maxClean) {
                totalWays += count[i];
                // 构建一条路径
                if (path.empty()) {
                    int cur = i;
                    while (cur != -1) {
                        path.push_back(garbage[cur].index);
                        cur = prev[cur];
                    }
                    reverse(path.begin(), path.end());
                }
            }
        }
        
        // 输出结果
        cout << "CASE#" << testCase++ << ": " << maxClean << " " << totalWays;
        for (int cell : path) cout << " " << cell;
        cout << '\n';
    }
    
    return 0;
}
