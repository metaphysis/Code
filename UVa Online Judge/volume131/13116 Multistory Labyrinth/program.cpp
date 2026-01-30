// Multistory Labyrinth
// UVa ID: 13116
// Verdict: Accepted
// Submission Date: 2026-01-26
// UVa Run Time: 0.100s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;  // 最大维度

struct Point {
    int x, y, z;  // x:行, y:列, z:层
    Point(int x, int y, int z) : x(x), y(y), z(z) {}
};

// 方向数组：dx 表示行变化，dy 表示列变化
int dx[] = {1, -1, 0, 0, 0, 0}, dy[] = {0, 0, 1, -1, 0, 0};

char grid[MAXN][MAXN][MAXN];  // 存储迷宫：[层][行][列]
int dist[MAXN][MAXN][MAXN];   // 存储距离：[层][行][列]

int bfs(Point start, Point end, int l, int w, int h) {
    // 初始化距离为 -1（未访问）
    memset(dist, -1, sizeof dist);
    queue<Point> q;
    dist[start.z][start.x][start.y] = 0;
    q.push(start);
    
    while (!q.empty()) {
        Point p = q.front(); q.pop();
        // 到达终点，返回最短步数
        if (p.x == end.x && p.y == end.y && p.z == end.z)
            return dist[p.z][p.x][p.y];
        
        // 四方向移动（同一层内）
        for (int i = 0; i < 4; i++) {
            int nx = p.x + dx[i], ny = p.y + dy[i], nz = p.z;
            if (nx >= 0 && nx < l && ny >= 0 && ny < w && nz >= 0 && nz < h) {
                if (grid[nz][nx][ny] != '#' && dist[nz][nx][ny] == -1) {
                    dist[nz][nx][ny] = dist[p.z][p.x][p.y] + 1;
                    q.push(Point(nx, ny, nz));
                }
            }
        }
        
        // 电梯上下移动
        if (grid[p.z][p.x][p.y] == '-') {
            for (int dz : {1, -1}) {  // 上楼和下楼
                int nz = p.z + dz;
                if (nz >= 0 && nz < h && grid[nz][p.x][p.y] == '-') {
                    if (dist[nz][p.x][p.y] == -1) {
                        dist[nz][p.x][p.y] = dist[p.z][p.x][p.y] + 1;
                        q.push(Point(p.x, p.y, nz));
                    }
                }
            }
        }
    }
    return -1;  // 无法到达终点
}

int main() {
    int l, w, h;
    while (cin >> l >> w >> h) {
        if (l == 0 && w == 0 && h == 0) break;
        Point start(0, 0, 0), end(0, 0, 0);
        
        // 读取 h 层，每层 l 行，每行 w 个字符
        for (int k = 0; k < h; k++) {
            for (int i = 0; i < l; i++) {  // 每层有 l 行
                string line;
                cin >> line;
                for (int j = 0; j < w; j++) {  // 每行有 w 列
                    grid[k][i][j] = line[j];
                    if (line[j] == 'S') start = Point(i, j, k);  // 记录起点
                    if (line[j] == 'E') end = Point(i, j, k);    // 记录终点
                }
            }
        }
        
        int r = bfs(start, end, l, w, h);
        cout << r << endl;
    }
    return 0;
}
