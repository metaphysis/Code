// Ricochet Robots
// UVa ID: 12881
// Verdict: Accepted
// Submission Date: 2026-07-17
// UVa Run Time: 0.200s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int n, w, h, l;
vector<string> grid;
int targetIdx;
array<int, 4> initPos;
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

// 计算机器人 robot 沿方向 dir 移动后的终点（若无法移动则返回原位置）
int getMove(int robot, int dir, const array<int, 4>& pos) {
    int idx = pos[robot];
    int x = idx % w, y = idx / w;
    while (true) {
        int nx = x + dx[dir], ny = y + dy[dir];
        if (nx < 0 || nx >= w || ny < 0 || ny >= h) break;          // 边界阻挡
        int nidx = ny * w + nx;
        // 墙壁阻挡（大小写兼容）
        if (grid[ny][nx] == 'w' || grid[ny][nx] == 'W') break;
        bool occupied = false;
        for (int i = 0; i < n; ++i)
            if (i != robot && pos[i] == nidx) { occupied = true; break; }
        if (occupied) break;                                        // 其他机器人阻挡
        // 可前进
        x = nx; y = ny; idx = nidx;
    }
    return idx;
}

// BFS 搜索，返回最小步数或 -1（无解或超过上限）
int bfsSolve() {
    queue<pair<array<int, 4>, int>> q;
    set<array<int, 4>> visited;
    array<int, 4> start;
    start.fill(-1);
    for (int i = 0; i < n; ++i) start[i] = initPos[i];
    q.push({start, 0});
    visited.insert(start);
    while (!q.empty()) {
        auto cur = q.front(); q.pop();
        array<int, 4> s = cur.first;
        int steps = cur.second;
        if (s[0] == targetIdx) return steps;
        if (steps >= l) continue;   // 超出上限不再扩展
        for (int robot = 0; robot < n; ++robot) {
            for (int d = 0; d < 4; ++d) {
                int newIdx = getMove(robot, d, s);
                if (newIdx == s[robot]) continue;
                array<int, 4> ns = s;
                ns[robot] = newIdx;
                if (visited.find(ns) == visited.end()) {
                    visited.insert(ns);
                    q.push({ns, steps + 1});
                }
            }
        }
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> n >> w >> h >> l) {
        grid.resize(h);
        initPos.fill(-1);
        targetIdx = -1;
        for (int y = 0; y < h; ++y) {
            cin >> grid[y];
            for (int x = 0; x < w; ++x) {
                char ch = grid[y][x];
                if (ch == 'X') targetIdx = y * w + x;
                else if (ch >= '1' && ch <= '4') {
                    int id = ch - '1';
                    if (id < n) initPos[id] = y * w + x;
                }
            }
        }
        int ans = bfsSolve();
        if (ans == -1) cout << "NO SOLUTION\n";
        else cout << ans << '\n';
    }
    return 0;
}
