// A General Recurrence Relation
// UVa ID: 1177
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Matrix {
    double m[2][2];
};

// 矩阵乘法
Matrix mul(const Matrix& x, const Matrix& y) {
    Matrix res;
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j) {
            res.m[i][j] = 0.0;
            for (int k = 0; k < 2; ++k)
                res.m[i][j] += x.m[i][k] * y.m[k][j];
        }
    return res;
}

// 矩阵快速幂
Matrix mpow(Matrix base, long long exp) {
    Matrix res;
    res.m[0][0] = res.m[1][1] = 1.0;
    res.m[0][1] = res.m[1][0] = 0.0;
    while (exp > 0) {
        if (exp & 1) res = mul(res, base);
        base = mul(base, base);
        exp >>= 1;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;
    while (N--) {
        long long f0, f1, n;
        double a, b;
        cin >> f0 >> f1 >> a >> b >> n;
        if (n == 0) {
            cout << f0 << '\n';
            continue;
        }
        Matrix M;
        M.m[0][0] = a; M.m[0][1] = b;
        M.m[1][0] = 1.0; M.m[1][1] = 0.0;
        Matrix P = mpow(M, n - 1);
        double fn = P.m[0][0] * f1 + P.m[0][1] * f0;
        long long ans = llround(fn);
        cout << ans << '\n';
    }
    return 0;
}
