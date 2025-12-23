// An Odd Love
// UVa ID: 11617
// Verdict: Accepted
// Submission Date: 2025-12-15
// UVa Run Time: 0.010s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    int t; cin >> t;
    while (t--) {
        int W, H; cin >> W >> H;
        vector<string> grid(H);
        for (int i = 0; i < H; i++) cin >> grid[i];
        
        // 存储有目标的行及其目标列
        vector<pair<int, vector<int>>> targetRows;
        for (int h = 0; h < H; h++) {
            vector<int> cols;
            for (int w = 0; w < W; w++) {
                if ((grid[h][w] - '0') % 2 == 0) cols.push_back(w);
            }
            if (!cols.empty()) {
                targetRows.push_back({h, cols});
            }
        }
        
        // 如果没有目标行，答案就是0（从起点开始不用移动）
        if (targetRows.empty()) {
            cout << 0 << endl;
            continue;
        }
        
        const int INF = 1e9;
        int m = targetRows.size();
        vector<vector<int>> dp(m, vector<int>(2, INF));
        
        // 初始化第一个目标行
        int firstRow = targetRows[0].first;
        vector<int> firstCols = targetRows[0].second;
        int firstLeft = *min_element(firstCols.begin(), firstCols.end());
        int firstRight = *max_element(firstCols.begin(), firstCols.end());
        int firstRowDist = firstRight - firstLeft;
        
        // 从起点(0,0)到第一个目标行
        // 需要先向下移动firstRow行
        int downSteps = firstRow;  // 从第0行到第firstRow行
        
        // 停在左端点
        dp[0][0] = downSteps + firstLeft + firstRowDist + firstRowDist;  // 下移，到最左，到最右，回最左
        dp[0][0] = min(dp[0][0], downSteps + firstRight + firstRowDist);  // 下移，到最右，到最左
        
        // 停在右端点
        dp[0][1] = downSteps + firstLeft + firstRowDist;  // 下移，到最左，到最右
        dp[0][1] = min(dp[0][1], downSteps + firstRight + firstRowDist + firstRowDist);  // 下移，到最右，到最左，回最右
        
        // 处理后续目标行
        for (int i = 1; i < m; i++) {
            int prevRow = targetRows[i-1].first;
            vector<int> prevCols = targetRows[i-1].second;
            int prevLeft = *min_element(prevCols.begin(), prevCols.end());
            int prevRight = *max_element(prevCols.begin(), prevCols.end());
            
            int currRow = targetRows[i].first;
            vector<int> currCols = targetRows[i].second;
            int currLeft = *min_element(currCols.begin(), currCols.end());
            int currRight = *max_element(currCols.begin(), currCols.end());
            int currRowDist = currRight - currLeft;
            
            int rowGap = currRow - prevRow;  // 行间距离
            
            for (int prevSide = 0; prevSide < 2; prevSide++) {
                if (dp[i-1][prevSide] == INF) continue;
                
                int prevCol = (prevSide == 0) ? prevLeft : prevRight;
                
                // 从上一目标行到当前目标行
                // 中间需要下移rowGap行
                // 我们可以选择在中间行的任意列移动
                
                // 对于停在左端点
                // 方案1：先到当前行最左，访问到最右，然后回到最左
                int cost1 = dp[i-1][prevSide] + rowGap + abs(prevCol - currLeft) + currRowDist + currRowDist;
                // 方案2：先到当前行最右，访问到最左（停在最左）
                int cost2 = dp[i-1][prevSide] + rowGap + abs(prevCol - currRight) + currRowDist;
                dp[i][0] = min(dp[i][0], min(cost1, cost2));
                
                // 对于停在右端点
                // 方案3：先到当前行最左，访问到最右（停在最右）
                int cost3 = dp[i-1][prevSide] + rowGap + abs(prevCol - currLeft) + currRowDist;
                // 方案4：先到当前行最右，访问到最左，然后回到最右
                int cost4 = dp[i-1][prevSide] + rowGap + abs(prevCol - currRight) + currRowDist + currRowDist;
                dp[i][1] = min(dp[i][1], min(cost3, cost4));
            }
        }
        
        int ans = min(dp[m-1][0], dp[m-1][1]);
        cout << ans << endl;
    }
    return 0;
}
