#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x, y, z;
};

const int dir[6][3] = {
    {1, 0, 0}, {-1, 0, 0}, {0, 1, 0},
    {0, -1, 0}, {0, 0, 1}, {0, 0, -1}
};

int n;
char cube[10][10][10];
int countColor[3];
char colors[3] = {'R', 'G', 'B'};

bool inside(int x, int y, int z) {
    return x >= 0 && x < n && y >= 0 && y < n && z >= 0 && z < n;
}

bool canMoveOne(char color, int d) {
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < n; y++) {
            for (int z = 0; z < n; z++) {
                if (cube[x][y][z] != color) continue;
                int nx = x + dir[d][0], ny = y + dir[d][1], nz = z + dir[d][2];
                if (inside(nx, ny, nz) && cube[nx][ny][nz] != color) return false;
            }
        }
    }
    return true;
}

void removeColor(char color) {
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < n; y++) {
            for (int z = 0; z < n; z++) {
                if (cube[x][y][z] == color) cube[x][y][z] = 0;
            }
        }
    }
}

bool canEscape(char color, int blockCount) {
    int size = 2 * n + 1;
    vector<vector<vector<bool>>> visited(size, vector<vector<bool>>(size, vector<bool>(size, false)));
    queue<Point> que;
    que.push({0, 0, 0});
    visited[n][n][n] = true;
    while (!que.empty()) {
        Point cur = que.front();
        que.pop();
        for (int d = 0; d < 6; d++) {
            int dx = cur.x + dir[d][0], dy = cur.y + dir[d][1], dz = cur.z + dir[d][2];
            if (dx < -n || dx > n || dy < -n || dy > n || dz < -n || dz > n) continue;
            if (visited[dx + n][dy + n][dz + n]) continue;
            bool valid = true;
            int outsideCount = 0;
            for (int x = 0; x < n && valid; x++) {
                for (int y = 0; y < n && valid; y++) {
                    for (int z = 0; z < n; z++) {
                        if (cube[x][y][z] != color) continue;
                        int nx = x + dx, ny = y + dy, nz = z + dz;
                        if (!inside(nx, ny, nz)) {
                            outsideCount++;
                        } else if (cube[nx][ny][nz] != 0 && cube[nx][ny][nz] != color) {
                            valid = false;
                            break;
                        }
                    }
                }
            }
            if (!valid) continue;
            visited[dx + n][dy + n][dz + n] = true;
            if (outsideCount == blockCount) return true;
            que.push({dx, dy, dz});
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> n) {
        memset(cube, 0, sizeof(cube));
        memset(countColor, 0, sizeof(countColor));
        for (int x = 0; x < n; x++) {
            for (int y = 0; y < n; y++) {
                string row;
                cin >> row;
                for (int z = 0; z < n; z++) {
                    cube[x][y][z] = row[z];
                    if (row[z] == 'R') countColor[0]++;
                    else if (row[z] == 'G') countColor[1]++;
                    else countColor[2]++;
                }
            }
        }
        vector<int> direct;
        for (int color = 0; color < 3; color++) {
            for (int d = 0; d < 6; d++) {
                if (canMoveOne(colors[color], d)) {
                    direct.push_back(color);
                    break;
                }
            }
        }
        if (direct.empty()) {
            cout << "NO\n";
            continue;
        }
        if (direct.size() >= 2) {
            cout << "RGB\n";
            continue;
        }
        int firstColor = direct[0];
        removeColor(colors[firstColor]);
        int secondColor = -1;
        for (int color = 0; color < 3; color++) {
            if (color == firstColor || countColor[color] == 0) continue;
            if (secondColor == -1 || countColor[color] < countColor[secondColor]) secondColor = color;
        }
        if (secondColor != -1 && canEscape(colors[secondColor], countColor[secondColor])) cout << "RGB\n";
        else cout << colors[firstColor] << '\n';
    }
    return 0;
}
