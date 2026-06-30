// Powerful Magic Squares
// UVa ID: 10538
// Verdict: Accepted
// Submission Date: 2026-06-29
// UVa Run Time: 0.070s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int S[26][1160][5][5], C[32];

void initialize() {
    int a[5] = {0, 1, 2, 3, 4};
    do {
        int b[5] = {0, 1, 2, 3, 4};
        do {
            int vip = 5 * a[0] + b[0] + 1;
            for (int r = 0; r < 5; ++r)
                for (int c = 0; c < 5; ++c) {
                    int v = 5 * a[(c + 2 * r) % 5] + b[(c - 2 * r + 10) % 5] + 1;
                    S[vip][C[vip]][r][c] = v;
                    S[vip][C[vip] + 1][c][r] = v;
                }
                C[vip] += 2;
        } while (next_permutation(b, b + 5));
    } while (next_permutation(a, a + 5));
}

int pms[5][5] = {
    { 1,  7, 13, 19, 25},
    {14, 20, 21,  2,  8},
    {22,  3,  9, 15, 16},
    {10, 11, 17, 23,  4},
    {18, 24,  5,  6, 12},
};

struct I { int v, r, c; } D[25];

int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    initialize();
    int n; cin >> n;
    for (int cs = 1; cs <= n; ++cs) {
        cout << "Case " << cs << ": ";
        int raw[5][5] = {0}, g[5][5] = {0}, seen[32] = {0};
        int error = 0;
        int dc = 0;
        int fr = -1, fc = -1;
        for (int r = 0; r < 5; r++)
            for (int c = 0; c < 5; c++) {
                string s; cin >> s;
                if (s != "--") {
                    int v = stoi(s);
                    if (v < 1 || v > 25) error = 1;
                    if (seen[v]) error = 1;
                    else seen[v] = 1;
                    if (fr == -1 && fc == -1) fr = r, fc = c;
                    raw[r][c] = g[r][c] = v;
                    D[dc++] = {v, r, c};
                }
            }
        if (error) { cout << "0\n"; continue; }
        if (dc == 0) { cout << 28800 << '\n'; continue; }
        if (dc == 1) { cout << 1152 << '\n'; continue; }
        if (!raw[0][0]) {
            dc = 0;
            for (int r = 0; r < 5; r++)
                for (int c = 0; c < 5; c++) {
                    g[r][c] = raw[(r + fr) % 5][(c + fc) % 5];
                    if (g[r][c]) D[dc++] = {g[r][c], r, c};
                }
        }
        int vip = g[0][0], answer = 0;
        for (int i = 0; i < C[vip]; i++) {
            int matched = 1;
            for (int j = 0; j < dc && matched; j++)
                if (D[j].v != S[vip][i][D[j].r][D[j].c])
                    matched = 0;
            answer += matched;
        }
        cout << answer << '\n';
    }
    return 0;
}
