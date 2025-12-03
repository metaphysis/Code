// Mountain Village
// UVa ID: 10486
// Verdict: Accepted
// Submission Date: 2025-12-02
// UVa Run Time: 0.020s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAX = 45;

int r, c;
int altitude[MAX][MAX];
bool inRange[MAX][MAX];
int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

// BFS统计连通块大小
int bfs(int startRow, int startCol) {
    if (!inRange[startRow][startCol]) return 0;
    queue<pair<int, int>> q;
    q.push({startRow, startCol});
    inRange[startRow][startCol] = false; // 标记为已访问
    int cnt = 0;
    
    while (!q.empty()) {
        auto [row, col] = q.front(); q.pop();
        cnt++;
        
        for (int i = 0; i < 4; ++i) {
            int nr = row + dirs[i][0];
            int nc = col + dirs[i][1];
            if (nr >= 1 && nr <= r && nc >= 1 && nc <= c && inRange[nr][nc]) {
                inRange[nr][nc] = false;
                q.push({nr, nc});
            }
        }
    }
    return cnt;
}

// 检查是否存在高度范围在[minH, maxH]内的连通块，其大小至少为k
bool checkRange(int minH, int maxH, int k) {
    // 标记所有在高度范围内的格子
    int totalInRange = 0;
    for (int i = 1; i <= r; ++i) {
        for (int j = 1; j <= c; ++j) {
            inRange[i][j] = (altitude[i][j] >= minH && altitude[i][j] <= maxH);
            if (inRange[i][j]) totalInRange++;
        }
    }
    
    // 如果总数都不够k，直接返回false
    if (totalInRange < k) return false;
    
    // 寻找最大的连通块
    for (int i = 1; i <= r; ++i) {
        for (int j = 1; j <= c; ++j) {
            if (inRange[i][j]) {
                int size = bfs(i, j);
                if (size >= k) return true;
            }
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> r >> c;
    vector<int> heights;
    for (int i = 1; i <= r; ++i) {
        for (int j = 1; j <= c; ++j) {
            cin >> altitude[i][j];
            heights.push_back(altitude[i][j]);
        }
    }
    
    // 去重并排序所有高度值
    sort(heights.begin(), heights.end());
    heights.erase(unique(heights.begin(), heights.end()), heights.end());
    
    int n;
    cin >> n;
    
    while (n--) {
        int k;
        cin >> k;
        
        if (k == 1) { // 特殊情况处理
            cout << 0 << '\n';
            continue;
        }
        
        int ans = 100; // 最大可能高度差
        int hCount = heights.size();
        
        // 枚举所有可能的高度范围
        for (int i = 0; i < hCount; ++i) {
            int low = heights[i];
            // 二分查找满足条件的最小高度差
            int left = 0, right = 99 - low;
            int bestForLow = 100;
            
            while (left <= right) {
                int mid = (left + right) / 2;
                int high = low + mid;
                
                // 查找heights中不超过high的最大值
                auto it = upper_bound(heights.begin(), heights.end(), high);
                if (it == heights.begin()) {
                    left = mid + 1;
                    continue;
                }
                int actualHigh = *prev(it);
                
                if (checkRange(low, actualHigh, k)) {
                    bestForLow = mid;
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            }
            
            ans = min(ans, bestForLow);
        }
        
        cout << ans << '\n';
    }
    
    return 0;
}
