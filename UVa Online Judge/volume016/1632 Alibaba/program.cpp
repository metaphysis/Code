// Alibaba
// UVa ID: 1632
// Verdict: Accepted
// Submission Date: 2025-11-05
// UVa Run Time: 0.340s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

struct Treasure {
    int pos;
    int deadline;
};

bool comparePos(const Treasure& a, const Treasure& b) {
    return a.pos < b.pos;
}

int main() {
    int n;
    while (cin >> n) {
        vector<Treasure> treasures(n);
        for (int i = 0; i < n; i++) {
            cin >> treasures[i].pos >> treasures[i].deadline;
        }
        
        // 按位置排序
        sort(treasures.begin(), treasures.end(), comparePos);
        
        // 滚动数组DP：dp0[i][0/1]表示当前区间，dp1[i][0/1]表示下一区间
        vector<vector<int>> dp0(n, vector<int>(2, INT_MAX));
        vector<vector<int>> dp1(n, vector<int>(2, INT_MAX));
        
        // 初始化单个宝藏
        for (int i = 0; i < n; i++) {
            if (0 < treasures[i].deadline) {
                dp0[i][0] = 0;
                dp0[i][1] = 0;
            }
        }
        
        // 区间DP，按长度递增
        for (int len = 2; len <= n; len++) {
            for (int i = 0; i + len - 1 < n; i++) {
                int j = i + len - 1;
                dp1[i][0] = INT_MAX;
                dp1[i][1] = INT_MAX;
                
                // 从dp[i+1][j][0]扩展到dp[i][j][0]
                if (dp0[i+1][0] != INT_MAX) {
                    int move_time = treasures[i+1].pos - treasures[i].pos;
                    int new_time = dp0[i+1][0] + move_time;
                    if (new_time < treasures[i].deadline) {
                        dp1[i][0] = min(dp1[i][0], new_time);
                    }
                }
                
                // 从dp[i+1][j][1]扩展到dp[i][j][0]
                if (dp0[i+1][1] != INT_MAX) {
                    int move_time = treasures[j].pos - treasures[i].pos;
                    int new_time = dp0[i+1][1] + move_time;
                    if (new_time < treasures[i].deadline) {
                        dp1[i][0] = min(dp1[i][0], new_time);
                    }
                }
                
                // 从dp[i][j-1][0]扩展到dp[i][j][1]
                if (dp0[i][0] != INT_MAX) {
                    int move_time = treasures[j].pos - treasures[i].pos;
                    int new_time = dp0[i][0] + move_time;
                    if (new_time < treasures[j].deadline) {
                        dp1[i][1] = min(dp1[i][1], new_time);
                    }
                }
                
                // 从dp[i][j-1][1]扩展到dp[i][j][1]
                if (dp0[i][1] != INT_MAX) {
                    int move_time = treasures[j].pos - treasures[j-1].pos;
                    int new_time = dp0[i][1] + move_time;
                    if (new_time < treasures[j].deadline) {
                        dp1[i][1] = min(dp1[i][1], new_time);
                    }
                }
            }
            swap(dp0, dp1);
        }
        
        int result = min(dp0[0][0], dp0[0][1]);
        if (result == INT_MAX) {
            cout << "No solution" << endl;
        } else {
            cout << result << endl;
        }
    }
    return 0;
}
