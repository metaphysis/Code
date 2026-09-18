#include <bits/stdc++.h>
using namespace std;

const int boardSize = 19;
const int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};

bool removeDead(string &board, int pos) {
    bool vis[361] = {}, hasLib = false;
    vector<int> block;
    char color = board[pos];
    block.push_back(pos);
    vis[pos] = true;
    for (int i = 0; i < (int)block.size(); ++i) {
        int cur = block[i], x = cur / boardSize, y = cur % boardSize;
        for (int dir = 0; dir < 4; ++dir) {
            int nx = x + dx[dir], ny = y + dy[dir];
            if (nx < 0 || nx >= boardSize || ny < 0 || ny >= boardSize) continue;
            int nextPos = nx * boardSize + ny;
            if (board[nextPos] == '+') hasLib = true;
            else if (board[nextPos] == color && !vis[nextPos]) {
                vis[nextPos] = true;
                block.push_back(nextPos);
            }
        }
    }
    if (hasLib) return false;
    for (int cur : block) board[cur] = '+';
    return true;
}

int tryPut(string &board, int x, int y, int color) {
    if (x == 0 && y == 0) return -1;
    int row = x - 1, col = y - 1, pos = row * boardSize + col;
    if (board[pos] != '+') return -2;
    char own = color == 1 ? 'e' : 'o', enemy = color == 1 ? 'o' : 'e';
    board[pos] = own;
    for (int dir = 0; dir < 4; ++dir) {
        int nx = row + dx[dir], ny = col + dy[dir];
        if (nx < 0 || nx >= boardSize || ny < 0 || ny >= boardSize) continue;
        int nextPos = nx * boardSize + ny;
        if (board[nextPos] == enemy) removeDead(board, nextPos);
    }
    if (removeDead(board, pos)) return -3;
    return 0;
}

void printBoard(const string &board, int turn, bool isTie) {
    cout << "Total " << turn << " turn(s)\n";
    if (isTie) cout << "(Tie)\n";
    for (int row = 0; row < boardSize; ++row) cout << board.substr(row * boardSize, boardSize) << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int x, y, gameId = 0, turn = 0, color = 0;
    bool started = false, lastPass = false;
    string board(361, '+'), lastBoard[2];
    set<string> seen;
    auto resetGame = [&]() {
        board.assign(361, '+');
        lastBoard[0].clear();
        lastBoard[1].clear();
        seen.clear();
        turn = 0;
        color = 0;
        lastPass = false;
    };
    while (cin >> x >> y) {
        if (x == -1 && y == -1) {
            if (started) cout << '\n';
            started = false;
            resetGame();
            continue;
        }
        if (!started) {
            started = true;
            cout << "Game #" << ++gameId << '\n';
        }
        ++turn;
        color ^= 1;
        string nextBoard = board;
        int result = tryPut(nextBoard, x, y, color);
        if (result == 0 && nextBoard == lastBoard[color ^ 1]) result = -3;
        if (result < 0) {
            string player = result == -2 ? "PLAYER" : color == 1 ? "black" : "white";
            cout << "Turn " << turn << ' ' << player << " pass ";
            if (result == -1) cout << "(by player)\n";
            else if (result == -2) cout << "(invalid put " << x << ',' << y << ")\n";
            else cout << "(taboo point " << x << ',' << y << ")\n";
            if (result == -1 && lastPass) {
                printBoard(board, turn, false);
                resetGame();
                continue;
            }
            seen.clear();
        } else {
            if (seen.count(nextBoard)) {
                board = nextBoard;
                printBoard(board, turn, true);
                resetGame();
                continue;
            }
            seen.insert(nextBoard);
            lastBoard[color] = board;
            board = nextBoard;
        }
        lastPass = result == -1;
    }
    return 0;
}
