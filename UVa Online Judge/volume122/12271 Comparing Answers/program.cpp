// Comparing Answers
// UVa ID: 12271
// Verdict: Accepted
// Submission Date: 2026-06-21
// UVa Run Time: 0.950s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    while (cin >> n && n) {
        vector<int> matrixA(n * n), matrixB(n * n), matrixC(n * n, 0);

        // 读入邻接矩阵
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                cin >> matrixA[i * n + j];

        // 读入朋友答案
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                cin >> matrixB[i * n + j];

        // 计算矩阵乘法 C = A * A
        for (int i = 0; i < n; ++i) {
            int rowI = i * n;
            for (int k = 0; k < n; ++k) {
                int aik = matrixA[rowI + k];
                if (aik == 0) continue;          // 跳过零值
                int rowK = k * n;
                for (int j = 0; j < n; ++j)
                    matrixC[rowI + j] += aik * matrixA[rowK + j];
            }
        }

        // 比较答案
        bool ok = true;
        for (int i = 0; i < n && ok; ++i)
            for (int j = 0; j < n; ++j)
                if (matrixC[i * n + j] != matrixB[i * n + j]) {
                    ok = false;
                    break;
                }

        cout << (ok ? "YES" : "NO") << '\n';
    }

    return 0;
}
