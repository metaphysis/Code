// Mystical Matrix
// UVa ID: 10775
// Verdict: Accepted
// Submission Date: 2026-05-24
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 固定的 3x3 幻方模板
const int A[3][3] = {{8, 1, 6}, {3, 5, 7}, {4, 9, 2}};
int G[3][350];  // 平移基数矩阵，n <= 333 时够用

int main() {
    int n;
    while (cin >> n && n) {
        n /= 3;                     // N = 3n
        if (n % 2 == 0) {           // n 必须是奇数
            cout << "IMPOSSIBLE" << '\n';
            continue;
        }
        // 构造 G 矩阵
        for (int i = 0; i < n; ++i) G[0][i] = i;
        G[1][0] = n / 2, G[2][0] = n - 1;
        for (int i = 1; i < n; ++i) {
            G[1][i] = G[2][i - 1];
            G[2][i] = (n / 2 * 3) - G[0][i] - G[1][i];
        }
        // 输出最终矩阵
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < n; ++j) {
                for (int k = 0; k < 3; ++k) {
                    if (j + k) cout << ' ';
                    cout << A[i][k] + 9 * G[i][j];
                }
            }
            cout << '\n';
        }
    }
    return 0;
}
