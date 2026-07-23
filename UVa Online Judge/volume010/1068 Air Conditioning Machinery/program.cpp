// Air Conditioning Machinery
// UVa ID: 1068
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 方向映射：0:+x, 1:-x, 2:+y, 3:-y, 4:+z, 5:-z
int dx[6] = {1, -1, 0, 0, 0, 0};
int dy[6] = {0, 0, 1, -1, 0, 0};
int dz[6] = {0, 0, 0, 0, 1, -1};

int X, Y, Z;                   // 空间尺寸
int sx, sy, sz, ex, ey, ez;    // 入口/出口立方体坐标
int sinDir, soutDir;           // 入口/出口方向
int K;                         // 当前尝试的肘段数
bool vis[21][21][21];          // 访问标记，最大20

// 判断两个方向是否垂直（点积为0）
bool isVertical(int a, int b) {
    return dx[a] * dx[b] + dy[a] * dy[b] + dz[a] * dz[b] == 0;
}

// 方向字符串转编号
int dirToId(const string& s) {
    if (s == "+x") return 0;
    if (s == "-x") return 1;
    if (s == "+y") return 2;
    if (s == "-y") return 3;
    if (s == "+z") return 4;
    return 5; // "-z"
}

// 深度优先搜索
// 当前所在立方体 (x,y,z)，正在构建第 segIdx 个段（0起始），
// 段内已走步数 segStep (0~3)，本段入口方向 inDir，
// mode: 0=未定, 1=模式A(入口,入口,出口), 2=模式B(入口,出口,出口)
// outDir: 本段出口方向（未定时为 -1）
bool dfs(int x, int y, int z, int segIdx, int segStep, int inDir, int mode, int outDir) {
    // 如果段内三步已经走完
    if (segStep == 3) {
        // 如果是最后一段，检查是否到达出口且方向匹配
        if (segIdx == K - 1)
            return (x == ex && y == ey && z == ez && outDir == soutDir);
        // 否则需要走连接步，方向必须等于本段出口方向
        int d = outDir;
        int nx = x + dx[d], ny = y + dy[d], nz = z + dz[d];
        if (nx < 1 || nx > X || ny < 1 || ny > Y || nz < 1 || nz > Z) return false;
        if (vis[nx][ny][nz]) return false;
        vis[nx][ny][nz] = true;
        bool res = dfs(nx, ny, nz, segIdx + 1, 0, d, 0, -1);
        vis[nx][ny][nz] = false;
        return res;
    }
    // 枚举下一步方向
    for (int d = 0; d < 6; ++d) {
        bool ok = false;
        int newMode = mode, newOut = outDir;
        if (segStep == 0) {
            // 第一步必须等于入口方向
            if (d == inDir) ok = true;
        } else if (segStep == 1) {
            // 第二步：可选入口方向（模式A）或垂直方向（模式B）
            if (d == inDir) {
                ok = true;
                newMode = 1;      // 模式A
                newOut = -1;
            } else if (isVertical(inDir, d)) {
                ok = true;
                newMode = 2;      // 模式B，出口方向就是 d
                newOut = d;
            }
        } else if (segStep == 2) {
            // 第三步
            if (mode == 1) {
                // 模式A：第三步必须垂直于入口方向且不等于入口方向
                if (isVertical(inDir, d) && d != inDir) {
                    ok = true;
                    newOut = d;
                }
            } else if (mode == 2) {
                // 模式B：第三步必须等于之前确定的出口方向
                if (d == outDir) {
                    ok = true;
                    newOut = outDir;
                }
            }
        }
        if (!ok) continue;
        int nx = x + dx[d], ny = y + dy[d], nz = z + dz[d];
        if (nx < 1 || nx > X || ny < 1 || ny > Y || nz < 1 || nz > Z) continue;
        if (vis[nx][ny][nz]) continue;
        vis[nx][ny][nz] = true;
        bool res = false;
        if (segStep == 0) res = dfs(nx, ny, nz, segIdx, 1, inDir, 0, -1);
        else if (segStep == 1) res = dfs(nx, ny, nz, segIdx, 2, inDir, newMode, newOut);
        else res = dfs(nx, ny, nz, segIdx, 3, inDir, mode, newOut);
        vis[nx][ny][nz] = false;
        if (res) return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int caseNo = 1;
    while (cin >> X && X != 0) {
        cin >> Y >> Z;
        cin >> sx >> sy >> sz;
        string sinStr; cin >> sinStr;
        cin >> ex >> ey >> ez;
        string soutStr; cin >> soutStr;
        sinDir = dirToId(sinStr);
        soutDir = dirToId(soutStr);
        int ans = -1;
        for (K = 1; K <= 6; ++K) {
            memset(vis, false, sizeof(vis));
            vis[sx][sy][sz] = true;
            if (dfs(sx, sy, sz, 0, 0, sinDir, 0, -1)) {
                ans = K;
                break;
            }
        }
        cout << "Case " << caseNo++ << ": ";
        if (ans == -1) cout << "Impossible\n";
        else cout << ans << '\n';
    }
    return 0;
}
