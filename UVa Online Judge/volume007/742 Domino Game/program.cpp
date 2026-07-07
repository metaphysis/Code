// Domino Game
// UVa ID: 742
// Verdict: Accepted
// Submission Date: 2026-07-05
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 28张多米诺牌，每张牌两个数字，编号0~27
int domino[28][2];
int idxMap[7][7];

// 游戏状态
struct State {
    int left, right;          // 当前链两端数字
    int turn;                 // 0: Red, 1: Green
    uint32_t maskR, maskG;    // 各自剩余牌的位掩码（28位）

    bool operator==(const State& other) const {
        return left == other.left && right == other.right &&
               turn == other.turn && maskR == other.maskR && maskG == other.maskG;
    }
};

// 哈希函数，用于unordered_set
struct StateHash {
    size_t operator()(const State& s) const {
        uint64_t h1 = (uint64_t)s.left << 60 | (uint64_t)s.right << 54 |
                      (uint64_t)s.turn << 53 | (uint64_t)s.maskR << 25 |
                      (uint64_t)s.maskG;
        return (size_t)h1;
    }
};

// 判断目标玩家（target = 0 表示 Red，1 表示 Green）是否有获胜路径
bool canWin(int target, const State& init) {
    queue<State> q;
    unordered_set<State, StateHash> visited;
    q.push(init);
    visited.insert(init);

    while (!q.empty()) {
        State cur = q.front(); q.pop();

        // 检查是否有人获胜
        if (cur.maskR == 0) return target == 0;   // Red 出完
        if (cur.maskG == 0) return target == 1;   // Green 出完

        uint32_t mask = (cur.turn == 0) ? cur.maskR : cur.maskG;
        bool hasMove = false;

        // 枚举当前玩家的每张牌
        for (int id = 0; id < 28; ++id) {
            if (!(mask & (1u << id))) continue;
            int a = domino[id][0], b = domino[id][1];

            // 尝试匹配左端
            if (a == cur.left || b == cur.left) {
                hasMove = true;
                int newLeft = (a == cur.left) ? b : a;
                int newRight = cur.right;
                uint32_t newMaskR = cur.maskR, newMaskG = cur.maskG;
                if (cur.turn == 0) newMaskR &= ~(1u << id);
                else newMaskG &= ~(1u << id);
                State nxt{newLeft, newRight, 1 - cur.turn, newMaskR, newMaskG};
                if (!visited.count(nxt)) {
                    if (nxt.maskR == 0 && target == 0) return true;
                    if (nxt.maskG == 0 && target == 1) return true;
                    visited.insert(nxt);
                    q.push(nxt);
                }
            }

            // 尝试匹配右端
            if (a == cur.right || b == cur.right) {
                hasMove = true;
                int newRight = (a == cur.right) ? b : a;
                int newLeft = cur.left;
                uint32_t newMaskR = cur.maskR, newMaskG = cur.maskG;
                if (cur.turn == 0) newMaskR &= ~(1u << id);
                else newMaskG &= ~(1u << id);
                State nxt{newLeft, newRight, 1 - cur.turn, newMaskR, newMaskG};
                if (!visited.count(nxt)) {
                    if (nxt.maskR == 0 && target == 0) return true;
                    if (nxt.maskG == 0 && target == 1) return true;
                    visited.insert(nxt);
                    q.push(nxt);
                }
            }
        }

        // 当前玩家无牌可出，跳过回合
        if (!hasMove) {
            State nxt{cur.left, cur.right, 1 - cur.turn, cur.maskR, cur.maskG};
            if (!visited.count(nxt)) {
                if (nxt.maskR == 0 && target == 0) return true;
                if (nxt.maskG == 0 && target == 1) return true;
                visited.insert(nxt);
                q.push(nxt);
            }
        }
    }
    return false;
}

int main() {
    // 初始化所有牌（编号0~27）
    int cnt = 0;
    for (int a = 0; a <= 6; ++a)
        for (int b = a; b <= 6; ++b) {
            domino[cnt][0] = a;
            domino[cnt][1] = b;
            idxMap[a][b] = cnt;
            ++cnt;
        }

    bool needBlank = false;
    int n;
    while (cin >> n && n != 0) {
        uint32_t maskR = 0, maskG = 0;

        // 读取 Red 的 n 张牌
        for (int i = 0; i < n; ++i) {
            int x, y;
            cin >> x >> y;
            if (x > y) swap(x, y);
            int id = idxMap[x][y];
            maskR |= (1u << id);
        }

        // 读取 Green 的 n 张牌
        for (int i = 0; i < n; ++i) {
            int x, y;
            cin >> x >> y;
            if (x > y) swap(x, y);
            int id = idxMap[x][y];
            maskG |= (1u << id);
        }

        // 找出最大双块的持有者
        int maxDoubleVal = -1, maxDoublePlayer = -1, maxDoubleId = -1;
        for (int id = 0; id < 28; ++id) {
            if (domino[id][0] == domino[id][1]) {
                int val = domino[id][0];
                if (maskR & (1u << id) || maskG & (1u << id)) {
                    if (val > maxDoubleVal) {
                        maxDoubleVal = val;
                        maxDoublePlayer = (maskR & (1u << id)) ? 0 : 1;
                        maxDoubleId = id;
                    }
                }
            }
        }

        // 初始状态：最大双块已由先手放下
        State init;
        init.left = init.right = maxDoubleVal;
        init.maskR = maskR;
        init.maskG = maskG;
        if (maxDoublePlayer == 0) init.maskR &= ~(1u << maxDoubleId);
        else init.maskG &= ~(1u << maxDoubleId);
        init.turn = 1 - maxDoublePlayer;   // 轮到对方

        bool redWin  = canWin(0, init);
        bool greenWin = canWin(1, init);

        if (needBlank) cout << endl;
        needBlank = true;

        if (redWin && greenWin) cout << "Both players can win\n";
        else if (redWin && !greenWin) cout << "Only player Red can win\n";
        else if (!redWin && greenWin) cout << "Only player Green can win\n";
        else cout << "No players can win\n";
    }

    return 0;
}
