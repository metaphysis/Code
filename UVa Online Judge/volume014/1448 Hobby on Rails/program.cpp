#include <bits/stdc++.h>
using namespace std;

const int maxSize = 8, maxMask = 1 << 8;
const int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};
char grid[maxSize][maxSize];
int width, height, switchCnt, bestAns;
int switchPos[maxSize][2], rotation[maxSize][maxSize], switchIndex[maxSize][maxSize];
bool used[maxSize][maxSize], stateVisited[maxSize][maxSize][3][maxMask];

struct Edge {
    int x, y, len, inPort;
};

Edge graph[maxSize][maxSize][3];

bool inBoard(int x, int y) {
    return x >= 0 && x < height && y >= 0 && y < width;
}

int getDirection(int x, int y, int nx, int ny) {
    if (nx < x) return 0;
    if (ny > y) return 1;
    if (nx > x) return 2;
    return 3;
}

int getSwitchDirection(char type, int rot, int port) {
    static const int leftBase[3] = {1, 0, 3}, rightBase[3] = {2, 3, 0};
    const int *base = type == 'L' ? leftBase : rightBase;
    return (base[port] + rot) % 4;
}

bool hasPort(int x, int y, int dir) {
    char type = grid[x][y];
    int rot = rotation[x][y];
    if (type == 'S') return rot == 0 ? dir == 1 || dir == 3 : dir == 0 || dir == 2;
    if (type == 'C') return dir == rot || dir == (rot + 3) % 4;
    for (int port = 0; port < 3; port++) if (getSwitchDirection(type, rot, port) == dir) return true;
    return false;
}

bool setSwitchRotations(int code) {
    for (int i = 0; i < switchCnt; i++) {
        int x = switchPos[i][0], y = switchPos[i][1];
        rotation[x][y] = code & 3;
        code >>= 2;
        for (int port = 0; port < 3; port++) {
            int dir = getSwitchDirection(grid[x][y], rotation[x][y], port);
            int nx = x + dx[dir], ny = y + dy[dir];
            if (!inBoard(nx, ny)) return false;
        }
    }
    return true;
}

bool inspectSwitches(int &missingSwitch, int &missingDir) {
    missingSwitch = -1;
    missingDir = -1;
    for (int i = 0; i < switchCnt; i++) {
        int x = switchPos[i][0], y = switchPos[i][1];
        for (int dir = 0; dir < 4; dir++) {
            int nx = x + dx[dir], ny = y + dy[dir];
            bool currentPort = hasPort(x, y, dir);
            if (!inBoard(nx, ny)) {
                if (currentPort) return false;
                continue;
            }
            if (currentPort) {
                if (!used[nx][ny]) {
                    missingSwitch = i;
                    missingDir = dir;
                } else if (!hasPort(nx, ny, (dir + 2) % 4)) {
                    return false;
                }
            } else if (used[nx][ny] && hasPort(nx, ny, (dir + 2) % 4)) {
                return false;
            }
        }
    }
    return true;
}

bool buildGraph() {
    memset(switchIndex, -1, sizeof(switchIndex));
    for (int i = 0; i < switchCnt; i++) switchIndex[switchPos[i][0]][switchPos[i][1]] = i;
    for (int i = 0; i < switchCnt; i++) {
        int sx = switchPos[i][0], sy = switchPos[i][1];
        for (int port = 0; port < 3; port++) {
            int dir = getSwitchDirection(grid[sx][sy], rotation[sx][sy], port);
            int prevX = sx, prevY = sy, x = sx + dx[dir], y = sy + dy[dir], len = 0;
            if (!inBoard(x, y)) return false;
            while (switchIndex[x][y] < 0) {
                int inDir = getDirection(x, y, prevX, prevY), outDir = -1;
                for (int nextDir = 0; nextDir < 4; nextDir++) if (nextDir != inDir && hasPort(x, y, nextDir)) outDir = nextDir;
                if (outDir < 0) return false;
                int nextX = x + dx[outDir], nextY = y + dy[outDir];
                if (!inBoard(nextX, nextY)) return false;
                prevX = x;
                prevY = y;
                x = nextX;
                y = nextY;
                len++;
            }
            len++;
            int inDir = getDirection(x, y, prevX, prevY), inPort = -1;
            for (int nextPort = 0; nextPort < 3; nextPort++) if (getSwitchDirection(grid[x][y], rotation[x][y], nextPort) == inDir) inPort = nextPort;
            if (inPort < 0) return false;
            graph[sx][sy][port] = {x, y, len, inPort};
        }
    }
    return true;
}

