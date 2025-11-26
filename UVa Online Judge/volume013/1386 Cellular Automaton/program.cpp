// Cellular Automaton
// UVa ID: 1386
// Verdict: Accepted
// Submission Date: 2025-11-26
// UVa Run Time: 0.450s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net


#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int n, m, d, k;
vector<ll> initial;

// 循环矩阵乘法：计算两个循环矩阵的乘积
vector<ll> multiply(const vector<ll>& a, const vector<ll>& b) {
    vector<ll> res(n, 0);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            res[(i + j) % n] = (res[(i + j) % n] + a[i] * b[j]) % m;
    return res;
}

// 矩阵快速幂：计算循环矩阵的k次幂
vector<ll> matrixPower(vector<ll> base, int exp) {
    vector<ll> res(n, 0);
    res[0] = 1; // 单位矩阵的第一行
    while (exp > 0) {
        if (exp & 1) res = multiply(res, base);
        base = multiply(base, base);
        exp >>= 1;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    while (cin >> n >> m >> d >> k) {
        initial.resize(n);
        for (int i = 0; i < n; i++) cin >> initial[i];

        // 构造转移矩阵的第一行
        vector<ll> mat(n, 0);
        for (int i = 0; i < n; i++) {
            int dist = min(i, n - i); // 环形距离
            if (dist <= d) mat[i] = 1;
        }

        // 计算M^k的第一行
        vector<ll> matk = matrixPower(mat, k);

        // 计算最终状态：初始状态与M^k的卷积
        vector<ll> result(n, 0);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                result[i] = (result[i] + initial[j] * matk[(i - j + n) % n]) % m;

        // 输出结果
        for (int i = 0; i < n; i++) {
            if (i > 0) cout << " ";
            cout << result[i];
        }
        cout << "\n";
    }

    return 0;
}
