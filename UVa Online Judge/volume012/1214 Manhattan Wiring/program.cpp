// Manhattan Wiring
// UVa ID: 1214
// Verdict: Accepted
// Submission Date: 2025-10-09
// UVa Run Time: 0.630s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f;
const int MAX_N = 9;
const int MAX_M = 9;
const int MAX_STATE = 1 << 20;

// 网格和DP状态
int grid[MAX_N][MAX_M];
int dp[MAX_N][MAX_M][MAX_STATE];
int visited[MAX_N][MAX_M][MAX_STATE];
int caseId = 0;

int n, m;
int stateMask;

// 转移模式定义
// 每个模式是一个4字符字符串，分别表示: [左, 上, 右, 下] 方向是否有连接
const char TRANSFER_PATTERNS[10][5] = {
    "0100", "0010", "0001", "1000",  // 直线连接模式
    "0110", "0011", "1001", "1100",  // 拐角连接模式  
    "1010", "0101"                   // 交叉连接模式
};

// 获取当前格子上方的插头状态
inline int getUpperPlug(int state) {
    return state & 3;
}

// 获取当前格子左方的插头状态
inline int getLeftPlug(int state) {
    return (state >> (m * 2)) & 3;
}

/**
 * 深度优先搜索进行插头DP
 * @param x 当前列坐标 (0-based)
 * @param y 当前行坐标 (0-based) 
 * @param state 当前轮廓线状态
 * @return 从当前状态到结束的最小路径长度
 */
int dfs(int x, int y, int state) {
    // 换行处理：到达行末时转到下一行开头
    if (x == m) {
        y++;
        x = 0;
    }
    
    // 终止条件：处理完所有格子
    if (y == n) {
        return 0;
    }
    
    // 记忆化检查
    if (visited[x][y][state] == caseId) {
        return dp[x][y][state];
    }
    
    int minLength = INF;
    int upperPlug = getUpperPlug(state);
    int leftPlug = getLeftPlug(state);
    int cellType = grid[y][x];
    
    // 处理障碍物或普通格子
    if (cellType <= 1) {
        // 空状态转移：没有插头连接时可以直接跳过
        if (upperPlug == 0 && leftPlug == 0) {
            int newState = state >> 2;
            minLength = min(minLength, dfs(x + 1, y, newState));
        }
        
        // 普通格子可以创建新路径
        if (cellType == 0) {
            // 尝试类型2和类型3的路径（pathType=2代表类型2，pathType=3代表类型3）
            for (int patternIndex = 4; patternIndex < 10; patternIndex++) {
                for (int pathType = 2; pathType <= 3; pathType++) {
                    // 解析转移模式
                    int leftConn = (TRANSFER_PATTERNS[patternIndex][0] - '0') ? pathType : 0;
                    int upperConn = (TRANSFER_PATTERNS[patternIndex][1] - '0') ? pathType : 0;
                    int rightConn = (TRANSFER_PATTERNS[patternIndex][2] - '0') ? pathType : 0;
                    int downConn = (TRANSFER_PATTERNS[patternIndex][3] - '0') ? pathType : 0;
                    
                    // 边界检查
                    if (x == m - 1 && rightConn) continue;  // 最右列不能向右连接
                    if (y == n - 1 && downConn) continue;   // 最下行不能向下连接
                    
                    // 状态匹配检查
                    if (upperPlug != upperConn) continue;
                    if (leftPlug != leftConn) continue;
                    
                    // 构建新状态
                    int newState = (state & stateMask) >> 2;
                    newState |= rightConn << (m * 2);
                    newState |= downConn << (m * 2 - 2);
                    
                    minLength = min(minLength, dfs(x + 1, y, newState) + 2);
                }
            }
        }
    } 
    // 处理特殊点（类型2或3）
    else {
        // 尝试4种基本连接模式
        for (int patternIndex = 0; patternIndex < 4; patternIndex++) {
            int leftConn = (TRANSFER_PATTERNS[patternIndex][0] - '0') ? cellType : 0;
            int upperConn = (TRANSFER_PATTERNS[patternIndex][1] - '0') ? cellType : 0;
            int rightConn = (TRANSFER_PATTERNS[patternIndex][2] - '0') ? cellType : 0;
            int downConn = (TRANSFER_PATTERNS[patternIndex][3] - '0') ? cellType : 0;
            
            // 边界检查
            if (x == m - 1 && rightConn) continue;  // 最右列不能向右连接
            if (y == n - 1 && downConn) continue;   // 最下行不能向下连接
            
            // 状态匹配检查
            if (upperPlug != upperConn) continue;
            if (leftPlug != leftConn) continue;
            
            // 构建新状态
            int newState = (state & stateMask) >> 2;
            newState |= rightConn << (m * 2);
            newState |= downConn << (m * 2 - 2);
            
            minLength = min(minLength, dfs(x + 1, y, newState) + 1);
        }
    }
    
    // 记忆化存储结果
    visited[x][y][state] = caseId;
    return dp[x][y][state] = minLength;
}

int main() {
    // 初始化访问标记数组
    memset(visited, -1, sizeof(visited));
    
    while (scanf("%d%d", &n, &m) == 2 && n && m) {
        // 读取网格数据
        for (int row = 0; row < n; row++) {
            for (int col = 0; col < m; col++) {
                scanf("%d", &grid[row][col]);
            }
        }
        
        // 初始化状态掩码（用于清除当前列的状态位）
        stateMask = (1 << (m * 2)) - 1;
        caseId++;
        
        // 求解并输出结果
        int result = dfs(0, 0, 0);
        if (result < INF) {
            // 除以2是因为每条边被计算了两次（进入和离开）
            printf("%d\n", result / 2);
        } else {
            printf("0\n");
        }
    }
    
    return 0;
}
