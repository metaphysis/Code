// Finding Seats Again
// UVa ID: 11846
// Verdict: Accepted
// Submission Date: 2026-01-20
// UVa Run Time: 0.010s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Leader {
    int r, c, size;  // 组长位置和小组人数
    bool placed;     // 该组是否已放置
    char letter;     // 分配给该组的字母
};

int n, K;
char grid[20][20];   // 当前填充状态
char orig[20][20];   // 原始输入地图
Leader leaders[26];  // 组长信息数组
int leaderMap[20][20]; // 位置到组长索引的映射，-1表示无组长

// 获取下一个未填充的位置（从左到右、从上到下）
pair<int, int> getNextEmpty(int r, int c) {
    for (int i = r; i < n; i++)
        for (int j = (i == r ? c : 0); j < n; j++)
            if (grid[i][j] == '.')
                return {i, j};
    return {-1, -1};  // 所有位置都已填充
}

// 尝试放置矩形
bool tryPlace(int g, int sr, int sc, int h, int w) {
    Leader& l = leaders[g];
    // 检查矩形是否包含组长
    if (l.r < sr || l.r >= sr + h || l.c < sc || l.c >= sc + w) return false;
    
    // 检查矩形内是否有冲突
    for (int i = sr; i < sr + h; i++)
        for (int j = sc; j < sc + w; j++)
            if (grid[i][j] != '.' || (leaderMap[i][j] != -1 && leaderMap[i][j] != g))
                return false;
    
    // 放置矩形
    for (int i = sr; i < sr + h; i++)
        for (int j = sc; j < sc + w; j++)
            grid[i][j] = l.letter;
    l.placed = true;
    return true;
}

// 移除矩形
void removeRect(int sr, int sc, int h, int w) {
    for (int i = sr; i < sr + h; i++)
        for (int j = sc; j < sc + w; j++)
            grid[i][j] = '.';
}

// 深度优先搜索
bool dfs(int r, int c) {
    auto next = getNextEmpty(r, c);
    if (next.first == -1) return true;  // 所有位置已填充
    int cr = next.first, cc = next.second;
    
    // 如果当前位置已被填充，继续下一个位置
    if (grid[cr][cc] != '.') return dfs(cr, cc);
    
    // 检查当前位置是否是组长
    int g = leaderMap[cr][cc];
    if (g != -1) {
        // 当前位置是组长
        if (leaders[g].placed) return dfs(cr, cc);  // 组长已放置
        
        int size = leaders[g].size;
        // 枚举所有可能的矩形尺寸
        for (int h = 1; h <= size; h++) {
            if (size % h != 0) continue;
            int w = size / h;
            // 枚举矩形左上角位置（必须包含组长）
            for (int sr = max(0, cr - h + 1); sr <= cr && sr + h <= n; sr++)
                for (int sc = max(0, cc - w + 1); sc <= cc && sc + w <= n; sc++)
                    if (tryPlace(g, sr, sc, h, w)) {
                        if (dfs(cr, cc)) return true;
                        // 回溯
                        removeRect(sr, sc, h, w);
                        leaders[g].placed = false;
                    }
        }
        return false;
    } else {
        // 当前位置是普通点，必须被某个矩形覆盖
        for (int g = 0; g < K; g++) {
            if (leaders[g].placed) continue;  // 该组已放置
            
            int size = leaders[g].size;
            for (int h = 1; h <= size; h++) {
                if (size % h != 0) continue;
                int w = size / h;
                // 矩形必须能覆盖当前点且包含组长
                for (int sr = max(0, cr - h + 1); sr <= cr && sr + h <= n; sr++)
                    for (int sc = max(0, cc - w + 1); sc <= cc && sc + w <= n; sc++)
                        if (leaders[g].r >= sr && leaders[g].r < sr + h &&
                            leaders[g].c >= sc && leaders[g].c < sc + w &&
                            tryPlace(g, sr, sc, h, w)) {
                            if (dfs(cr, cc)) return true;
                            // 回溯
                            removeRect(sr, sc, h, w);
                            leaders[g].placed = false;
                        }
            }
        }
        return false;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    while (cin >> n >> K, n) {
        // 初始化
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                grid[i][j] = '.';
                leaderMap[i][j] = -1;
            }
        
        // 读取输入
        for (int i = 0; i < n; i++) {
            string line; cin >> line;
            for (int j = 0; j < n; j++)
                orig[i][j] = line[j];
        }
        
        // 处理组长信息
        int cnt = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (isdigit(orig[i][j])) {
                    leaders[cnt] = {i, j, orig[i][j] - '0', false, 'A' + cnt};
                    leaderMap[i][j] = cnt;
                    cnt++;
                }
        
        // 开始搜索
        dfs(0, 0);
        
        // 输出结果
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) cout << grid[i][j];
            cout << '\n';
        }
    }
    
    return 0;
}
