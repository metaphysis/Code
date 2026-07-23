// Fibonacci Triangle
// UVa ID: 13039
// Verdict: Accepted
// Submission Date: 2026-07-23
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        ll oddCnt = 0;   // 长度数量为奇数的种类数（每个此类贡献一根“单棍”）
        ll pairCnt = 0;  // 所有长度能形成的“对棍”总数（每根长度取 floor(cnt/2)）
        for (int i = 1; i <= n; ++i) {
            ll x;
            cin >> x;
            if (x & 1) ++oddCnt;
            pairCnt += x / 2;
        }
        ll ans;
        if (oddCnt > pairCnt) {
            // 单棍太多，每个三角形至少需要一个“对”，最多形成 pairCnt 个
            ans = pairCnt;
        } else {
            // 先用单棍和对应数量的对棍组成三角形
            ans = oddCnt;
            pairCnt -= oddCnt;
            // 剩余的对棍，每 3 对可额外组成 2 个三角形
            ans += 2 * (pairCnt / 3);
            // 剩余 2 对时，可额外组成 1 个三角形
            if (pairCnt % 3 == 2) ++ans;
        }
        cout << ans << '\n';
    }
    return 0;
}
