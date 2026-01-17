// Find the Winning Move
// UVa ID: 10111
// Verdict: Accepted
// Submission Date: 2026-01-08
// UVa Run Time: 0.010s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int WIN = 1, LOSE = 0;
const int X = 0, O = 1;
unordered_map<long long, int> dp;

// 胜利条件（16位棋盘）
const int wins[10] = {
    0xF000, 0x0F00, 0x00F0, 0x000F, // 行
    0x8888, 0x4444, 0x2222, 0x1111, // 列
    0x8421, 0x1248                  // 对角线
};

// 编码状态：高16位存X，次16位存O，最低1位存当前玩家
long long encode(int boardX, int boardO, int player) {
    return (boardX << 17) | (boardO << 1) | player;
}

bool isWin(int board) {
    for (int w : wins)
        if ((board & w) == w) return true;
    return false;
}

// 返回当前玩家在该状态下的胜负，WIN: 必胜, LOSE: 必败
int dfs(int boardX, int boardO, int player) {
    long long key = encode(boardX, boardO, player);
    if (dp.find(key) != dp.end()) return dp[key];
    int curBoard = (player == X) ? boardX : boardO;
    int oppBoard = (player == X) ? boardO : boardX;
    // 如果当前玩家已经赢了（上一手已经形成连线）
    if (isWin(curBoard)) return dp[key] = WIN;
    // 获取空位
    int empty = ~(boardX | boardO) & 0xFFFF;
    // 平局，当前玩家没有获胜
    if (empty == 0) return dp[key] = LOSE;
    // 尝试所有可能的移动
    bool canWin = false;
    for (int pos = 0; pos < 16; pos++) {
        if (empty & (1 << pos)) {
            int newCurBoard = curBoard | (1 << pos);
            int newBoardX = (player == X) ? newCurBoard : boardX;
            int newBoardO = (player == O) ? newCurBoard : boardO;
            // 如果下这步后，对方必败，则当前必胜
            if (dfs(newBoardX, newBoardO, 1 - player) == LOSE) {
                canWin = true;
                break;
            }
        }
    }
    return dp[key] = (canWin ? WIN : LOSE);
}

int main() {
    char piece;
    while (cin >> piece, piece != '$') {
        if (piece != '?') continue;
        // 读入棋盘
        int boardX = 0, boardO = 0;
        vector<int> emptyPos;
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++) {
                cin >> piece;
                while (piece != '.' && piece != 'x' && piece != 'o')
                    cin >> piece;
                int pos = i * 4 + j;
                if (piece == 'x') boardX |= (1 << pos);
                else if (piece == 'o') boardO |= (1 << pos);
                else emptyPos.push_back(pos);
            }
        // 清空记忆化表
        dp.clear();
        bool found = false;
        // 按顺序尝试每个空位
        for (int pos : emptyPos) {
            int newBoardX = boardX | (1 << pos);
            // X 下了一步后，轮到 O，如果 O 必败，则 X 的这一步是必胜步
            if (dfs(newBoardX, boardO, O) == LOSE) {
                int row = pos / 4, col = pos % 4;
                cout << '(' << row << ',' << col << ")\n";
                found = true;
                break;
            }
        }
        if (!found) cout << "#####\n";
    }
    return 0;
}
