// Be Wary of Roses
// UVa ID: 10798
// Verdict: Accepted
// Submission Date: 2025-12-23
// UVa Run Time: 1.520s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int n;
string grid[32];
int bestAnswer;
int dx[4] = {0, 1, -1, 0}, dy[4] = {1, 0, 0, -1};
int visited[32][32], roses[4];

void dfs(int x, int y) {
    // 检查路径是否在边界上，已在边界上则更新答案
    if (x == 0 || y == 0 || x == n - 1 || y == n - 1) {
        bestAnswer = min(bestAnswer, *max_element(roses, roses + 4));
        return;
    }
    // 尝试四个方向移动
    for (int d = 0; d < 4; d++) {
        int newX = x + dx[d], newY = y + dy[d];
        if (newX < 0 || newX >= n || newY < 0 || newY >= n) continue;
        if (visited[newX][newY]) continue;
        for (int i = 0; i < 4; i++) {
            int xx = newX, yy = newY;
            if (i == 1) { xx = newY; yy = n - 1 - newX; }
            if (i == 2) { xx = n - 1 - newX; yy = n - 1 - newY; }
            if (i == 3) { xx = n - 1 - newY; yy = newX; }
            roses[i] += grid[xx][yy] == 'R';
        }
        // 剪枝
        if (*max_element(roses, roses + 4) < bestAnswer) {
            visited[newX][newY] = true;
            dfs(newX, newY);
            visited[newX][newY] = false;
        }
        for (int i = 0; i < 4; i++) {
            int xx = newX, yy = newY;
            if (i == 1) { xx = newY; yy = n - 1 - newX; }
            if (i == 2) { xx = n - 1 - newX; yy = n - 1 - newY; }
            if (i == 3) { xx = n - 1 - newY; yy = newX; }
            roses[i] -= grid[xx][yy] == 'R';
        }
    }
}

int main() {
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
    while (cin >> n && n) {
        for (int i = 0; i < n; i++) cin >> grid[i];
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
