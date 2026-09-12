#include <bits/stdc++.h>
using namespace std;

int solve() {
    int testCount, n, r, x, y, dir;
    cin >> testCount;
    while (testCount--) {
        cin >> n >> r;
        vector<vector<bool>> hasTurner(n + 2, vector<bool>(n + 2, false));
        for (int i = 0; i < r; i++) {
            cin >> x >> y;
            hasTurner[x][y] = true;
        }
        cin >> x >> y;
        if (y == 0) dir = 0;
        else if (x == n + 1) dir = 3;
        else if (y == n + 1) dir = 2;
        else dir = 1;
        vector<vector<vector<bool>>> visited(n + 2, vector<vector<bool>>(n + 2, vector<bool>(4, false)));
        int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};
        while (true) {
            x += dx[dir];
            y += dy[dir];
            if (x < 1 || x > n || y < 1 || y > n) {
                cout << x << " " << y << "\n";
                break;
            }
            if (visited[x][y][dir]) {
                cout << "0 0\n";
                break;
            }
            visited[x][y][dir] = true;
            if (hasTurner[x][y]) dir = (dir + 1) % 4;
        }
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return solve();
}