void searchCycle(int startX, int startY, int startPort, int startMask, int x, int y, int port, int mask, int length) {
    if (stateVisited[x][y][port][mask]) {
        if (x == startX && y == startY && port == startPort && mask == startMask) bestAns = max(bestAns, length);
        return;
    }
    Edge edge = graph[x][y][port];
    int index = switchIndex[edge.x][edge.y], nextPort = 2, nextMask = mask;
    if (edge.inPort == 2) {
        nextPort = mask & (1 << index) ? 1 : 0;
        nextMask ^= 1 << index;
    }
    stateVisited[x][y][port][mask] = true;
    searchCycle(startX, startY, startPort, startMask, edge.x, edge.y, nextPort, nextMask, length + edge.len);
    stateVisited[x][y][port][mask] = false;
}

void evaluateLayout() {
    if (!buildGraph()) return;
    for (int mask = 0; mask < (1 << switchCnt); mask++) {
        for (int i = 0; i < switchCnt; i++) {
            int x = switchPos[i][0], y = switchPos[i][1];
            for (int port = 0; port < 3; port++) searchCycle(x, y, port, mask, x, y, port, mask, 0);
        }
    }
}

void searchLayouts(int x, int y, int prevX, int prevY) {
    if (grid[x][y] == 'S' || grid[x][y] == 'C') {
        int inDir = getDirection(x, y, prevX, prevY), outDir = -1;
        for (int dir = 0; dir < 4; dir++) if (dir != inDir && hasPort(x, y, dir)) outDir = dir;
        if (outDir < 0) return;
        int nx = x + dx[outDir], ny = y + dy[outDir];
        if (!inBoard(nx, ny)) return;
        if (!used[nx][ny]) {
            used[nx][ny] = true;
            if (grid[nx][ny] == 'S') {
                rotation[nx][ny] = outDir % 2 == 0 ? 1 : 0;
                searchLayouts(nx, ny, x, y);
            } else {
                int nextInDir = (outDir + 2) % 4;
                for (int rot = 0; rot < 4; rot++) {
                    rotation[nx][ny] = rot;
                    if (hasPort(nx, ny, nextInDir)) searchLayouts(nx, ny, x, y);
                }
            }
            used[nx][ny] = false;
            return;
        }
        if (!hasPort(nx, ny, (outDir + 2) % 4)) return;
    }
    int missingSwitch, missingDir;
    if (!inspectSwitches(missingSwitch, missingDir)) return;
    if (missingSwitch < 0) {
        evaluateLayout();
        return;
    }
    int sx = switchPos[missingSwitch][0], sy = switchPos[missingSwitch][1];
    int nx = sx + dx[missingDir], ny = sy + dy[missingDir];
    if (!inBoard(nx, ny)) return;
    used[nx][ny] = true;
    if (grid[nx][ny] == 'S') {
        rotation[nx][ny] = missingDir % 2 == 0 ? 1 : 0;
        searchLayouts(nx, ny, sx, sy);
    } else {
        int inDir = (missingDir + 2) % 4;
        for (int rot = 0; rot < 4; rot++) {
            rotation[nx][ny] = rot;
            if (hasPort(nx, ny, inDir)) searchLayouts(nx, ny, sx, sy);
        }
    }
    used[nx][ny] = false;
}

int solveCase() {
    switchCnt = 0;
    bestAns = 0;
    memset(used, 0, sizeof(used));
    memset(stateVisited, 0, sizeof(stateVisited));
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            cin >> grid[i][j];
            if (grid[i][j] == 'L' || grid[i][j] == 'R') {
                switchPos[switchCnt][0] = i;
                switchPos[switchCnt][1] = j;
                switchCnt++;
                used[i][j] = true;
            }
        }
    }
    int rotationCount = 1 << (switchCnt * 2);
    for (int code = 0; code < rotationCount; code++) if (setSwitchRotations(code)) searchLayouts(switchPos[0][0], switchPos[0][1], switchPos[0][0], switchPos[0][1]);
    return bestAns;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> width >> height && (width != 0 || height != 0)) cout << solveCase() << '\n';
    return 0;
}
