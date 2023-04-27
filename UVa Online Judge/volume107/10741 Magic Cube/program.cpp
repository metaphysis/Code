// Magic Cube
// UVa ID: 10741
// Verdict: Accepted
// Submission Date: 2023-04-27
// UVa Run Time: 0.000s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;
int cube[32][32][32];
int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int n, cases = 0;
    while (cin >> n, n) {
        if (cases++) cout << '\n';
        memset(cube, 0, sizeof cube);
        int level = n - 1, row = n / 2, cln = n / 2;
        for (int i = 1; i <= n * n * n; i++) {
            cube[level][row][cln] = i;
            if (cube[(level + 1) % n][row][(cln + 1) % n]) {
                if (cube[(level + 1) % n][(row - 1 + n) % n][cln]) {
                    level = (level - 1 + n) % n;
                } else {
                    level = (level + 1) % n;
                    row = (row - 1 + n) % n;
                }
            } else {
                level = (level + 1) % n;
                cln = (cln + 1) % n;
            }
        }
        for (int i = 0; i < n; i++) {
            if (i) cout << '\n';
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {
                    if (k) cout << ' ';
                    cout << setw(5) << setfill(' ') << cube[i][j][k];
                }
                cout << '\n';
            }
        }
    }
    return 0;
}
