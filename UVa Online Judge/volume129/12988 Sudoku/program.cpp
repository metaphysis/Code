// Sudoku
// UVa ID: 12988
// Verdict: Accepted
// Submission Date: 2025-11-18
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

vector<string> board(4);
vector<pair<int, int>> emptyCells;

bool isValid(int row, int col, char num) {
    // 检查行
    for (int i = 0; i < 4; i++) {
        if (board[row][i] == num && i != col) return false;
        if (board[i][col] == num && i != row) return false;
    }
    
    // 检查2x2子块
    int startRow = (row / 2) * 2;
    int startCol = (col / 2) * 2;
    for (int i = startRow; i < startRow + 2; i++)
        for (int j = startCol; j < startCol + 2; j++)
            if (board[i][j] == num && !(i == row && j == col)) return false;
    
    return true;
}

bool solve(int index) {
    // 所有空单元格都已填充，找到解
    if (index == emptyCells.size()) return true;
    
    int row = emptyCells[index].first;
    int col = emptyCells[index].second;
    
    // 尝试所有可能的数字
    for (char num = '1'; num <= '4'; num++) {
        if (isValid(row, col, num)) {
            board[row][col] = num;
            if (solve(index + 1)) return true;
            board[row][col] = '*';  // 回溯
        }
    }
    return false;
}

int main() {
    int T;
    cin >> T;
    
    for (int caseNum = 1; caseNum <= T; caseNum++) {
        emptyCells.clear();
        
        // 读取输入并记录空单元格位置
        for (int i = 0; i < 4; i++) {
            cin >> board[i];
            for (int j = 0; j < 4; j++)
                if (board[i][j] == '*') emptyCells.push_back({i, j});
        }
        
        // 解决数独
        solve(0);
        
        // 输出结果
        cout << "Case #" << caseNum << ":" << endl;
        for (int i = 0; i < 4; i++) cout << board[i] << endl;
    }
    
    return 0;
}
