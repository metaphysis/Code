// Colorful Eggs
// UVa ID: 12042
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.080s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net


#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll MOD = 1000000007LL;
typedef vector<vector<ll>> Matrix;

// 矩阵乘法
Matrix matMul(const Matrix& A, const Matrix& B) {
    int n = (int)A.size();
    Matrix C(n, vector<ll>(n, 0));
    for (int i = 0; i < n; ++i)
        for (int k = 0; k < n; ++k) {
            if (A[i][k] == 0) continue;
            for (int j = 0; j < n; ++j)
                C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
        }
    return C;
}

// 矩阵快速幂
Matrix matPow(Matrix base, ll exp) {
    int n = (int)base.size();
    Matrix res(n, vector<ll>(n, 0));
    for (int i = 0; i < n; ++i) res[i][i] = 1;
    while (exp > 0) {
        if (exp & 1) res = matMul(res, base);
        base = matMul(base, base);
        exp >>= 1;
    }
    return res;
}

// 矩阵乘向量
vector<ll> matVecMul(const Matrix& A, const vector<ll>& v) {
    int n = (int)A.size();
    vector<ll> res(n, 0);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            res[i] = (res[i] + A[i][j] * v[j]) % MOD;
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n;
        ll d;
        cin >> n >> d;
        vector<ll> init(n);
        for (int i = 0; i < n; ++i) cin >> init[i];
        // 构造转移矩阵 M
        Matrix M(n, vector<ll>(n, 0));
        for (int i = 0; i < n; ++i) {
            if (i == 0) { // 第一行：a_2 到 a_n 为 1
                for (int j = 1; j < n; ++j) M[i][j] = 1;
            } else { // 第 i+1 行：a_1 到 a_{i+1} 为 1
                for (int j = 0; j <= i; ++j) M[i][j] = 1;
            }
        }
        ll exp = d - 1; // 实际变换次数
        Matrix P = matPow(M, exp);
        vector<ll> ans = matVecMul(P, init);
        for (int i = 0; i < n; ++i) {
            if (i) cout << ' ';
            cout << ans[i];
        }
        cout << '\n';
    }
    return 0;
}
