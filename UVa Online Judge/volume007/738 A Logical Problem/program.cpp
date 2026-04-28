// A Logical Problem
// UVa ID: 738
// Verdict: Accepted
// Submission Date: 2026-04-28
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 110;
const int UP = 0, LEFT = 1, DOWN = 2, RIGHT = 3;

int V[32];
int offset[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
char g[MAXN][MAXN], marker = '.';

// 从 (x, y) 沿方向 dir 走到下一个节点（变量或门输出端）
pair<int, int> walkToNode(int x, int y, int dir) {
    while (true) {
        int tx = x + offset[dir][0], ty = y + offset[dir][1];
        char c = g[tx][ty];
        // 路径字符：继续直行
        if (c == 'o' || c == '-' || c == '|') {
            x = tx, y = ty;
            continue;
        }
        // 交叉点：尝试转向
        if (c == '+') {
            for (int i = 1; i <= 3; i += 2) {
                int ndir = (dir + i) % 4;
                int nx = tx + offset[ndir][0], ny = ty + offset[ndir][1];
                if ((g[x][y] == '-' && g[nx][ny] == '|') || 
                    (g[x][y] == '|' && g[nx][ny] == '-')) {
                    x = nx, y = ny;
                    dir = ndir;
                    break;
                }
            }
            continue;
        }
        // 到达门输出端或输入变量
        if (c == ')' || c == '>' || isupper(c)) return {tx, ty};
    }
}

// 递归计算节点值
int dfs(int x, int y, int dir) {
    auto [cx, cy] = walkToNode(x, y, dir);
    char c = g[cx][cy];
    // 输入变量
    if (c >= 'A' && c <= 'Z') return V[c - 'A'];
    // 门输出端
    int v1 = dfs(cx - 1, cy - 3, LEFT);
    int v2 = dfs(cx + 1, cy - 3, LEFT);
    if (g[cx - 1][cy - 3] == 'o') v1 = 1 - v1;
    if (g[cx + 1][cy - 3] == 'o') v2 = 1 - v2;
    int v = (c == ')') ? (v1 & v2) : (v1 | v2);
    if (g[cx][cy + 1] == 'o') v = 1 - v;
    return v;
}

// 确定 '?' 的起始方向（只检测 '-' 或 '|' 的直接连接）
int getStartDir(int x, int y) {
    for (int d = 0; d < 4; d++) {
        int nx = x + offset[d][0], ny = y + offset[d][1];
        char c = g[nx][ny];
        if (c == '-' || c == '|') return d;
    }
    return -1;
}

int main() {
    string line;
    int rows = 1, outx, outy;
    memset(g, marker, sizeof g);
    
    while (getline(cin, line)) {
        if (line == "*") {
            // 处理当前电路的所有输入
            while (getline(cin, line)) {
                if (line == "*") {
                    // 电路结束，输出空行（每组测试数据后都有一个空行）
                    cout << '\n';
                    // 重置网格和行号
                    memset(g, marker, sizeof g);
                    rows = 1;
                    break;
                }
                // 解析输入值
                for (int i = 0; i < (int)line.length(); i++) V[i] = line[i] - '0';
                int startDir = getStartDir(outx, outy);
                cout << dfs(outx, outy, startDir) << '\n';
            }
        } else {
            // 读取电路图的一行
            for (int j = 0; j < (int)line.length(); j++) {
                g[rows][j + 1] = line[j];
                if (line[j] == '?') {
                    outx = rows;
                    outy = j + 1;
                }
            }
            rows++;
        }
    }
    return 0;
}
