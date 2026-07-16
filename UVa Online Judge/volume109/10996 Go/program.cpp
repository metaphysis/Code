// Go
// UVa ID: 10996
// Verdict: Accepted
// Submission Date: 2026-07-16
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 19;
int board[MAXN][MAXN];      // 0空, 1黑, 2白
int n, m;
int blackCaptures, whiteCaptures;
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

// 坐标映射：将题目坐标 [-k, k] 映射到数组下标 [0, n-1]
int toBoardX(int x) { return x + (n - 1) / 2; }
int toBoardY(int y) { return y + (n - 1) / 2; }

// 解析落子字符串，如 "B(-2,-3)" 或 "W(3,2)"
struct Move {
    int color; // 1黑 2白
    int x, y;
};
Move parseMove(const string& s) {
    char c = s[0];
    size_t lp = s.find('('), rp = s.find(')');
    string inside = s.substr(lp + 1, rp - lp - 1);
    inside.erase(remove(inside.begin(), inside.end(), ' '), inside.end());
    int x, y;
    sscanf(inside.c_str(), "%d,%d", &x, &y);
    return {(c == 'B' || c == 'b') ? 1 : 2, x, y};
}

// 移除对手所有无气连通块，并累加提子数
void removeCaptured(int opponent) {
    bool visited[MAXN][MAXN] = {false};
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            if (board[i][j] == opponent && !visited[i][j]) {
                vector<pair<int,int>> group;
                queue<pair<int,int>> q;
                q.push({i, j});
                visited[i][j] = true;
                int liberties = 0;
                while (!q.empty()) {
                    auto p = q.front(); q.pop();
                    group.push_back(p);
                    int x = p.first, y = p.second;
                    for (int d = 0; d < 4; ++d) {
                        int nx = x + dx[d], ny = y + dy[d];
                        if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
                        if (board[nx][ny] == 0) liberties++;
                        else if (board[nx][ny] == opponent && !visited[nx][ny]) {
                            visited[nx][ny] = true;
                            q.push({nx, ny});
                        }
                    }
                }
                if (liberties == 0) {
                    for (auto& p : group) board[p.first][p.second] = 0;
                    if (opponent == 1) whiteCaptures += group.size(); // 白方提黑
                    else blackCaptures += group.size();               // 黑方提白
                }
            }
        }
}

// 计算最终得分（领地 + 提子）
pair<int,int> calculateScore() {
    bool visited[MAXN][MAXN] = {false};
    int blackScore = 0, whiteScore = 0;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            if (board[i][j] == 0 && !visited[i][j]) {
                queue<pair<int,int>> q;
                q.push({i, j});
                visited[i][j] = true;
                vector<pair<int,int>> points;
                int colorSet = 0;   // 位1:黑, 位2:白
                while (!q.empty()) {
                    auto p = q.front(); q.pop();
                    points.push_back(p);
                    int x = p.first, y = p.second;
                    for (int d = 0; d < 4; ++d) {
                        int nx = x + dx[d], ny = y + dy[d];
                        if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
                        if (board[nx][ny] == 0 && !visited[nx][ny]) {
                            visited[nx][ny] = true;
                            q.push({nx, ny});
                        } else if (board[nx][ny] != 0) {
                            if (board[nx][ny] == 1) colorSet |= 1;
                            else colorSet |= 2;
                        }
                    }
                }
                if (colorSet == 1) blackScore += points.size();
                else if (colorSet == 2) whiteScore += points.size();
            }
        }
    blackScore += blackCaptures;
    whiteScore += whiteCaptures;
    return {blackScore, whiteScore};
}

int main() {
    while (cin >> n >> m) {
        if (n == 0 && m == 0) break;
        memset(board, 0, sizeof(board));
        blackCaptures = whiteCaptures = 0;
        for (int i = 0; i < m; ++i) {
            string s;
            cin >> s;
            Move mv = parseMove(s);
            int bx = toBoardX(mv.x);
            int by = toBoardY(mv.y);
            board[bx][by] = mv.color;
            int opponent = (mv.color == 1) ? 2 : 1;
            removeCaptured(opponent);
        }
        pair<int,int> ans = calculateScore();
        cout << ans.first << " " << ans.second << endl;
    }
    return 0;
}
