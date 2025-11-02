// Ships
// UVa ID: 322
// Verdict: Accepted
// Submission Date: 2025-11-01
// UVa Run Time: 0.010s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

char grid[16][17];           // 输入的游戏网格
char solutions[300][16][17]; // 存储所有可能的解
int solutionCount;          // 解的个数

// 每种船型的旋转数量
int rotations[7] = {1, 2, 2, 4, 4, 4, 2};

// 7种船型的定义，每种有最多4种旋转
char ships[7][4][4][5] = {
    // 1. 2x2方块
    {"xx  ", "xx  ", "    ", "    "},
    // 2. Z型1
    {"xx  ", " xx ", "    ", "    ", 
     " x  ", "xx  ", "x   ", "    "},
    // 3. Z型2  
    {" xx ", "xx  ", "    ", "    ",
     "x   ", "xx  ", " x  ", "    "},
    // 4. T型（4种旋转）
    {"x   ", "xxx ", "    ", "    ",
     "xx  ", "x   ", "x   ", "    ", 
     "xxx ", "  x ", "    ", "    ",
     " x  ", " x  ", "xx  ", "    "},
    // 5. L型1（4种旋转）
    {"  x ", "xxx ", "    ", "    ",
     "xx  ", " x  ", " x  ", "    ",
     "xxx ", "x   ", "    ", "    ",
     "x   ", "x   ", "xx  ", "    "},
    // 6. L型2（4种旋转）
    {" x  ", "xxx ", "    ", "    ",
     " x  ", "xx  ", " x  ", "    ",
     "xxx ", " x  ", "    ", "    ",
     "x   ", "xx  ", "x   ", "    "},
    // 7. 直线型（2种旋转）
    {"xxxx", "    ", "    ", "    ",
     "x   ", "x   ", "x   ", "x   "}
};

char backup[7][16][17]; // 用于回溯时保存状态

// 检查船型能否放置在指定位置
bool canPlace(int shipType, int rotation, int row, int col, int height, int width) {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            // 只检查船体部分('x')
            if (ships[shipType][rotation][i][j] == 'x') {
                // 检查边界
                if (row + i >= height || col + j >= width) return false;
                // 检查网格是否可放置(只能是'.'或'x')
                if (grid[row + i][col + j] != '.' && grid[row + i][col + j] != 'x') return false;
            }
    return true;
}

// 深度优先搜索放置所有7艘船
void dfs(int depth, int height, int width, int dotCount) {
    // 剪枝：如果解的数量超过未知格子数量，提前返回
    if (solutionCount > dotCount) return;
    // 所有船都已放置完成
    if (depth == 7) {
        // 检查是否所有已知的'x'都被覆盖
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (grid[i][j] == 'x') return;
            }
        }
        // 保存当前解：标记为船的位置存为'x'，其他为空格
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (grid[i][j] >= '0' && grid[i][j] <= '9') {
                    solutions[solutionCount][i][j] = 'x'; // 船的位置
                } else {
                    solutions[solutionCount][i][j] = ' '; // 水的位置
                }
            }
        }
        // 去重：检查是否与已有解重复
        for (int k = 0; k < solutionCount; k++) {
            bool isDuplicate = true;
            for (int i = 0; i < height && isDuplicate; i++) {
                for (int j = 0; j < width && isDuplicate; j++) {
                    if (solutions[k][i][j] != solutions[solutionCount][i][j]) {
                        isDuplicate = false;
                    }
                }
            }
            if (isDuplicate) return;
        }
        solutionCount++;
        return;
    }
    
    // 尝试所有可能的位置和旋转
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            // 尝试所有可能的旋转
            for (int rotation = rotations[depth] - 1; rotation >= 0; rotation--) {
                if (canPlace(depth, rotation, row, col, height, width)) {
                    // 保存当前状态并放置船
                    for (int i = 0; i < 4; i++) {
                        for (int j = 0; j < 4; j++) {
                            if (ships[depth][rotation][i][j] == 'x') {
                                backup[depth][row + i][col + j] = grid[row + i][col + j];
                                grid[row + i][col + j] = '0' + depth; // 用数字标记船
                            }
                        }
                    }
                    // 递归放置下一艘船
                    dfs(depth + 1, height, width, dotCount);
                    // 回溯：恢复原始状态
                    for (int i = 0; i < 4; i++)
                        for (int j = 0; j < 4; j++)
                            if (ships[depth][rotation][i][j] == 'x')
                                grid[row + i][col + j] = backup[depth][row + i][col + j];
                }
            }
        }
    }
}

// 检查是否能在最多一次miss的情况下确定所有船的位置
bool canDetermine(int height, int width, int dotCount) {
    solutionCount = 0;
    dfs(0, height, width, dotCount);
    
    // 如果只有一个解，直接可以确定
    if (solutionCount == 1) return true;
    // 如果解太多或没有解，无法确定
    if (solutionCount > dotCount || solutionCount == 0) return false;
    
    // 逐步消元：模拟翻牌过程
    bool changed;
    do {
        changed = false;
        for (int row = 0; row < height; row++) {
            for (int col = 0; col < width; col++) {
                // 只检查未知格子
                if (grid[row][col] == '.') {
                    int waterCount = 0;    // 该位置为水的解的数量
                    int waterIndex = -1;   // 唯一为水的解的索引
                    
                    // 统计在所有解中该位置为水的次数
                    for (int i = 0; i < solutionCount; i++)
                        if (solutions[i][row][col] == ' ') {
                            waterCount++;
                            waterIndex = i;
                        }
                    
                    // 如果只有一个解中这里是水，翻到这个水就能排除这个解
                    if (waterCount == 1 && solutionCount > 1) {
                        // 移除这个解（用最后一个解覆盖它）
                        for (int i = 0; i < height; i++)
                            for (int j = 0; j < width; j++)
                                solutions[waterIndex][i][j] = solutions[solutionCount - 1][i][j];
                        solutionCount--;
                        changed = true;
                    }
                }
            }
        }
    } while (changed); // 继续直到没有变化
    return solutionCount < 2;
}

int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int width, height, testCase = 1;
    while (cin >> width >> height && width != 0) {
        int dotCount = 0;
        // 读取输入并统计未知格子数量
        for (int i = 0; i < height; i++) {
            cin >> grid[i];
            for (int j = 0; j < width; j++)
                if (grid[i][j] == '.') dotCount++;
        }
        cout << "Game #" << testCase++ << endl;
        if (canDetermine(height, width, dotCount)) cout << "yes.";
        else cout << "no.";
        cout << "\n\n";
    }
    return 0;
}
