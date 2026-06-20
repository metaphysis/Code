// Guards Imbecile Guards
// UVa ID: 11359
// Verdict: Accepted
// Submission Date: 2026-06-20
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 访问数组，最大编码值为 (99*22 + 21)*22*22 + 21*22 + 21 = 1064799
bool vis[1064800];

// 将守卫的列和方向编码为一个整数 (状态值范围 2..21，0 表示无守卫)
int encodeGuardState(int col, int dir) {
    return (col + 1) * 2 + dir;
}

// 解码守卫状态，返回 {列, 方向}，方向 0 左 1 右
pair<int, int> decodeGuardState(int state) {
    int dir = state % 2;
    int col = state / 2 - 1;
    return {col, dir};
}

// 计算守卫下一秒的列和方向
pair<int, int> nextGuardState(int row, int col, int dir, const vector<string>& maze, int N) {
    int dc = (dir == 1) ? 1 : -1;
    int nc = col + dc;
    // 碰到障碍物或边界则掉头
    if (nc < 0 || nc >= N || maze[row][nc] == '#') {
        dir = 1 - dir;
        dc = (dir == 1) ? 1 : -1;
        nc = col + dc;
        // 若掉头后仍无法移动（极少情况），则原地不动
        if (nc < 0 || nc >= N || maze[row][nc] == '#')
            nc = col;
    }
    return {nc, dir};
}

// 搜索状态：玩家位置 + 最多3个守卫的状态
struct State {
    int playerRow, playerCol;
    int guardStates[3];

    long long encode() const {
        return ((((playerRow * 10LL + playerCol) * 22LL + guardStates[0]) * 22LL + guardStates[1]) * 22LL + guardStates[2]);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int totalCases;
    cin >> totalCases;
    for (int caseIdx = 1; caseIdx <= totalCases; ++caseIdx) {
        int gridSize;
        cin >> gridSize;
        vector<string> maze(gridSize);
        for (int i = 0; i < gridSize; ++i) cin >> maze[i];

        int startRow = -1, startCol = -1, targetRow = -1, targetCol = -1;
        vector<pair<int, int>> guardsPos; // 守卫的 (行, 列)
        for (int i = 0; i < gridSize; ++i)
            for (int j = 0; j < gridSize; ++j)
                if (maze[i][j] == 'S') startRow = i, startCol = j;
                else if (maze[i][j] == 'T') targetRow = i, targetCol = j;
                else if (maze[i][j] == 'X') guardsPos.push_back({i, j});

        int guardCount = guardsPos.size();

        // 起点与守卫同格则直接失败
        bool startBlocked = false;
        for (int i = 0; i < guardCount; ++i)
            if (guardsPos[i].first == startRow && guardsPos[i].second == startCol)
                startBlocked = true;
        if (startBlocked) {
            cout << "Case " << caseIdx << ": -1\n";
            continue;
        }
        // 起点等于终点
        if (startRow == targetRow && startCol == targetCol) {
            cout << "Case " << caseIdx << ": 0\n";
            continue;
        }

        memset(vis, 0, sizeof(vis));
        State startState;
        startState.playerRow = startRow;
        startState.playerCol = startCol;
        // 初始所有守卫方向向右 (1)
        for (int i = 0; i < 3; ++i)
            if (i < guardCount) startState.guardStates[i] = encodeGuardState(guardsPos[i].second, 1);
            else startState.guardStates[i] = 0;

        queue<pair<State, int>> q;
        q.push({startState, 0});
        vis[startState.encode()] = true;
        int minSteps = -1;

        // BFS 搜索最短路程
        while (!q.empty()) {
            State curState = q.front().first;
            int curSteps = q.front().second;
            q.pop();

            // 尝试五个动作：上、下、左、右、停留
            for (int dr = -1; dr <= 1; ++dr) for (int dc = -1; dc <= 1; ++dc) if (abs(dr) + abs(dc) <= 1) {
                int nextPlayerRow = curState.playerRow + dr;
                int nextPlayerCol = curState.playerCol + dc;
                if (nextPlayerRow < 0 || nextPlayerRow >= gridSize || nextPlayerCol < 0 || nextPlayerCol >= gridSize) continue;
                if (maze[nextPlayerRow][nextPlayerCol] == '#') continue;

                bool isCaught = false;
                int nextGuardStates[3];
                // 同时移动所有守卫并检测碰撞
                for (int i = 0; i < guardCount; ++i) {
                    int guardRow = guardsPos[i].first;
                    pair<int, int> dec = decodeGuardState(curState.guardStates[i]);
                    int guardCol = dec.first, guardDir = dec.second;
                    pair<int, int> nextG = nextGuardState(guardRow, guardCol, guardDir, maze, gridSize);
                    int nextGuardCol = nextG.first, nextGuardDir = nextG.second;
                    nextGuardStates[i] = encodeGuardState(nextGuardCol, nextGuardDir);

                    // 检查最终位置是否重合
                    if (nextPlayerRow == guardRow && nextPlayerCol == nextGuardCol) isCaught = true;
                    // 检查是否在移动过程中交叉相遇
                    if (curState.playerRow == guardRow && curState.playerCol == nextGuardCol &&
                        nextPlayerRow == guardRow && nextPlayerCol == guardCol) isCaught = true;
                }
                if (isCaught) continue;
                for (int i = guardCount; i < 3; ++i) nextGuardStates[i] = 0;

                // 安全抵达终点
                if (nextPlayerRow == targetRow && nextPlayerCol == targetCol) {
                    minSteps = curSteps + 1;
                    break;
                }

                State nextState = {nextPlayerRow, nextPlayerCol, {nextGuardStates[0], nextGuardStates[1], nextGuardStates[2]}};
                long long code = nextState.encode();
                if (!vis[code]) {
                    vis[code] = true;
                    q.push({nextState, curSteps + 1});
                }
            }
            if (minSteps != -1) break;
        }
        cout << "Case " << caseIdx << ": " << minSteps << '\n';
    }
    return 0;
}
