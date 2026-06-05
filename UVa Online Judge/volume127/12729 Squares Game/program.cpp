// Squares Game
// UVa ID: 12729
// Verdict: Accepted
// Submission Date: 2026-06-05
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    scanf("%d", &T);
    for (int caseNum = 1; caseNum <= T; ++caseNum) {
        int N, M;
        scanf("%d %d", &N, &M);
        
        int total = N * M;                      // 总格子数
        
        // 核心区：最大的偶数×偶数子棋盘
        int evenN = N - (N % 2);                // N为奇数时减1，偶数不变
        int evenM = M - (M % 2);                // M为奇数时减1，偶数不变
        
        int blockRows = evenN / 2;              // 核心区有多少行2×2方块
        int blockCols = evenM / 2;              // 核心区有多少列2×2方块
        int totalBlocks = blockRows * blockCols; // 核心区2×2方块总数
        
        // 安娜能占的方块数 = 总方块数的一半（向上取整）
        int anaBlocks = (totalBlocks + 1) / 2;
        int anaCells = anaBlocks * 4;            // 安娜标记的格子数
        
        int bobCells = total - anaCells;         // 鲍勃标记的格子数
        
        if (anaCells > bobCells)
            printf("Case #%d: Ana\n", caseNum);
        else if (anaCells == bobCells)
            printf("Case #%d: Draw\n", caseNum);
        else
            printf("Case #%d: Bob\n", caseNum);
    }
    return 0;
}
