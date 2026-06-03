// Square Garden
// UVa ID: 12520
// Verdict: Accepted
// Submission Date: 2026-06-03
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// 计算最大周长的函数
ll calcularMaxPerimetro(ll a, ll b, ll c, ll N) {
    if (N <= a) return N * 4;
    if (N <= a + b) return a * 4;
    if (N <= a + b + c) return a * 4 - (N - a - b) * 2;
    return a * 4 - c * 2 - (N - a - b - c) * 4;
}

int main() {
    ll L, N;
    while (cin >> L >> N, L || N) {
        ll ans = 0;
        // L为偶数的情况
        if (L % 2 == 0) {
            ll a = L * L / 2;
            ll b = 2;
            ll c = (L / 2 - 1) * 4;
            ans = calcularMaxPerimetro(a, b, c, N);
        } 
        // L为奇数的情况，分两种排列方式取最大值
        else {
            // 方式1
            ll a1 = L * L / 2;
            ll b1 = (L == 1) ? 1 : 4;
            ll c1 = (L - 3) / 2 * 4;
            ll ans1 = calcularMaxPerimetro(a1, b1, c1, N);
            
            // 方式2
            ll a2 = L * L / 2 + 1;
            ll b2 = 0;
            ll c2 = (L - 1) / 2 * 4;
            ll ans2 = calcularMaxPerimetro(a2, b2, c2, N);
            
            ans = max(ans1, ans2);
        }
        cout << ans << endl;
    }
    return 0;
}
