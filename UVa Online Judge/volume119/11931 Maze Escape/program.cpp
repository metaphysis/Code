// Maze Escape
// UVa ID: 11931
// Verdict: Accepted
// Submission Date: 2025-10-28
// UVa Run Time: 0.010s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

// 状态结构体：记录玩家位置、箱子位置和步数
struct State {
    int playerY, playerX; // 玩家坐标
    int boxY, boxX;       // 箱子坐标
    int steps;            // 已走步数
};

int mazeRows, mazeCols;                // 迷宫行列数
vector<string> mazeLayout;             // 迷宫布局
int startY, startX;                    // 起点坐标
int boxStartY, boxStartX;              // 箱子初始坐标
int doorY, doorX;                      // 门坐标
int buttonY, buttonX;                  // 按钮坐标
bool visited[20][20][20][20];          // 访问标记数组

// 方向数组：上、下、左、右
const int dirY[4] = {-1, 1, 0, 0};
const int dirX[4] = {0, 0, -1, 1};

// 检查坐标是否在迷宫范围内
bool isInBounds(int y, int x) {
    return y >= 0 && y < mazeRows && x >= 0 && x < mazeCols;
}

// 检查格子是否可进入（考虑门的开关状态）
bool isCellPassable(int y, int x, int boxY, int boxX) {
    // 墙壁永远不可通过
    if (mazeLayout[y][x] == '#') return false;
    // 如果是门，检查是否打开（箱子在按钮上时门打开）
    if (y == doorY && x == doorX) {
        return (boxY == buttonY && boxX == buttonX);
    }
    // 其他情况（空地、按钮、起点、箱子位置）都可进入
    return true;
}

// BFS 搜索最短路径
int findShortestPath() {
    // 初始化访问数组
    memset(visited, 0, sizeof(visited));
    queue<State> stateQueue;
    
    // 将初始状态加入队列
    stateQueue.push({startY, startX, boxStartY, boxStartX, 0});
    visited[startY][startX][boxStartY][boxStartX] = true;
    
    while (!stateQueue.empty()) {
        State current = stateQueue.front(); 
        stateQueue.pop();
        
        // 检查是否到达胜利条件：玩家在门位置且箱子在按钮上
        if (current.playerY == doorY && current.playerX == doorX && 
            current.boxY == buttonY && current.boxX == buttonX) {
            return current.steps;
        }
        
        // 尝试四个方向的移动
        for (int direction = 0; direction < 4; direction++) {
            int newPlayerY = current.playerY + dirY[direction];
            int newPlayerX = current.playerX + dirX[direction];
            
            // 检查新位置是否在迷宫范围内
            if (!isInBounds(newPlayerY, newPlayerX)) continue;
            
            // 如果移动目标是箱子位置，尝试推箱子
            if (newPlayerY == current.boxY && newPlayerX == current.boxX) {
                int newBoxY = current.boxY + dirY[direction];
                int newBoxX = current.boxX + dirX[direction];
                
                // 检查箱子目标位置是否合法
                if (!isInBounds(newBoxY, newBoxX)) continue;
                if (!isCellPassable(newBoxY, newBoxX, current.boxY, current.boxX)) continue;
                
                // 推箱子操作有效，创建新状态
                if (!visited[newPlayerY][newPlayerX][newBoxY][newBoxX]) {
                    visited[newPlayerY][newPlayerX][newBoxY][newBoxX] = true;
                    stateQueue.push({newPlayerY, newPlayerX, newBoxY, newBoxX, current.steps + 1});
                }
            } else {
                // 普通移动：检查目标位置是否可进入
                if (!isCellPassable(newPlayerY, newPlayerX, current.boxY, current.boxX)) continue;
                
                // 移动有效，创建新状态（箱子位置不变）
                if (!visited[newPlayerY][newPlayerX][current.boxY][current.boxX]) {
                    visited[newPlayerY][newPlayerX][current.boxY][current.boxX] = true;
                    stateQueue.push({newPlayerY, newPlayerX, current.boxY, current.boxX, current.steps + 1});
                }
            }
        }
    }
    
    // 无解情况
    return -1;
}

int main() {
    while (cin >> mazeRows >> mazeCols) {
        if (mazeRows == 0 && mazeCols == 0) break;
        
        // 读取迷宫布局
        mazeLayout.resize(mazeRows);
        for (int i = 0; i < mazeRows; i++) {
            cin >> mazeLayout[i];
        }
        
        // 定位特殊格子的位置
        for (int i = 0; i < mazeRows; i++) {
            for (int j = 0; j < mazeCols; j++) {
                switch (mazeLayout[i][j]) {
                    case '@': 
                        startY = i; startX = j; 
                        break;
                    case 'x': 
                        boxStartY = i; boxStartX = j; 
                        break;
                    case 'b': 
                        buttonY = i; buttonX = j; 
                        break;
                    case 'd': 
                        doorY = i; doorX = j; 
                        break;
                }
            }
        }
        
        // 执行 BFS 搜索
        int result = findShortestPath();
        if (result == -1) {
            cout << "No Way!" << endl;
        } else {
            cout << result << endl;
        }
    }
    return 0;
}
