// Going Together
// UVa ID: 11160
// Verdict: Accetped
// Submission Date: 2023-04-15
// UVa Run Time: 0.460s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;
int d[11][11][11][11][11][11];
char g[11][11];
int offset[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
struct st { int x1, y1, x2, y2, x3, y3, t; };
int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int T, n;
    cin >> T;
    for (int cs = 1; cs <= T; cs++) {
        cout << "Case " << cs << ": ";
        cin >> n;
        int rx1 = -1, ry1 = -1, rx2 = -1, ry2 = -1, rx3 = -1, ry3 = -1;
        int tx1 = -1, ty1 = -1, tx2 = -1, ty2 = -1, tx3 = -1, ty3 = -1;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                cin >> g[i][j];
                if (g[i][j] == 'A') rx1 = i, ry1 = j;
                if (g[i][j] == 'B') rx2 = i, ry2 = j;
                if (g[i][j] == 'C') rx3 = i, ry3 = j;
                if (g[i][j] == 'X') {
                    if (tx1 == -1) tx1 = i, ty1 = j;
                    else if (tx2 == -1) tx2 = i, ty2 = j;
                    else if (tx3 == -1) tx3 = i, ty3 = j;
                }
            }
        memset(d, 0x3f, sizeof d);
        d[rx1][ry1][rx2][ry2][rx3][ry3] = 0;
        queue<st> q;
        q.push(st{rx1, ry1, rx2, ry2, rx3, ry3, 0});
        while (!q.empty()) {
            st nd = q.front(); q.pop();
            for (int k = 0; k < 4; k++) {
                int nx1 = nd.x1 + offset[k][0], ny1 = nd.y1 + offset[k][1];
                int nx2 = nd.x2 + offset[k][0], ny2 = nd.y2 + offset[k][1];
                int nx3 = nd.x3 + offset[k][0], ny3 = nd.y3 + offset[k][1];
                int f1 = 0, f2 = 0, f3 = 0;
                if (nx1 < 0 || nx1 >= n || ny1 < 0 || ny1 >= n || g[nx1][ny1] == '#') f1 = 1, nx1 = nd.x1, ny1 = nd.y1;
                if (nx2 < 0 || nx2 >= n || ny2 < 0 || ny2 >= n || g[nx2][ny2] == '#') f2 = 1, nx2 = nd.x2, ny2 = nd.y2;
                if (nx3 < 0 || nx3 >= n || ny3 < 0 || ny3 >= n || g[nx3][ny3] == '#') f3 = 1, nx3 = nd.x3, ny3 = nd.y3;
                if (!f1) {
                    if (f2 && nx1 == nx2 && ny1 == ny2) nx1 = nd.x1, ny1 = nd.y1;
                    if (f3 && nx1 == nx3 && ny1 == ny3) nx1 = nd.x1, ny1 = nd.y1;
                }
                if (!f2) {
                    if (f1 && nx2 == nx1 && ny2 == ny1) nx2 = nd.x2, ny2 = nd.y2;
                    if (f3 && nx2 == nx3 && ny2 == ny3) nx2 = nd.x2, ny2 = nd.y2;
                }
                if (!f3) {
                    if (f1 && nx3 == nx1 && ny3 == ny1) nx3 = nd.x3, ny3 = nd.y3;
                    if (f2 && nx3 == nx2 && ny3 == ny2) nx3 = nd.x3, ny3 = nd.y3;
                }
                if (d[nx1][ny1][nx2][ny2][nx3][ny3] > nd.t + 1) {
                    d[nx1][ny1][nx2][ny2][nx3][ny3] = nd.t + 1;
                    q.push(st{nx1, ny1, nx2, ny2, nx3, ny3, nd.t + 1});
                }
            }
        }
        int r1 = min(d[tx1][ty1][tx2][ty2][tx3][ty3], d[tx1][ty1][tx3][ty3][tx2][ty2]);
        int r2 = min(d[tx2][ty2][tx1][ty1][tx3][ty3], d[tx2][ty2][tx3][ty3][tx1][ty1]);
        int r3 = min(d[tx3][ty3][tx1][ty1][tx2][ty2], d[tx3][ty3][tx2][ty2][tx1][ty1]);
        int r = min(r1, min(r2, r3));
        if (r != 0x3f3f3f3f) cout << r << '\n';
        else cout << "trapped\n";
    }
    return 0;
}
