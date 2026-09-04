#include <bits/stdc++.h>
using namespace std;

int parentSet[400], regionCnt, edgeMap[30][30], answer;

int findRoot(int x) {
    if (parentSet[x] == x) return x;
    return parentSet[x] = findRoot(parentSet[x]);
}

void uniteSet(int x, int y) {
    int rootX = findRoot(x), rootY = findRoot(y);
    if (rootX == rootY) return;
    parentSet[rootX] = rootY;
}

long long countPart(int mask, bool selected) {
    int color[30], queueData[30], head, tail, compCnt, vertexCnt;
    bool hasEdge;
    memset(color, -1, sizeof(color));
    compCnt = 0;
    vertexCnt = 0;
    hasEdge = false;
    for (int i = 0; i < regionCnt; i++)
        if (((mask >> i) & 1) == selected)
            vertexCnt++;
    if (vertexCnt == 0) return 0;
    for (int i = 0; i < regionCnt; i++) {
        if (((mask >> i) & 1) != selected || color[i] != -1) continue;
        compCnt++;
        head = 0;
        tail = 0;
        queueData[tail++] = i;
        color[i] = 0;
        while (head < tail) {
            int u = queueData[head++];
            for (int v = 0; v < regionCnt; v++) {
                if (!edgeMap[u][v] || ((mask >> v) & 1) != selected) continue;
                hasEdge = true;
                if (color[v] == -1) {
                    color[v] = color[u] ^ 1;
                    queueData[tail++] = v;
                } else if (color[v] == color[u]) {
                    return 0;
                }
            }
        }
    }
    if (!hasEdge) {
        if (vertexCnt < 2) return 0;
        return (1LL << vertexCnt) - 2;
    }
    return 1LL << compCnt;
}

void enumerateMask(int start, int chosen, int mask) {
    if (chosen > 0 && chosen < regionCnt) {
        long long firstWays = countPart(mask, true);
        long long secondWays = countPart(mask, false);
        answer += firstWays * secondWays;
    }
    if (chosen == 5) return;
    for (int i = start; i < regionCnt; i++)
        enumerateMask(i + 1, chosen + 1, mask | (1 << i));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int rowCnt, colCnt, caseNo = 1;
    while (cin >> rowCnt >> colCnt) {
        if (rowCnt == 0 && colCnt == 0) break;
        string grid[20];
        int cellId[20][20], rootId[400], dirX[4] = {-1, 1, 0, 0}, dirY[4] = {0, 0, -1, 1};
        for (int i = 0; i < rowCnt; i++)
            cin >> grid[i];
        for (int i = 0; i < rowCnt * colCnt; i++)
            parentSet[i] = i;
        for (int i = 0; i < rowCnt; i++) {
            for (int j = 0; j < colCnt; j++) {
                int current = i * colCnt + j;
                for (int k = 0; k < 4; k++) {
                    int nextX = i + dirX[k], nextY = j + dirY[k];
                    if (nextX < 0 || nextX >= rowCnt || nextY < 0 || nextY >= colCnt) continue;
                    if (grid[i][j] == grid[nextX][nextY])
                        uniteSet(current, nextX * colCnt + nextY);
                }
            }
        }
        fill(rootId, rootId + 400, -1);
        regionCnt = 0;
        for (int i = 0; i < rowCnt; i++) {
            for (int j = 0; j < colCnt; j++) {
                int root = findRoot(i * colCnt + j);
                if (rootId[root] == -1)
                    rootId[root] = regionCnt++;
                cellId[i][j] = rootId[root];
            }
        }
        memset(edgeMap, 0, sizeof(edgeMap));
        for (int i = 0; i < rowCnt; i++) {
            for (int j = 0; j < colCnt; j++) {
                for (int k = 0; k < 4; k++) {
                    int nextX = i + dirX[k], nextY = j + dirY[k];
                    if (nextX < 0 || nextX >= rowCnt || nextY < 0 || nextY >= colCnt) continue;
                    int first = cellId[i][j], second = cellId[nextX][nextY];
                    if (first != second)
                        edgeMap[first][second] = edgeMap[second][first] = 1;
                }
            }
        }
        answer = 0;
        enumerateMask(0, 0, 0);
        cout << "Case " << caseNo++ << ": " << answer << '\n';
    }
    return 0;
}
