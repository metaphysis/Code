// Power of Matrix
// UVa ID: 11149
// Verdict: Accepted
// Submission Date: 2025-10-19
// UVa Run Time: 0.010s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
using namespace std;

typedef vector<vector<int>> Matrix;
int n;

// 矩阵乘法，结果对10取模
Matrix multiply(const Matrix &a, const Matrix &b) {
    Matrix res(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                res[i][j] = (res[i][j] + a[i][k] * b[k][j]) % 10;
            }
        }
    }
    return res;
}

// 矩阵加法，结果对10取模
Matrix add(const Matrix &a, const Matrix &b) {
    Matrix res(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            res[i][j] = (a[i][j] + b[i][j]) % 10;
        }
    }
    return res;
}

// 分治求解：返回 {B(k), F(k)}，其中B(k)=A^k, F(k)=A+A^2+...+A^k
pair<Matrix, Matrix> solve(const Matrix &A, int k) {
    // 基本情况：k=1
    if (k == 1) {
        return {A, A};
    }
    
    if (k % 2 == 0) {
        // 偶数情况：k = 2m
        auto [Bm, Fm] = solve(A, k / 2);  // 递归求解子问题
        Matrix Bk = multiply(Bm, Bm);     // B(k) = B(m) * B(m)
        Matrix Fk = add(Fm, multiply(Bm, Fm));  // F(k) = F(m) + B(m) * F(m)
        return {Bk, Fk};
    } else {
        // 奇数情况：k = 2m + 1
        auto [Bm, Fm] = solve(A, k / 2);  // 递归求解子问题
        Matrix Bk = multiply(multiply(Bm, Bm), A);  // B(k) = B(m) * B(m) * A
        Matrix Fk = add(add(Fm, multiply(Bm, Fm)), Bk);  // F(k) = F(m) + B(m) * F(m) + B(k)
        return {Bk, Fk};
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    while (true) {
        int k;
        cin >> n >> k;
        if (n == 0) break;
        
        Matrix A(n, vector<int>(n));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> A[i][j];
                A[i][j] %= 10;  // 输入时直接取模
            }
        }
        
        // 调用分治算法求解
        auto [_, res] = solve(A, k);
        
        // 输出结果
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << res[i][j];
                if (j < n - 1) cout << " ";
            }
            cout << "\n";
        }
        cout << "\n";
    }
    
    return 0;
}
