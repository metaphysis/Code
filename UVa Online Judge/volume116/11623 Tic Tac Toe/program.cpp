// Tic Tac Toe
// UVa ID: 11623
// Verdict: Accepted
// Submission Date: 2026-01-11
// UVa Run Time: 0.030s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;
char board[MAXN][MAXN];
int n, m;

int dr[4] = {0, 1, 1, 1}, dc[4] = {1, 0, 1, -1};

// 检查从 (r,c) 方向 (dr,dc) 的连续同色棋子长度
int getLength(int r, int c, int dir, char symbol) {
    int length = 0;
    int rr = r, cc = c;
    while (rr >= 0 && rr < n && cc >= 0 && cc < n && board[rr][cc] == symbol) {
        length++;
        rr += dr[dir], cc += dc[dir];
    }
    return length;
}

bool firstSet = true;
set<pair<int, int>> intersection;

void getIntersection(int i, int j, int length, int dir) {
    set<pair<int,int>> current;
    int rr = i, cc = j;
    for (int k = 0; k < length; k++) {
        current.insert({rr, cc});
        rr += dr[dir], cc += dc[dir];
    }
    if (firstSet) {
        intersection = current;
        firstSet = false;
    } else {
        set<pair<int,int>> next;
        for (auto &p : intersection)
            if (current.count(p)) next.insert(p);
        intersection = next;
    }
}

pair<bool, bool> checkWinner(char symbol) {
    firstSet = true;
    intersection.clear();
    int winCount = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            if (board[i][j] != symbol) continue;
            for (int dir = 0; dir < 4; dir++) {
                // 限制起始位置，不重复检查
                if (dir == 0 && j && board[i][j - 1] == symbol) continue;
                if (dir == 1 && i && board[i - 1][j] == symbol) continue;
                if (dir == 2 && i && j && board[i - 1][j - 1] == symbol) continue;
                if (dir == 3 && i && j <= n - 2 && board[i - 1][j + 1] == symbol) continue;
                int length = getLength(i, j, dir, symbol);
                // 连续同色棋子长度约束
                if (length >= 2 * m) return {true, false};
                // 检查交集
                if (length >= m) {
                    winCount++;
                    getIntersection(i, j, length, dir);
                    if (winCount >= 2 && intersection.size() != 1) return {true, false};
                }
            }
        }
    // 检查去除公共棋子后是否还存在获胜段
    if (winCount >= 2) {
        int r, c;
        for (auto p : intersection) r = p.first, c = p.second;
        char original = board[r][c];
        board[r][c] = '.';
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (board[i][j] == symbol)
                    for (int dir = 0; dir < 4; dir++)
                        if (getLength(i, j, dir, symbol) >= m) {
                            board[r][c] = original;
                            return {true, winCount};
                        }
        board[r][c] = original;
    }
    return {false, winCount};
}

int main() {
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--) {
        cin >> n >> m;
        int countX = 0, countO = 0;
        // 统计两种棋子的数量
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                cin >> board[i][j];
                if (board[i][j] == 'X') countX++;
                else if (board[i][j] == 'O') countO++;
            }
        bool error = false, xWin, oWin;
        // 棋子数量需要满足约束
        if (countX != countO && countX != countO + 1) error = true;
        if (!error) {
            // 检查 X 胜利是否符合约束
            auto [xError, xxWin] = checkWinner('X');
            xWin = xxWin;
            if (xError) error = true;
            if (xWin && countX != countO + 1) error = true;
            if (!error) {
                // 检查 O 胜利是否符合约束
                auto [oError, ooWin] = checkWinner('O');
                oWin = ooWin;
                if (oError) error = true;
                if (xWin && oWin) error = true;
                if (oWin && countX != countO) error = true;
            }
        }
        // 输出结果
        if (error) cout << "ERROR";
        else if (xWin) cout << "X WINS";
        else if (oWin) cout << "O WINS";
        else if (countX + countO == n * n) cout << "DRAW";
        else cout << "IN PROGRESS";
        cout << '\n';
    }
    return 0;
}
