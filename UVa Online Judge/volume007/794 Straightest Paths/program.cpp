// Straightest Paths
// UVa ID: 794
// Verdict: Accepted
// Submission Date: 2026-07-08
// UVa Run Time: 0.100s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct State {
    int r, c, d;
};

void solveMap(const vector<string>& mapLines, const string& termLine) {
    if (mapLines.empty()) return;
    const int R = (int)mapLines.size();
    int C = 0;
    for (const string& s : mapLines) C = max(C, (int)s.size());
    vector<string> grid(R, string(C, ' '));
    for (int i = 0; i < R; ++i)
        for (int j = 0; j < (int)mapLines[i].size(); ++j)
            grid[i][j] = mapLines[i][j];
    int sr = -1, sc = -1, er = -1, ec = -1;
    for (int i = 0; i < R; ++i)
        for (int j = 0; j < C; ++j)
            if (grid[i][j] == '@') {
                if (sr == -1) { sr = i; sc = j; }
                else { er = i; ec = j; }
            }
    const int dr[4] = {-1, 1, 0, 0};
    const int dc[4] = {0, 0, -1, 1};
    // BFS 求最短距离（步数）
    vector<vector<int>> dist(R, vector<int>(C, -1));
    queue<pair<int,int>> q;
    dist[sr][sc] = 0;
    q.push({sr, sc});
    while (!q.empty()) {
        pair<int,int> cur = q.front(); q.pop();
        int r = cur.first, c = cur.second;
        for (int d = 0; d < 4; ++d) {
            int nr = r + dr[d], nc = c + dc[d];
            if (nr < 0 || nr >= R || nc < 0 || nc >= C) continue;
            if (grid[nr][nc] == 'X') continue;
            if (dist[nr][nc] == -1) {
                dist[nr][nc] = dist[r][c] + 1;
                q.push({nr, nc});
            }
        }
    }
    int shortestDist = dist[er][ec];
    int points = shortestDist + 1;
    const int INF = 1e9;
    vector<vector<vector<int>>> turn(R, vector<vector<int>>(C, vector<int>(4, INF)));
    vector<vector<vector<long long>>> ways(R, vector<vector<long long>>(C, vector<long long>(4, 0)));
    // 从起点出发的第一步
    for (int d = 0; d < 4; ++d) {
        int nr = sr + dr[d], nc = sc + dc[d];
        if (nr < 0 || nr >= R || nc < 0 || nc >= C) continue;
        if (grid[nr][nc] == 'X') continue;
        if (dist[nr][nc] == 1) {
            turn[nr][nc][d] = 0;
            ways[nr][nc][d] = 1;
        }
    }
    // DP 按距离递增
    for (int step = 1; step <= shortestDist; ++step) {
        for (int r = 0; r < R; ++r)
            for (int c = 0; c < C; ++c) {
                if (dist[r][c] != step) continue;
                for (int d = 0; d < 4; ++d) {
                    if (turn[r][c][d] == INF) continue;
                    int curTurn = turn[r][c][d];
                    long long curWays = ways[r][c][d];
                    for (int nd = 0; nd < 4; ++nd) {
                        int nr = r + dr[nd], nc = c + dc[nd];
                        if (nr < 0 || nr >= R || nc < 0 || nc >= C) continue;
                        if (grid[nr][nc] == 'X') continue;
                        if (dist[nr][nc] != dist[r][c] + 1) continue;
                        int newTurn = curTurn + (nd != d ? 1 : 0);
                        if (newTurn < turn[nr][nc][nd]) {
                            turn[nr][nc][nd] = newTurn;
                            ways[nr][nc][nd] = curWays;
                        } else if (newTurn == turn[nr][nc][nd]) {
                            ways[nr][nc][nd] += curWays;
                        }
                    }
                }
            }
    }
    // 统计终点的最优值
    int minTurns = INF;
    long long totalPaths = 0;
    for (int d = 0; d < 4; ++d) {
        if (turn[er][ec][d] < minTurns) {
            minTurns = turn[er][ec][d];
            totalPaths = ways[er][ec][d];
        } else if (turn[er][ec][d] == minTurns) {
            totalPaths += ways[er][ec][d];
        }
    }
    // 标记所有最优路径上的点
    vector<vector<bool>> mark(R, vector<bool>(C, false));
    vector<vector<vector<bool>>> visited(R, vector<vector<bool>>(C, vector<bool>(4, false)));
    vector<State> st;
    for (int d = 0; d < 4; ++d)
        if (turn[er][ec][d] == minTurns && !visited[er][ec][d]) {
            visited[er][ec][d] = true;
            st.push_back({er, ec, d});
        }
    while (!st.empty()) {
        State cur = st.back(); st.pop_back();
        int r = cur.r, c = cur.c, d = cur.d;
        mark[r][c] = true;
        if (r == sr && c == sc) continue;
        int pr = r - dr[d], pc = c - dc[d];
        if (pr < 0 || pr >= R || pc < 0 || pc >= C) continue;
        if (grid[pr][pc] == 'X') continue;
        if (dist[pr][pc] != dist[r][c] - 1) continue;
        for (int pd = 0; pd < 4; ++pd) {
            if (turn[pr][pc][pd] == INF) continue;
            int cost = (pd != d ? 1 : 0);
            if (turn[pr][pc][pd] + cost == turn[r][c][d]) {
                if (pr == sr && pc == sc) {
                    mark[pr][pc] = true;
                } else if (!visited[pr][pc][pd]) {
                    visited[pr][pc][pd] = true;
                    st.push_back({pr, pc, pd});
                }
            }
        }
    }
    // 输出
    cout << totalPaths << " paths, " << points << " points, " << minTurns << " turns\n";
    for (int i = 0; i < R; ++i) {
        string out;
        for (int j = 0; j < C; ++j) {
            if (grid[i][j] == '@') out += '@';
            else if (mark[i][j]) out += '#';
            else out += grid[i][j];
        }
        while (out.size() && out.back() == ' ') out.pop_back();
        cout << out << '\n';
    }
    cout << termLine << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string line;
    vector<string> mapLines;
    while (getline(cin, line)) {
        bool isTerm = true;
        for (char ch : line)
            if (ch != '_') { isTerm = false; break; }
        if (isTerm) {
            solveMap(mapLines, line);
            mapLines.clear();
        } else mapLines.push_back(line);
    }
    return 0;
}
