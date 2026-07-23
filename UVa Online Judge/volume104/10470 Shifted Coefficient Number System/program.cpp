// Shifted Coefficient Number System
// UVa ID: 10470
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// 计算 B 的 power 次幂（power >= 0）
ll powInt(ll b, int power) {
    ll res = 1;
    for (int i = 0; i < power; ++i) res *= b;
    return res;
}

int main() {
    int B, L, N;
    int caseNo = 1;
    while (cin >> B >> L >> N) {
        bool found = false;
        // 枚举最高位指数 n，系数个数为 n+1，最多15个 => n <= 14
        for (int n = 0; n <= 14; ++n) {
            ll powB_n1 = powInt(B, n + 1);          // B^(n+1)
            ll sumS = (powB_n1 - 1) / (B - 1);       // S_n
            ll diff = (ll)N - (ll)L * sumS;          // N - L*S_n
            if (diff >= 0 && diff <= powB_n1 - 1) {
                // diff 的 B 进制表示即为 d_i (低位到高位)
                vector<int> d(n + 1);
                ll tmp = diff;
                for (int i = 0; i <= n; ++i) {
                    d[i] = tmp % B;
                    tmp /= B;
                }
                // 构造系数 c_i = L + d_i
                vector<int> c(n + 1);
                for (int i = 0; i <= n; ++i) c[i] = L + d[i];

                // 输出
                cout << "CASE# " << caseNo << ":\n";
                for (int i = n; i >= 0; --i) {
                    if (c[i] >= 0) cout << '+';
                    else cout << '-';
                    cout << abs(c[i]) << '*' << B << '^' << i;
                }
                cout << " = " << N << '\n';
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "CASE# " << caseNo << ":\n";
            cout << "NOT REPRESENTABLE\n";
        }
        ++caseNo;
    }
    return 0;
}
