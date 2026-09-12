#include <bits/stdc++.h>
using namespace std;

int n, tileCount;
int tileTop[25], tileRight[25], tileBottom[25], tileLeft[25];
int tileNum[25], board[25], codeToId[10000];
int cand[11][11][25], candCount[11][11];

bool dfs(int pos) {
    if (pos == n * n) return true;
    int row = pos / n, col = pos % n, needTop = 10, needLeft = 10;
    if (row > 0) needTop = tileBottom[board[pos - n]];
    if (col > 0) needLeft = tileRight[board[pos - 1]];
    for (int i = 0; i < candCount[needTop][needLeft]; i++) {
        int id = cand[needTop][needLeft][i];
        if (tileNum[id] == 0) continue;
        tileNum[id]--;
        board[pos] = id;
        if (dfs(pos + 1)) return true;
        tileNum[id]++;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int gameId = 0;
    while (cin >> n && n) {
        tileCount = 0;
        memset(tileNum, 0, sizeof(tileNum));
        memset(board, 0, sizeof(board));
        memset(candCount, 0, sizeof(candCount));
        memset(codeToId, -1, sizeof(codeToId));
        for (int i = 0; i < n * n; i++) {
            int top, right, bottom, left, code, id;
            cin >> top >> right >> bottom >> left;
            code = ((top * 10 + right) * 10 + bottom) * 10 + left;
            id = codeToId[code];
            if (id == -1) {
                id = tileCount++;
                codeToId[code] = id;
                tileTop[id] = top;
                tileRight[id] = right;
                tileBottom[id] = bottom;
                tileLeft[id] = left;
                cand[top][left][candCount[top][left]++] = id;
                cand[top][10][candCount[top][10]++] = id;
                cand[10][left][candCount[10][left]++] = id;
                cand[10][10][candCount[10][10]++] = id;
            }
            tileNum[id]++;
        }
        gameId++;
        cout << "Game " << gameId << ": ";
        if (dfs(0)) cout << "Possible\n";
        else cout << "Impossible\n";
        if (gameId > 0) {
            int nextChar = cin.peek();
            if (nextChar != EOF) cout << '\n';
        }
    }
    return 0;
}
