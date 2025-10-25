// Cake Slicing
// UVa ID: 1629
// Verdict: Accepted
// Submission Date: 2025-10-23
// UVa Run Time: 0.420s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int rowSize, colSize, cherryCount;
int cherryGrid[25][25];
int prefixSum[25][25];
int dp[25][25][25][25];

// 计算矩形区域内的樱桃数量
int countCherries(int startRow, int startCol, int endRow, int endCol) {
    int total = prefixSum[endRow][endCol];
    if (startRow > 0) total -= prefixSum[startRow - 1][endCol];
    if (startCol > 0) total -= prefixSum[endRow][startCol - 1];
    if (startRow > 0 && startCol > 0) total += prefixSum[startRow - 1][startCol - 1];
    return total;
}

// 动态规划求解最小切割长度
int findMinCutLength(int startRow, int startCol, int endRow, int endCol) {
    if (startRow > endRow || startCol > endCol) return 0;
    int &result = dp[startRow][startCol][endRow][endCol];
    if (result != -1) return result;
    
    int cherryNum = countCherries(startRow, startCol, endRow, endCol);
    if (cherryNum == 0) {
        return result = INT_MAX / 2; // 不可能情况，区域无樱桃
    }
    if (cherryNum == 1) {
        return result = 0; // 不需要切割
    }
    
    result = INT_MAX;
    // 尝试所有横切位置
    for (int cutRow = startRow; cutRow < endRow; cutRow++) {
        int topPart = findMinCutLength(startRow, startCol, cutRow, endCol);
        int bottomPart = findMinCutLength(cutRow + 1, startCol, endRow, endCol);
        if (topPart < INT_MAX / 2 && bottomPart < INT_MAX / 2) {
            int cutLength = endCol - startCol + 1;
            result = min(result, topPart + bottomPart + cutLength);
        }
    }
    // 尝试所有竖切位置
    for (int cutCol = startCol; cutCol < endCol; cutCol++) {
        int leftPart = findMinCutLength(startRow, startCol, endRow, cutCol);
        int rightPart = findMinCutLength(startRow, cutCol + 1, endRow, endCol);
        if (leftPart < INT_MAX / 2 && rightPart < INT_MAX / 2) {
            int cutLength = endRow - startRow + 1;
            result = min(result, leftPart + rightPart + cutLength);
        }
    }
    return result;
}

int main() {
    int testCase = 1;
    while (cin >> rowSize >> colSize >> cherryCount) {
        memset(cherryGrid, 0, sizeof(cherryGrid));
        memset(prefixSum, 0, sizeof(prefixSum));
        memset(dp, -1, sizeof(dp));
        
        for (int i = 0; i < cherryCount; i++) {
            int row, col;
            cin >> row >> col;
            cherryGrid[row - 1][col - 1] = 1;
        }
        
        // 构建二维前缀和数组
        for (int i = 0; i < rowSize; i++) {
            for (int j = 0; j < colSize; j++) {
                prefixSum[i][j] = cherryGrid[i][j];
                if (i > 0) prefixSum[i][j] += prefixSum[i - 1][j];
                if (j > 0) prefixSum[i][j] += prefixSum[i][j - 1];
                if (i > 0 && j > 0) prefixSum[i][j] -= prefixSum[i - 1][j - 1];
            }
        }
        
        int answer = findMinCutLength(0, 0, rowSize - 1, colSize - 1);
        cout << "Case " << testCase++ << ": " << answer << endl;
    }
    return 0;
}
