// Fix the Pond
// UVa ID: 12529
// Verdict: Accepted
// Submission Date: 2025-10-16
// UVa Run Time: 0.140s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAX = 605;
char b[MAX][MAX];  // 存储屏障方向信息，b[i][j] 表示第 i 行第 j 列的屏障方向
bool v[MAX][MAX];  // 访问标记数组，v[i][j] 表示单元格 (i,j) 是否被访问过
int n, cnt;        // n: 输入参数，cnt: 连通分量计数器
int dx[4] = {0, -1, 0, 1};  // 方向数组: 左、上、右、下
int dy[4] = {-1, 0, 1, 0};  // 对应的列坐标变化

// 检查从单元格 (x,y) 向方向 dir 移动是否可行
bool canMove(int x, int y, int dir) {
    bool evenX = (x % 2 == 0), evenY = (y % 2 == 0);  // 判断行列奇偶性
    // 根据坐标奇偶性的 4 种组合情况分别处理
    if (evenX && evenY) {
        // 偶数行偶数列
        if (dir == 0) return x == 1 || y == 1 || b[x - 1][y / 2] == 'H';  // 向左
        if (dir == 1) return x == 1 || y == 1 || b[x - 1][y / 2] == 'V';  // 向上
        if (dir == 2) return y == 1 || x == 2 * n || b[x][y / 2] == 'H';  // 向右
        return y == 1 || x == 2 * n || b[x][y / 2] == 'V';  // 向下
    }
    else if (evenX && !evenY) {
        // 偶数行奇数列
        if (dir == 0) return x == 2 * n || y == 1 || b[x][y / 2] == 'H';  // 向左
        if (dir == 1) return x == 1 || y == 2 * n + 1 || b[x - 1][(y + 1) / 2] == 'V';  // 向上
        if (dir == 2) return x == 1 || y == 2 * n + 1 || b[x - 1][(y + 1) / 2] == 'H';  // 向右
        return x == 2 * n || y == 1 || b[x][y / 2] == 'V';  // 向下
    }
    else if (!evenX && evenY) {
        // 奇数行偶数列
        if (dir == 0) return x == 2 * n || y == 1 || b[x][y / 2] == 'H';  // 向左
        if (dir == 1) return x == 1 || y == 1 || b[x - 1][y / 2] == 'V';  // 向上
        if (dir == 2) return x == 1 || y == 1 || b[x - 1][y / 2] == 'H';  // 向右
        return x == 2 * n || y == 1 || b[x][y / 2] == 'V';  // 向下
    }
    else {
        // 奇数行奇数列
        if (dir == 0) return x == 1 || y == 1 || b[x - 1][y / 2] == 'H';  // 向左
        if (dir == 1) return x == 1 || y == 1 || b[x - 1][y / 2] == 'V';  // 向上
        if (dir == 2) return y == 2 * n + 1 || x == 2 * n || b[x][(y + 1) / 2] == 'H';  // 向右
        return y == 2 * n + 1 || x == 2 * n || b[x][(y + 1) / 2] == 'V';  // 向下
    }
}

// BFS 遍历连通分量
void bfs(int sx, int sy) {
    queue<pair<int, int>> q;
    q.push({sx, sy});
    v[sx][sy] = true;
    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();  // 结构化绑定，C++17 特性
        // 检查四个方向的移动可能性
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            // 检查新坐标是否在网格内、未被访问且可以移动
            if (nx >= 1 && nx <= 2 * n && ny >= 1 && ny <= 2 * n + 1 && !v[nx][ny] && canMove(x, y, i)) {
                v[nx][ny] = true;
                q.push({nx, ny});
            }
        }
    }
}

int main() {
    while (cin >> n) {
        memset(v, 0, sizeof(v));  // 重置访问标记
        cnt = 0;  // 重置连通分量计数器
        // 读取屏障方向信息
        for (int i = 1; i <= 2 * n - 1; i++) cin >> (b[i] + 1);
        // 遍历所有单元格，统计连通分量
        for (int i = 1; i <= 2 * n; i++)
            for (int j = 1; j <= 2 * n + 1; j++)
                if (!v[i][j]) {
                    cnt++;  // 发现新的连通分量
                    bfs(i, j);  // 遍历该连通分量
                }
        // 输出最小切换次数：连通分量数 - 1
        cout << cnt - 1 << endl;
    }
    return 0;
}
