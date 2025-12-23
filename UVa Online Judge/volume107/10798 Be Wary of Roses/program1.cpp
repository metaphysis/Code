// Be Wary of Roses
// UVa ID: 10798
// Verdict: Accepted
// Submission Date: 2025-12-23
// UVa Run Time: 0.240s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int n;
string grid[32];
int bestAnswer;
int dx[4] = {0, 1, -1, 0}, dy[4] = {1, 0, 0, -1};
int minRoses[32][32];
int visited[32][32], roses[4];

// 预计算从边界到某个位置踩下的最少玫瑰数量作为启发式剪枝
void bfs() {
    memset(minRoses, 0x3f, sizeof minRoses);
    queue<pair<int, int>> q;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (i == 0 || i == n - 1 || j == 0 || j == n - 1) {
                minRoses[i][j] = (grid[i][j] == 'R') ? 1 : 0;
                q.push({i, j});
            }
    while (!q.empty()) {
        pair<int, int> xy = q.front(); q.pop();
        for (int d = 0; d < 4; d++) {
            int nx = xy.first + dx[d], ny = xy.second + dy[d];
            if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
            if (grid[nx][ny] == 'P') continue;
            int v = minRoses[xy.first][xy.second] + ((grid[nx][ny] == 'R') ? 1 : 0);
            if (v < minRoses[nx][ny]) {
                minRoses[nx][ny] = v;
                q.push({nx, ny});
            }
        }
    }
}

void dfs(int x, int y) {
    // 检查路径是否在边界上，已在边界上则更新答案
    if (x == 0 || y == 0 || x == n - 1 || y == n - 1) {
        bestAnswer = min(bestAnswer, *max_element(roses, roses + 4));
        return;
    }
    // 尝试四个方向移动
    int tmp[4];
    for (int d = 0; d < 4; d++) {
        int newX = x + dx[d], newY = y + dy[d];
        if (newX < 0 || newX >= n || newY < 0 || newY >= n) continue;
        if (visited[newX][newY]) continue;
        bool valid = true;
        for (int i = 0; i < 4; i++) {
            // 利用对称性获取四条路径要走的下一个位置
            int xx = newX, yy = newY;
            if (i == 1) { xx = newY; yy = n - 1 - newX; }
            if (i == 2) { xx = n - 1 - newX; yy = n - 1 - newY; }
            if (i == 3) { xx = n - 1 - newY; yy = newX; }
            // 检查要走的位置是否有玫瑰
            tmp[i] = grid[xx][yy] == 'R';
            // 剪枝
            // 从当前位置到边界至少还需要踩下的玫瑰数量加上到达当前位置已经踩下的玫瑰数量，
            // 如果该数量大于等于最优值，则该条路径可以放弃继续搜索
            if (roses[i] + minRoses[xx][yy] >= bestAnswer) {
                valid = false;
                break;
            }
        }
        if (!valid) continue;
        for (int i = 0; i < 4; i++) roses[i] += tmp[i];
        visited[newX][newY] = true;
        dfs(newX, newY);
        visited[newX][newY] = false;
        for (int i = 0; i < 4; i++) roses[i] -= tmp[i];
    }
}

int main() {
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
    while (cin >> n && n) {
        for (int i = 0; i < n; i++) cin >> grid[i];
        // 确定从边界到任意一个位置至少需要踩下多少玫瑰
        bfs();
        // 先直走，确定一个初始最优值
        bestAnswer = 0;
        for (int i = 0; i < 4; i++) {
            int cnt = 0, x = n / 2, y = n / 2;
            while (true) {
                x += dx[i], y += dy[i];
                if (x < 0 || x >= n || y < 0 || y >= n) break;
                cnt += grid[x][y] == 'R';
            }
            bestAnswer = max(bestAnswer, cnt);
        }
        memset(roses, 0, sizeof roses);
        memset(visited, 0, sizeof visited);
        visited[n / 2][n / 2] = 1;
        dfs(n / 2, n / 2);
        cout << "At most " << bestAnswer << " rose(s) trampled.\n";
    }
    return 0;
}
