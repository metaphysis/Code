#include <bits/stdc++.h>
using namespace std;

const int MaxN = 55;
const int MaxV = 26;

int m, n, vCnt;
char grid[MaxN][MaxN], finalGrid[MaxN][MaxN];
int graphMask[MaxV], colorArr[MaxV];
int dirX[4] = {-1, 1, 0, 0};
int dirY[4] = {0, 0, -1, 1};

void floodFill(char blockChar, bool vis[MaxN][MaxN]) {
    int queueX[MaxN * MaxN], queueY[MaxN * MaxN], head = 0, tail = 0;
    memset(vis, false, sizeof(bool) * MaxN * MaxN);
    for (int i = 0; i < m; i++) {
        if (grid[i][0] != blockChar && !vis[i][0]) {
            vis[i][0] = true;
            queueX[tail] = i;
            queueY[tail++] = 0;
        }
        if (grid[i][n - 1] != blockChar && !vis[i][n - 1]) {
            vis[i][n - 1] = true;
            queueX[tail] = i;
            queueY[tail++] = n - 1;
        }
    }
    for (int j = 0; j < n; j++) {
        if (grid[0][j] != blockChar && !vis[0][j]) {
            vis[0][j] = true;
            queueX[tail] = 0;
            queueY[tail++] = j;
        }
        if (grid[m - 1][j] != blockChar && !vis[m - 1][j]) {
            vis[m - 1][j] = true;
            queueX[tail] = m - 1;
            queueY[tail++] = j;
        }
    }
    while (head < tail) {
        int x = queueX[head], y = queueY[head++];
        for (int k = 0; k < 4; k++) {
            int nx = x + dirX[k], ny = y + dirY[k];
            if (nx < 0 || nx >= m || ny < 0 || ny >= n) continue;
            if (vis[nx][ny] || grid[nx][ny] == blockChar) continue;
            vis[nx][ny] = true;
            queueX[tail] = nx;
            queueY[tail++] = ny;
        }
    }
}

bool dfsColor(int coloredCnt, int colorLimit) {
    if (coloredCnt == vCnt) return true;
    int best = -1, bestSat = -1, bestDeg = -1;
    for (int i = 0; i < vCnt; i++) {
        if (colorArr[i] != -1) continue;
        bool used[MaxV] = {};
        int sat = 0, degree = 0;
        for (int j = 0; j < vCnt; j++) {
            if ((graphMask[i] >> j) & 1) {
                degree++;
                if (colorArr[j] != -1 && !used[colorArr[j]]) {
                    used[colorArr[j]] = true;
                    sat++;
                }
            }
        }
        if (sat > bestSat || sat == bestSat && degree > bestDeg) {
            best = i;
            bestSat = sat;
            bestDeg = degree;
        }
    }
    for (int c = 0; c < colorLimit; c++) {
        bool canUse = true;
        for (int j = 0; j < vCnt; j++)
            if ((graphMask[best] >> j) & 1 && colorArr[j] == c) canUse = false;
        if (!canUse) continue;
        colorArr[best] = c;
        if (dfsColor(coloredCnt + 1, colorLimit)) return true;
        colorArr[best] = -1;
    }
    return false;
}

int getMinColor() {
    for (int limit = 1; limit <= 4; limit++) {
        for (int i = 0; i < vCnt; i++) colorArr[i] = -1;
        if (dfsColor(0, limit)) return limit;
    }
    return 4;
}

void solveCase() {
    bool erased[MaxV] = {};
    bool vis[MaxN][MaxN];
    for (int p = 0; p < MaxV; p++) {
        char blockChar = char('A' + p);
        floodFill(blockChar, vis);
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (!vis[i][j] && grid[i][j] != blockChar && grid[i][j] >= 'A' && grid[i][j] <= 'Z')
                    erased[grid[i][j] - 'A'] = true;
    }
    memcpy(finalGrid, grid, sizeof(grid));
    for (int p = 0; p < MaxV; p++) {
        if (erased[p]) continue;
        char blockChar = char('A' + p);
        floodFill(blockChar, vis);
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (!vis[i][j] && grid[i][j] != blockChar)
                    finalGrid[i][j] = blockChar;
    }
    memset(graphMask, 0, sizeof(graphMask));
    bool active[MaxV] = {};
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            if (finalGrid[i][j] >= 'A' && finalGrid[i][j] <= 'Z')
                active[finalGrid[i][j] - 'A'] = true;
    int id[MaxV];
    memset(id, -1, sizeof(id));
    vCnt = 0;
    for (int i = 0; i < MaxV; i++)
        if (active[i]) id[i] = vCnt++;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (finalGrid[i][j] < 'A' || finalGrid[i][j] > 'Z') continue;
            int a = id[finalGrid[i][j] - 'A'];
            for (int k = 0; k < 4; k++) {
                int ni = i + dirX[k], nj = j + dirY[k];
                if (ni < 0 || ni >= m || nj < 0 || nj >= n) continue;
                if (finalGrid[ni][nj] < 'A' || finalGrid[ni][nj] > 'Z') continue;
                int b = id[finalGrid[ni][nj] - 'A'];
                if (a != b) {
                    graphMask[a] |= 1 << b;
                    graphMask[b] |= 1 << a;
                }
            }
        }
    }
    int answer = getMinColor();
    cout << answer << '\n';
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++)
            cout << finalGrid[i][j];
        cout << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    for (int caseId = 1; caseId <= t; caseId++) {
        cin >> m >> n;
        for (int i = 0; i < m; i++)
            cin >> grid[i];
        cout << "Case " << caseId << ": ";
        solveCase();
    }
    return 0;
}
