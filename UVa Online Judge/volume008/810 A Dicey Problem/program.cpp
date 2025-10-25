// A Dicey Problem
// UVa ID: 810
// Verdict: Accepted
// Submission Date: 2025-10-24
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int mazeRows, mazeCols, startRow, startCol, startTop, startFront;
int mazeGrid[11][11];
bool visited[11][11][7][7]; // 访问标记：行、列、顶面、前面
vector<pair<int, int>> path; // 存储路径

// 骰子滚动函数：根据当前状态和方向计算新状态
pair<int, int> rollDice(int top, int front, int direction) {
    int bottom = 7 - top;
    int back = 7 - front;
    int left, right;
    
    // 预计算的右面映射表
    if (top == 1 && front == 2) { right = 3; }
    else if (top == 1 && front == 3) { right = 5; }
    else if (top == 1 && front == 4) { right = 2; }
    else if (top == 1 && front == 5) { right = 4; }
    else if (top == 2 && front == 1) { right = 4; }
    else if (top == 2 && front == 3) { right = 1; }
    else if (top == 2 && front == 4) { right = 6; }
    else if (top == 2 && front == 6) { right = 3; }
    else if (top == 3 && front == 1) { right = 2; }
    else if (top == 3 && front == 2) { right = 6; }
    else if (top == 3 && front == 5) { right = 1; }
    else if (top == 3 && front == 6) { right = 5; }
    else if (top == 4 && front == 1) { right = 5; }
    else if (top == 4 && front == 2) { right = 1; }
    else if (top == 4 && front == 5) { right = 6; }
    else if (top == 4 && front == 6) { right = 2; }
    else if (top == 5 && front == 1) { right = 3; }
    else if (top == 5 && front == 3) { right = 6; }
    else if (top == 5 && front == 4) { right = 1; }
    else if (top == 5 && front == 6) { right = 4; }
    else if (top == 6 && front == 2) { right = 4; }
    else if (top == 6 && front == 3) { right = 2; }
    else if (top == 6 && front == 4) { right = 5; }
    else if (top == 6 && front == 5) { right = 3; }
    else { right = 1; } // 默认值
    
    left = 7 - right; // 计算左面
    
    // 根据方向计算新状态
    if (direction == 0) { // 向上滚动
        return {front, bottom}; // 前面变顶面，底面变前面
    } else if (direction == 1) { // 向下滚动
        return {back, top}; // 背面变顶面，顶面变前面
    } else if (direction == 2) { // 向左滚动
        return {right, front}; // 右面变顶面，前面不变
    } else { // 向右滚动
        return {left, front}; // 左面变顶面，前面不变
    }
}

// 检查是否可以移动到目标格子
bool canMoveTo(int targetRow, int targetCol, int currentTop) {
    // 检查边界和空格
    if (targetRow < 1 || targetRow > mazeRows || targetCol < 1 || targetCol > mazeCols) return false;
    if (mazeGrid[targetRow][targetCol] == 0) return false;
    
    // 起点位置第一次进入无条件允许
    bool isFirstVisitToStart = (targetRow == startRow && targetCol == startCol && path.size() == 0);
    if (isFirstVisitToStart) return true;
    
    // 其他位置：检查是否为万能格或数字匹配
    return (mazeGrid[targetRow][targetCol] == -1 || mazeGrid[targetRow][targetCol] == currentTop);
}

// 深度优先搜索函数
bool depthFirstSearch(int currentRow, int currentCol, int currentTop, int currentFront) {
    // 如果回到起点且不是初始状态，找到解
    if (path.size() > 0 && currentRow == startRow && currentCol == startCol) {
        path.push_back({currentRow, currentCol});
        return true;
    }
    
    // 检查是否已访问过该状态
    if (visited[currentRow][currentCol][currentTop][currentFront]) return false;
    
    // 标记当前状态为已访问
    visited[currentRow][currentCol][currentTop][currentFront] = true;
    path.push_back({currentRow, currentCol});
    
    // 四个方向：上、下、左、右
    int rowOffsets[4] = {-1, 1, 0, 0};
    int colOffsets[4] = {0, 0, -1, 1};
    
    for (int i = 0; i < 4; i++) {
        int nextRow = currentRow + rowOffsets[i];
        int nextCol = currentCol + colOffsets[i];
        
        // 检查是否可以移动到目标格子
        if (!canMoveTo(nextRow, nextCol, currentTop)) continue;
        
        // 计算滚动后的新骰子状态
        auto newState = rollDice(currentTop, currentFront, i);
        int newTop = newState.first;
        int newFront = newState.second;
        
        // 递归搜索
        if (depthFirstSearch(nextRow, nextCol, newTop, newFront)) return true;
    }
    
    // 回溯
    path.pop_back();
    visited[currentRow][currentCol][currentTop][currentFront] = false;
    return false;
}

int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    string mazeName;
    while (cin >> mazeName) {
        if (mazeName == "END") break;
        cin >> mazeRows >> mazeCols >> startRow >> startCol >> startTop >> startFront;
        for (int i = 1; i <= mazeRows; i++) {
            for (int j = 1; j <= mazeCols; j++) {
                cin >> mazeGrid[i][j];
            }
        }
        
        // 初始化
        memset(visited, 0, sizeof(visited));
        path.clear();
        
        // 添加起点到路径
        path.push_back({startRow, startCol});
        visited[startRow][startCol][startTop][startFront] = true;
        
        bool solutionFound = false;
        int rowOffsets[4] = {-1, 1, 0, 0};
        int colOffsets[4] = {0, 0, -1, 1};
        
        // 从起点尝试四个方向
        for (int i = 0; i < 4 && !solutionFound; i++) {
            int nextRow = startRow + rowOffsets[i];
            int nextCol = startCol + colOffsets[i];
            
            // 检查移动是否合法
            if (!canMoveTo(nextRow, nextCol, startTop)) continue;
            
            // 计算新状态并开始搜索
            auto newState = rollDice(startTop, startFront, i);
            if (depthFirstSearch(nextRow, nextCol, newState.first, newState.second)) {
                solutionFound = true;
            }
        }
        
        // 输出结果
        cout << mazeName << "\n";
        if (solutionFound) {
            // 输出路径，每行最多 $9$ 个位置
            for (size_t i = 0; i < path.size(); i++) {
                if (i > 0) {
                    if (i % 9 == 0) cout << ",\n";
                    else cout << ",";
                }
                if (i % 9 == 0) cout << "  ";
                cout << "(" << path[i].first << "," << path[i].second << ")";
            }
            cout << "\n";
        } else {
            cout << "  No Solution Possible\n";
        }
    }
    return 0;
}
