#include <bits/stdc++.h>
using namespace std;

struct State {
    int r, c, d;
};

struct Move {
    int r, c;
    bool out;
};

int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, 1, 0, -1};

int dirId(char ch) {
    if (ch == 'U') return 0;
    if (ch == 'R') return 1;
    if (ch == 'D') return 2;
    return 3;
}

bool inside(int r, int c, int rows, int cols) {
    return r >= 0 && r < rows && c >= 0 && c < cols;
}

int buildCycle(const vector<string> &maze, int rows, int cols, int startR, int startC, int startD, vector<State> &states, vector<Move> &moves) {
    vector<int> seen(rows * cols * 4, -1);
    State cur = {startR, startC, startD};
    while (true) {
        int key = (cur.r * cols + cur.c) * 4 + cur.d;
        if (seen[key] != -1) return seen[key];
        seen[key] = states.size();
        states.push_back(cur);
        int order[4] = {(cur.d + 1) % 4, cur.d, (cur.d + 3) % 4, (cur.d + 2) % 4};
        Move nxt = {cur.r, cur.c, false};
        int nextD = cur.d;
        for (int i = 0; i < 4; i++) {
            int nd = order[i];
            int nr = cur.r + dr[nd], nc = cur.c + dc[nd];
            if (!inside(nr, nc, rows, cols)) {
                nxt.r = startR;
                nxt.c = startC;
                nxt.out = true;
                nextD = startD;
                break;
            }
            if (maze[nr][nc] == '.') {
                nxt.r = nr;
                nxt.c = nc;
                nextD = nd;
                break;
            }
        }
        moves.push_back(nxt);
        cur = {nxt.r, nxt.c, nextD};
    }
}

int solveCase(const vector<string> &maze, int rows, int cols, int startR, int startC, int destR, int destC, int agentR, int agentC, int agentD) {
    vector<State> states;
    vector<Move> moves;
    int repeatAt = buildCycle(maze, rows, cols, agentR, agentC, agentD, states, moves);
    int stateCount = states.size(), cellCount = rows * cols;
    vector<int> dist(stateCount * cellCount, -1);
    queue<pair<int, int>> que;
    int startPos = startR * cols + startC;
    int initialAgentPos = agentR * cols + agentC;
    if (startPos == initialAgentPos) return -1;
    dist[startPos] = 0;
    que.push({startPos, 0});
    while (!que.empty()) {
        int pos = que.front().first, phase = que.front().second;
        que.pop();
        int time = dist[phase * cellCount + pos];
        int r = pos / cols, c = pos % cols;
        if (r == destR && c == destC) return time;
        int agentPos = states[phase].r * cols + states[phase].c;
        int nextPhase = phase + 1 < stateCount ? phase + 1 : repeatAt;
        Move agentMove = moves[phase];
        int nextAgentPos = agentMove.r * cols + agentMove.c;
        int playerDr[5] = {-1, 0, 1, 0, 0};
        int playerDc[5] = {0, 1, 0, -1, 0};
        for (int i = 0; i < 5; i++) {
            int nr = r + playerDr[i], nc = c + playerDc[i];
            if (i < 4 && !inside(nr, nc, rows, cols)) continue;
            if (i < 4 && maze[nr][nc] != '.') continue;
            int nextPos = nr * cols + nc;
            if (nextPos == nextAgentPos) continue;
            if (!agentMove.out && pos == nextAgentPos && nextPos == agentPos) continue;
            int index = nextPhase * cellCount + nextPos;
            if (dist[index] != -1) continue;
            dist[index] = time + 1;
            que.push({nextPos, nextPhase});
        }
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    for (int testCase = 1; testCase <= testCount; testCase++) {
        int rows, cols;
        cin >> rows >> cols;
        int startR, startC, destR, destC, agentR, agentC;
        char face;
        cin >> startR >> startC >> destR >> destC >> agentR >> agentC >> face;
        vector<string> maze(rows);
        for (int i = 0; i < rows; i++) cin >> maze[i];
        int answer = solveCase(maze, rows, cols, startR, startC, destR, destC, agentR, agentC, dirId(face));
        cout << "Maze " << testCase << ": " << answer << '\n';
    }
    return 0;
}
