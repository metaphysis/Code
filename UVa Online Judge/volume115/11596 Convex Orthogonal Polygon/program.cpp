// Convex Orthogonal Polygon
// UVa ID: 11596
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.080s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef __int128 i128;

// 判断 x 是否为完全平方数，若是则返回 sqrt(x)
bool isSquare(i128 x, i128 &r) {
    if (x < 0) return false;
    i128 lo = 0, hi = 5000000000LL; // 5e9，足够覆盖最大值 sqrt(1.6e19)
    while (lo <= hi) {
        i128 mid = (lo + hi) / 2;
        i128 sq = mid * mid;
        if (sq == x) { r = mid; return true; }
        else if (sq < x) lo = mid + 1;
        else hi = mid - 1;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    ll A0, An, B0;
    while (cin >> A0 >> An >> B0) {
        if (A0 == 0 && An == 0 && B0 == 0) break;
        set<ll> ans;
        // 枚举 B0 的所有因子对 (W, H)，W <= H
        for (ll w = 1; w * w <= B0; ++w) {
            if (B0 % w) continue;
            ll h = B0 / w;
            // 可行性检查
            if (A0 < w + h - 1) continue;
            ll P = 2 * (w + h);
            i128 D = (i128)P * P + (i128)16 * (An - A0);
            i128 sqrtD;
            if (isSquare(D, sqrtD)) {
                if ((sqrtD - P) % 8 == 0) {
                    ll n = (ll)((sqrtD - P) / 8);
                    if (n >= 0) ans.insert(n);
                }
            }
        }
        if (ans.empty()) cout << -1 << '\n';
        else for (ll n : ans) cout << n << '\n';
        cout << '\n'; // 每组后空行
    }
    return 0;
}
