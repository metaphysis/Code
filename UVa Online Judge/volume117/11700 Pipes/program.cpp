// Pipes
// UVa ID: 11700
// Verdict: Accepted
// Submission Date: 2026-06-05
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int dx[4] = {-1, 0, 1, 0}; // N, E, S, W
const int dy[4] = {0, 1, 0, -1};

int R, C;
int g[16][16][4];  // 当前格子各方向是否有线
int kind[16][16];   // 需要尝试的旋转次数
bool solvable;

// 顺时针旋转一次
void rotateCell(int r, int c) {
    int t = g[r][c][0];
    for (int i = 1; i < 4; i++)
        g[r][c][i - 1] = g[r][c][i];
    g[r][c][3] = t;
}

// 检查格子(r,c)与所有方向邻居的匹配，ign表示忽略检查的方向（-1表示检查所有）
bool check(int r, int c, int ign) {
    for (int i = 0; i < 4; i++) {
        if (i == ign) continue;
        if (g[r][c][i]) {
            int tx = r + dx[i], ty = c + dy[i];
            // 指向边界外，非法
            if (tx < 0 || ty < 0 || tx >= R || ty >= C) return false;
            // 邻居必须有相反方向的线
            if (!g[tx][ty][(i + 2) % 4]) return false;
        }
    }
    return true;
}

void dfs(int r, int c) {
    if (solvable) return;
    
    // 一行结束，检查该行最右侧格子的东方向，然后进入下一行
    if (c == C) {
        if (check(r, c - 1, 2)) // 检查最后一格的南方向（忽略？这里ign=2表示忽略检查南？）
            dfs(r + 1, 0);
        return;
    }
    
    // 所有格子处理完毕，检查最后一行
    if (r == R) {
        bool ok = true;
        for (int i = 0; i < C; i++)
            ok &= check(r - 1, i, -1); // 检查最后一行的所有方向
        solvable |= ok;
        return;
    }
    
    // 无线段的格子
    if (kind[r][c] == 0) {
        // 检查上方和左方（如果有）是否匹配
        if (check(r - 1, c, -1)) {
            if (c && !check(r, c - 1, 2)) return;
            dfs(r, c + 1);
        }
        return;
    }
    
    // 有线段，尝试所有需要的旋转
    for (int i = 0; i < kind[r][c]; i++) {
        // 检查与上方格子是否匹配
        if (check(r - 1, c, -1)) {
            // 检查与左方格子是否匹配
            if (c && !check(r, c - 1, 2)) {
                rotateCell(r, c);
                continue;
            }
            dfs(r, c + 1);
            if (solvable) return;
        }
        rotateCell(r, c);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int mapped[256] = {};
    mapped['N'] = 0;
    mapped['E'] = 1;
    mapped['S'] = 2;
    mapped['W'] = 3;
    
    while (cin >> R >> C && (R || C)) {
        memset(g, 0, sizeof(g));
        
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                string s; cin >> s;
                if (s != "x") {
                    for (char ch : s)
                        g[i][j][mapped[ch]] = 1;
                }
                
                // 计算需要尝试的旋转次数
                if (s == "x") {
                    kind[i][j] = 0;
                } else {
                    int len = s.length();
                    if (len == 4) {
                        kind[i][j] = 0; // 全方向，旋转不变
                    } else if (len == 1 || len == 3) {
                        kind[i][j] = 4; // 需要尝试4次
                    } else { // len == 2
                        // 检查是否是直线（相反方向）
                        if (g[i][j][0] && g[i][j][2]) // N和S
                            kind[i][j] = 2;
                        else if (g[i][j][1] && g[i][j][3]) // E和W
                            kind[i][j] = 2;
                        else
                            kind[i][j] = 4; // 拐角
                    }
                }
            }
        }
        
        solvable = false;
        dfs(0, 0);
        cout << (solvable ? "SOLVABLE" : "UNSOLVABLE") << '\n';
    }
    
    return 0;
}
