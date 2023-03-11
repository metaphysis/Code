// Nurikabe
// UVa ID: 11585
// Verdict: Accepted
// Submission Date: 2023-03-11
// UVa Run Time: 0.029s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int r, c, d;
int grid[110][110], visited[110][110];

bool chk1() {
    memset(visited, 0, sizeof visited);
    queue<pair<int, int>> q;
    int added = 0;
    for (int i = 0; i < r && !added; i++)
        for (int j = 0; j < c && !added; j++)
            if (grid[i][j] == -1) {
                q.push(make_pair(i, j));
                visited[i][j] = 1;
                added = 1;
            }
    while (!q.empty()) {
        pair<int, int> p = q.front(); q.pop();
        for (int x = -1; x <= 1; x++)
            for (int y = -1; y <= 1; y++)
                if (x * y == 0) {
                    int ni = p.first + x, nj = p.second + y;
                    if (ni < 0 || ni >= r || nj < 0 || nj >= c) continue;
                    if (!visited[ni][nj] && grid[ni][nj] == -1) {
                        visited[ni][nj] = 1;
                        q.push(make_pair(ni, nj));
                    }
                }
    }
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            if (!visited[i][j] && grid[i][j] == -1)
                return false;
    return true;
}

bool chk2() {
    memset(visited, 0, sizeof visited);
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++) {
            if (grid[i][j] > 0) {
                queue<pair<int, int>> q;
                q.push(make_pair(i, j));
                int cnt = 1;
                visited[i][j] = 1;
                while (!q.empty()) {
                    pair<int, int> p = q.front(); q.pop();
                    for (int x = -1; x <= 1; x++)
                        for (int y = -1; y <= 1; y++)
                            if ((x * y) == 0 && (x + y) != 0) {
                                int ni = p.first + x, nj = p.second + y;
                                if (ni < 0 || ni >= r || nj < 0 || nj >= c) continue;
                                if (!visited[ni][nj]) {
                                    if (grid[ni][nj] == 0) {
                                        cnt++;
                                        q.push(make_pair(ni, nj));
                                        visited[ni][nj] = 1;
                                    }
                                    if (grid[ni][nj] > 0) return false;
                                }
                            }
                }
                if (cnt != grid[i][j]) return false;
            }
        }
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            if (grid[i][j] == 0 && !visited[i][j])
                return false;
    return true;
}

bool chk3() {
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++) {
            if (grid[i][j] > 0) {
                memset(visited, 0, sizeof visited);
                queue<pair<int, int>> q;
                q.push(make_pair(i, j));
                int sided = i == 0 || i == r - 1 || j == 0 || j == c - 1;
                visited[i][j] = 1;
                while (!q.empty()) {
                    pair<int, int> p = q.front(); q.pop();
                    for (int x = -1; x <= 1; x++)
                        for (int y = -1; y <= 1; y++) {
                            int ni = p.first + x, nj = p.second + y;
                            if (ni < 0 || ni >= r || nj < 0 || nj >= c) continue;
                            if (!visited[ni][nj] && grid[ni][nj] >= 0) {
                                q.push(make_pair(ni, nj));
                                visited[ni][nj] = 1;
                                sided |= ni == 0 || ni == r - 1 || nj == 0 || nj == c - 1;
                            }
                        }
                }
                if (!sided) return false;
            }
        }
    return true;
}

bool chk4() {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (i == r - 1 || j == c - 1) continue;
            int cnt = 0;
            if (grid[i][j] >= 0) cnt++;
            if (grid[i + 1][j] >= 0) cnt++;
            if (grid[i][j + 1] >= 0) cnt++;
            if (grid[i + 1][j + 1] >= 0) cnt++;
            if (cnt == 0) return false;
        }
    }
    return true;
}

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int cases; cin >> cases;
    while (cases--) {
        cin >> r >> c >> d;
        memset(grid, 0, sizeof grid);
        for (int i = 0, rr, cc, nn; i < d; i++) {
            cin >> rr >> cc >> nn;
            grid[rr][cc] = nn;
        }
        int bad = 0;
        char space;
        for (int i = 0; i < r; i++)
            for (int j = 0; j < c; j++) {
                cin >> space;
                if (space == '#') {
                    if (grid[i][j] > 0) bad = 1;
                    grid[i][j] = -1;
                }
            }
        if (!bad && chk1() && chk2() && chk3() && chk4()) cout << "solved";
        else cout << "not solved";
        cout << '\n';
    }
    return 0;
}
