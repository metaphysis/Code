#include <bits/stdc++.h>
using namespace std;

const int maxN = 8, maxE = 10, inf = 0x3f3f3f3f;
int n, emptyCount, me, startPlayer;
char board[maxN][maxN];
int emptyRow[maxE], emptyCol[maxE];
int memo[1 << (2 * maxE)];
int dirRow[4] = {-1, 1, 0, 0}, dirCol[4] = {0, 0, -1, 1};

int getMaxRegion(int player) {
    bool visited[maxN][maxN];
    int maxSize = 0, queueRow[maxN * maxN], queueCol[maxN * maxN];
    memset(visited, 0, sizeof(visited));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            if (visited[i][j] || board[i][j] - '0' != player)
                continue;
            int head = 0, tail = 0;
            queueRow[tail] = i;
            queueCol[tail++] = j;
            visited[i][j] = true;
            while (head < tail) {
                int row = queueRow[head], col = queueCol[head++];
                for (int d = 0; d < 4; d++) {
                    int nextRow = row + dirRow[d], nextCol = col + dirCol[d];
                    if (nextRow < 0 || nextRow >= n || nextCol < 0 || nextCol >= n)
                        continue;
                    if (visited[nextRow][nextCol] || board[nextRow][nextCol] - '0' != player)
                        continue;
                    visited[nextRow][nextCol] = true;
                    queueRow[tail] = nextRow;
                    queueCol[tail++] = nextCol;
                }
            }
            maxSize = max(maxSize, tail);
        }
    return maxSize;
}

int getResult() {
    int myScore = getMaxRegion(me), opponentScore = getMaxRegion(1 - me);
    return myScore - opponentScore;
}

int search(int fillMask, int oneMask) {
    int key = fillMask | (oneMask << emptyCount);
    int &result = memo[key];
    if (result != inf)
        return result;
    if (fillMask == (1 << emptyCount) - 1)
        return result = getResult();
    int depth = __builtin_popcount(static_cast<unsigned>(fillMask));
    int player = (startPlayer + depth) & 1;
    result = player == me ? -inf : inf;
    for (int i = 0; i < emptyCount; i++) {
        if (fillMask & (1 << i))
            continue;
        int row = emptyRow[i], col = emptyCol[i];
        board[row][col] = char('0' + player);
        int nextFillMask = fillMask | (1 << i), nextOneMask = oneMask;
        if (player == 1)
            nextOneMask |= 1 << i;
        int value = search(nextFillMask, nextOneMask);
        board[row][col] = '.';
        if (player == me)
            result = max(result, value);
        else
            result = min(result, value);
    }
    return result;
}

int solve() {
    if (!(cin >> n))
        return 0;
    if (n == 0)
        return 0;
    int zeroCount = 0, oneCount = 0;
    emptyCount = 0;
    for (int i = 0; i < n; i++) {
        string line;
        cin >> line;
        for (int j = 0; j < n; j++) {
            board[i][j] = line[j];
            if (board[i][j] == '0')
                zeroCount++;
            else if (board[i][j] == '1')
                oneCount++;
            else {
                emptyRow[emptyCount] = i;
                emptyCol[emptyCount++] = j;
            }
        }
    }
    startPlayer = zeroCount == oneCount ? 0 : 1;
    me = startPlayer;
    fill(memo, memo + (1 << (2 * emptyCount)), inf);
    int bestValue = -inf, bestIndex = -1;
    for (int i = 0; i < emptyCount; i++) {
        int row = emptyRow[i], col = emptyCol[i];
        board[row][col] = char('0' + me);
        int fillMask = 1 << i, oneMask = me == 1 ? 1 << i : 0;
        int value = search(fillMask, oneMask);
        board[row][col] = '.';
        if (value > bestValue) {
            bestValue = value;
            bestIndex = i;
        }
    }
    cout << "(" << emptyRow[bestIndex] << "," << emptyCol[bestIndex] << ") " << bestValue << '\n';
    return 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (solve())
        ;
    return 0;
}
