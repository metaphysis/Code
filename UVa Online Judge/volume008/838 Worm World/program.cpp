// Worm World
// UVa ID: 838
// Verdict: Accepted
// Submission Date: 2025-11-30
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net


#include <bits/stdc++.h>
using namespace std;

int grid[12][12];
int directions[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};  // 上左下右
bool numberVisited[1001];  // 记录数字是否被访问过
int maxAnswer, uniqueCount, gridSize, testCases, currentSteps;

void dfs(int row, int col) {
    if (maxAnswer == uniqueCount) return;  // 找到理论最大值，提前返回
    numberVisited[grid[row][col]] = false;  // 标记当前数字为未访问
    for (int k = 0; k < 4; k++) {
        int newRow = row + directions[k][0];
        int newCol = col + directions[k][1];
        // 边界检查
        if (newRow < 0 || newRow >= gridSize || newCol < 0 || newCol >= gridSize) continue;
        // 数字重复检查
        if (!numberVisited[grid[newRow][newCol]]) continue;
        currentSteps++;
        dfs(newRow, newCol);
        currentSteps--;
    }
    maxAnswer = max(maxAnswer, currentSteps);
    numberVisited[grid[row][col]] = true;  // 恢复当前数字状态
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> testCases;
    for (int caseNum = 0; caseNum < testCases; caseNum++) {
        cin >> gridSize;
        maxAnswer = uniqueCount = 0;
        memset(numberVisited, 0, sizeof(numberVisited));
        // 读取网格并计算不同数字的数量
        for (int i = 0; i < gridSize; i++)
            for (int j = 0; j < gridSize; j++) {
                cin >> grid[i][j];
                if (!numberVisited[grid[i][j]]) {
                    numberVisited[grid[i][j]] = true;
                    uniqueCount++;
                }
            }
        // 从每个格子开始DFS
        for (int i = 0; i < gridSize; i++)
            for (int j = 0; j < gridSize; j++) {
                currentSteps = 1;
                dfs(i, j);
            }
        cout << maxAnswer << '\n';
        if (caseNum < testCases - 1) cout << '\n';
    }
    return 0;
}
