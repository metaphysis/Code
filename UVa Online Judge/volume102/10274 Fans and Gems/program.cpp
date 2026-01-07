// Fans and Gems
// UVa ID: 10274
// Verdict: Accepted
// Submission Date: 2025-12-31
// UVa Run Time: 0.040s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 16;
// D, L, R, U (字典序顺序)
const int dx[4] = {1, 0, 0, -1}, dy[4] = {0, -1, 1, 0};
const char dirChar[4] = {'D', 'L', 'R', 'U'};

struct State { string board, path; };

string grid[MAXN];
int n, m;

string simulate(string board, int dir, bool &finished) {
    finished = false;
    vector<string> grid(n, string(m, ' '));

    // 从字符串转回网格
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            grid[i][j] = board[i * m + j];

    // 根据方向确定遍历顺序
    int startRow, endRow, stepRow, startCln, endCln, stepCln;
    
    if (dir == 0) { // D: 从上到下，从下到上移动
        startRow = n - 1; endRow = -1; stepRow = -1;
        startCln = 0; endCln = m; stepCln = 1;
    } else if (dir == 1) { // L: 从左到右，从左到右移动
        startRow = 0; endRow = n; stepRow = 1;
        startCln = 1; endCln = m; stepCln = 1;
    } else if (dir == 2) { // R: 从左到右，从右到左移动
        startRow = 0; endRow = n; stepRow = 1;
        startCln = m - 2; endCln = -1; stepCln = -1;
    } else { // U: 从下到上，从上到下移动
        startRow = 1; endRow = n; stepRow = 1;
        startCln = 0; endCln = m; stepCln = 1;
    }

    bool changed = true;
    while (changed) {
        changed = false;
        
        // 阶段1: 移动所有可移动物体（一次性完成）
        vector<string> newGrid = grid;
        for (int i = startRow; i != endRow; i += stepRow)
            for (int j = startCln; j != endCln; j += stepCln) {
                char ch = grid[i][j];
                if (ch == '1' || ch == '2' || ch == '3' || ch == '@') {
                    int x = i, y = j;
                    // 移动到不能移动为止
                    while (true) {
                        int nx = x + dx[dir], ny = y + dy[dir];
                        if (nx < 0 || nx >= n || ny < 0 || ny >= m) break;
                        if (grid[nx][ny] == '#' || grid[nx][ny] != ' ') break;
                        x = nx; y = ny;
                    }
                    if (x != i || y != j) {
                        grid[i][j] = ' ';
                        grid[x][y] = ch;
                        changed = true;
                    }
                }
            }
        
        // 检查是否有移动发生
        if (!changed) break;
        
        // 阶段2: 检查并消除相邻的同色宝石（可能存在 3 个或以上的同色宝石）
        vector<pair<int, int>> toRemove;

        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) {
                char ch = grid[i][j];
                if (ch >= '1' && ch <= '3') {
                    // 检查四个方向是否有同色
                    for (int d = 0; d < 4; d++) {
                        int ni = i, nj = j;
                        vector<pair<int, int>> tmp;
                        while (true) {
                            if (ni >= 0 && ni < n && nj >= 0 && nj < m && grid[ni][nj] == ch) tmp.push_back({ni, nj});
                            else break;
                            ni += dx[d], nj += dy[d];
                        }
                        if (tmp.size() >= 2) toRemove.insert(toRemove.end(), tmp.begin(), tmp.end());
                    }
                }
            }
        
        if (!toRemove.empty()) {
            changed = true;
            for (auto &p : toRemove) grid[p.first][p.second] = ' ';
        }
    }

    // 转回字符串，并检查是否所有宝石已消失
    string result(n * m, ' ');
    int gemCount = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            result[i * m + j] = grid[i][j];
            if (grid[i][j] >= '1' && grid[i][j] <= '3') gemCount++;
        }
    
    if (gemCount == 0) finished = true;
    return result;
}

string solve() {
    string startBoard(n * m, ' ');
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            startBoard[i * m + j] = grid[i][j];

    queue<State> q;
    unordered_set<string> visited;
    q.push({startBoard, ""});
    visited.insert(startBoard);

    while (!q.empty()) {
        State u = q.front(); q.pop();
        if (u.path.size() > 18) continue;
        for (int d = 0; d < 4; d++) {
            bool finished = false;
            string nextBoard = simulate(u.board, d, finished);
            string nextPath = u.path + dirChar[d];
            if (finished) return nextPath;
            if (visited.find(nextBoard) == visited.end()) {
                visited.insert(nextBoard);
                q.push({nextBoard, nextPath});
            }
        }
    }
    return "-1";
}

int main() {
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
    int T; cin >> T;
    while (T--) {
        cin >> n >> m;
        cin.ignore(128, '\n');
        for (int i = 0; i < n; i++) getline(cin, grid[i]);
        // 注意空行的处理，若不处理，会导致运行时错误，可能改行包含了某些不需要的字符
        string emptyLine;
        if (T > 0) getline(cin, emptyLine);
        cout << solve() << '\n';
    }
    return 0;
}
