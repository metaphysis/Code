// The Pawn Chess
// UVa ID: 10838
// Verdict: Accepted
// Submission Date: 2025-12-14
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 棋盘编码：每格 2 位，共 16 格，64 位整数存储
// 00: 空, 01: 白兵(P), 10: 黑兵(p)
const int WHITE = 1, BLACK = 2;
const int INF = 1e9;

// 方向：白兵向上(row-1)，黑兵向下(row+1)
const int WHITE_DIR = -1, BLACK_DIR = 1;
const int CAPTURE_DIRS[2][2] = {{-1, -1}, {-1, 1}}; // 白兵吃子方向（左上、右上）
const int BLACK_CAPTURE_DIRS[2][2] = {{1, -1}, {1, 1}}; // 黑兵吃子方向（左下、右下）

// 记忆化缓存：map<状态, pair<结果, 步数>>
unordered_map<unsigned long long, pair<int, int>> memo[2]; // 0:白方走, 1:黑方走

// 从状态中获取某格的值
int getCell(unsigned long long state, int r, int c) {
    int pos = (r * 4 + c) * 2;
    return (state >> pos) & 3;
}

// 设置某格的值
void setCell(unsigned long long& state, int r, int c, int val) {
    int pos = (r * 4 + c) * 2;
    state &= ~(3ULL << pos);
    state |= ((unsigned long long)val << pos);
}

// 判断是否到达底线
bool isWhiteWin(unsigned long long state) {
    for (int c = 0; c < 4; ++c)
        if (getCell(state, 0, c) == WHITE) return true; // 白兵到达第0行（黑方底线）
    return false;
}

bool isBlackWin(unsigned long long state) {
    for (int c = 0; c < 4; ++c)
        if (getCell(state, 3, c) == BLACK) return true; // 黑兵到达第3行（白方底线）
    return false;
}

// 生成所有合法走法
vector<pair<unsigned long long, int>> generateMoves(unsigned long long state, int turn) {
    vector<pair<unsigned long long, int>> moves;
    int player = (turn == 0) ? WHITE : BLACK;
    int dir = (turn == 0) ? WHITE_DIR : BLACK_DIR;

    for (int r = 0; r < 4; ++r) {
        for (int c = 0; c < 4; ++c) {
            if (getCell(state, r, c) != player) continue;

            // 向前走一步
            int nr = r + dir;
            if (nr >= 0 && nr < 4 && getCell(state, nr, c) == 0) {
                unsigned long long next = state;
                setCell(next, r, c, 0);
                setCell(next, nr, c, player);
                moves.push_back({next, 1});
            }

            // 吃子
            auto& capDirs = (turn == 0) ? CAPTURE_DIRS : BLACK_CAPTURE_DIRS;
            for (auto& d : capDirs) {
                int nr = r + d[0];
                int nc = c + d[1];
                if (nr >= 0 && nr < 4 && nc >= 0 && nc < 4) {
                    int target = getCell(state, nr, nc);
                    if (target != 0 && target != player) {
                        unsigned long long next = state;
                        setCell(next, r, c, 0);
                        setCell(next, nr, nc, player);
                        moves.push_back({next, 1});
                    }
                }
            }
        }
    }
    return moves;
}

// Minimax 搜索，返回 (胜负, 步数)
pair<int, int> solve(unsigned long long state, int turn) {
    // 检查缓存
    if (memo[turn].count(state)) return memo[turn][state];

    // 终局判断
    if (isWhiteWin(state)) return {0, 0}; // 白方赢，步数为0（当前还未走）
    if (isBlackWin(state)) return {1, 0}; // 黑方赢

    auto moves = generateMoves(state, turn);
    if (moves.empty()) {
        // 当前玩家无棋可走，对方赢
        if (turn == 0) return {1, 0}; // 白方无棋，黑方赢
        else return {0, 0}; // 黑方无棋，白方赢
    }

    int bestWinner = -1;
    int bestSteps = INF;
    int worstSteps = -1;

    for (auto& mv : moves) {
        auto res = solve(mv.first, turn ^ 1);
        int winner = res.first;
        int steps = res.second + mv.second; // 加上这一步

        if (bestWinner == -1) {
            bestWinner = winner;
            bestSteps = steps;
            worstSteps = steps;
        } else {
            if (winner == turn) {
                // 当前玩家能赢，取最短步数
                if (winner == bestWinner) bestSteps = min(bestSteps, steps);
                else {
                    bestWinner = winner;
                    bestSteps = steps;
                }
            } else {
                // 当前玩家会输，取最长步数（拖延）
                if (bestWinner == winner) worstSteps = max(worstSteps, steps);
                else {
                    // 如果之前有赢的可能，保留赢法
                    if (bestWinner != turn) {
                        bestWinner = winner;
                        worstSteps = steps;
                    }
                }
            }
        }
    }

    int finalSteps = (bestWinner == turn) ? bestSteps : worstSteps;
    memo[turn][state] = {bestWinner, finalSteps};
    return {bestWinner, finalSteps};
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        vector<string> board(4);
        for (int i = 0; i < 4; ++i) {
            cin >> board[i];
            // 处理可能的空格（样例中有空格，但实际输入可能没有）
            if (board[i].size() < 4) board[i] = "....";
        }

        // 构建状态
        unsigned long long state = 0;
        for (int r = 0; r < 4; ++r) {
            for (int c = 0; c < 4; ++c) {
                int val = 0;
                if (board[r][c] == 'P') val = WHITE;
                else if (board[r][c] == 'p') val = BLACK;
                setCell(state, r, c, val);
            }
        }

        // 初始化缓存
        memo[0].clear();
        memo[1].clear();

        auto res = solve(state, 0);
        int winner = res.first;
        int steps = res.second;

        if (winner == 0) cout << "white (" << steps << ")\n";
        else cout << "black (" << steps << ")\n";
    }
    return 0;
}
