#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x, y;
};

const int maxCoord = 1000;

void buildInside(const vector<Point> &p, vector<vector<char>> &inside) {
    int n = p.size();
    for (int y = 0; y <= maxCoord; y++) {
        vector<int> cross;
        for (int i = 0; i < n; i++) {
            Point a = p[i], b = p[(i + 1) % n];
            if (a.x == b.x) {
                int low = min(a.y, b.y), high = max(a.y, b.y);
                if (y >= low && y < high) cross.push_back(a.x);
            }
        }
        sort(cross.begin(), cross.end());
        for (int i = 0; i + 1 < (int)cross.size(); i += 2) {
            int left = cross[i], right = cross[i + 1];
            for (int x = left + 1; x < right; x++) inside[x][y] = 1;
        }
    }
}

void markBad(const vector<Point> &p, int m, vector<vector<char>> &bad) {
    int n = p.size();
    int limit = m * m;
    for (int i = 0; i < n; i++) {
        Point a = p[i], b = p[(i + 1) % n];
        if (a.x == b.x) {
            int x1 = a.x, low = min(a.y, b.y), high = max(a.y, b.y);
            int left = max(0, x1 - m), right = min(maxCoord, x1 + m);
            int bottom = max(0, low - m), top = min(maxCoord, high + m);
            for (int x = left; x <= right; x++) {
                for (int y = bottom; y <= top; y++) {
                    int dx = abs(x - x1), dy = 0;
                    if (y < low) dy = low - y;
                    else if (y > high) dy = y - high;
                    if (dx * dx + dy * dy <= limit) bad[x][y] = 1;
                }
            }
        } else {
            int y1 = a.y, low = min(a.x, b.x), high = max(a.x, b.x);
            int bottom = max(0, y1 - m), top = min(maxCoord, y1 + m);
            int left = max(0, low - m), right = min(maxCoord, high + m);
            for (int x = left; x <= right; x++) {
                for (int y = bottom; y <= top; y++) {
                    int dx = 0, dy = abs(y - y1);
                    if (x < low) dx = low - x;
                    else if (x > high) dx = x - high;
                    if (dx * dx + dy * dy <= limit) bad[x][y] = 1;
                }
            }
        }
    }
}

bool canReach(const vector<vector<char>> &inside, const vector<vector<char>> &bad, int sx, int sy, int lx, int ly) {
    if (!inside[sx][sy] || bad[sx][sy] || !inside[lx][ly] || bad[lx][ly]) return false;
    vector<vector<char>> vis(maxCoord + 1, vector<char>(maxCoord + 1, 0));
    queue<pair<int, int>> que;
    int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1}, dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
    que.push({sx, sy});
    vis[sx][sy] = 1;
    while (!que.empty()) {
        int x = que.front().first, y = que.front().second;
        que.pop();
        if (x == lx && y == ly) return true;
        for (int i = 0; i < 8; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx < 0 || nx > maxCoord || ny < 0 || ny > maxCoord) continue;
            if (!inside[nx][ny] || bad[nx][ny] || vis[nx][ny]) continue;
            vis[nx][ny] = 1;
            que.push({nx, ny});
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    while (cin >> n >> m) {
        if (n == 0 && m == 0) break;
        vector<Point> polygon(n);
        for (int i = 0; i < n; i++) {
            cin >> polygon[i].x >> polygon[i].y;
        }
        int sx, sy, lx, ly;
        cin >> sx >> sy >> lx >> ly;
        vector<vector<char>> inside(maxCoord + 1, vector<char>(maxCoord + 1, 0));
        vector<vector<char>> bad(maxCoord + 1, vector<char>(maxCoord + 1, 0));
        buildInside(polygon, inside);
        markBad(polygon, m, bad);
        cout << (canReach(inside, bad, sx, sy, lx, ly) ? "Yes" : "No") << '\n';
    }
    return 0;
}
