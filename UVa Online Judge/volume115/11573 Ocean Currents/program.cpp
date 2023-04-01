// Ocean Currents
// UVa ID: 11573
// Verdict: Accepted
// Submission Date: 2023-04-01
// UVa Run Time: 0.640s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1010, INF = 0x3f3f3f3f;

int r, c, n, g[MAXN][MAXN];
int rs, cs, rd, cd;
int d[MAXN][MAXN];
int offset[8][2] = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};

struct block {
    int rr, cc, dd;
    bool operator<(const block &b) const { return dd > b.dd; }
};

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    while (cin >> r >> c) {
        char cc;
        for (int i = 0; i < r; i++)
            for (int j = 0; j < c; j++) {
                cin >> cc;
                g[i][j] = cc - '0';
            }
        cin >> n;
        while (n--) {
            cin >> rs >> cs >> rd >> cd;
            rs--, cs--, rd--, cd--;
            for (int i = 0; i < r; i++)
                for (int j = 0; j < c; j++)
                    d[i][j] = INF;
            priority_queue<block> q;
            d[rs][cs] = 0;
            q.push(block{rs, cs, 0});
            while (!q.empty()) {
                block b = q.top(); q.pop();
                if (b.rr == rd && b.cc == cd) break;
                for (int i = 0; i < 8; i++) {
                    int nr = b.rr + offset[i][0], nc = b.cc + offset[i][1];
                    if (nr < 0 || nr >= r || nc < 0 || nc >= c) continue;
                    if (d[nr][nc] > b.dd + (g[b.rr][b.cc] != i)) {
                        d[nr][nc] = b.dd + (g[b.rr][b.cc] != i);
                        q.push(block{nr, nc, d[nr][nc]});
                    }
                }
            }
            cout << d[rd][cd] << '\n';
        }
    }
    return 0;
}
