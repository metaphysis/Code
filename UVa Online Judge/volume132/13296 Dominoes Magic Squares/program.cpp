#include <bits/stdc++.h>
using namespace std;

int tileA[8], tileB[8], board[4][4], target;
bool used[8];

bool checkLines() {
    for (int i = 0; i < 4; i++) {
        int rowSum = 0, colSum = 0;
        bool rowFull = true, colFull = true;
        for (int j = 0; j < 4; j++) {
            if (board[i][j] == -1)
                rowFull = false;
            else
                rowSum += board[i][j];
            if (board[j][i] == -1)
                colFull = false;
            else
                colSum += board[j][i];
        }
        if (rowSum > target || colSum > target)
            return false;
        if (rowFull && rowSum != target)
            return false;
        if (colFull && colSum != target)
            return false;
    }
    int mainDiagSum = 0, subDiagSum = 0;
    bool mainDiagFull = true, subDiagFull = true;
    for (int i = 0; i < 4; i++) {
        if (board[i][i] == -1)
            mainDiagFull = false;
        else
            mainDiagSum += board[i][i];
        if (board[i][3 - i] == -1)
            subDiagFull = false;
        else
            subDiagSum += board[i][3 - i];
    }
    if (mainDiagSum > target || subDiagSum > target)
        return false;
    if (mainDiagFull && mainDiagSum != target)
        return false;
    if (subDiagFull && subDiagSum != target)
        return false;
    return true;
}

bool dfs() {
    int emptyR = -1, emptyC = -1;
    for (int i = 0; i < 4 && emptyR == -1; i++)
        for (int j = 0; j < 4; j++)
            if (board[i][j] == -1) {
                emptyR = i;
                emptyC = j;
                break;
            }
    if (emptyR == -1)
        return true;
    int dr[2] = {0, 1}, dc[2] = {1, 0};
    for (int i = 0; i < 8; i++) {
        if (used[i])
            continue;
        for (int d = 0; d < 2; d++) {
            int nextR = emptyR + dr[d], nextC = emptyC + dc[d];
            if (nextR >= 4 || nextC >= 4 || board[nextR][nextC] != -1)
                continue;
            int dirCount = tileA[i] == tileB[i] ? 1 : 2;
            for (int dir = 0; dir < dirCount; dir++) {
                int firstValue = dir == 0 ? tileA[i] : tileB[i];
                int secondValue = dir == 0 ? tileB[i] : tileA[i];
                board[emptyR][emptyC] = firstValue;
                board[nextR][nextC] = secondValue;
                used[i] = true;
                if (checkLines() && dfs())
                    return true;
                used[i] = false;
                board[emptyR][emptyC] = -1;
                board[nextR][nextC] = -1;
            }
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> tileA[0] >> tileB[0]) {
        for (int i = 1; i < 8; i++)
            cin >> tileA[i] >> tileB[i];
        int sum = 0;
        for (int i = 0; i < 8; i++) {
            if (tileA[i] > tileB[i])
                swap(tileA[i], tileB[i]);
            sum += tileA[i] + tileB[i];
        }
        if (sum % 4 != 0) {
            cout << "N\n";
            continue;
        }
        target = sum / 4;
        memset(board, -1, sizeof(board));
        memset(used, false, sizeof(used));
        cout << (dfs() ? "Y\n" : "N\n");
    }
    return 0;
}
