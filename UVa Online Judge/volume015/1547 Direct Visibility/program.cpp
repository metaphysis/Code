#include <bits/stdc++.h>
using namespace std;

int gcdValue(int a, int b) {
    while (b != 0) {
        int temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

bool canSee(const vector<vector<int>>& height, int sr, int sc, int tr, int tc) {
    int dx = tc - sc, dy = tr - sr, dz = height[tr][tc] - height[sr][sc];
    if (dx == 0 && dy == 0)
        return true;
    int absDx = abs(dx), absDy = abs(dy), base = 1;
    if (absDx != 0 && absDy != 0)
        base = absDx / gcdValue(absDx, absDy) * absDy;
    else if (absDx != 0)
        base = absDx;
    else
        base = absDy;
    long long den = 2LL * base, currentNum = 0, nextX = LLONG_MAX, nextY = LLONG_MAX;
    long long stepX = LLONG_MAX, stepY = LLONG_MAX;
    if (dx != 0) {
        stepX = 2LL * base / absDx;
        nextX = base / absDx;
    }
    if (dy != 0) {
        stepY = 2LL * base / absDy;
        nextY = base / absDy;
    }
    int row = sr, col = sc, rowStep = (dy > 0 ? 1 : -1), colStep = (dx > 0 ? 1 : -1);
    while (currentNum < den) {
        long long nextNum = min(den, min(nextX, nextY));
        long long checkNum = dz >= 0 ? currentNum : nextNum;
        long long pointHeight = (2LL * height[sr][sc] + 1) * den + 2LL * dz * checkNum;
        if (pointHeight < 2LL * height[row][col] * den)
            return false;
        currentNum = nextNum;
        if (currentNum == den)
            break;
        if (nextX == currentNum) {
            col += colStep;
            nextX += stepX;
        }
        if (nextY == currentNum) {
            row += rowStep;
            nextY += stepY;
        }
    }
    return true;
}

int solve() {
    int p, q;
    cin >> p >> q;
    vector<vector<int>> height(p, vector<int>(q));
    for (int i = 0; i < p; i++)
        for (int j = 0; j < q; j++)
            cin >> height[i][j];
    int r1, c1, r2, c2;
    cin >> r1 >> c1 >> r2 >> c2;
    --r1;
    --c1;
    --r2;
    --c2;
    vector<vector<bool>> visible1(p, vector<bool>(q)), visible2(p, vector<bool>(q));
    for (int i = 0; i < p; i++)
        for (int j = 0; j < q; j++) {
            visible1[i][j] = canSee(height, r1, c1, i, j);
            visible2[i][j] = canSee(height, r2, c2, i, j);
        }
    vector<vector<int>> distance(p, vector<int>(q, -1));
    queue<pair<int, int>> que;
    distance[r1][c1] = 0;
    que.push({r1, c1});
    int dr[4] = {-1, 1, 0, 0}, dc[4] = {0, 0, -1, 1};
    while (!que.empty()) {
        pair<int, int> current = que.front();
        que.pop();
        int row = current.first, col = current.second;
        if (row == r2 && col == c2) {
            cout << "The shortest path is " << distance[row][col] << " steps long.\n";
            return 0;
        }
        for (int k = 0; k < 4; k++) {
            int nextRow = row + dr[k], nextCol = col + dc[k];
            if (nextRow < 0 || nextRow >= p || nextCol < 0 || nextCol >= q)
                continue;
            if (distance[nextRow][nextCol] != -1)
                continue;
            int heightDiff = height[nextRow][nextCol] - height[row][col];
            if (heightDiff < -3 || heightDiff > 1)
                continue;
            if (!visible1[nextRow][nextCol] && !visible2[nextRow][nextCol])
                continue;
            distance[nextRow][nextCol] = distance[row][col] + 1;
            que.push({nextRow, nextCol});
        }
    }
    cout << "Mission impossible!\n";
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    while (testCount--)
        solve();
    return 0;
}
