// Ancient Go
// UVa ID: 12987
// Verdict: Accepted
// Submission Date: 2026-08-01
// UVa Run Time: 0.000s

#include <bits/stdc++.h>
using namespace std;

const int dx[4] = {-1, 1, 0, 0};
const int dy[4] = {0, 0, -1, 1};

// 深度优先搜索白棋连通块，同时检查是否有相邻的空格
void dfsWhite(int x, int y, const vector<string>& board, vector<vector<bool>>& visited, bool& hasEmpty) {
    visited[x][y] = true;
    for (int k = 0; k < 4; ++k) {
        int nx = x + dx[k], ny = y + dy[k];
        if (nx < 0 || nx >= 9 || ny < 0 || ny >= 9) continue;
        if (board[nx][ny] == '.') hasEmpty = true;
        else if (board[nx][ny] == 'o' && !visited[nx][ny]) dfsWhite(nx, ny, board, visited, hasEmpty);
    }
}

// 判断是否存在一步黑棋能杀死至少一个白棋组件
bool canKill(vector<string>& board) {
    for (int i = 0; i < 9; ++i) for (int j = 0; j < 9; ++j) if (board[i][j] == '.') {
        board[i][j] = 'x'; // 模拟黑棋落子
        bool kill = false;
        vector<vector<bool>> visited(9, vector<bool>(9, false));
        for (int r = 0; r < 9 && !kill; ++r) for (int c = 0; c < 9 && !kill; ++c) if (board[r][c] == 'o' && !visited[r][c]) {
            bool hasEmpty = false;
            dfsWhite(r, c, board, visited, hasEmpty);
            if (!hasEmpty) kill = true;
        }
        board[i][j] = '.'; // 撤销落子
        if (kill) return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; ++tc) {
        vector<string> board(9);
        for (int i = 0; i < 9; ++i) cin >> board[i];
        bool res = canKill(board);
        cout << "Case #" << tc << ": " << (res ? "Can kill in one move!!!" : "Can not kill in one move!!!") << '\n';
    }
    return 0;
}
