// Numerical Methods A Satire
// UVa ID: 11011
// Verdict: Accepted
// Submission Date: 2025-12-26
// UVa Run Time: 0.020s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

char g[13][40][30010];

void initialize() {
    string line[5] = {
        "f(x..)-f(x..)",
        "...00.....01.",
        "_____________",
        "...x..-x.....",
        "....00..01..."
    };
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 13; j++)
            g[1][i][j] = line[i][j];
    int height = 5, width = 13;
    for (int i = 2; i <= 12; i++) {
        for (int x = 0; x < height; x++) {
            for (int y = 0; y < width; y++)
                g[i][x][y] = g[i - 1][x][y];
            g[i][x][width] = '.';
        }
        g[i][height - 3][width] = '-';
        for (int x = 0; x < height; x++)
            for (int y = 0; y < width; y++) {
                char c1 = g[i - 1][x][y];
                if (!isdigit(c1)) g[i][x][y + width + 1] = c1;
                else {
                    char c2 = g[i - 1][x][y + 1];
                    int n = (c1 - '0') * 10 + (c2 - '0');
                    n += 1;
                    string s = to_string(n);
                    if (n < 10) s = '0' + s;
                    g[i][x][y + width + 1] = s[0];
                    g[i][x][y + width + 2] = s[1];
                    y++;
                }
            }
        for (int y = 0; y < 2 * width + 1; y++) {
            g[i][height][y] = '_';
            g[i][height + 1][y] = g[i][height + 2][y] = '.';
        }
        g[i][height + 1][width] = '-';
        g[i][height + 1][width + 1] = g[i][height + 1][width - 3] = 'x';
        g[i][height + 2][width - 1] = g[i][height + 2][width - 2] = '0';
        string s = to_string(i);
        if (i < 10) s = '0' + s;
        g[i][height + 2][width + 2] = s[0];
        g[i][height + 2][width + 3] = s[1];
        height += 3;
        width = 2 * width + 1;
    }
}

int main() {
    initialize();
    int d[13][2];
    d[1][0] = 5, d[1][1] = 13;
    for (int i = 2; i <= 12; i++) {
        d[i][0] = d[i - 1][0] + 3;
        d[i][1] = 2 * d[i - 1][1] + 1;
    }
    int n, caseNum = 1;
    while (cin >> n && n) {
        cout << "Case " << caseNum << ":\n";
        for (int x = 0; x < d[n][0]; x++) {
            for (int y = 0; y < d[n][1]; y++) cout << g[n][x][y];
            cout << '\n';
        }
        cout << '\n';
        caseNum++;
    }
    return 0;
}
