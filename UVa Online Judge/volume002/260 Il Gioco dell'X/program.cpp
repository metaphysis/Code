// Il Gioco dell'X
// UVa ID: 260
// Verdict: Accepted
// Submission Date: 2016-05-10
// UVa Run Time: 0.200s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

char board[200][200];   // 存储棋盘，'b' 表示黑棋，'w' 表示白棋
bool visited[200][200]; // 标记 DFS 过程中已访问的格子
int n;                  // 棋盘大小 N
// 六边形网格的六个邻接方向，对应题目中定义的邻居关系
int step[6][2] = {{0, -1}, {-1, -1}, {-1, 0}, {0, 1}, {1, 1}, {1, 0}};

// 深度优先搜索，从 (x, y) 出发，标记所有连通的 'b' 格子
void dfs(int x, int y) {
    visited[x][y] = true;
    for (int i = 0; i < 6; i++) {
        int xx = x + step[i][0], yy = y + step[i][1];
        // 检查边界、是否为黑棋、是否未访问
        if (xx >= 0 && xx < n && yy >= 0 && yy < n && board[xx][yy] == 'b' && !visited[xx][yy])
            dfs(xx, yy);
    }
}

int main() {
    cin.tie(0); cin.sync_with_stdio(false);
    int cases = 0;  // 游戏局数计数器
    while (cin >> n, n) {
        // 读入棋盘
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                cin >> board[i][j];
        // 检查黑方是否获胜
        bool blackWin = false;
        // 遍历第一行（上边界）的所有格子
        for (int i = 0; i < n; i++) {
            // 如果上边界的某个格子是黑棋，则从它开始 DFS
            if (board[0][i] == 'b') {
                // 重置访问标记数组
                for (int x = 0; x < n; x++)
                    for (int y = 0; y < n; y++)
                        visited[x][y] = false;
                dfs(0, i);  // 从 (0, i) 开始搜索
                // 检查最后一行（下边界）是否有被标记的黑棋
                for (int k = 0; k < n; k++)
                    if (visited[n - 1][k]) {
                        blackWin = true;
                        break;
                    }
            }
            // 如果已经判定黑方获胜，提前结束循环
            if (blackWin) break;
        }
        // 输出结果：局数编号和胜者（B 或 W）
        cases++;
        cout << cases << " " << (blackWin ? "B" : "W") << endl;
    }
	return 0;
}
