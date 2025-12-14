// Cubic Eight-Puzzle
// UVa ID: 1604
// Verdict: Accepted
// Submission Date: 2025-12-09
// UVa Run Time: 0.590s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const char BLUE = 'B', WHITE = 'W', RED = 'R', EMPTY = 'E';

// 上、右、下、左
const int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};

// 立方体状态：1-6表示
// 1: WRB (顶W,前R) - 初始状态
// 2: WBR (顶W,前B)
// 3: RWB (顶R,前W)
// 4: RBW (顶R,前B)
// 5: BWR (顶B,前W)
// 6: BRW (顶B,前R)
int rollCube(int state, int dir) {
    // 方向：0上，1右，2下，3左
    const int rollTable[7][4] = {
        {0, 0, 0, 0},  // 占位
        {3, 6, 3, 6},  // WRB: 上下->RWB, 左右->BRW
        {5, 4, 5, 4},  // WBR: 上下->BWR, 左右->RBW
        {1, 5, 1, 5},  // RWB: 上下->WRB, 左右->BWR
        {6, 2, 6, 2},  // RBW: 上下->BRW, 左右->WBR
        {2, 3, 2, 3},  // BWR: 上下->WBR, 左右->RWB
        {4, 1, 4, 1}   // BRW: 上下->RBW, 左右->WRB
    };
    return rollTable[state][dir];
}

map<char, vector<int>> getStatesForTopColor = {{WHITE, {1, 2}}, {RED, {3, 4}}, {BLUE, {5, 6}}};

struct State {
    int states[9];   // 0表示空位
    int emptyPos;
    int steps;
    int encode() const {
        int s = 0;
        for (int i = 0; i < 9; i++) s = s * 7 + states[i];
        return s;
    }
};

char target[3][3];

// 生成所有可能的目标状态
vector<State> getStates() {
    vector<State> result;
    vector<vector<int>> possibleStates(9);
    int emptyPos = -1;
    for (int i = 0; i < 9; i++) {
        int row = i / 3, col = i % 3;
        char color = target[row][col];
        if (color == EMPTY) {
            possibleStates[i] = {0};
            emptyPos = i;
        } else possibleStates[i] = getStatesForTopColor[color];
    }
    State base;
    base.emptyPos = emptyPos;
    base.steps = 0;
    function<void(int)> dfs = [&](int pos) {
        if (pos == 9) {
            result.push_back(base);
            return;
        }
        for (int s : possibleStates[pos]) {
            base.states[pos] = s;
            dfs(pos + 1);
        }
    };
    dfs(0);
    return result;
}

int bfs(const State& start) {
    // q[0]正向BFS, q[1]反向BFS
    queue<State> q[2];
    // visited[0]记录正向结果，visited[1]记录反向结果
    unordered_map<int, int> visited[2];
    q[0].push(start);
    visited[0][start.encode()] = 0;
    // 将目标状态放入队列
    int startCode = start.encode();
    for (const State& ts : getStates()) {
        int tsCode = ts.encode();
        if (tsCode == startCode) return 0;  // 初始状态已经是某个目标状态
        q[1].push(ts);
        visited[1][tsCode] = 0;
    }
    // 双向BFS，每边最多15步
    while (!q[0].empty() || !q[1].empty()) {
        int self;
        if (q[0].empty()) self = 1;
        else if (q[1].empty()) self = 0;
        else self = q[0].size() < q[1].size() ? 0 : 1;
        int other = 1 - self;
        // 选择较小的队列扩展（优化）
        int levelSize = q[self].size();
        for (int i = 0; i < levelSize; i++) {
            State cur = q[self].front(); q[self].pop();
            // 两个方向的步数限制不同，正向不超过21步，反向不超过9步，因为正向
            // 只有一个状态，而反向初始状态有256个
            if (!self && cur.steps >= 21) continue;
            if (self && cur.steps >= 9) continue;
            int x = cur.emptyPos / 3, y = cur.emptyPos % 3;
            for (int d = 0; d < 4; d++) {
                int nx = x + dx[d], ny = y + dy[d];
                if (nx < 0 || nx >= 3 || ny < 0 || ny >= 3) continue;
                int newEmptyPos = nx * 3 + ny;
                State next = cur;
                next.emptyPos = newEmptyPos;
                next.steps = cur.steps + 1;
                // 滚动立方体，空位的滚动方向和立方体的滚动方向相反
                int rolledState = rollCube(cur.states[newEmptyPos], (d + 2) % 4);
                next.states[cur.emptyPos] = rolledState;
                next.states[newEmptyPos] = 0;
                int code = next.encode();
                if (visited[self].count(code)) continue;
                // 检查是否与反向状态相遇
                if (visited[other].count(code)) return next.steps + visited[other][code];
                visited[self][code] = next.steps;
                q[self].push(next);
            }
        }
    }
    return -1;  // 未找到30步内的解
}

int main() {
    int x, y;
    while (cin >> x >> y && (x || y)) {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                cin >> target[i][j];
        // 构建初始状态：所有立方体状态为1 (WRB)
        State start;
        for (int i = 0; i < 9; i++) start.states[i] = 1;
        start.emptyPos = (y - 1) * 3 + (x - 1);  // x是列，y是行
        start.states[start.emptyPos] = 0;
        start.steps = 0;
        // 双向BFS
        int result = bfs(start);
        // 输出结果
        if (result > 30 || result < 0) cout << "-1\n";
        else cout << result << "\n";
    }
    return 0;
}
