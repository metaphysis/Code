// Keyboarding
// UVa ID: 1714
// Verdict: Accepted
// Submission Date: 2023-06-10
// UVa Run Time: 2.720s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct block { int x, y, c, idx; };

int r, c;
string text;
char g[64][64];
int used[64][64];
pair<int, int> nxt[64][64][4];
int offset[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    while (cin >> r >> c) {
        for (int i = 0; i < r; i++)
            for (int j = 0; j < c; j++)
                cin >> g[i][j];
        cin >> text;
        text += '*';
        for (int i = 0; i < r; i++)
            for (int j = 0; j < c; j++) {
                for (int k = 0; k < 4; k++) {
                    int ni = i, nj = j;
                    while (true) {
                        if (ni < 0 || ni >= r || nj < 0 || nj >= c) break;
                        if (g[ni][nj] != g[i][j]) break;
                        ni += offset[k][0], nj += offset[k][1];
                    }
                    if (ni < 0 || ni >= r || nj < 0 || nj >= c) nxt[i][j][k] = make_pair(-1, -1);
                    else nxt[i][j][k] = make_pair(ni, nj);
                }
            }
        queue<block> q;
        q.push(block{0, 0, 0, 0});
        memset(used, -1, sizeof used);
        while (!q.empty()) {
            block blk = q.front(); q.pop();
            if (g[blk.x][blk.y] == text[blk.idx]) {
                if (blk.idx + 1 == text.length()) {
                    cout << blk.c + 1 << '\n';
                    break;
                }
                blk.c += 1, blk.idx += 1;
                used[blk.x][blk.y] = blk.idx;
                q.push(blk);
            } else {
                for (int k = 0, nx, ny; k < 4; k++) {
                    nx = nxt[blk.x][blk.y][k].first, ny = nxt[blk.x][blk.y][k].second;
                    if (nx == -1) continue;
                    if (used[nx][ny] >= blk.idx) continue;
                    used[nx][ny] = blk.idx;
                    q.push(block{nx, ny, blk.c + 1, blk.idx});
                }
            }
        }
    }
    return 0;
}
