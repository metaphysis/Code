// Brick Wall
// UVa ID: 13271
// Verdict: Accepted
// Submission Date: 2025-11-30
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

/**
 * 计算两个山谷点之间的最短路径距离
 * @param startRow 起始行号
 * @param startCol 起始列号  
 * @param endRow 目标行号
 * @param endCol 目标列号
 * @return 最短路径距离
 */
int64_t calculateDistance(int64_t startRow, int64_t startCol, int64_t endRow, int64_t endCol) {
    // 情况1：同一行，直接返回列差的绝对值（可以水平移动）
    if (startRow == endRow) return abs(startCol - endCol);
    
    // 情况2：保证起始行号小于目标行号，方便后续处理
    if (startRow > endRow) return calculateDistance(endRow, endCol, startRow, startCol);
    
    // 情况3：保证起始列号小于目标列号，通过对称变换
    if (startCol > endCol) return calculateDistance(startRow, startCol, endRow, startCol + (startCol - endCol));
    
    // 计算行差和列差（此时startRow <= endRow, startCol <= endCol）
    int64_t rowDiff = endRow - startRow;
    int64_t colDiff = endCol - startCol;
    
    // 情况4：行差小于等于列差，可以直接走曼哈顿距离
    // 因为水平移动相对自由，当列差较大时可以直接到达
    if (rowDiff <= colDiff) return rowDiff + colDiff;
    
    // 情况5：复杂情况 - 行差大于列差，需要蛇形移动
    // 由于砖墙的特殊结构，垂直移动受到限制
    
    // 步骤1：先在水平方向移动到目标列
    startRow += colDiff;  // 同时向下移动colDiff行
    int64_t distance = colDiff * 2;  // 水平移动colDiff，垂直移动colDiff
    
    // 步骤2：检查当前行与目标行的奇偶性是否相同
    // 砖墙结构导致不同奇偶性的行之间移动受限
    if (startRow % 2 != endRow % 2) {
        // 行奇偶性不同，需要额外绕行
        // 根据当前位置的奇偶性决定绕行代价
        if ((startRow + endCol) % 2) {
            distance += 3;  // 需要3步绕行
        } else {
            distance += 1;  // 需要1步绕行
        }
        startRow++;  // 移动到下一行
    }
    
    // 步骤3：剩余的行差通过蛇形移动完成
    // 每向下移动一行需要2步（上下往返）
    distance += (endRow - startRow) * 2;
    
    return distance;
}

int main() {
    int64_t startRow, startCol, endRow, endCol;
    
    // 读取测试用例，直到遇到 0 0 0 0
    while (scanf("%lld %lld %lld %lld", &startRow, &startCol, &endRow, &endCol) == 4 && startRow) {
        printf("%lld\n", calculateDistance(startRow, startCol, endRow, endCol));
    }
    
    return 0;
}
