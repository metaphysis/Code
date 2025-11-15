// Biggest Number
// UVa ID: 11882
// Verdict: Accepted
// Submission Date: 2025-11-09
// UVa Run Time: 0.120s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 全局变量定义
int rowCount, colCount;          // 迷宫的行数和列数
char grid[20][20];               // 存储迷宫网格
int deltaX[4] = {0, 0, 1, -1};   // 四个方向的x偏移量
int deltaY[4] = {1, -1, 0, 0};   // 四个方向的y偏移量
int reachableCount;              // 记录可达格子数量
bool visited[20][20];            // 记录DFS访问状态
bool tempVisited[20][20];        // 临时访问状态，用于floodFill
string bestNumber, currentString; // 最佳数字和当前字符串

// 洪水填充算法，计算从(x,y)出发能到达的格子数量
void floodFill(int x, int y) {
    reachableCount++;                    // 统计当前格子
    tempVisited[x][y] = 1;               // 标记为已访问
    for (int i = 0; i < 4; i++) {        // 遍历四个方向
        int nextX = x + deltaX[i];
        int nextY = y + deltaY[i];
        // 边界检查
        if (nextX < 1 || nextX > rowCount || nextY < 1 || nextY > colCount) continue;
        // 访问检查
        if (tempVisited[nextX][nextY]) continue;
        // 障碍物检查
        if (grid[nextX][nextY] == '#') continue;
        floodFill(nextX, nextY);         // 递归填充
    }
}

// 深度优先搜索函数
void dfs(int x, int y, string currentPath, int pathLength) {
    // 计算剩余可达格子数
    reachableCount = 0;
    memcpy(tempVisited, visited, sizeof(visited)); // 复制当前访问状态
    floodFill(x, y);
    
    // 剪枝1：长度不可能超过当前最佳数字
    if (pathLength + reachableCount - 1 < bestNumber.size()) return;
    
    // 剪枝2：长度相等但字典序不可能更大
    // 使用"z"作为占位符，因为'z' > '9'（ASCII码比较）
    if (pathLength + reachableCount - 1 == bestNumber.size() && bestNumber > currentPath + "z") return;
    
    // 更新最佳数字
    if (pathLength > bestNumber.size() || (pathLength == bestNumber.size() && currentPath > bestNumber)) 
        bestNumber = currentPath;
    
    // 向四个方向继续搜索
    for (int i = 0; i < 4; i++) {
        int nextX = x + deltaX[i];
        int nextY = y + deltaY[i];
        // 边界检查
        if (nextX < 1 || nextX > rowCount || nextY < 1 || nextY > colCount) continue;
        // 访问检查
        if (visited[nextX][nextY]) continue;
        // 障碍物检查
        if (grid[nextX][nextY] == '#') continue;
        
        // 递归搜索
        visited[nextX][nextY] = 1;
        dfs(nextX, nextY, currentPath + grid[nextX][nextY], pathLength + 1);
        visited[nextX][nextY] = 0; // 回溯
    }
}

int main() {
    while (1) {
        scanf("%d %d", &rowCount, &colCount);
        if (rowCount == 0 && colCount == 0) return 0; // 输入结束
        
        bestNumber = ""; // 重置最佳数字
        // 读入迷宫
        for (int i = 1; i <= rowCount; i++) 
            scanf("%s", grid[i] + 1);
        
        // 从每个非障碍格子出发进行搜索
        for (int i = 1; i <= rowCount; i++) {
            for (int j = 1; j <= colCount; j++) {
                currentString = grid[i][j]; // 当前起始字符
                if (grid[i][j] != '#') {    // 非障碍格子
                    memset(visited, 0, sizeof(visited)); // 重置访问状态
                    visited[i][j] = 1;      // 标记起点为已访问
                    dfs(i, j, currentString, 1); // 开始DFS
                }
            }
        }
        
        cout << bestNumber << endl; // 输出结果
    }
}
