// Fun with Strings
// UVa ID: 12045
// Verdict: Accepted
// Submission Date: 2026-04-20
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1000000007;

// 2x2 矩阵乘法
void matMul(ll a[2][2], ll b[2][2], ll res[2][2]) {
    ll tmp[2][2] = {{0, 0}, {0, 0}};
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j)
            for (int k = 0; k < 2; ++k)
                tmp[i][j] = (tmp[i][j] + a[i][k] * b[k][j]) % MOD;
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j)
            res[i][j] = tmp[i][j];
}

// 矩阵快速幂
void matPow(ll base[2][2], ll exp, ll res[2][2]) {
    ll ans[2][2] = {{1, 0}, {0, 1}};
    ll cur[2][2];
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j)
            cur[i][j] = base[i][j];
    while (exp > 0) {
        if (exp & 1) matMul(ans, cur, ans);
        matMul(cur, cur, cur);
        exp >>= 1;
    }
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j)
            res[i][j] = ans[i][j];
}

// 快速计算第 n 个斐波那契数模 MOD (F1=1, F2=1)
ll fibMod(ll n) {
    if (n <= 0) return 0;
    if (n == 1 || n == 2) return 1;
    ll base[2][2] = {{1, 1}, {1, 0}};
    ll res[2][2];
    matPow(base, n - 2, res);
    return (res[0][0] + res[0][1]) % MOD;
}

// 精确计算第 n 个斐波那契数 (n ≤ 45 时使用)
ll fibExact(ll n) {
    if (n <= 0) return 0;
    if (n == 1 || n == 2) return 1;
    ll a = 1, b = 1, c;
    for (ll i = 3; i <= n; ++i) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    while (T--) {
        ll N, X, M, Y, K;
        cin >> N >> X >> M >> Y >> K;
        
        if (N > M) { swap(N, M); swap(X, Y); }
        
        // 长度增长极快，M 过大则不可能
        if (M > 45) { cout << "Impossible\n"; continue; }
        
        // 获取斐波那契系数 Ln = Fn-2 * L1 + Fn-1 * L2
        auto getF = [&](ll n, ll& f1, ll& f2) {
            if (n == 1) { f1 = 1; f2 = 0; }
            else if (n == 2) { f1 = 0; f2 = 1; }
            else { f1 = fibExact(n - 2); f2 = fibExact(n - 1); }
        };
        
        ll FN2, FN1, FM2, FM1;
        getF(N, FN2, FN1);
        getF(M, FM2, FM1);
        
        ll delta = FN2 * FM1 - FN1 * FM2;
        if (delta == 0) { cout << "Impossible\n"; continue; }
        
        ll numL1 = X * FM1 - Y * FN1;
        ll numL2 = Y * FN2 - X * FM2;
        
        if (numL1 % delta != 0 || numL2 % delta != 0) { cout << "Impossible\n"; continue; }
        
        ll L1 = numL1 / delta;
        ll L2 = numL2 / delta;
        
        // 检查正整数及变换约束：a = 2L1 - L2 >= 0, b = L2 - L1 >= 0
        if (L1 <= 0 || L2 <= 0 || L2 < L1 || L2 > 2 * L1) { cout << "Impossible\n"; continue; }
        
        // 验证原始方程
        if (FN2 * L1 + FN1 * L2 != X || FM2 * L1 + FM1 * L2 != Y) { cout << "Impossible\n"; continue; }
        
        // 计算 L_K
        ll FK2, FK1;
        if (K == 1) { FK2 = 1; FK1 = 0; }
        else if (K == 2) { FK2 = 0; FK1 = 1; }
        else { FK2 = fibMod(K - 2); FK1 = fibMod(K - 1); }
        
        ll ans = (FK2 * (L1 % MOD) + FK1 * (L2 % MOD)) % MOD;
        cout << ans << "\n";
    }
    return 0;
}
