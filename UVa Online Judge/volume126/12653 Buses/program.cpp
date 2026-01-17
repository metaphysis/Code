// Buses
// UVa ID: 12653
// Verdict: Accepted
// Submission Date: 2026-01-10
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll MOD = 1000000; // 我们只关心最后6位，因此取模 10^6

// 矩阵乘法，返回 a*b，结果对 MOD 取模
vector<vector<ll>> matMul(const vector<vector<ll>> &a, const vector<vector<ll>> &b) {
    int n = a.size();
    vector<vector<ll>> res(n, vector<ll>(n, 0));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            for (int k = 0; k < n; ++k)
                res[i][j] = (res[i][j] + a[i][k] * b[k][j]) % MOD;
    return res;
}

// 矩阵快速幂，返回 mat^p
vector<vector<ll>> matPow(vector<vector<ll>> mat, ll p) {
    int n = mat.size();
    vector<vector<ll>> res(n, vector<ll>(n, 0));
    for (int i = 0; i < n; ++i) res[i][i] = 1; // 单位矩阵
    while (p) {
        if (p & 1) res = matMul(res, mat);
        mat = matMul(mat, mat);
        p >>= 1;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, k, l;
    while (cin >> n >> k >> l) {
        n /= 5; // 将长度单位转换为“5米块”，这样 minibus 长度为1，bus 长度为2

        // dp[n] = l*dp[n-2] + k*dp[n-1]
        // 构造转移矩阵
        vector<vector<ll>> trans = {
            {0, l % MOD},
            {1, k % MOD}
        };

        // 初始状态：dp[0] = 1, dp[1] = k
        // 我们要求 dp[n]
        if (n == 1) {
            // 只有 minibus 一种情况
            ll ans = k % MOD;
            printf("%06lld\n", ans);
            continue;
        }

        // 计算 trans^(n-1)
        auto powMat = matPow(trans, n - 1);
        // 初始向量 [dp[0], dp[1]] = [1, k]
        ll dp0 = 1;
        ll dp1 = k % MOD;
        // dp[n] = powMat[0][1]*dp[0] + powMat[1][1]*dp[1]   （实际上我们只需要第二列）
        ll ans = (powMat[0][1] * dp0 + powMat[1][1] * dp1) % MOD;
        printf("%06lld\n", ans);
    }

    return 0;
}
