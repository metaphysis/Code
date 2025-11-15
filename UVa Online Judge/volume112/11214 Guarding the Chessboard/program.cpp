// Guarding the Chessboard
// UVa ID: 11214
// Verdict: Accepted
// Submission Date: 2025-11-05
// UVa Run Time: 0.080s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <string>
#include <bitset>
#include <algorithm>
using namespace std;

int n, m;
vector<pair<int, int>> marks;  // 存储所有标记格子的坐标
int maxMarks;                  // 标记格子的总数
vector<bitset<100>> coverMask; // coverMask[i]表示在位置i放置皇后能覆盖的标记格子
int ans;                       // 最终答案（最少皇后数）

/**
 * 预计算每个位置放置皇后能覆盖哪些标记格子
 * @param board 棋盘状态
 */
void precomputeCoverMasks(const vector<string>& board) {
    coverMask.assign(n * m, bitset<100>());
    
    // 建立坐标到索引的映射
    vector<vector<int>> markIndex(n, vector<int>(m, -1));
    for (int k = 0; k < maxMarks; k++) {
        markIndex[marks[k].first][marks[k].second] = k;
    }
    
    // 对每个位置计算覆盖范围
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            bitset<100> mask;
            
            // 行覆盖：同一行的所有标记格子
            for (int c = 0; c < m; c++) {
                int idx = markIndex[i][c];
                if (idx != -1) mask.set(idx);
            }
            
            // 列覆盖：同一列的所有标记格子
            for (int r = 0; r < n; r++) {
                int idx = markIndex[r][j];
                if (idx != -1) mask.set(idx);
            }
            
            // 主对角线覆盖（左上到右下方向）
            for (int r = i, c = j; r >= 0 && c >= 0; r--, c--) {
                int idx = markIndex[r][c];
                if (idx != -1) mask.set(idx);
            }
            for (int r = i + 1, c = j + 1; r < n && c < m; r++, c++) {
                int idx = markIndex[r][c];
                if (idx != -1) mask.set(idx);
            }
            
            // 副对角线覆盖（右上到左下方向）
            for (int r = i, c = j; r >= 0 && c < m; r--, c++) {
                int idx = markIndex[r][c];
                if (idx != -1) mask.set(idx);
            }
            for (int r = i + 1, c = j - 1; r < n && c >= 0; r++, c--) {
                int idx = markIndex[r][c];
                if (idx != -1) mask.set(idx);
            }
            
            coverMask[i * m + j] = mask;
        }
    }
}

/**
 * 带剪枝的暴力搜索
 * @param curMask 当前已覆盖的标记格子（位掩码）
 * @param queens  当前已放置的皇后数量
 * @param startPos 开始搜索的位置（避免重复组合）
 */
void bruteForceWithPruning(bitset<100> curMask, int queens, int startPos) {
    // 最优性剪枝：当前皇后数已经不少于已知最优解
    if (queens >= ans) return;
    
    // 找到解：所有标记格子都被覆盖
    if (curMask.count() == maxMarks) {
        ans = queens;  // 更新最优解
        return;
    }
    
    // 进一步剪枝：如果已经用了接近最优解的皇后数但还没覆盖完
    if (queens >= ans - 1) return;
    
    // 枚举下一个皇后的位置
    for (int pos = startPos; pos < n * m; pos++) {
        const bitset<100>& newCover = coverMask[pos];
        
        // 有效性剪枝：新皇后必须至少覆盖一个新的标记格子
        // 使用位运算快速检查 newCover & ~curMask 是否非空
        if ((newCover & ~curMask).any()) {
            // 递归搜索：放置皇后并更新覆盖状态
            bruteForceWithPruning(curMask | newCover, queens + 1, pos + 1);
        }
    }
}

int main() {
    int caseNum = 1;
    
    // 处理多个测试用例
    while (cin >> n >> m) {
        if (n == 0) break;  // 输入0结束
        
        // 读入棋盘
        vector<string> board(n);
        for (int i = 0; i < n; i++) {
            cin >> board[i];
            // 确保字符串长度正确
            if (board[i].length() > m) {
                board[i] = board[i].substr(0, m);
            }
        }
        
        // 收集所有标记格子
        marks.clear();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (board[i][j] == 'X') {
                    marks.push_back({i, j});
                }
            }
        }
        maxMarks = marks.size();
        
        // 特殊情况：没有标记格子，需要0个皇后
        if (maxMarks == 0) {
            cout << "Case " << caseNum++ << ": 0" << endl;
            continue;
        }
        
        // 预计算覆盖掩码
        precomputeCoverMasks(board);
        
        // 初始化答案为最坏情况（每个标记格子放一个皇后）
        ans = maxMarks;
        
        // 开始搜索
        bruteForceWithPruning(bitset<100>(), 0, 0);
        
        // 输出结果
        cout << "Case " << caseNum++ << ": " << ans << endl;
    }
    return 0;
}
