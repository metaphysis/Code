// Chocolate
// UVa ID: 1305
// Verdict: Accepted
// Submission Date: 2026-07-31
// UVa Run Time: 0.110s

#include <bits/stdc++.h>
using namespace std;

typedef vector<vector<double>> Matrix;

// 矩阵乘法
Matrix matrixMultiply(const Matrix& a, const Matrix& b) {
    int n = (int)a.size();
    Matrix c(n, vector<double>(n, 0.0));
    for (int i = 0; i < n; ++i)
        for (int k = 0; k < n; ++k) {
            if (a[i][k] == 0.0) continue;
            double aik = a[i][k];
            for (int j = 0; j < n; ++j)
                c[i][j] += aik * b[k][j];
        }
    return c;
}

// 矩阵快速幂
Matrix matrixPower(Matrix base, int exponent) {
    int n = (int)base.size();
    Matrix result(n, vector<double>(n, 0.0));
    for (int i = 0; i < n; ++i) result[i][i] = 1.0;
    while (exponent > 0) {
        if (exponent & 1) result = matrixMultiply(result, base);
        base = matrixMultiply(base, base);
        exponent >>= 1;
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int C, N, M;
    while (cin >> C) {
        if (C == 0) break;
        cin >> N >> M;
        if (M > C) {
            cout << fixed << setprecision(3) << 0.0 << "\n";
            continue;
        }
        int n = C + 1;
        Matrix trans(n, vector<double>(n, 0.0));
        for (int i = 0; i < n; ++i) {
            if (i > 0) trans[i][i - 1] = (double)i / C;          // 取到已有的颜色
            if (i < C) trans[i][i + 1] = (double)(C - i) / C;    // 取到新的颜色
        }
        Matrix powered = matrixPower(trans, N);
        double answer = powered[0][M];  // 从状态 0 出发
        cout << fixed << setprecision(3) << answer << "\n";
    }
    return 0;
}
