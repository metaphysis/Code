#include <bits/stdc++.h>
using namespace std;

const int boardSize = 5, cellCount = 25, center = 12, stateCount = 1 << 25;

void initMoves(int nearCell[][8], int jumpCell[][8]) {
    int dr[8] = {-1, -1, -1, 0, 0, 1, 1, 1}, dc[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
    for (int i = 0; i < cellCount; i++)
        for (int d = 0; d < 8; d++) {
            int row = i / boardSize, col = i % boardSize;
            int nearRow = row + dr[d], nearCol = col + dc[d];
            int jumpRow = row + 2 * dr[d], jumpCol = col + 2 * dc[d];
            nearCell[i][d] = -1;
            jumpCell[i][d] = -1;
            if (nearRow >= 0 && nearRow < boardSize && nearCol >= 0 && nearCol < boardSize)
                nearCell[i][d] = nearRow * boardSize + nearCol;
            if (jumpRow >= 0 && jumpRow < boardSize && jumpCol >= 0 && jumpCol < boardSize)
                jumpCell[i][d] = jumpRow * boardSize + jumpCol;
        }
}

void buildTable(vector<unsigned char> &dist, int nearCell[][8], int jumpCell[][8]) {
    vector<int> queue;
    int head = 0, startMask = 1 << center;
    queue.reserve(3850756);
    queue.push_back(startMask);
    dist[startMask] = 0;
    while (head < static_cast<int>(queue.size())) {
        int mask = queue[head++], curDist = dist[mask];
        int pieceCount = __builtin_popcount(static_cast<unsigned int>(mask));
        int pieces = mask;
        while (pieces) {
            int to = __builtin_ctz(static_cast<unsigned int>(pieces));
            pieces &= pieces - 1;
            for (int d = 0; d < 8; d++) {
                int source = nearCell[to][d];
                if (source != -1 && (mask & (1 << source)) == 0) {
                    int nextMask = mask ^ (1 << to) ^ (1 << source);
                    if (dist[nextMask] == 255) {
                        dist[nextMask] = static_cast<unsigned char>(curDist + 1);
                        queue.push_back(nextMask);
                    }
                }
                if (pieceCount == 9)
                    continue;
                int middle = nearCell[to][d], jumpSource = jumpCell[to][d];
                if (jumpSource == -1 || (mask & (1 << middle)) != 0 || (mask & (1 << jumpSource)) != 0)
                    continue;
                int nextMask = (mask ^ (1 << to)) | (1 << middle) | (1 << jumpSource);
                if (dist[nextMask] == 255) {
                    dist[nextMask] = static_cast<unsigned char>(curDist + 1);
                    queue.push_back(nextMask);
                }
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int nearCell[cellCount][8], jumpCell[cellCount][8];
    initMoves(nearCell, jumpCell);
    vector<unsigned char> dist(stateCount, 255);
    buildTable(dist, nearCell, jumpCell);
    int testCount;
    cin >> testCount;
    for (int caseId = 1; caseId <= testCount; caseId++) {
        int mask = 0;
        string row;
        for (int i = 0; i < boardSize; i++) {
            cin >> row;
            for (int j = 0; j < boardSize; j++)
                if (row[j] == '*')
                    mask |= 1 << (i * boardSize + j);
        }
        cout << "Case " << caseId << ": " << static_cast<int>(dist[mask]) << '\n';
    }
    return 0;
}
