// Least Squares
// UVa ID: 10563
// Verdict: Accepted
// Submission Date: 2025-11-18
// UVa Run Time: 0.040s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAX_ROWS = 105;
const int MAX_COLS = 85;

char grid[MAX_ROWS][MAX_COLS];

char findMinColor(int rows, int cols, int r, int c) {
    for (char color = 'A'; color <= 'Z'; color++) {
        bool valid = true;
        // 检查上边相邻
        if (r > 0 && grid[r - 1][c] == color) valid = false;
        // 检查左边相邻
        if (c > 0 && grid[r][c - 1] == color) valid = false;
        // 检查右边相邻
        if (c + 1 < cols && grid[r][c + 1] == color) valid = false;
        
        if (valid) return color;
    }
    return 'A'; // 理论上不会执行到这里
}

bool canExpandSquare(int rows, int cols, int r, int c, int size, char color) {
    // 检查是否超出边界
    if (r + size >= rows || c + size >= cols) return false;
    
    // 检查新增的右边列和下边行是否都是'?'
    for (int i = r; i <= r + size; i++) {
        if (grid[i][c + size] != '?') return false;
    }
    for (int j = c; j <= c + size; j++) {
        if (grid[r + size][j] != '?') return false;
    }
    
    // 检查扩展后是否会产生颜色冲突
    // 检查扩展后正方形的右边相邻
    if (c + size + 1 < cols) {
        for (int i = r; i <= r + size; i++) {
            if (grid[i][c + size + 1] == color) return false;
        }
    }
    // 检查扩展后正方形的上边相邻
    if (r > 0) {
        for (int j = c; j <= c + size; j++) {
            if (grid[r - 1][j] == color) return false;
        }
    }
    
    return true;
}

void expandSquare(int r, int c, int size, char color) {
    // 填充新增的右边列
    for (int i = r; i <= r + size; i++) {
        grid[i][c + size] = color;
    }
    // 填充新增的下边行
    for (int j = c; j <= c + size; j++) {
        grid[r + size][j] = color;
    }
}

void solveGrid(int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] == '?') {
                // 步骤1：确定基础颜色
                char baseColor = findMinColor(rows, cols, i, j);
                grid[i][j] = baseColor;
                
                // 步骤2：尝试向右扩展正方形
                int currentSize = 0;
                while (true) {
                    // 检查能否继续扩展
                    if (j + currentSize + 1 >= cols || grid[i][j + currentSize + 1] != '?') {
                        break;
                    }
                    
                    // 检查扩展位置的颜色是否满足单调性
                    char extendColor = findMinColor(rows, cols, i, j + currentSize + 1);
                    if (extendColor < baseColor) {
                        break;
                    }
                    
                    // 检查能否形成更大的正方形
                    if (canExpandSquare(rows, cols, i, j, currentSize + 1, baseColor)) {
                        currentSize++;
                        expandSquare(i, j, currentSize, baseColor);
                    } else {
                        break;
                    }
                }
            }
        }
    }
}

int main() {
    int rows, cols;
    int caseCount = 0;
    
    while (cin >> rows >> cols) {
        if (rows == 0 && cols == 0) break;
        
        // 读取输入
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cin >> grid[i][j];
            }
        }
        
        // 解决当前测试用例
        solveGrid(rows, cols);
        
        // 输出结果
        if (caseCount > 0) cout << endl;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << grid[i][j];
            }
            cout << endl;
        }
        
        caseCount++;
    }
    
    return 0;
}
