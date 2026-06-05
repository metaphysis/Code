// Pipes
// UVa ID: 11700
// Verdict: Accepted
// Submission Date: 2026-06-05
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXC = 12;
const int MAXS = 1 << MAXC;

int R, C;
int grid[15][15];          // 原始方向掩码
int dp[15][MAXS];          // dp[row][status] 记忆化
int vis[15][MAXS];         // 访问标记
int curCase;               // 当前测试用例编号

int rotateMask(int mask, int k) {
    if (k == 0) return mask;
    int res = 0;
    for (int d = 0; d < 4; d++)
        if (mask & (1 << d))
            res |= (1 << ((d + k) % 4));
    return res;
}

// 检查当前格子旋转后是否与左、上匹配，并返回新的状态
int check(int upStatus, int curMask, int col, int leftMask) {
    // 检查与上方邻居（北）
    bool upNeed = (upStatus >> col) & 1;
    bool curNorth = (curMask >> 0) & 1;
    if (upNeed != curNorth) return -1;
    
    // 检查与左方邻居（西）
    if (col > 0) {
        bool leftNeed = (leftMask >> 1) & 1;
        bool curWest = (curMask >> 3) & 1;
        if (leftNeed != curWest) return -1;
    }
    
    // 构建新的状态（当前格子朝南的线）
    int newStatus = upStatus;
    bool curSouth = (curMask >> 2) & 1;
    if (curSouth) newStatus |= (1 << col);
    else newStatus &= ~(1 << col);
    
    return newStatus;
}

// 处理第row行，upStatus是上一行留下的朝南状态
bool dfsRow(int row, int upStatus) {
    if (row == R) return upStatus == 0; // 最后一行不能有向下的线
    
    if (vis[row][upStatus] == curCase) return dp[row][upStatus];
    vis[row][upStatus] = curCase;
    
    vector<int> curMask(C);
    
    // 递归枚举当前行的每一列
    function<bool(int, int)> dfsCol = [&](int col, int curStatus) -> bool {
        if (col == C) return dfsRow(row + 1, curStatus);
        
        for (int rot = 0; rot < 4; rot++) {
            int rotated = rotateMask(grid[row][col], rot);
            
            // 边界检查
            if (col == C - 1 && (rotated & (1 << 1))) continue; // 朝东出界
            if (row == R - 1 && (rotated & (1 << 2))) continue; // 朝南出界
            if (col == 0 && (rotated & (1 << 3))) continue;     // 朝西出界
            // 朝北出界由check函数处理（upStatus对应位为0则不能有北线）
            
            int leftMask = (col > 0) ? curMask[col - 1] : 0;
            int newStatus = check(curStatus, rotated, col, leftMask);
            if (newStatus != -1) {
                curMask[col] = rotated;
                if (dfsCol(col + 1, newStatus)) return true;
            }
        }
        return false;
    };
    
    return dp[row][upStatus] = dfsCol(0, upStatus);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    memset(vis, 0, sizeof(vis));
    curCase = 0;
    
    while (cin >> R >> C && (R || C)) {
        curCase++;
        
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                string s; cin >> s;
                if (s == "x") {
                    grid[i][j] = 0;
                    continue;
                }
                int mask = 0;
                for (char ch : s) {
                    if (ch == 'N') mask |= 1 << 0;
                    else if (ch == 'E') mask |= 1 << 1;
                    else if (ch == 'S') mask |= 1 << 2;
                    else if (ch == 'W') mask |= 1 << 3;
                }
                grid[i][j] = mask;
            }
        }
        
        bool solvable = dfsRow(0, 0);
        cout << (solvable ? "SOLVABLE" : "UNSOLVABLE") << '\n';
    }
    
    return 0;
}
