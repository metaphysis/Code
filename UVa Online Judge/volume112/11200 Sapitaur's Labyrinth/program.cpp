// Sapitaur's Labyrinth
// UVa ID: 11200
// Verdict: Accepted
// Submission Date: 2025-11-12
// UVa Run Time: 0.030s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <tuple>
using namespace std;

const int MAX = 505;

int rows, cols;
char grid[MAX][MAX];
bool visited[MAX][MAX][4]; // (r, c, dir)

// 方向: 0=上, 1=右, 2=下, 3=左
int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, 1, 0, -1};

// 根据单元格类型和进入方向，得到出口方向
int getOutDirection(int dir, char cell) {
    if (cell == '\\') {
        // NOWSE: 左→下, 上→右, 右→上, 下→左
        switch (dir) {
            case 3: return 2; // 左→下
            case 0: return 1; // 上→右
            case 1: return 0; // 右→上
            case 2: return 3; // 下→左
        }
    } else {
        // NESOW: 左→上, 上→左, 右→下, 下→右
        switch (dir) {
            case 3: return 0; // 左→上
            case 0: return 3; // 上→左
            case 1: return 2; // 右→下
            case 2: return 1; // 下→右
        }
    }
    return -1;
}

int bfs() {
    memset(visited, 0, sizeof(visited));
    int pathCount = 0;
    
    // 从第一行每个单元格的上方进入
    for (int startCol = 0; startCol < cols; startCol++) {
        if (visited[0][startCol][0]) continue;
        
        queue<tuple<int, int, int>> q;
        visited[0][startCol][0] = true;
        q.push(make_tuple(0, startCol, 0));
        
        bool reachedExit = false;
        
        while (!q.empty()) {
            auto current = q.front();
            q.pop();
            int r = get<0>(current);
            int c = get<1>(current);
            int inDir = get<2>(current);
            
            int outDir = getOutDirection(inDir, grid[r][c]);
            
            int nr = r + dr[outDir];
            int nc = c + dc[outDir];
            
            // 检查是否到达出口（从最后一行向下离开）
            if (r == rows - 1 && outDir == 2) {
                reachedExit = true;
                continue;
            }
            
            // 检查边界
            if (nr < 0 || nr >= rows || nc < 0 || nc >= cols) {
                continue; // 进入深渊
            }
            
            // 计算进入相邻单元格的方向（与outDir相反）
            int newInDir = (outDir + 2) % 4;
            
            if (!visited[nr][nc][newInDir]) {
                visited[nr][nc][newInDir] = true;
                q.push(make_tuple(nr, nc, newInDir));
            }
        }
        
        if (reachedExit) {
            pathCount++;
        }
    }
    
    return pathCount;
}

int main() {
    int testCases;
    cin >> testCases;
    
    while (testCases--) {
        cin >> cols >> rows;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cin >> grid[i][j];
            }
        }
        
        int result = bfs();
        cout << result << endl;
    }
    
    return 0;
}
