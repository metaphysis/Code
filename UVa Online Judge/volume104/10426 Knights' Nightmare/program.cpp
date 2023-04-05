// Knights' Nightmare
// UVa ID: 10426
// Verdict: Accepted
// Submission Date: 2023-04-05
// UVa Run Time: 0.110s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 20, INF = 1 << 20;

int d[MAXN][MAXN][4][2];
int offset[8][2] = {{-2, 1}, {-2, -1}, {-1, -2}, {1, -2}, {2, -1}, {2, 1}, {1, 2}, {-1, 2}};
pair<int, int> kings[4], monster;

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    string cases;
    int R, C;
    while (cin >> cases) {
        cout << cases << '\n';
        cin >> R >> C;
        for (int i = 0; i < 4; i++) cin >> kings[i].first >> kings[i].second;
        cin >> monster.first >> monster.second;
        for (int i = 1; i <= R; i++)
            for (int j = 1; j <= C; j++)
                for (int k = 0; k < 4; k++)
                    d[i][j][k][0] = d[i][j][k][1] = INF;
        for (int i = 0; i < 4; i++)
            for (int in = 0; in <= 1; in++) {
                d[kings[i].first][kings[i].second][i][in] = 0;
                queue<pair<int, int>> q;
                q.push(kings[i]);
                while (!q.empty()) {
                    pair<int, int> pr = q.front(); q.pop();
                    for (int j = 0; j < 8; j++) {
                        int nr = pr.first + offset[j][0], nc = pr.second + offset[j][1];
                        if (nr < 1 || nr > R || nc < 1 || nc > C) continue;
                        if (!in && nr == monster.first && nc == monster.second) continue;
                        if (d[nr][nc][i][in] > d[pr.first][pr.second][i][in] + 1) {
                            d[nr][nc][i][in] = d[pr.first][pr.second][i][in] + 1;
                            q.push(make_pair(nr, nc));
                        }
                    }
                }
            }
        int r = INF;
        for (int i = 1; i <= R; i++)
            for (int j = 1; j <= C; j++)
                for (int x = 0; x < 4; x++) {
                    int rr = 0;
                    for (int k = 0; k < 4; k++) rr += d[i][j][k][k == x];
                    r = min(r, rr);
                }
        if (r != INF) cout << "Minimum time required is " << r << " minutes.\n";
        else cout << "Meeting is impossible.\n";
    }
    return 0;
}
