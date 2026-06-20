// Pyramid
// UVa ID: 10632
// Verdict: Accepted
// Submission Date: 2026-06-20
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 55;
int n;
int col[MAXN][MAXN];     // 当前颜色 0=R,1=G,2=B
int backup[MAXN][MAXN];  // 初始颜色备份
vector<int> path;        // 存储跳跃方向数字

// 递归构造跳跃序列
void dfs(int r, int c) {
    if (r == n && c == n) return;
    if (r == c) { // 对角线上的格子
        int nr = r + 1, nc = c + 1;
        // 通过来回跳跃将 (r,c) 变成蓝色
        while (col[r][c] != 2) {
            path.push_back(3); // 右下
            path.push_back(7); // 左上
            col[nr][nc] = (col[nr][nc] + 1) % 3;
            col[r][c] = (col[r][c] + 1) % 3;
        }
        // 若已经到达底部倒数第二格且右下角已是蓝色，结束
        if (col[nr][nc] == 2 && r == n - 1 && c == n - 1) return;
        // 跳向右下方，处理下一列
        path.push_back(3);
        col[nr][nc] = (col[nr][nc] + 1) % 3;
        // 沿着左边向下移动到底部
        while (nr < n) {
            path.push_back(1); // 左下
            nr++;
            col[nr][nc] = (col[nr][nc] + 1) % 3;
        }
        dfs(n, c + 1);
    } else { // 非对角线 (r > c)
        int nr = r - 1, nc = c;
        // 通过来回跳跃将 (r,c) 变成蓝色
        while (col[r][c] != 2) {
            path.push_back(9); // 右上
            path.push_back(1); // 左下
            col[nr][nc] = (col[nr][nc] + 1) % 3;
            col[r][c] = (col[r][c] + 1) % 3;
        }
        // 跳向右上方，继续处理上一行
        path.push_back(9);
        col[nr][nc] = (col[nr][nc] + 1) % 3;
        dfs(nr, nc);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    while (cin >> n && n != 0) {
        // 读入初始配置
        for (int i = 1; i <= n; ++i) {
            string s; cin >> s;
            for (int j = 1; j <= i; ++j) {
                char ch = s[j - 1];
                int val = (ch == 'R' ? 0 : (ch == 'G' ? 1 : 2));
                backup[i][j] = col[i][j] = val;
            }
        }
        path.clear();
        dfs(n, 1); // 尝试从底部最左出发
        int startRow;
        if (col[n][n] != 2) { // 若右下角未变蓝，从上一行重新开始
            path.clear();
            path.push_back(1); // 先向下跳一步
            backup[n][1] = (backup[n][1] + 1) % 3;
            for (int i = 1; i <= n; ++i)
                for (int j = 1; j <= i; ++j)
                    col[i][j] = backup[i][j];
            dfs(n, 1);
            startRow = n - 1;
        } else {
            startRow = n;
        }
        cout << startRow << " 1\n";
        for (int d : path) cout << char(d + '0');
        cout << "\n";
    }
    return 0;
}
