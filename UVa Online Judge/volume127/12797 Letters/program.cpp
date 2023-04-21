// Letters
// UVa ID: 12797
// Verdict: Accepted
// Submission Date: 2023-04-22
// UVa Run Time: 0.040s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int n, mask, d[110][110], best;
int offset[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
char g[110][110];

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    while (cin >> n) {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                cin >> g[i][j];
        best = 0x3f3f3f3f;
        for (mask = 0; mask < 1024; mask++) {
            if ('a' <= g[0][0] && g[0][0] <= 'j' && mask & (1 << g[0][0] - 'a')) continue;
            if ('A' <= g[0][0] && g[0][0] <= 'J' && ~mask & (1 << g[0][0] - 'A')) continue;
            memset(d, 0x3f, sizeof d);
            queue<tuple<int, int, int>> q;
            d[0][0] = 1;
            q.push(make_tuple(0, 0, 1));
            while (!q.empty()) {
                tuple<int, int, int> t = q.front(); q.pop();
                int x = get<0>(t), y = get<1>(t), c = get<2>(t);
                for (int k = 0; k < 4; k++) {
                    int nx = x + offset[k][0], ny = y + offset[k][1];
                    if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
                    if ('a' <= g[nx][ny] && g[nx][ny] <= 'j' && mask & (1 << g[nx][ny] - 'a')) continue;
                    if ('A' <= g[nx][ny] && g[nx][ny] <= 'J' && ~mask & (1 << g[nx][ny] - 'A')) continue;
                    if (d[nx][ny] > c + 1) {
                        d[nx][ny] = c + 1;
                        q.push(make_tuple(nx, ny, c + 1));
                    }
                }
            }
            best = min(best, d[n - 1][n - 1]);
        }
        if (best == 0x3f3f3f3f) best = -1;
        cout << best << '\n';
    }
    return 0;
}
