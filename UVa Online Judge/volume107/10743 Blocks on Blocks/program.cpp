// Blocks on Blocks
// UVa ID: 10743
// Verdict: Accepted
// Submission Date: 2026-01-15
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net


#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MOD = 10000;  // 只需要最后4位

// 矩阵乘法 (3x3) 模 MOD
void mul(int a[3][3], int b[3][3], int r[3][3]) {
    ll t[3][3] = {0};
    for (int i = 0; i < 3; ++i)
    for (int j = 0; j < 3; ++j)
    for (int k = 0; k < 3; ++k)
        t[i][j] += (ll)a[i][k] * b[k][j];
    for (int i = 0; i < 3; ++i)
    for (int j = 0; j < 3; ++j)
        r[i][j] = ((t[i][j] % MOD) + MOD) % MOD;  // 处理负数
}

// 矩阵快速幂
void powM(int m[3][3], ll n, int r[3][3]) {
    int b[3][3], t[3][3];
    memcpy(b, m, sizeof(b));  // 复制矩阵
    // 初始化结果矩阵为单位矩阵
    for (int i = 0; i < 3; ++i)
    for (int j = 0; j < 3; ++j)
        r[i][j] = (i == j);
    while (n) {
        if (n & 1) memcpy(t, r, sizeof(t)), mul(t, b, r);  // r = r * b
        memcpy(t, b, sizeof(t)), mul(t, t, b);  // b = b * b
        n >>= 1;
    }
}

int main() {
    ios::sync_with_stdio(false), cin.tie(0);
    int t, cs = 0; cin >> t;
    // 转移矩阵
    int M[3][3] = {{5, -7, 4}, {1, 0, 0}, {0, 1, 0}};
    // 前3项的初始值
    int base[4] = {0, 1, 2, 6};
    
    while (t--) {
        ll n; cin >> n;
        cout << "Case " << ++cs << ": ";
        
        // 处理前4项
        if (n <= 3) { cout << base[n] << "\n"; continue; }
        if (n == 4) { cout << "19\n"; continue; }
        
        // 计算 M^(n-4)
        int Mp[3][3];
        powM(M, n - 4, Mp);
        
        // 计算 a_n = Mp[0][0]*19 + Mp[0][1]*6 + Mp[0][2]*2
        ll fn = (Mp[0][0] * 19LL + Mp[0][1] * 6 + Mp[0][2] * 2) % MOD;
        fn = (fn + MOD) % MOD;  // 确保非负
        
        // 输出规则：如果 n >= 10，答案一定超过9999，输出最后4位（补0）
        if (n >= 10) cout << setw(4) << setfill('0') << fn << "\n";
        else cout << fn << "\n";
    }
    
    return 0;
}
