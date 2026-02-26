// Grasshopper
// UVa ID: 11705
// Verdict: Accepted
// Submission Date: 2026-02-25
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Point {
    int r, c;
    Point(int r, int c) : r(r), c(c) {}
};

int main() {
    int rows, cols;
    while (cin >> rows >> cols && (rows || cols)) {
        vector<vector<int>> grid(rows, vector<int>(cols));
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                cin >> grid[i][j];
        
        // BFS 从出口开始反向搜索
        vector<vector<int>> dist(rows, vector<int>(cols, -1));
        vector<vector<char>> direction(rows, vector<char>(cols, 'X'));
        queue<Point> q;
        
        // 出口位置
        dist[0][0] = 0;
        direction[0][0] = '*';
        q.push(Point(0, 0));
        
        while (!q.empty()) {
            Point p = q.front(); q.pop();
            
            // 检查同一列上哪些点可以跳到 p
            for (int r = 0; r < rows; r++) {
                if (r == p.r) continue;
                if (abs(r - p.r) == grid[r][p.c] && dist[r][p.c] == -1) {
                    dist[r][p.c] = dist[p.r][p.c] + 1;
                    q.push(Point(r, p.c));
                }
            }
            
            // 检查同一行上哪些点可以跳到 p
            for (int c = 0; c < cols; c++) {
                if (c == p.c) continue;
                if (abs(c - p.c) == grid[p.r][c] && dist[p.r][c] == -1) {
                    dist[p.r][c] = dist[p.r][p.c] + 1;
                    q.push(Point(p.r, c));
                }
            }
        }
        
        // 确定每个位置的方向
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (i == 0 && j == 0) continue;
                if (dist[i][j] == -1) {
                    direction[i][j] = 'X';
                    continue;
                }
                
                int bestR = rows, bestC = cols;
                char bestDir = 'X';
                int val = grid[i][j];
                
                // 北方向：跳到 (i - val, j)
                if (i - val >= 0 && dist[i - val][j] == dist[i][j] - 1) {
                    if (i - val < bestR || (i - val == bestR && j < bestC)) {
                        bestR = i - val;
                        bestC = j;
                        bestDir = 'N';
                    }
                }
                
                // 西方向：跳到 (i, j - val)
                if (j - val >= 0 && dist[i][j - val] == dist[i][j] - 1) {
                    if (i < bestR || (i == bestR && j - val < bestC)) {
                        bestR = i;
                        bestC = j - val;
                        bestDir = 'W';
                    }
                }
                
                // 南方向：跳到 (i + val, j)
                if (i + val < rows && dist[i + val][j] == dist[i][j] - 1) {
                    if (i + val < bestR || (i + val == bestR && j < bestC)) {
                        bestR = i + val;
                        bestC = j;
                        bestDir = 'S';
                    }
                }
                
                // 东方向：跳到 (i, j + val)
                if (j + val < cols && dist[i][j + val] == dist[i][j] - 1) {
                    if (i < bestR || (i == bestR && j + val < bestC)) {
                        bestR = i;
                        bestC = j + val;
                        bestDir = 'E';
                    }
                }
                
                direction[i][j] = bestDir;
            }
        }
        
        // 输出结果
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++)
                cout << direction[i][j];
            cout << endl;
        }
        cout << endl;
    }
    return 0;
}
