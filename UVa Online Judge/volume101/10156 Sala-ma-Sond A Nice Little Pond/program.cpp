// Sala-ma-Sond A Nice Little Pond
// UVa ID: 10156
// Verdict: Accepted
// Submission Date: 2025-11-23
// UVa Run Time: 0.110s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m, t, k;
    // 处理多个数据集
    while (cin >> n >> m >> t >> k) {
        // 存储乌龟ID到坐标的映射
        map<int, pair<int, int>> turtles;
        // 标记网格位置是否被占用
        vector<vector<bool>> occupied(n, vector<bool>(m, false));
        
        // 读取乌龟初始位置
        for (int i = 0; i < t; i++) {
            int id, x, y;
            cin >> id >> x >> y;
            turtles[id] = {x, y};
            occupied[x][y] = true;
        }

        // 定义八个方向的坐标偏移量
        map<string, pair<int, int>> dirs = {
            {"N", {-1, 0}}, {"S", {1, 0}}, {"E", {0, 1}}, {"W", {0, -1}},
            {"NE", {-1, 1}}, {"NW", {-1, -1}}, {"SE", {1, 1}}, {"SW", {1, -1}}
        };

        // 处理移动指令
        for (int i = 0; i < k; i++) {
            int id;
            string dir;
            cin >> id >> dir;
            // 检查乌龟ID是否存在
            if (turtles.find(id) == turtles.end()) continue;
            
            // 获取当前位置
            int x = turtles[id].first, y = turtles[id].second;
            // 计算目标位置
            int dx = dirs[dir].first, dy = dirs[dir].second;
            int nx = x + dx, ny = y + dy;
            
            // 检查边界
            if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
            // 检查位置冲突
            if (occupied[nx][ny]) continue;
            
            // 更新位置：先释放原位置，再占用新位置
            occupied[x][y] = false;
            occupied[nx][ny] = true;
            turtles[id] = {nx, ny};
        }

        // 输出最终状态
        for (int i = 0; i < n; i++) {
            string line = "";
            for (int j = 0; j < m; j++) {
                if (occupied[i][j]) line += '*';
                else line += ' ';
            }
            // 去除行尾空格
            while (!line.empty() && line.back() == ' ') line.pop_back();
            cout << line << endl;
        }
        cout << endl;
    }
    return 0;
}
