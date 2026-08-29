#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<string> mazeMap;
vector<vector<int> > outsideMap;
vector<vector<int> > yardMap;
int dirX[4] = {-1, 0, 1, 0};
int dirY[4] = {0, 1, 0, -1};

bool InMap(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m;
}

bool IsCorridor(int x, int y) {
    if (mazeMap[x][y] != '.')
        return false;
    bool upWall = x > 0 && mazeMap[x - 1][y] == '#';
    bool downWall = x + 1 < n && mazeMap[x + 1][y] == '#';
    bool leftWall = y > 0 && mazeMap[x][y - 1] == '#';
    bool rightWall = y + 1 < m && mazeMap[x][y + 1] == '#';
    return (upWall && downWall) || (leftWall && rightWall);
}

void MarkOutside() {
    queue<pair<int, int> > que;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i != 0 && i != n - 1 && j != 0 && j != m - 1)
                continue;
            if (mazeMap[i][j] == '.' && !IsCorridor(i, j) && !outsideMap[i][j]) {
                outsideMap[i][j] = 1;
                que.push(make_pair(i, j));
            }
        }
    }
    while (!que.empty()) {
        pair<int, int> cur = que.front();
        que.pop();
        for (int d = 0; d < 4; d++) {
            int nx = cur.first + dirX[d], ny = cur.second + dirY[d];
            if (!InMap(nx, ny) || mazeMap[nx][ny] != '.' || IsCorridor(nx, ny) || outsideMap[nx][ny])
                continue;
            outsideMap[nx][ny] = 1;
            que.push(make_pair(nx, ny));
        }
    }
}

void MarkCourtyard() {
    for (int i = 0; i + 1 < n; i++) {
        for (int j = 0; j + 1 < m; j++) {
            if (mazeMap[i][j] != '.' || mazeMap[i + 1][j] != '.' || mazeMap[i][j + 1] != '.' || mazeMap[i + 1][j + 1] != '.')
                continue;
            if (outsideMap[i][j] || outsideMap[i + 1][j] || outsideMap[i][j + 1] || outsideMap[i + 1][j + 1])
                continue;
            yardMap[i][j] = yardMap[i + 1][j] = 1;
            yardMap[i][j + 1] = yardMap[i + 1][j + 1] = 1;
        }
    }
}

bool ReachCourtyard() {
    MarkOutside();
    MarkCourtyard();
    int sx = -1, sy = -1, sd = -1;
    for (int i = 0; i < n && sx == -1; i++) {
        for (int j = 0; j < m && sx == -1; j++) {
            if (mazeMap[i][j] != '.' || !outsideMap[i][j])
                continue;
            for (int d = 0; d < 4; d++) {
                int nx = i + dirX[d], ny = j + dirY[d];
                if (!InMap(nx, ny) || mazeMap[nx][ny] != '.' || outsideMap[nx][ny])
                    continue;
                sx = nx;
                sy = ny;
                sd = d;
                break;
            }
        }
    }
    if (sx == -1)
        return false;
    vector<vector<vector<int> > > visited(n, vector<vector<int> >(m, vector<int>(4, 0)));
    int x = sx, y = sy, d = sd;
    while (!visited[x][y][d]) {
        if (yardMap[x][y])
            return true;
        visited[x][y][d] = 1;
        int nextDir = -1;
        for (int k = 0; k < 4; k++) {
            int nd = (d + 3 + k) % 4;
            int nx = x + dirX[nd], ny = y + dirY[nd];
            if (InMap(nx, ny) && mazeMap[nx][ny] == '.' && !outsideMap[nx][ny]) {
                nextDir = nd;
                break;
            }
        }
        if (nextDir == -1)
            return false;
        x += dirX[nextDir];
        y += dirY[nextDir];
        d = nextDir;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int testCases;
    cin >> testCases;
    for (int caseId = 0; caseId < testCases; caseId++) {
        cin >> n >> m;
        mazeMap.resize(n);
        for (int i = 0; i < n; i++)
            cin >> mazeMap[i];
        outsideMap.assign(n, vector<int>(m, 0));
        yardMap.assign(n, vector<int>(m, 0));
        if (caseId > 0)
            cout << '\n';
        cout << (ReachCourtyard() ? "YES" : "NO") << '\n';
    }
    return 0;
}
