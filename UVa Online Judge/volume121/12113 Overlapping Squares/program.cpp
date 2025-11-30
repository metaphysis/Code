// Overlapping Squares
// UVa ID: 12113
// Verdict: Accepted
// Submission Date: 2025-11-28
// UVa Run Time: 0.130s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 存储所有可能的图案（使用字符串表示，避免编码冲突）
unordered_set<string> allPatterns;

// 标准2x2正方形的字符模板（3行5列）
const char squareTemplate[3][5] = {
    {' ', '_', ' ', '_', ' '},  // 上边框：两条横线，中间有空格
    {'|', ' ', ' ', ' ', '|'},  // 中间行：左右竖边，内部空格
    {'|', '_', ' ', '_', '|'}   // 下边框：左右竖边和两条横线
};

// 将5x9网格转换为字符串表示
string patternToString(const char grid[5][10]) {
    string result;
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 9; j++)
            result += grid[i][j];
    return result;
}

// 在指定位置放置一个2x2正方形
void placeSquare(char grid[5][10], int pos) {
    int row = pos / 3;  // 计算行位置（0-2）
    int col = pos % 3;  // 计算列位置（0-2）
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 5; j++) {
            int gridRow = row + i;
            int gridCol = col * 2 + j;  // 列位置乘以2，因为每个正方形水平占5个字符
            if (gridRow >= 5 || gridCol >= 9) continue;
            char templateChar = squareTemplate[i][j];
            char currentChar = grid[gridRow][gridCol];
            if (i == 0) {  // 上边界特殊处理
                if (templateChar == '_') 
                    grid[gridRow][gridCol] = '_';  // 横线直接覆盖
                else if (currentChar == '|') 
                    ;  // 保留竖边（竖边穿过上边界）
                else 
                    grid[gridRow][gridCol] = ' ';  // 其他情况用空格覆盖
            } else {
                // 中间行和下边界：直接用模板字符覆盖
                grid[gridRow][gridCol] = templateChar;
            }
        }
    }
}

// 标准化图案：提取有效区域并靠上靠左放置
void normalizePattern(char grid[5][10]) {
    int minRow = 5, maxRow = -1, minCol = 9, maxCol = -1;
    
    // 找到包含非空格字符的最小矩形区域
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 9; j++) {
            if (grid[i][j] != ' ') {
                minRow = min(minRow, i);
                maxRow = max(maxRow, i);
                minCol = min(minCol, j);
                maxCol = max(maxCol, j);
            }
        }
    }
    
    if (minRow > maxRow || minCol > maxCol) return;  // 没有有效字符
    
    // 创建新的标准化网格
    char normalized[5][10];
    memset(normalized, ' ', sizeof(normalized));
    
    // 将有效区域平移到左上角
    for (int i = minRow; i <= maxRow; i++) {
        for (int j = minCol; j <= maxCol; j++) {
            int newI = i - minRow;
            int newJ = j - minCol;
            if (newI < 5 && newJ < 9) 
                normalized[newI][newJ] = grid[i][j];
        }
    }
    
    memcpy(grid, normalized, sizeof(normalized));
}

// DFS回溯生成所有可能的图案组合（最多6个正方形）
void generatePatterns(char grid[5][10], int count) {
    // 标准化当前图案并存储
    char normalized[5][10];
    memcpy(normalized, grid, sizeof(normalized));
    normalizePattern(normalized);
    allPatterns.insert(patternToString(normalized));
    
    if (count == 6) return;  // 最多放置6个正方形
    
    // 尝试在所有9个可能位置放置正方形
    for (int i = 0; i < 9; i++) {
        // 保存当前状态用于回溯
        char backup[5][10];
        memcpy(backup, grid, sizeof(backup));
        
        // 放置正方形并继续搜索
        placeSquare(grid, i);
        generatePatterns(grid, count + 1);
        
        // 回溯：恢复之前的状态
        memcpy(grid, backup, sizeof(backup));
    }
}

// 预生成所有可能的图案
void generateAllPatterns() {
    char grid[5][10];
    memset(grid, ' ', sizeof(grid));  // 初始化为全空格
    generatePatterns(grid, 0);
}

// 标准化输入的目标图案
void normalizeTarget(char target[5][10]) {
    char processed[5][10];
    memset(processed, ' ', sizeof(processed));
    // 去除输入中的#号，只保留有效字符
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 9 && target[i][j] != '#'; j++)
            processed[i][j] = target[i][j];
    // 标准化处理后的图案
    normalizePattern(processed);
    memcpy(target, processed, sizeof(processed));
}

int main() {
    // 预处理：生成所有可能的图案
    generateAllPatterns();
    
    int caseNum = 1;
    string line;
    
    // 处理每个测试用例
    while (true) {
        getline(cin, line);
        if (line == "0") break;  // 输入0结束
        
        // 读取目标图案
        char target[5][10];
        memset(target, ' ', sizeof(target));
        for (int i = 0; i < 5; i++) {
            if (i > 0) getline(cin, line);
            for (int j = 0; j < 9; j++) 
                target[i][j] = line[j];
        }
        
        // 标准化目标图案并在预生成的图案集合中查找
        normalizeTarget(target);
        string targetStr = patternToString(target);
        bool found = allPatterns.count(targetStr);
        
        // 输出结果
        cout << "Case " << caseNum++ << ": " << (found ? "Yes" : "No") << endl;
    }
    
    return 0;
}
