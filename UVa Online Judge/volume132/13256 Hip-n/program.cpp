#include <bits/stdc++.h>
using namespace std;

bool inBoard(int row, int col, int n) {
    return row >= 0 && row < n && col >= 0 && col < n;
}

bool hasSquare(int row, int col, int player, int n, const vector<vector<int> >& board, const vector<pair<int, int> >& points) {
    for (const pair<int, int>& point : points) {
        int r, c, dx, dy, r1, c1, r2, c2;
        r = point.first;
        c = point.second;
        dx = r - row;
        dy = c - col;
        r1 = row - dy;
        c1 = col + dx;
        r2 = r - dy;
        c2 = c + dx;
        if (inBoard(r1, c1, n) && inBoard(r2, c2, n) && board[r1][c1] == player && board[r2][c2] == player) return true;
        r1 = row + dy;
        c1 = col - dx;
        r2 = r + dy;
        c2 = c - dx;
        if (inBoard(r1, c1, n) && inBoard(r2, c2, n) && board[r1][c1] == player && board[r2][c2] == player) return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while (cin >> n) {
        vector<vector<int> > board(n, vector<int>(n, 0));
        vector<pair<int, int> > points[3];
        bool ended = false;
        int loser = 0;
        for (int i = 0; i < n * n; i++) {
            int row, col, player;
            cin >> row >> col;
            player = i % 2 + 1;
            if (!ended) {
                if (hasSquare(row, col, player, n, board, points[player])) {
                    ended = true;
                    loser = player;
                }
                board[row][col] = player;
                points[player].push_back(make_pair(row, col));
            }
        }
        cout << loser << '\n';
    }
    return 0;
}
