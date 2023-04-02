// Incomplete Chessboard
// UVa ID: 12826
// Verdict: Accepted
// Submission Date: 2023-04-02
// UVa Run Time: 0.030s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int cases = 1;
    int dd[10][10], r1, c1, r2, c2, r3, c3;
    int offset[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}};
    while (cin >> r1 >> c1 >> r2 >> c2 >> r3 >> c3) {
        cout << "Case " << cases++ << ": ";
        for (int i = 1; i <= 8; i++)
            for (int j = 1; j <= 8; j++)
                dd[i][j] = 0x3f3f3f3f;
        queue<int> R, C, D;
        dd[r1][c1] = 0;
        R.push(r1); C.push(c1); D.push(0);
        while (!R.empty()) {
            int r = R.front(), c = C.front(), d = D.front();
            R.pop(); C.pop(); D.pop();
            for (int i = 0; i < 8; i++) {
                int nr = r + offset[i][0], nc = c + offset[i][1];
                if (nr < 1 || nr > 8 || nc < 1 || nc > 8) continue;
                if (nr == r3 && nc == c3) continue;
                if (dd[nr][nc] > d + 1) {
                    dd[nr][nc] = d + 1;
                    R.push(nr); C.push(nc); D.push(d + 1);
                }
            }
        }
        cout << dd[r2][c2] << '\n';
    }
    return 0;
}
