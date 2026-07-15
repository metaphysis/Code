// The Predator
// UVa ID: 10864
// Verdict: Accepted
// Submission Date: 2026-07-15
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Square {
    int x, y, side; // x=列坐标, y=行坐标
};

long long solveCase(int sx, int sy, const vector<Square>& squares) {
    const int ROOM = 10000;
    vector<int> xs, ys;
    xs.push_back(0);
    xs.push_back(ROOM);
    ys.push_back(0);
    ys.push_back(ROOM);

    for (const auto& sq : squares) {
        xs.push_back(sq.x);
        xs.push_back(sq.x + sq.side);
        ys.push_back(sq.y);
        ys.push_back(sq.y + sq.side);
    }

    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());

    int nx = (int)xs.size() - 1;
    int ny = (int)ys.size() - 1;

    vector<vector<bool>> vertBlock(nx - 1, vector<bool>(ny, false));
    vector<vector<bool>> horiBlock(nx, vector<bool>(ny - 1, false));

    for (const auto& sq : squares) {
        int x1 = sq.x, y1 = sq.y;
        int x2 = sq.x + sq.side, y2 = sq.y + sq.side;

        // 垂直边（左右边界）
        for (int i = 0; i < nx - 1; ++i) {
            if (xs[i + 1] == x1 || xs[i + 1] == x2) {
                for (int j = 0; j < ny; ++j) {
                    if (max(y1, ys[j]) < min(y2, ys[j + 1]))
                        vertBlock[i][j] = true;
                }
            }
        }
        // 水平边（上下边界）
        for (int j = 0; j < ny - 1; ++j) {
            if (ys[j + 1] == y1 || ys[j + 1] == y2) {
                for (int i = 0; i < nx; ++i) {
                    if (max(x1, xs[i]) < min(x2, xs[i + 1]))
                        horiBlock[i][j] = true;
                }
            }
        }
    }

    // 定位起点所在的单元格（边界点归入最外侧单元格）
    int ix = upper_bound(xs.begin(), xs.end(), sx) - xs.begin() - 1;
    if (ix < 0) ix = 0;
    if (ix >= nx) ix = nx - 1;
    int iy = upper_bound(ys.begin(), ys.end(), sy) - ys.begin() - 1;
    if (iy < 0) iy = 0;
    if (iy >= ny) iy = ny - 1;
    int si = ix, sj = iy;

    queue<pair<int, int>> q;
    q.push({si, sj});
    vector<vector<bool>> visited(nx, vector<bool>(ny, false));
    visited[si][sj] = true;
    long long area = 0;

    int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}}; // 右、左、上、下

    while (!q.empty()) {
        auto cur = q.front();
        q.pop();
        int i = cur.first, j = cur.second;
        long long w = xs[i + 1] - xs[i];
        long long h = ys[j + 1] - ys[j];
        area += w * h;

        for (int d = 0; d < 4; ++d) {
            int ni = i + dirs[d][0];
            int nj = j + dirs[d][1];
            if (ni < 0 || ni >= nx || nj < 0 || nj >= ny) continue;
            if (visited[ni][nj]) continue;

            bool blocked = false;
            if (d == 0) blocked = vertBlock[i][j];
            else if (d == 1) blocked = vertBlock[i - 1][j];
            else if (d == 2) blocked = horiBlock[i][j];
            else if (d == 3) blocked = horiBlock[i][j - 1];
            if (blocked) continue;

            visited[ni][nj] = true;
            q.push({ni, nj});
        }
    }

    return area;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int C;
    int caseNo = 1;
    while (cin >> C) {
        vector<Square> squares(C);
        for (int i = 0; i < C; ++i) {
            int r, c, s;
            cin >> r >> c >> s;
            squares[i].x = c;
            squares[i].y = r;
            squares[i].side = s;
        }

        int Q;
        cin >> Q;
        cout << "Case " << caseNo << ":\n";
        for (int i = 0; i < Q; ++i) {
            int pr, pc;
            cin >> pr >> pc;
            long long ans = solveCase(pc, pr, squares);
            cout << ans << '\n';
        }
        ++caseNo;
    }
    return 0;
}
