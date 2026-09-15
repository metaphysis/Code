#include <bits/stdc++.h>
using namespace std;

int fixedGrid[4][4], blockCount;
long long comb[25][10];

unsigned long long makeKey(const int blocks[], int player) {
    unsigned long long key = 0;
    for (int i = 0; i < blockCount; i++)
        key |= (unsigned long long)blocks[i] << (i * 4);
    key |= (unsigned long long)player << 32;
    return key;
}

void decodeKey(unsigned long long key, int blocks[], int &player) {
    for (int i = 0; i < blockCount; i++)
        blocks[i] = (key >> (i * 4)) & 15;
    player = (key >> 32) & 15;
}

int getRank(const int blocks[]) {
    int total = 15 + blockCount, last = -1;
    long long rank = 0;
    for (int i = 0; i < blockCount; i++) {
        int value = blocks[i] + i;
        for (int j = last + 1; j < value; j++)
            rank += comb[total - j - 1][blockCount - i - 1];
        last = value;
    }
    return (int)rank;
}

void getStateInfo(const int blocks[], int height[], int &target) {
    for (int i = 0; i < 16; i++)
        height[i] = fixedGrid[i / 4][i % 4];
    for (int i = 0; i < blockCount; i++)
        height[blocks[i]]++;
    target = -1;
    for (int i = 0; i < 16; i++) {
        if (height[i] == 0)
            continue;
        if (target == -1)
            target = height[i];
        else if (target != height[i])
            return;
    }
}

bool isGoal(const int height[]) {
    int target = -1;
    for (int i = 0; i < 16; i++) {
        if (height[i] == 0)
            continue;
        if (target == -1)
            target = height[i];
        else if (target != height[i])
            return false;
    }
    return true;
}

int solveCase() {
    int blocks[8], playerRow, playerCol, position, count;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            cin >> fixedGrid[i][j];
    blockCount = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cin >> count;
            position = i * 4 + j;
            for (int k = 0; k < count; k++)
                blocks[blockCount++] = position;
        }
    }
    cin >> playerRow >> playerCol;
    int player = playerRow * 4 + playerCol;
    unsigned long long startKey = makeKey(blocks, player);
    int stateCount = (int)comb[15 + blockCount][blockCount] * 16;
    vector<unsigned char> visited(stateCount, 0);
    queue<unsigned long long> bfs;
    int startIndex = getRank(blocks) * 16 + player;
    visited[startIndex] = 1;
    bfs.push(startKey);
    const int dr[4] = {1, 0, -1, 0}, dc[4] = {0, 1, 0, -1};
    int distance = 0;
    while (!bfs.empty()) {
        int layerSize = (int)bfs.size();
        while (layerSize--) {
            unsigned long long key = bfs.front();
            bfs.pop();
            int currentBlocks[8], currentPlayer, height[16], target;
            decodeKey(key, currentBlocks, currentPlayer);
            getStateInfo(currentBlocks, height, target);
            if (isGoal(height))
                return distance;
            int row = currentPlayer / 4, col = currentPlayer % 4;
            for (int d = 0; d < 4; d++) {
                int nextRow = row + dr[d], nextCol = col + dc[d];
                if (nextRow < 0 || nextRow >= 4 || nextCol < 0 || nextCol >= 4)
                    continue;
                int nextPosition = nextRow * 4 + nextCol;
                if (abs(height[nextPosition] - height[currentPlayer]) <= 1) {
                    int nextIndex = getRank(currentBlocks) * 16 + nextPosition;
                    if (!visited[nextIndex]) {
                        visited[nextIndex] = 1;
                        unsigned long long nextKey = (key & 0xffffffffULL) | ((unsigned long long)nextPosition << 32);
                        bfs.push(nextKey);
                    }
                }
                int targetRow = nextRow + dr[d], targetCol = nextCol + dc[d];
                if (targetRow < 0 || targetRow >= 4 || targetCol < 0 || targetCol >= 4)
                    continue;
                int targetPosition = targetRow * 4 + targetCol;
                int heightDifference = height[nextPosition] - height[currentPlayer];
                if (heightDifference < 1 || heightDifference > 2)
                    continue;
                if (height[nextPosition] <= height[targetPosition])
                    continue;
                int blockIndex = -1;
                for (int i = 0; i < blockCount; i++) {
                    if (currentBlocks[i] == nextPosition) {
                        blockIndex = i;
                        break;
                    }
                }
                if (blockIndex == -1)
                    continue;
                int nextBlocks[8];
                for (int i = 0; i < blockCount; i++)
                    nextBlocks[i] = currentBlocks[i];
                nextBlocks[blockIndex] = targetPosition;
                sort(nextBlocks, nextBlocks + blockCount);
                int nextIndex = getRank(nextBlocks) * 16 + nextPosition;
                if (!visited[nextIndex]) {
                    visited[nextIndex] = 1;
                    bfs.push(makeKey(nextBlocks, nextPosition));
                }
            }
        }
        distance++;
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    for (int i = 0; i < 25; i++)
        for (int j = 0; j < 10; j++)
            comb[i][j] = 0;
    for (int i = 0; i < 25; i++) {
        comb[i][0] = 1;
        for (int j = 1; j <= min(i, 9); j++)
            comb[i][j] = comb[i - 1][j - 1] + comb[i - 1][j];
    }
    int testCount;
    cin >> testCount;
    for (int testCase = 1; testCase <= testCount; testCase++) {
        int answer = solveCase();
        cout << "Case " << testCase << ": ";
        if (answer == -1)
            cout << "impossible\n";
        else
            cout << answer << '\n';
    }
    return 0;
}
