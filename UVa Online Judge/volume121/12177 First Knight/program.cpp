// First Knight
// UVa ID: 12177
// Verdict: Accepted
// Submission Date: 2026-07-26
// UVa Run Time: 0.350s
// https://blog.csdn.net/metaphysis/article/details/163217541

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(10);
    int m, n;
    while (cin >> m >> n) {
        if (m == 0 && n == 0) break;
        static double prob[4][40][40];
        for (int k = 0; k < 4; ++k)
            for (int i = 0; i < m; ++i)
                for (int j = 0; j < n; ++j)
                    cin >> prob[k][i][j];
        int total = m * n;
        int endIdx = total - 1;
        vector<int> idx(total, -1);
        int cur = 0;
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j)
                if (!(i == m - 1 && j == n - 1))
                    idx[i * n + j] = cur++;
        int M = cur; // 非终点状态数
        vector<vector<double>> A(M, vector<double>(M, 0.0));
        vector<double> b(M, 1.0); // 每个方程右侧为1
        int dirs[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j) {
                if (i == m - 1 && j == n - 1) continue;
                int row = idx[i * n + j];
                A[row][row] = 1.0;
                for (int k = 0; k < 4; ++k) {
                    double p = prob[k][i][j];
                    if (p == 0.0) continue;
                    int ni = i + dirs[k][0], nj = j + dirs[k][1];
                    if (ni < 0 || ni >= m || nj < 0 || nj >= n) continue;
                    if (ni == m - 1 && nj == n - 1) continue;
                    int col = idx[ni * n + nj];
                    A[row][col] -= p;
                }
            }
        if (M == 0) { // 起点即终点
            cout << 0.0 << "\n";
            continue;
        }
        int band = n + 1; // 最大列偏移不超过 n，多留一位安全
        // 高斯消元（带简单的行交换处理极小主元）
        for (int i = 0; i < M; ++i) {
            double pivot = A[i][i];
            if (fabs(pivot) < 1e-15) {
                int swapRow = -1;
                int maxR = min(M - 1, i + band);
                for (int r = i + 1; r <= maxR; ++r)
                    if (fabs(A[r][i]) > fabs(pivot)) {
                        swapRow = r;
                        pivot = A[r][i];
                        break;
                    }
                if (swapRow != -1) {
                    swap(A[i], A[swapRow]);
                    swap(b[i], b[swapRow]);
                }
            }
            pivot = A[i][i];
            if (fabs(pivot) < 1e-15) continue;
            int maxRow = min(M - 1, i + band);
            for (int k = i + 1; k <= maxRow; ++k) {
                double factor = A[k][i] / pivot;
                if (fabs(factor) < 1e-18) continue;
                int maxCol = min(M - 1, i + band);
                for (int j = i; j <= maxCol; ++j)
                    A[k][j] -= factor * A[i][j];
                b[k] -= factor * b[i];
            }
        }
        vector<double> x(M, 0.0);
        for (int i = M - 1; i >= 0; --i) {
            double sum = 0.0;
            int maxCol = min(M - 1, i + band);
            for (int j = i + 1; j <= maxCol; ++j)
                sum += A[i][j] * x[j];
            x[i] = (b[i] - sum) / A[i][i];
        }
        double ans = x[idx[0]]; // 起点 (1,1) 对应编号0
        cout << ans << "\n";
    }
    return 0;
}
