#include <bits/stdc++.h>
using namespace std;

long long MOD = 100000007;

struct matrix {
    long long cell[2][2];
    matrix(long long a = 0, long long b = 0, long long c = 0, long long d = 0) {
        cell[0][0] = a, cell[0][1] = b, cell[1][0] = c, cell[1][1] = d;
    }
} M_BASE(1, 1, 1, 0), M_UNIT(1, 0, 0, 1);

matrix multiply(const matrix &a, const matrix &b) {
    matrix r;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            for (int k = 0; k < 2; k++) {
                r.cell[i][j] += a.cell[i][k] * b.cell[k][j] % MOD;
                r.cell[i][j] %= MOD;
            }
    return r;
}

matrix matrixPow1(long long k) {
    matrix r = M_UNIT;
    matrix cm = M_BASE;
    while (k) {
        if (k & 1) r = multiply(r, cm);
        cm = multiply(cm, cm);
        k >>= 1;
    }
    return r;
}

matrix matrixPow2(long long k) {
    if (k == 0) return M_UNIT;
    if (k == 1) return M_BASE;
    matrix r = matrixPow2(k >> 1);
    r = multiply(r, r);
    if (k & 1) r = multiply(r, M_BASE);
    return r;
}

// 判断两个矩阵是否完全相同
bool sameMatrix(const matrix &a, const matrix &b) {
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            if (a.cell[i][j] != b.cell[i][j]) return false;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // ============ 测试 1：迭代版与朴素递推对拍 (n = 0..99) ============
    {
        const int N = 100;
        vector<long long> fib(N);
        fib[0] = 0 % MOD;
        fib[1] = 1 % MOD;
        for (int i = 2; i < N; i++)
            fib[i] = (fib[i - 1] + fib[i - 2]) % MOD;

        bool ok = true;
        for (int n = 0; n < N; n++) {
            long long got = matrixPow1(n).cell[0][1];   // M^n 的右上角即 F(n)
            if (got != fib[n]) {
                ok = false;
                cout << "  [FAIL] n=" << n << " 得到 " << got
                     << "，期望 " << fib[n] << "\n";
            }
        }
        cout << "测试1 (迭代版 vs 朴素递推, n=0.." << N - 1 << ") : "
             << (ok ? "全部通过" : "存在错误") << "\n";
    }

    // ============ 测试 2：迭代版与递归版互相对拍 ============
    {
        bool ok = true;
        for (long long k = 0; k <= 100; k++)
            if (!sameMatrix(matrixPow1(k), matrixPow2(k))) ok = false;

        // 再挑几个大数测一测
        vector<long long> bigs = {1000, 10000, 100000, 1000000,
                                  1000000000LL, 1000000000000000000LL};
        for (long long k : bigs)
            if (!sameMatrix(matrixPow1(k), matrixPow2(k))) ok = false;

        cout << "测试2 (迭代版 vs 递归版, 含 k 到 10^18) : "
             << (ok ? "全部通过" : "存在错误") << "\n";
    }

    // ============ 测试 3：交互式输入 T 组 n，输出 F(n) mod MOD ============
    cout << "\n请输入 T，再输入 T 个 n :\n";
    int T;
    if (!(cin >> T)) return 0;

    while (T--) {
        long long n;
        cin >> n;

        matrix r1 = matrixPow1(n);   // 迭代版
        matrix r2 = matrixPow2(n);   // 递归版

        cout << "F(" << n << ") mod " << MOD << " = " << r1.cell[0][1]
             << (sameMatrix(r1, r2) ? "" : "   [WARN: 两法不一致]") << "\n";
    }
    return 0;
}
