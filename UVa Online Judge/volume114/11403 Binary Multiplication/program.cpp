// Binary Multiplication
// UVa ID: 11403
// Verdict: Accepted
// Submission Date: 2023-04-25
// UVa Run Time: 0.070s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    string x, y;
    char g[100][100];
    int cases = 0;
    while (cin >> x >> y) {
        if (x == "0" && y == "0") break;
        if (cases++) cout << '\n';
        memset(g, 'x', sizeof g);
        int END = 90, xL = x.length(), yL = y.length();
        int row = 0, cln = END - xL - yL + 2;
        for (int i = 0, j = END - xL + 1; i < xL; i++, j++) g[0][j] = x[i];
        for (int i = 0, j = END - yL + 1; i < yL; i++, j++) g[1][j] = y[i];
        int L = max(xL, yL);
        for (int i = 0, j = END - L + 1; i < L; i++, j++) g[2][j] = '-';
        row += 3;
        for (int j = yL - 1, bias = 0; j >= 0; j--, bias++) {
            for (int i = 0; i < xL; i++)
                g[row][END - xL + 1 - bias + i] = (x[i] == '1' && y[j] == '1' ? '1' : '0');
            row++;
        }
        long long r1 = 0, r2 = 0;
        for (int i = 0; i < xL; i++) r1 = r1 * 2 + x[i] - '0';
        for (int j = 0; j < yL; j++) r2 = r2 * 2 + y[j] - '0';
        r1 *= r2;
        if (!r1) g[row + 1][END] = '0';
        else {
            for (int i = 0; r1; i++, r1 /= 2) {
                g[row + 1][END - i] = '0' + (r1 % 2);
                cln = min(cln, END - i);
            }
        }
        for (int i = cln; i <= END; i++) g[row][i] = '-';
        row++;
        for (int i = 0; i <= row; i++) {
            int flag = 0;
            for (int j = cln; j <= END; j++) {
                if (g[i][j] == 'x') {
                    if (flag) break;
                    else cout << ' ';
                } else {
                    cout << g[i][j];
                    flag = 1;
                }
            }
            cout << '\n';
        }
    }
    return 0;
}
